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

// #include "op_planner/PlannerCommonDef.h"
// #include "op_planner/BehaviorPrediction.h"
#include "op_utility/DataRW.h"
#include "op_planner/MappingHelpers.h"
// #include "op_ros_helpers/op_ROSHelpers.h"
#include <std_msgs/Int32.h>

class MotionPredictionNew
{
private:

    // Parameters to identify different actors detected
    const double MAX_VELOCITY_PEDESTRIAN = 2; // in meter per second
    const double MAX_VELOCITY_BICYCLE = 8; // in meter per second
    const double MAX_LENGHT_BICYCLE = 2; // in meter
    const double MAX_WIDTH_BICYCLE = 0.8; // in meter

    // std::vector<PlannerHNS::DetectedObject> tracked_objects_;
    visualization_msgs::MarkerArray predicted_trajectories_;
    autoware_msgs::DetectedObjectArray predicted_objects_;
    // PlannerHNS::WayPoint current_pose_;

    autoware_msgs::DetectedObjectArray tracked_objects_;

    // Parameters of other actors
    double velocity_other_actors_;
    double width_other_actors_;
    double lenght_other_actors_;


    // Define publishers and subscribers
    ros::NodeHandle nh;
    ros::Publisher pub_predicted_objects_;
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

    /*!
     * \brief Called when information about tracked objects has changed
     * \param msg A pointer to the topic message
     * \details Stores detected objects and differenciates them (car, bicycle, pedestrian or static object) acoording to their velocity and their size
     */
    void trackedObjectsCallback(const autoware_msgs::DetectedObjectArrayConstPtr& msg)
    {
        tracked_objects_ = *msg;
        size_t nb_objects = msg->objects.size();
        for(int i = 0; i<(int)nb_objects; i++) {
            velocity_other_actors_ = pow(pow(tracked_objects_.objects.at(i).velocity.linear.x, 2) + pow(tracked_objects_.objects.at(i).velocity.linear.y, 2), 0.5);
            width_other_actors_ = tracked_objects_.objects.at(i).dimensions.y;
            lenght_other_actors_ = tracked_objects_.objects.at(i).dimensions.x;
        }

        // Different cases according to the value of the detected object
        if (velocity_other_actors_ = 0) {
            // Nothing is predicted, it's a static object
        }
        else if (velocity_other_actors_ < MAX_VELOCITY_PEDESTRIAN) { // The condition can also be if the actor is not on the road
            // Predict a trajectory for a pedestrian
        }
        else if ((velocity_other_actors_ < MAX_VELOCITY_BICYCLE) && 
                    (width_other_actors_ < MAX_WIDTH_BICYCLE) && 
                    (lenght_other_actors_ < MAX_LENGHT_BICYCLE))
        {
            // Predict a trajectory for a bicycle
        }
        else { // All other actors will be cars
            // Predict a trajectory for a car
        }

    }

    /*!
     * \brief Called when information about ego car position has changed
     * \param msg A pointer to the topic message
     * \details Stores the position of the ego car
     */
    void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg)
    {
        // current_pose_ = PlannerHNS::WayPoint(msg->pose.position.x, msg->pose.position.y, msg->pose.position.z, tf::getYaw(msg->pose.orientation));
    }

    /*!
     * \brief Called when information about ego car velocity has changed
     * \param msg A pointer to the topic message
     * \details Stores the velocity of the ego car
     */
    void vehicleStatusCallback(const geometry_msgs::TwistStampedConstPtr& msg)
    {
        // current_pose_.v = msg->twist.linear.x;
    }


    // Callback functions to update vectormap parameters

    void lanesCallback(const vector_map_msgs::LaneArrayConstPtr& msg) {

    }

    void pointsCallback(const vector_map_msgs::PointArrayConstPtr& msg) {

    }

    void dtLanesCallback(const vector_map_msgs::DTLaneArrayConstPtr& msg) {

    }

    void intersectionCallback(const vector_map_msgs::CrossRoadArrayConstPtr& msg) {

    }

    void areasCallback(const vector_map_msgs::AreaArrayConstPtr& msg) {

    }

    void linesCallback(const vector_map_msgs::LineArrayConstPtr& msg) {

    }

    void stopLinesCallback(const vector_map_msgs::StopLineArrayConstPtr& msg) {

    }

    void signalsCallback( const vector_map_msgs::SignalArrayConstPtr& msg) {

    }

    void vectorsCallback(const vector_map_msgs::VectorArrayConstPtr& msg) {

    }

    void curbsCallback(const vector_map_msgs::CurbArrayConstPtr& msg) {

    }

    void edgesCallback(const vector_map_msgs::RoadEdgeArrayConstPtr& msg) {

    }

    void wayAreasCallback(const vector_map_msgs::WayAreaArrayConstPtr& msg) {

    }

    void crossWalkCallback(const vector_map_msgs::CrossWalkArrayConstPtr& msg) {
        
    }

    void nodesCallback(const vector_map_msgs::NodeArrayConstPtr& msg) {

    }

    /*!
     * \brief Predict different trajectories for a detected object given
     * \param object_type The type of object to which trajectories are predicted
     */
    void predictTrajectories(std::string object_type)
    {

    }

    /*!
     * \brief Update information about the planning and the map
     */
    void updatePlanningParams()
    {

    }

    /*!
     * \brief Used to visualize predicted trajectories in Rviz
     */
    void predictionVisualizer()
    {

    }

