#include <ros/ros.h>

#include "vector_map_msgs/PointArray.h"
#include "vector_map_msgs/LaneArray.h"
#include "vector_map_msgs/NodeArray.h"
#include "vector_map_msgs/StopLineArray.h"
#include "vector_map_msgs/DTLaneArray.h"
#include "vector_map_msgs/LineArray.h"
#include "vector_map_msgs/AreaArray.h"
#include "vector_map_msgs/SignalArray.h"
#include "vector_map_msgs/StopLine.h"
#include "vector_map_msgs/VectorArray.h"

#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <visualization_msgs/MarkerArray.h>

#include "op_utility/DataRW.h"
#include "op_planner/MappingHelpers.h"
#include "tf/transform_datatypes.h"
#include <std_msgs/Int32.h>

/*!
 * \brief This class will predict trajectories for different actors
 * \details Tracked objects are sent to this node and it will identify which
 * objects are dynamic ones.
 * Then, the node predicts trajectories for theses objects.
 */
class MotionPredictior
{
private:

    // Parameters to identify different actors detected
    // For a pedestrian
    const double MIN_VELOCITY_PEDESTRIAN = 0.28; // in meter per second
    const double MAX_VELOCITY_PEDESTRIAN = 5.6; // in meter per second, for a person that runs (20km/h)
    const double MIN_LENGHT_PEDESTRIAN = 0.4; // in meter, for a child
    const double MAX_LENGHT_PEDESTRIAN = 1.6; // in meter, if she/he push something like a buggy
    const double MIN_WIDTH_PEDESTRIAN = 0.2; // in meter, for a child
    const double MAX_WIDTH_PEDESTRIAN = 1; // in meter, for biggest person
    // For a bicycle
    const double MIN_VELOCITY_BICYCLE = 0.5; // in meter per second
    const double MAX_VELOCITY_BICYCLE = 8; // in meter per second
    const double MIN_LENGHT_BICYCLE = 0.8; // in meter, for a child's bicycle
    const double MAX_LENGHT_BICYCLE = 2; // in meter, for an adult's bicycle
    const double MIN_WIDTH_BICYCLE = 0.3; // in meter, for a child's bicycle
    const double MAX_WIDTH_BICYCLE = 1; // in meter, for an adult's bicycle
    // For a car
    const double MIN_VELOCITY_CAR = 1.39; // in meter per second. The minimum velocity is set at 5km/h in case of traffic congestion.
    const double MIN_LENGHT_CAR = 2.2; // in meter. Motor are taking into account in cars type.
    const double MAX_LENGHT_CAR = 5; // in meter, for biggest cars
    const double MIN_WIDTH_CAR = 0.7; // in meter, for smallest cars
    const double MAX_WIDTH_CAR = 1.9; // in meter, for biggest cars

    // This variable will stores predicted trajectories for dynamic objects.
    visualization_msgs::MarkerArray predicted_trajectories_;
    // This variable will stores objects that need to have predicted trajectories 
    autoware_msgs::DetectedObjectArray detected_objects_;
    // This variable stores all detected objects.
    autoware_msgs::DetectedObjectArray tracked_objects_;

    // This enumeration is useful to know the type of actor that is detected.
    enum actor_type_ {static_object, pedestrian, bicycle, car};

    // Information about ego car
    geometry_msgs::Point32 current_pose_;
    double yaw_ego_;
    double velocity_ego_;

    // Parameters of other actors
    double velocity_other_actors_;
    double width_other_actors_;
    double lenght_other_actors_;

    // For map updates
    UtilityHNS::MapRaw map_raw_;

    // Define publishers and subscribers
    ros::NodeHandle &nh_;
    ros::Publisher pub_detected_objects_;
    ros::Publisher pub_predicted_trajectories_;
    ros::Subscriber sub_tracked_objects_;
    ros::Subscriber sub_current_pose_;
    ros::Subscriber sub_current_velocity_;
    // Mapping parameters
    ros::Subscriber sub_lanes_;
	ros::Subscriber sub_points_;
	ros::Subscriber sub_dt_lanes_;
	ros::Subscriber sub_intersection_;
	ros::Subscriber sup_area_;
	ros::Subscriber sub_lines_;
	ros::Subscriber sub_stop_line_;
	ros::Subscriber sub_signals_;
	ros::Subscriber sub_vectors_;
	ros::Subscriber sub_curbs_;
	ros::Subscriber sub_edges_;
	ros::Subscriber sub_way_areas_;
	ros::Subscriber sub_cross_walk_;
	ros::Subscriber sub_nodes_;

    // ROS utils
    ros::Rate rate_;