public:

    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function
     * \details Initializes publishers and subscribers
     */
    MotionPredictionNew(ros::NodeHandle& nh)
    {
        // Initialize node and Publisher/Subscribers
        pub_predicted_objects_ = nh.advertise<autoware_msgs::DetectedObjectArray>("/predicted_objects", 1, true);
        pub_predicted_trajectories_ = nh.advertise<visualization_msgs::MarkerArray>("/predicted_trajectories", 1, true);

        sub_tracked_objects_ = nh.subscribe<autoware_msgs::DetectedObjectArray>("/tracked_objects", 1, &MotionPredictionNew::trackedObjectsCallback, this);
        sub_current_pose_ = nh.subscribe<geometry_msgs::PoseStamped>("/current_pose", 10, &MotionPredictionNew::poseCallback, this);
        sub_current_velocity_ = nh.subscribe<geometry_msgs::TwistStamped>("/current_velocity", 10, &MotionPredictionNew::vehicleStatusCallback, this);

        sub_lanes_ = nh.subscribe("/vector_map_info/lane", 1, &MotionPredictionNew::lanesCallback,  this);
        sub_points_ = nh.subscribe("/vector_map_info/point", 1, &MotionPredictionNew::pointsCallback,  this);
        sub_dt_lanes_ = nh.subscribe("/vector_map_info/dtlane", 1, &MotionPredictionNew::dtLanesCallback,  this);
        sub_intersection_ = nh.subscribe("/vector_map_info/cross_road", 1, &MotionPredictionNew::intersectionCallback,  this);
        sup_area_ = nh.subscribe("/vector_map_info/area", 1, &MotionPredictionNew::areasCallback,  this);
        sub_lines_ = nh.subscribe("/vector_map_info/line", 1, &MotionPredictionNew::linesCallback,  this);
        sub_stop_line_ = nh.subscribe("/vector_map_info/stop_line", 1, &MotionPredictionNew::stopLinesCallback,  this);
        sub_signals_ = nh.subscribe("/vector_map_info/signal", 1, &MotionPredictionNew::signalsCallback,  this);
        sub_vectors_ = nh.subscribe("/vector_map_info/vector", 1, &MotionPredictionNew::vectorsCallback,  this);
        sub_curbs_ = nh.subscribe("/vector_map_info/curb", 1, &MotionPredictionNew::curbsCallback,  this);
        sub_edges_ = nh.subscribe("/vector_map_info/road_edge", 1, &MotionPredictionNew::edgesCallback,  this);
        sub_way_areas_ = nh.subscribe("/vector_map_info/way_area", 1, &MotionPredictionNew::wayAreasCallback,  this);
        sub_cross_walk_ = nh.subscribe("/vector_map_info/cross_walk", 1, &MotionPredictionNew::crossWalkCallback,  this);
        sub_nodes_ = nh.subscribe("/vector_map_info/node", 1, &MotionPredictionNew::nodesCallback,  this);


            
    }

    /*!
     * \brief The main loop
     */
    void run()
    {
        while(nh.ok()) {
            ros::spinOnce();

            pub_predicted_objects_.publish(predicted_objects_);
            pub_predicted_trajectories_.publish(predicted_trajectories_);
        }
    }
};

int main(int argc, char **argv) {
    // Initialize the node
    ros::init(argc, argv, "Behavior Prediction");
    ros::NodeHandle nh;
    MotionPredictionNew motionPrediction(nh);
    motionPrediction.run();
    return 0;
}