    /*!
     * \brief Called when information about tracked objects has changed
     * \param msg A pointer to the topic message
     * \details Stores detected objects and differenciates them (car, bicycle, pedestrian or static object)
     * acoording to their velocity and their size.
     */
    void trackedObjectsCallback(const autoware_msgs::DetectedObjectArrayConstPtr& msg)
    {
        tracked_objects_ = *msg;
        detected_objects_.objects.clear();
        size_t nb_objects = tracked_objects_.objects.size();
        for(int i = 0; i<(int)nb_objects; i++) {
            velocity_other_actors_ = pow(pow(tracked_objects_.objects.at(i).velocity.linear.x, 2) + pow(tracked_objects_.objects.at(i).velocity.linear.y, 2), 0.5);
            double size_x = tracked_objects_.objects.at(i).dimensions.x;
            double size_y = tracked_objects_.objects.at(i).dimensions.y;
            // Lenght will be the largest between size_x and size_y
            if (size_x >= size_y) {
                lenght_other_actors_ = size_x;
                width_other_actors_ = size_y;
            }
            else {
                lenght_other_actors_ = size_y;
                width_other_actors_ = size_x;
            }

            // Different cases according to the value of the detected object
            // This part has to be reviewed, some objects are not well detected
            // Add conditions on the position of the detected object, if it is not on the road,
            // it could be a pedestrian.

            // Check if the velocity and the size of the detected actor fit with a car
            if ((velocity_other_actors_ >= MIN_VELOCITY_CAR)
                    && (MAX_LENGHT_CAR >= lenght_other_actors_) && (lenght_other_actors_ >= MIN_LENGHT_CAR)
                    && (MAX_WIDTH_CAR >= width_other_actors_) && (width_other_actors_ >= MIN_WIDTH_CAR))
            {
                // Predict a trajectory for a car
                predictTrajectories(car); // This function is not implemented yet
                detected_objects_.objects.push_back(tracked_objects_.objects.at(i));
                detected_objects_.objects.at(detected_objects_.objects.size() - 1).label = "car";
            }
            // Check if the velocity and the size of the detected actor fit with a bicycle
            // And also check if the position of the actor is on the road.
            else if ((MAX_VELOCITY_BICYCLE >= velocity_other_actors_) && (velocity_other_actors_ >= MIN_VELOCITY_BICYCLE)
                        && (MAX_LENGHT_BICYCLE >= lenght_other_actors_) && (lenght_other_actors_ >= MIN_LENGHT_BICYCLE)
                        && (MAX_WIDTH_BICYCLE >= lenght_other_actors_) && (lenght_other_actors_ >= MIN_WIDTH_BICYCLE))
            {
                // Predict a trajectory for a bicycle
                predictTrajectories(bicycle); // This function is not implemented yet
                detected_objects_.objects.push_back(tracked_objects_.objects.at(i));
                detected_objects_.objects.at(detected_objects_.objects.size() - 1).label = "bicycle";
            }
            // Check if the velocity and the size of the detected actor fit with a pedestrian
            // And also check if the position of the actor is out of the road.
            else if ((MAX_VELOCITY_PEDESTRIAN >= velocity_other_actors_) && (velocity_other_actors_ >= MIN_VELOCITY_PEDESTRIAN)
                        && (MAX_LENGHT_PEDESTRIAN >= lenght_other_actors_) && (lenght_other_actors_ >= MIN_LENGHT_PEDESTRIAN)
                        && (MAX_WIDTH_PEDESTRIAN >= lenght_other_actors_) && (lenght_other_actors_ >= MIN_WIDTH_PEDESTRIAN))
            {
                // Predict a trajectory for a pedestrian
                predictTrajectories(pedestrian); // This function is not implemented yet
                detected_objects_.objects.push_back(tracked_objects_.objects.at(i));
                detected_objects_.objects.at(detected_objects_.objects.size() - 1).label = "pedestrian";
            }
            // If velocity and size of actors don't fit with cars, bicycles or pedestrians, it's a static object
            else {
                predictTrajectories(static_object); // This function is not implemented yet
            }
        }
    }

    /*!
     * \brief Called when information about ego car position has changed
     * \param msg A pointer to the topic message
     * \details Stores the position and the orientation of the ego car
     */
    void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg)
    {
        current_pose_.x = msg->pose.position.x;
        current_pose_.y = msg->pose.position.y;
        yaw_ego_ = tf::getYaw(msg->pose.orientation);
    }

    /*!
     * \brief Called when information about ego car velocity has changed
     * \param msg A pointer to the topic message
     * \details Stores the velocity of the ego car
     */
    void velocityCallback(const geometry_msgs::TwistStampedConstPtr& msg)
    {
        velocity_ego_ = msg->twist.linear.x;
    }


    // Callback functions to update vectormap parameters

    /*!
     * \brief Updates the value of Lanes in the map
     * \param msg A pointer to the topic message
     */
    void lanesCallback(const vector_map_msgs::LaneArray& msg) {
        std::cout << "Received Lanes" << std::endl;
        if(map_raw_.pLanes == nullptr) {
            map_raw_.pLanes = new UtilityHNS::AisanLanesFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of Points in the map
     * \param msg A pointer to the topic message
     */
    void pointsCallback(const vector_map_msgs::PointArray& msg) {
        std::cout << "Received Points" << std::endl;
        if(map_raw_.pPoints == nullptr) {
            map_raw_.pPoints = new UtilityHNS::AisanPointsFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of dtLanes in the map
     * \param msg A pointer to the topic message
     */
    void dtLanesCallback(const vector_map_msgs::DTLaneArray& msg) {
        std::cout << "Received dtLanes" << std::endl;
        if(map_raw_.pCenterLines == nullptr) {
            map_raw_.pCenterLines = new UtilityHNS::AisanCenterLinesFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of Intersections in the map
     * \param msg A pointer to the topic message
     */
    void intersectionCallback(const vector_map_msgs::CrossRoadArray& msg) {
        std::cout << "Received Intersections" << std::endl;
        if(map_raw_.pIntersections == nullptr) {
            map_raw_.pIntersections = new UtilityHNS::AisanIntersectionFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of Areas in the map
     * \param msg A pointer to the topic message
     */
    void areasCallback(const vector_map_msgs::AreaArray& msg) {
        std::cout << "Received Areas" << std::endl;
        if(map_raw_.pAreas == nullptr) {
            map_raw_.pAreas = new UtilityHNS::AisanAreasFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of Lines in the map
     * \param msg A pointer to the topic message
     */
    void linesCallback(const vector_map_msgs::LineArray& msg) {
        std::cout << "Received Lines" << std::endl;
        if(map_raw_.pLines == nullptr) {
            map_raw_.pLines = new UtilityHNS::AisanLinesFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of Stop lines in the map
     * \param msg A pointer to the topic message
     */
    void stopLinesCallback(const vector_map_msgs::StopLineArray& msg) {
        std::cout << "Received Stop Lines" << std::endl;
        if(map_raw_.pStopLines == nullptr) {
            map_raw_.pStopLines = new UtilityHNS::AisanStopLineFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of Signals in the map
     * \param msg A pointer to the topic message
     */
    void signalsCallback( const vector_map_msgs::SignalArray& msg) {
        std::cout << "Received Signals" << std::endl;
        if(map_raw_.pSignals == nullptr) {
            map_raw_.pSignals = new UtilityHNS::AisanSignalFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of Vectors in the map
     * \param msg A pointer to the topic message
     */
    void vectorsCallback(const vector_map_msgs::VectorArray& msg) {
        std::cout << "Received Vectors" << std::endl;
        if(map_raw_.pVectors == nullptr) {
            map_raw_.pVectors = new UtilityHNS::AisanVectorFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of Curbs in the map
     * \param msg A pointer to the topic message
     */
    void curbsCallback(const vector_map_msgs::CurbArray& msg) {
        std::cout << "Received Curbs" << std::endl;
        if(map_raw_.pCurbs == nullptr) {
            map_raw_.pCurbs = new UtilityHNS::AisanCurbFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of Road edges in the map
     * \param msg A pointer to the topic message
     */
    void edgesCallback(const vector_map_msgs::RoadEdgeArray& msg) {
        std::cout << "Received Road edges" << std::endl;
        if(map_raw_.pRoadedges == nullptr) {
            map_raw_.pRoadedges = new UtilityHNS::AisanRoadEdgeFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of Way areas in the map
     * \param msg A pointer to the topic message
     */
    void wayAreasCallback(const vector_map_msgs::WayAreaArray& msg) {
        std::cout << "Received Way areas" << std::endl;
        if(map_raw_.pWayAreas == nullptr) {
            map_raw_.pWayAreas = new UtilityHNS::AisanWayareaFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of Cross walks in the map
     * \param msg A pointer to the topic message
     */
    void crossWalkCallback(const vector_map_msgs::CrossWalkArray& msg) {
        std::cout << "Received Cross walks" << std::endl;
        if(map_raw_.pCrossWalks == nullptr) {
            map_raw_.pCrossWalks = new UtilityHNS::AisanCrossWalkFileReader(msg);
        }
    }

    /*!
     * \brief Updates the value of Nodes in the map
     * \param msg A pointer to the topic message
     */
    void nodesCallback(const vector_map_msgs::NodeArray& msg) {
        std::cout << "Received Nodes" << std::endl;
        if(map_raw_.pNodes == nullptr) {
            map_raw_.pNodes = new UtilityHNS::AisanNodesFileReader(msg);
        }
    }

    /*!
     * \brief Predict different trajectories for a detected object given
     * \param type The type of object to which trajectories are predicted
     * \details For an oject on the road (as car, bicycle or motorcycle),
     * the predicted trajectories will be, for example, go straight ahead,
     * turn left or turn right (if the actor arrives  to a crossroad).
     * For a pedestrian, the predicted trajectories will be cross the road,
     * turn left/ right or continue straight ahead on the walkways.
     */
    void predictTrajectories(actor_type_ type)
    {

    }

    /*!
     * \brief Update information about the planning and the map
     * \details The updated map will be used to predict trajectories.
     * For example where are the walkways, the crossroads,...
     */
    void updatePlanningParams()
    {

    }

    /*!
     * \brief Used to visualize predicted trajectories in Rviz
     */
    void predictionVisualizer()
    {
        // Update the variable predicted_trajectories

    }

public:

    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function
     * \details Initializes publishers and subscribers
     */
    MotionPredictior(ros::NodeHandle& nh) : nh_(nh), rate_(1)
    {
        // Initialize node and Publisher/Subscribers
        pub_detected_objects_ = nh.advertise<autoware_msgs::DetectedObjectArray>("/detected_objects", 1, true);
        pub_predicted_trajectories_ = nh.advertise<visualization_msgs::MarkerArray>("/predicted_trajectories", 1, true);

        sub_tracked_objects_ = nh.subscribe<autoware_msgs::DetectedObjectArray>("/tracked_objects", 1, &MotionPredictior::trackedObjectsCallback, this);
        sub_current_pose_ = nh.subscribe<geometry_msgs::PoseStamped>("/current_pose", 10, &MotionPredictior::poseCallback, this);
        sub_current_velocity_ = nh.subscribe<geometry_msgs::TwistStamped>("/current_velocity", 10, &MotionPredictior::velocityCallback, this);

        sub_lanes_ = nh.subscribe("/vector_map_info/lane", 1, &MotionPredictior::lanesCallback,  this);
        sub_points_ = nh.subscribe("/vector_map_info/point", 1, &MotionPredictior::pointsCallback,  this);
        sub_dt_lanes_ = nh.subscribe("/vector_map_info/dtlane", 1, &MotionPredictior::dtLanesCallback,  this);
        sub_intersection_ = nh.subscribe("/vector_map_info/cross_road", 1, &MotionPredictior::intersectionCallback,  this);
        sup_area_ = nh.subscribe("/vector_map_info/area", 1, &MotionPredictior::areasCallback,  this);
        sub_lines_ = nh.subscribe("/vector_map_info/line", 1, &MotionPredictior::linesCallback,  this);
        sub_stop_line_ = nh.subscribe("/vector_map_info/stop_line", 1, &MotionPredictior::stopLinesCallback,  this);
        sub_signals_ = nh.subscribe("/vector_map_info/signal", 1, &MotionPredictior::signalsCallback,  this);
        sub_vectors_ = nh.subscribe("/vector_map_info/vector", 1, &MotionPredictior::vectorsCallback,  this);
        sub_curbs_ = nh.subscribe("/vector_map_info/curb", 1, &MotionPredictior::curbsCallback,  this);
        sub_edges_ = nh.subscribe("/vector_map_info/road_edge", 1, &MotionPredictior::edgesCallback,  this);
        sub_way_areas_ = nh.subscribe("/vector_map_info/way_area", 1, &MotionPredictior::wayAreasCallback,  this);
        sub_cross_walk_ = nh.subscribe("/vector_map_info/cross_walk", 1, &MotionPredictior::crossWalkCallback,  this);
        sub_nodes_ = nh.subscribe("/vector_map_info/node", 1, &MotionPredictior::nodesCallback,  this);

        rate_ = ros::Rate(10);

        updatePlanningParams();
        predictionVisualizer();
    }

    /*!
     * \brief The main function of the node, contains the main loop.
     * \brief Publish detected objects and predicted trajectories.
     */
    void run()
    {
        // The main loop
        while(nh_.ok()) {
            ros::spinOnce();

            pub_detected_objects_.publish(detected_objects_);
            pub_predicted_trajectories_.publish(predicted_trajectories_);

            rate_.sleep();
        }
    }
};

int main(int argc, char **argv) {
    // Initialize the node
    ros::init(argc, argv, "motionPrediction");
    ros::NodeHandle nh;
    MotionPredictior motionPrediction(nh);
    motionPrediction.run();
    return 0;
}