#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
#include <autoware_msgs/Lane.h>
#include <autoware_msgs/LaneArray.h>
#include <jsk_recognition_msgs/PolygonArray.h>

#include <cpp_utils/pose_datatypes.h>

#include <visualization_msgs/Marker.h> //Used for critical area visualization
#include <std_msgs/ColorRGBA.h>        //Used for critical area visualization

#include "op_planner/PlannerH.h"
#include "op_ros_helpers/op_ROSHelpers.h"

#define ROAD_SIDE_PARKING_VALUE 250
#define REST_AREA_VALUE 200


/*!
 * \brief The Safety Supervisor supervise the automated driving.
 * \details Its goal is to trigger the switch that decides if the vehicle
 * listen to the DDT given by the nominal channel or by the safety channel.
 */
class SafetySupervisor
{
private:
    // node, publishers and subscribers
    ros::NodeHandle &nh_;
    ros::Publisher pub_switch_;
    ros::Publisher pub_overwrite_behavior_;
    ros::Publisher pub_limit_max_speed_;
    ros::Publisher pub_overwrite_trajectory_eval_;
    ros::Publisher pub_autoware_goal_;
    ros::Publisher pub_trigger_update_global_planner_;
    ros::Publisher pub_critical_area_;  //Used for critical area visualization
    ros::Subscriber sub_gnss_;
    ros::Subscriber sub_gridmap_;
    ros::Subscriber sub_autoware_trajectory_;
    ros::Subscriber sub_autoware_global_plan_;
    ros::Subscriber sub_current_velocity_;
    ros::Subscriber sub_switch_request_;
    ros::Subscriber sub_sensor_fov_;

    // constants
    const bool SAFE = false;
    const bool UNSAFE = true;
    const int NO_BEHAVIOR_OVERWRITE_ = -1;
    enum STATE_TYPE_ {INITIAL_STATE, WAITING_STATE, FORWARD_STATE, STOPPING_STATE, EMERGENCY_STATE,
	TRAFFIC_LIGHT_STOP_STATE,TRAFFIC_LIGHT_WAIT_STATE, STOP_SIGN_STOP_STATE, STOP_SIGN_WAIT_STATE, FOLLOW_STATE, LANE_CHANGE_STATE, OBSTACLE_AVOIDANCE_STATE, GOAL_STATE, FINISH_STATE, YIELDING_STATE, BRANCH_LEFT_STATE, BRANCH_RIGHT_STATE};
    const float PI_ = 3.141592654;

    // The number of the safety test
    enum SAFETY_TESTS_{CHECK_ACTIVE_NODES = 0, CHECK_CAR_OFF_ROAD = 1, CHECK_DYNAMIC_OJECT = 2, CHECK_CAR_OFF_ODD = 3, CHECK_FRONT_SENSORS = 4, CHECK_BACK_SENSORS = 5};

    bool was_switch_requested_ = false;
    std_msgs::Int32 switch_request_value_;

    //Critical area
    float car_length_ = 5;
    float car_width_ = 2;
    bool car_size_set_ = false;
    float critical_area_length_ = car_length_; //Size of the critical Area
    float critical_area_width_ = car_width_ * 1.2;
    grid_map::Polygon critical_area_;

    geometry_msgs::Pose pose_;
    float current_velocity_ = 0;
    bool var_switch_;
    int varoverwrite_behavior_;
    bool gnss_flag_ = false;
    bool gridmap_flag_ = false;
    bool autoware_trajectory_flag_ = false;
    bool autoware_global_path_flag_ = false;
    
    grid_map::GridMap gridmap_; //({"StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle", "Lanes", "RoadSideParking", "RestArea", "SensorSectors"});
    autoware_msgs::Lane autowareTrajectory_;
    ros::V_string nodes_to_check_;
    std::vector<std::vector<PlannerHNS::WayPoint>> autoware_global_path_;
    
    // Safety tests
    int num_safety_tests_ = 6;

    // Initiate the safety counter for tests
    std::vector<int> safety_test_counters_ = std::vector<int>(num_safety_tests_,0);

    // Set the default threshold value for each pass and fail safety test
    std::vector<int> thresholds_pass_test_ = std::vector<int>(num_safety_tests_,4);
    std::vector<int> thresholds_fail_test_ = std::vector<int>(num_safety_tests_,-4);

    // Set the default increment and decrement value for each pass and fail safety test
    std::vector<int> increments_pass_test_ = std::vector<int>(num_safety_tests_,1);
    std::vector<int> decrements_fail_test_ = std::vector<int>(num_safety_tests_,-1);
    
    // Constant Pass and Fail boolean
    const bool PASS_ = true;
    const bool FAIL_ = false;

    // Initiate Non-Instantaneous result vector
    std::vector<bool> non_instantaneous_results_ = std::vector<bool>(num_safety_tests_, PASS_);
   
    // result of the check functions
    double distance_to_lane_;
    double distance_to_road_edge_;

    // ODD Polygon coordinates
    // Format:- ODD_coordinates_ = {x1, y1, x2, y2, x3, y3, x4, y4}
    std::vector<double> ODD_coordinates_, ODD_default_gridmap_coordinates_;

    struct CurvatureExtremum {
        double max;
        double min;
    };

    // enum to identifiate critical level
    enum CRITICAL_LEVEL_ {IMMEDIATE_STOP, CLOSEST_PARKING, BIGGER_PARKING, INITIAL_GOAL};

    // Test for sensor coverage
    jsk_recognition_msgs::PolygonArray sensors_fov_;
    bool sensors_fov_flag_ = false;
    enum SENSOR_TYPE_ {radar, lidar, camera1, camera2, cameratl}; // numbers of sensors have to fit with those defined in sensor monitor
    std::vector<int> FRONT_SENSORS_ = {radar, lidar, camera1}; // in the front of the car, there are radar, camera 1 and lidar
    std::vector<int> BACK_SENSORS_ = {lidar, camera2}; // in the back of the car, there are camera 2 and lidar
    int number_front_sensors_ = FRONT_SENSORS_.size();
    int number_back_sensors_ = BACK_SENSORS_.size();
    int nb_defective_front_sensors_; // stores the number of defective sensors in the front of the car
    int nb_defective_back_sensors_; // stores the number of defective sensors in the back of the car

    /*!
     * \brief currentVelocity Callback : Updates the knowledge about the car speed.
     * \param msg A smart pointer to the message from the topic.
     */
    void currentVelocityCallback(const geometry_msgs::TwistStamped::ConstPtr& msg)
    {
        current_velocity_ = msg->twist.linear.x;
    }

    /*!
     * \brief Gnss Callback : Called when the gnss information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates gnss information of the vehicle position.
     */
    void gnssCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
    {
        geometry_msgs::PoseStamped gnss = *msg;
        pose_ = gnss.pose;
        gnss_flag_ = true;
    }

    /*!
     * \brief Gridmap Callback : Called when the gridmap information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates the gridmap information.
     */
    void gridmapCallback(const grid_map_msgs::GridMap::ConstPtr& msg)
    {
        grid_map::GridMapRosConverter::fromMessage(*msg, gridmap_);

        // Operational design domain default polygon coordinates are same as full grid map
        ODD_default_gridmap_coordinates_ = {gridmap_.getPosition().x() - gridmap_.getLength().x() * 0.5, gridmap_.getPosition().y() - gridmap_.getLength().y() * 0.5, gridmap_.getPosition().x() - gridmap_.getLength().x() * 0.5, gridmap_.getLength().y() - (gridmap_.getPosition().y() - gridmap_.getLength().y() * 0.5), gridmap_.getLength().x() - (gridmap_.getPosition().x() - gridmap_.getLength().x() * 0.5), gridmap_.getLength().y() - (gridmap_.getPosition().y() - gridmap_.getLength().y() * 0.5), gridmap_.getLength().x() - (gridmap_.getPosition().x() - gridmap_.getLength().x() * 0.5), gridmap_.getPosition().y() - gridmap_.getLength().y() * 0.5};
        gridmap_flag_ = true;
    }

    /*!
     * \brief Autoware trajectory Callback : Called when the trajectory from autoware has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates the autoware trajectory information.
     */
    void autowareTrajectoryCallback(const autoware_msgs::Lane::ConstPtr& msg)
    {
        autowareTrajectory_ = *msg;
        autoware_trajectory_flag_ = true;
    }

    /*!
     * \brief Autoware global plan Callback : Called when the global plan from autoware has changed.
     * \param msg A smart pointer to the message from the topic.
     */
    void autowareGlobalPlanCallback(const autoware_msgs::LaneArrayConstPtr& msg)
    {
      if(msg->lanes.size() > 0)
      {
          std::vector<PlannerHNS::WayPoint> m_temp_path;
          autoware_global_path_.clear();
          autoware_global_path_flag_ = true;
          for(unsigned int i = 0 ; i < msg->lanes.size(); i++)
          {
              PlannerHNS::ROSHelpers::ConvertFromAutowareLaneToLocalLane(msg->lanes.at(i), m_temp_path);
              PlannerHNS::PlanningHelpers::CalcAngleAndCost(m_temp_path);
              autoware_global_path_.push_back(m_temp_path);
          }
      }
    }

    /*!
     * \brief Switch request Callback : Called when the manager makes a request to change control channel.
     * \param msg A smart pointer to the message from the topic.
     */
    void switchRequestCallback(const std_msgs::Int32& msg)
    {
        was_switch_requested_ = true;
        switch_request_value_ = msg;
    }

    /*!
     * \brief Sensor field of view callback : Called when the sensors information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores polygons that represent sensor field of view
     */
    void sensorFovCallback(const jsk_recognition_msgs::PolygonArrayConstPtr& msg)
    {
        sensors_fov_ = *msg;
        sensors_fov_flag_ = true;
    }

    /*!
     * \brief Get distance to lane : Called at every iteration of the main loop
     * \return Distance to the center line of the lane
     */
    double getDistanceToLane(const std::vector<PlannerHNS::WayPoint>& trajectory)
    {

        PlannerHNS::WayPoint p0 = PlannerHNS::WayPoint(pose_.position.x, pose_.position.y, pose_.position.z, tf::getYaw(pose_.orientation));
        std::vector<int> two_closest_index = getClosestIndex(trajectory, p0);
        int closest_index = two_closest_index.at(0);
        int second_closest_index = two_closest_index.at(1);
        PlannerHNS::WayPoint p1 = trajectory.at(closest_index);
        PlannerHNS::WayPoint p2 = trajectory.at(second_closest_index);
        // the distance is the distance from the car's position to the line formed by the two points fron the path
        double distance = double(fabs((p2.pos.y - p1.pos.y) * p0.pos.x - (p2.pos.x - p1.pos.x) * p0.pos.y + p2.pos.x * p1.pos.y - p2.pos.y * p1.pos.x)/sqrt(pow(p2.pos.y - p1.pos.y, 2) + pow(p2.pos.x - p1.pos.x, 2)));
        std::cout << "Closest index = " << closest_index << ". Second closest index: " << second_closest_index << ". Distance = " << distance << '\n';
        return distance;
    }

    /*!
     * \brief Get closest index : Called at every iteration of the main loop
     * Finds the closest point in a trajectory to a certain point
     */
    std::vector<int> getClosestIndex(const std::vector<PlannerHNS::WayPoint>& trajectory, const PlannerHNS::WayPoint& p)
    {
        int closest_index = 0;
        int second_closest_index = 0;
        double d_closest_index = DBL_MAX;
        double d_second_closest_index = DBL_MAX;
        if(trajectory.size()>1){
            for(int i=0; i<trajectory.size(); i++){
                double d = pow(trajectory[i].pos.x - p.pos.x, 2) + pow(trajectory[i].pos.y - p.pos.y, 2);
                if(d < d_second_closest_index){
                    if(d < d_closest_index){
                        second_closest_index = closest_index;
                        d_second_closest_index = d_closest_index;
                        closest_index = i;
                        d_closest_index = d;
                    }
                    else{
                        second_closest_index = i;
                        d_second_closest_index = d;
                    }
                }
            }
        }
        std::vector<int> two_closest_index;
        two_closest_index.push_back(closest_index);
        two_closest_index.push_back(second_closest_index);
        return two_closest_index;
    }

    /*!
     * \brief Get the distance to the road edges : Called at every iteration of the main loop
     * \return The distance to the closest road edge
     */
    double getDistanceToRoadEdge()
    {
        float right_lane_id;
        float left_lane_id;
        double x = pose_.position.x;
        double y = pose_.position.y;
        double h = tf::getYaw(pose_.orientation);
        double h_left = h + M_PI/2;
        double h_right = h - M_PI/2;
        double max_distance_to_check = 3;
        double resolution = 0.1;
        double nb_iterations = max_distance_to_check/resolution; //This is the maximum value for the counter i
        double right_distance = 0;
        double left_distance = 0;
        for (size_t i = 0; i <= nb_iterations; i++) {
            double d = i * resolution;
            double x_left = x + d*std::cos(h_left);
            double y_left = y + d*std::sin(h_left);
            double x_right = x + d*std::cos(h_right);
            double y_right = y + d*std::sin(h_right);
            left_lane_id = gridmap_.atPosition("Lanes", grid_map::Position(x_left, y_left));
            if (left_lane_id != 0) {
                left_distance = d;
            }
            right_lane_id = gridmap_.atPosition("Lanes", grid_map::Position(x_right, y_right));
            if (right_lane_id != 0) {
                right_distance = d;
            }
        }
        std::cout << "The distance to the right road edge is: " << right_distance << '\n';
        std::cout << "The distance to the left road edge is: " << left_distance << '\n';
        return std::min(right_distance, left_distance);
    }

    /*!
     * \brief Get curvature : Called at every iteration of the main loop
     * \return The minimum and maximum curvature of the global plan
     */
    CurvatureExtremum getCurvature(const std::vector<PlannerHNS::WayPoint>& trajectory)
    {
        CurvatureExtremum curvature;
        curvature.max = 0;
        curvature.min = 0;
        if(trajectory.size()>2){
            for (size_t i = 0; i<trajectory.size()-2; i++) {
                double signed_curvature = getSignedCurvature(trajectory[i], trajectory[i+1], trajectory[i+2]);
                if (signed_curvature > curvature.max) {
                    curvature.max = signed_curvature;
                }
                if (signed_curvature < curvature.min) {
                    curvature.min = signed_curvature;
                }
            }
        }
        std::cout << "The max curvature is: " << curvature.max << '\n';
        std::cout << "The min curvature is: " << curvature.min << '\n';
        return curvature;
    }

    /*!
     * \brief Get menger curvature : References can be found looking for "Menger curvature"
     * \Calculates the inverse of the radius of the circle defined by 3 points
     */
    double getSignedCurvature(const PlannerHNS::WayPoint& P1, const PlannerHNS::WayPoint& P2, const PlannerHNS::WayPoint& P3)
    {
        double curvature = 0;
        double cross_product = (P2.pos.x-P1.pos.x)*(P3.pos.y-P1.pos.y)-(P2.pos.y-P1.pos.y)*(P3.pos.x-P1.pos.x);
        if (cross_product != 0) { //If the points are not collinear
            double area_triangle = (P1.pos.x * (P2.pos.y - P3.pos.y) + P2.pos.x * (P3.pos.y - P1.pos.y) + P3.pos.x * (P1.pos.y - P2.pos.y)) / 2;
            double dist12 = getDistance(P1, P2);
            double dist13 = getDistance(P1, P3);
            double dist23 = getDistance(P2, P3);
            curvature = 4 * area_triangle / (dist12 * dist13 * dist23);
        }
        return curvature;
    }

    /*!
     * \brief Get distance : Called at every iteration of the main loop
     * \return Distance between 2 points
     */
    double getDistance(const PlannerHNS::WayPoint& P1, const PlannerHNS::WayPoint& P2)
    {
        return sqrt((P2.pos.x - P1.pos.x) * (P2.pos.x - P1.pos.x) + (P2.pos.y - P1.pos.y) * (P2.pos.y - P1.pos.y));
    }

    /*!
     * \brief Get distance : Called to calculate the distance between two points
       \param x_one, x_two, y_one, y_two The inputs contains the waypoints coordinates .
     * \return Distance between 2 points
     */
    double getDistance(double x_one, double x_two, double y_one, double y_two)
    {
        return pow(pow(x_one - x_two, 2) + pow(y_one - y_two, 2), 0.5);
    }

    /*!
     * \brief Check dynamic objects : Called at every iteration of the main loop
     * \Checks if there is a dynamic object in the critical area
     * \return Boolean indicating the presence of an obstacle in the critical area
     */
    bool isObjectInCriticalArea()
    {
        const float x = pose_.position.x;    //Center is currently in the front of the car
        const float y = pose_.position.y;
        const float yaw = cpp_utils::extract_yaw(pose_.orientation);
        const grid_map::Position center(x + car_length_ * cos(yaw)/2, y + car_length_ * sin(yaw)/2);
        critical_area_length_ = car_length_  + current_velocity_;
        
        // Condition for creating a critical area through autoware trajectory waypoints
        if (autowareTrajectory_.waypoints.size() > 0)
        {   
            // Remove critical area vertices
            critical_area_.removeVertices();
            
            // Initiate the index value and length for getting the critical area length
            int index = 0;
            double length = 0;

            // `For` loop for finding an index value from autoware trajectory to set the critical area length
            for (int k = 0; k < autowareTrajectory_.waypoints.size()-1; k++)
            {
                // Calculate the distance between two autoware trajectory waypoints through euclidean distance equation
                double distance_between_two_waypoints = getDistance(autowareTrajectory_.waypoints.at(k+1).pose.pose.position.x, autowareTrajectory_.waypoints.at(k).pose.pose.position.x, autowareTrajectory_.waypoints.at(k+1).pose.pose.position.y, autowareTrajectory_.waypoints.at(k).pose.pose.position.y);
                         
                // Add the distance between two waypoints into the length
                length += distance_between_two_waypoints;

                // If the length from autoware trajectory is higher than critical area length, store the index value
                if (length >= critical_area_length_ )
                {
                    // Store the index value and break the loop
                    index = k;
                    break;
                }  
            }
            
            // Creating the critical area polygon through two `for` loops
            // First `for` loop define the vertices for one side of the critical area
            for (int i = 0; i <= index; i++)
            {
                float yaw = cpp_utils::extract_yaw(autowareTrajectory_.waypoints.at(i).pose.pose.orientation);
                critical_area_.addVertex(grid_map::Position(autowareTrajectory_.waypoints.at(i).pose.pose.position.x - sin(yaw) * critical_area_width_/2, 
                                                                 autowareTrajectory_.waypoints.at(i).pose.pose.position.y + cos(yaw) * critical_area_width_/2)); 
            }
            
            // Second `for` loop define the vertices for other side of the critical area
            for (int j = index; j >= 0; j--)
            {
                float yaw = cpp_utils::extract_yaw(autowareTrajectory_.waypoints.at(j).pose.pose.orientation);
                critical_area_.addVertex(grid_map::Position(autowareTrajectory_.waypoints.at(j).pose.pose.position.x + sin(yaw) * critical_area_width_/2, 
                                                                 autowareTrajectory_.waypoints.at(j).pose.pose.position.y -  cos(yaw) * critical_area_width_/2));     
            }

            visualization_msgs::Marker criticalAreaMarker;  //Used for demo critical area visualization
            std_msgs::ColorRGBA color;
            color.r = 1.0;
            color.a = 1.0;
            grid_map::PolygonRosConverter::toLineMarker(critical_area_, color, 0.2, 0.5, criticalAreaMarker);
            criticalAreaMarker.header.frame_id = gridmap_.getFrameId();
            criticalAreaMarker.header.stamp.fromNSec(gridmap_.getTimestamp());
            pub_critical_area_.publish(criticalAreaMarker);

            for(grid_map::PolygonIterator areaIt(gridmap_, critical_area_) ; !areaIt.isPastEnd() ; ++areaIt) 
            {
                if(gridmap_.at("DynamicObjects", *areaIt) > 0) 
                { //If there is something inside the area
                    ROS_WARN_THROTTLE(1, "There is a dynamic object in the critical Area !");
                    return true;
                }
            }
        }
        return false;
    }

    /*!
     * \brief Check active nodes : Called at every iteration of the main loop
     * \Checks if all the necessary nodes are alive
     */
    bool areCriticalNodesAlive()
    {
        ros::V_string nodes_alive;
        ros::master::getNodes(nodes_alive);
        for(auto node : nodes_to_check_){
          if(std::find(nodes_alive.begin(), nodes_alive.end(), node) == nodes_alive.end()){
            std::cout << "ERROR: " << node << "was not found" << '\n';
            return false;
          }
        }
        return true;
    }

    /*!
     * \brief Check car off road : Called at every interation of the main loop
     * \return Boolean indicating if the center of the car is off the road
     */
    bool isCarOffRoad()
    {
      float current_lane_id = gridmap_.atPosition("Lanes", grid_map::Position(pose_.position.x, pose_.position.y));
      //ROS_INFO("Lane ID : %f", current_lane_id);
      if (current_lane_id == 0) {
          ROS_WARN_THROTTLE(1, "The center of the car is not on the road");
          return true;
      }
      return false;
    }

    /*!
     * \brief Check front sensors : Called at every interation of the main loop
     * \return Boolean indicating if front sensors are activated
     */
    bool isFrontSensorsActive()
    {
        // if at least one sensor sent a message
        if(sensors_fov_flag_) {
            nb_defective_front_sensors_ = 0;
            bool front_sensors_active = true;
            for(std::vector<int>::iterator it=FRONT_SENSORS_.begin(); it<FRONT_SENSORS_.end(); it++) {
                int i;
                i = std::distance(FRONT_SENSORS_.begin(), it);
                if(sensors_fov_.polygons.at(i).polygon.points.size() == 0) {
                    nb_defective_front_sensors_+=1;
                    front_sensors_active = false;
                }
            }
            return front_sensors_active;
        }
        // if no sensor sent a message, they are all defectives
        else {
            nb_defective_front_sensors_ = number_front_sensors_;
        }
    }

    /*!
     * \brief Check back sensors : Called at every interation of the main loop
     * \return Boolean indicating if back sensors are activated
     */
    bool isBackSensorsActive()
    {
        // if at least one sensor sent a message
        if(sensors_fov_flag_) {
            nb_defective_back_sensors_ = 0;
            bool back_sensors_active = true;
            for(std::vector<int>::iterator it=BACK_SENSORS_.begin(); it<BACK_SENSORS_.end(); it++) {
                int i;
                i = std::distance(BACK_SENSORS_.begin(), it);
                if(sensors_fov_.polygons.at(i).polygon.points.size() == 0) {
                    nb_defective_back_sensors_+=1;
                    back_sensors_active = false;
                }
            }
            return back_sensors_active;
        }
        // if no sensor sent a message, they are all defectives
        else {
            nb_defective_back_sensors_ = number_back_sensors_;
        }
    }

    /*!
     * \brief It is in this function that the switch
     * is triggered or not.
     */
    void publish()
    {
        if(was_switch_requested_)
        {
            pub_switch_.publish(switch_request_value_);
        }
        else
        {
            std_msgs::Int32 msg_switch;
            msg_switch.data = var_switch_;
            pub_switch_.publish(msg_switch);
        }


        std_msgs::Int32 msg_overwrite_behavior;
        msg_overwrite_behavior.data = varoverwrite_behavior_;
        pub_overwrite_behavior_.publish(msg_overwrite_behavior);



        // std_msgs::Float32 msg_limit_max_speed;
        // msg_limit_max_speed.data = 3;
        // pub_limit_max_speed_.publish(msg_limit_max_speed);

        // autoware_msgs::Lane lane;
        // lane.cost = -1;
        // lane.is_blocked = true;
        // autoware_msgs::LaneArray msg_overwrite_trajectory_eval;
        // msg_overwrite_trajectory_eval.lanes.clear();
        // msg_overwrite_trajectory_eval.lanes.push_back(lane);
        // msg_overwrite_trajectory_eval.lanes.push_back(lane);
        // msg_overwrite_trajectory_eval.lanes.push_back(lane);
        // msg_overwrite_trajectory_eval.lanes.push_back(lane);
        // msg_overwrite_trajectory_eval.lanes.push_back(lane);
        // msg_overwrite_trajectory_eval.lanes.push_back(lane);
        // msg_overwrite_trajectory_eval.lanes.push_back(lane);
        // msg_overwrite_trajectory_eval.lanes.push_back(lane);
        // msg_overwrite_trajectory_eval.lanes.push_back(lane);
        // pub_overwrite_trajectory_eval_.publish(msg_overwrite_trajectory_eval);

        //geometry_msgs::PoseStamped newGoal;
        //newGoal.header.frame_id = "wold";
        //newGoal.pose.position.x = 100;
        //newGoal.pose.position.y = 171;
        //newGoal.pose.position.z = 0;
        //newGoal.pose.orientation.x = 0;
        //newGoal.pose.orientation.y = 0;
        //newGoal.pose.orientation.z = 0;
        //newGoal.pose.orientation.w = 1;
        //pub_autoware_goal_.publish(newGoal);

        //std_msgs::Int32 msgTriggerUpdateGlobalPlanner;
        //msgTriggerUpdateGlobalPlanner.data = 1;
        //pub_trigger_update_global_planner_.publish(msgTriggerUpdateGlobalPlanner);

    }
    
    /*!
     * \brief Check instantaneous result : Called at every iteration of the main loop
     * \Checks if all tests are true or false return instantaneous test result
     */
    std::vector<bool> checkInstantaneousResults()
    {
        // The pass result vector of safety test.
        std::vector<bool> instantaneous_test_results(num_safety_tests_);

        // Check that all necessary nodes are active and store in the vector
        instantaneous_test_results[CHECK_ACTIVE_NODES] = areCriticalNodesAlive();
        
        //Check that the center of the car on the road
        instantaneous_test_results[CHECK_CAR_OFF_ROAD] = !isCarOffRoad();
        
        //Is there a dynamic object in the critical area
        instantaneous_test_results[CHECK_DYNAMIC_OJECT] = !isObjectInCriticalArea();
        
        // Check that the vehicle is in operational design domain polygon area
        instantaneous_test_results[CHECK_CAR_OFF_ODD] = !isVehicleOffOperationalDesignDomain();

        // Check that all front sensors are active
        instantaneous_test_results[CHECK_FRONT_SENSORS] = isFrontSensorsActive();

        // Check that all back sensors are active
        instantaneous_test_results[CHECK_BACK_SENSORS] = isBackSensorsActive();

        return instantaneous_test_results;
    }
    
    /*!
     * \brief Update counter value : Called at every iteration of the main loop
     * \Updates the counter value based instantaneous test results
     * \param test_result, threshold_pass_test, threshold_fail_test, increment_value, decrement_value, counter_value, takes these parameter to update the counter
     */
    int updateCounter(bool test_result, int threshold_pass_test, int threshold_fail_test, int increment_value, int decrement_value, int counter_value)
    {
        // If loop for updating the counter values until it reaches to threshold value
        // If the test is successfully passed
        if (test_result)
        {
            // Increment counter
            counter_value += increment_value;
    
            // Check if the counter reaches the threshold value then counter value will be same as threshold value
            if (counter_value > threshold_pass_test)
            {
                // Increment counter
                counter_value = threshold_pass_test;
            }
            
        }
        else if(!test_result) // if the test is failed
        {
            // Decrement counter
            counter_value += decrement_value;  

            // Check if the counter reaches the threshold value then counter value will be same as threshold value
            if(counter_value < threshold_fail_test)
            {
                // Decrement counter
                counter_value = threshold_fail_test;    
            }
        } 
        return counter_value;
    }
    
    /*!
     * \brief Check non-instantaneous result : Called at every iteration of the main loop
     * \Checks if the instantaneous test results hit the threshold value and updates the non-instantaneous test result as pass and fail
     */
    void checkNonInstantaneousResults()
    {
        // Extract Instantaneous safety test result
        std::vector<bool> instantaneous_test_results = checkInstantaneousResults();
        
        // For loop for each test result
        for (int i = 0; i < num_safety_tests_; i++)
        {
            // Update the counter value based on instantaneous test results
            safety_test_counters_[i] = updateCounter(instantaneous_test_results[i], thresholds_pass_test_[i], thresholds_fail_test_[i], increments_pass_test_[i], decrements_fail_test_[i], safety_test_counters_[i] );
            
            // If the counter value is same as pass threshold value then non-instantaneous result will be considered as PASS test
            if (safety_test_counters_[i] == thresholds_pass_test_[i])
            {
                non_instantaneous_results_[i] = PASS_;

                ROS_DEBUG_STREAM("Counter number is " << safety_test_counters_[i]);
            }
            else if (safety_test_counters_[i] == thresholds_fail_test_[i]) // If the counter value is same as fail threshold value then non-instantaneous result will be considered as PASS test
            {
                non_instantaneous_results_[i] = FAIL_;

                ROS_DEBUG_STREAM("Counter number is " << safety_test_counters_[i]);
            }
        }
    }
    
    /*!
     * \brief Check the size of thresholds, increments and decrements vector size from ROS paramter server : Called at every iteration of the main loop
     * \Checks if the instantaneous test results hit the threshold value and updates the non-instantaneous test result as pass and fail
     */
    void checkSafetyChecksParameterValidity()
    {
        if (thresholds_pass_test_.size() != num_safety_tests_)
        {
            thresholds_pass_test_ = std::vector<int>(num_safety_tests_,4);
            ROS_WARN("The threshold pass test vector size is not same as number of safety tests");
        }
        else if (thresholds_fail_test_.size() != num_safety_tests_ )
        {
            thresholds_fail_test_ = std::vector<int>(num_safety_tests_,-4);
            ROS_WARN("The threshold fail test vector size is not same as number of safety tests");
        }
        else if (increments_pass_test_.size() != num_safety_tests_)
        {
            increments_pass_test_ = std::vector<int>(num_safety_tests_,1);
            ROS_WARN("The increment pass test vector size is not same as number of safety tests");
        } 
        else if (decrements_fail_test_.size() != num_safety_tests_)
        {
            decrements_fail_test_ = std::vector<int>(num_safety_tests_,-1);
            ROS_WARN("The decrement fail test vector size is not same as number of safety tests");
        }
    }

    /*!
     * \brief Take final decision based on non-instantaneous results : Called at every iteration of the main loop
     * \Checks if all tests are pass or fail and trigger the safety switch or nominal channel
     */
    void takeDecisionBasedOnTestResult()
    {
        if (ros::param::get("/threshold_vector_pass_test", thresholds_pass_test_) || ros::param::get("/threshold_vector_fail_test", thresholds_fail_test_)
                || ros::param::get("/increment_vector_pass_test_", increments_pass_test_)  || ros::param::get("/decrement_vector_fail_test_", decrements_fail_test_) )
        {
            checkSafetyChecksParameterValidity();
        }

        // Initiate Non-instantaneous test result vector
        checkNonInstantaneousResults();
        
        // Find if any non-instantaneous test result is FAIL
        std::vector<bool>::iterator it;
        it = std::find(non_instantaneous_results_.begin(), non_instantaneous_results_.end(), FAIL_);
        
        // if any non-instantaneous test result is FAIL then switch to safety channel
        if (it != non_instantaneous_results_.end())
        {
            ROS_WARN_STREAM("The test " << (it - non_instantaneous_results_.begin())+1 <<  " is FAIL");
            triggerSafetySwitch();
        }
        else // else switch to nominal channel
        {
            ROS_DEBUG_STREAM("All tests are PASS");
            switchNominalChannel();
        }
    }
    
    /*!
     * \brief Trigger the safety switch
     * \Activates if the non-instantaneous test is failed
     */ 
    void triggerSafetySwitch()
    {
        var_switch_ = UNSAFE;
        return;
    }
    
    /*!
     * \brief Switch to nominal channel
     * \Activates if the non-instantaneous test is passed
     */
    void switchNominalChannel()
    {
        var_switch_ = SAFE;
        return;
    }

    /*!
     * \brief The function where the checks are called
     * \details The situation is evaluated and the state of the vehicle is
     * declared safe or unsafe.
     */
    void performSafetyTests()
    {
        varoverwrite_behavior_ = NO_BEHAVIOR_OVERWRITE_;

        // Check the distance to the center line of the lane
        distance_to_lane_ = getDistanceToLane(autoware_global_path_.at(0));

        // Check the distance to the road edge
        distance_to_road_edge_ = getDistanceToRoadEdge();

        // Check the curvature of the global plan
        CurvatureExtremum curvature = getCurvature(autoware_global_path_.at(0));

        // Send test_result to the decision maker function
        takeDecisionBasedOnTestResult();
    }
    
    /*!
     * \brief Check if the vector of operational design domain polygon coordinates is valid.
     * \return Boolean indicating true if the operational design domain polygon coordinates are exactly into pairs.
     * \param polygon_coordinates The function takes one input parameter which contains polygon coordinates.
     */
    bool isPolygonValid(std::vector<double> polygon_coordinates)
    {
        if (polygon_coordinates.size() % 2 != 0)
        {
            ROS_WARN("Invalid polygon, the list defining the polygon contains an odd number of values");
            return false;
        }
        return true;
    }
    
    /*!
     * \brief Check if the vehicle is inside the operational design domain polygon area.
     * \return Boolean indicating true if the vehicle is off the operational design domain polygon area.
     */
    bool isVehicleOffOperationalDesignDomain()
    {
        // Extract the polygon area and send true if the vehicle is not in the polygon area
        float odd_value_at_ego_position = gridmap_.atPosition("ODD", grid_map::Position(pose_.position.x, pose_.position.y));

        if (odd_value_at_ego_position == 0)
        {
            ROS_WARN("The Vehicle is outside the operational design domain polygon");
            return true;
        }
        else
        {
            ROS_INFO("The vehicle is inside the operational design domain polygon");
            return false;
        }
    }
    
    /*!
     * \brief The function where the operational design domain polygon has been created.
     * \details Polygon iterator creates the polygon according to given coordinates.
     * \param polygon_coordinates The function takes one input parameter which contains polygon coordinates.
     */
    void defineOperationalDesignDomain(std::vector<double> polygon_coordinates)
    {
        // The operational design domain values
        const double ODD_LAYER_IN_VALUE = 5.0;
        const double ODD_LAYER_OUT_VALUE = 0.0;


        // Add new layer called ODD (Operational design domain)
        gridmap_.add("ODD", ODD_LAYER_OUT_VALUE);

        if (isPolygonValid(polygon_coordinates))
        {       
            // Initiate the grid map ODD polygon
            grid_map::Polygon polygon;
            
            // Define ODD Polygon area through coordinates from ROS parameter server
            for (int i = 0; i < polygon_coordinates.size() ; i+=2)
            {
                polygon.addVertex(grid_map::Position(polygon_coordinates[i],  polygon_coordinates[i+1]));
            }

            // Add again the first coordinates from the vector to close down the polygon area
            polygon.addVertex(grid_map::Position(polygon_coordinates[0],  polygon_coordinates[1]));

            // Polygon Interator
            for (grid_map::PolygonIterator iterator(gridmap_, polygon);
                !iterator.isPastEnd(); ++iterator) {
                gridmap_.at("ODD", *iterator) = ODD_LAYER_IN_VALUE;
            }
        }
    }

    /*!
     * \brief The initialization loop waits until all flags have been received.
     * \details Checks for gnss, gridmap and autoware global path flags.
     */
    void waitForInitialization()
    {
        ros::Rate rate(20);
        while(nh_.ok() && !(gnss_flag_ && gridmap_flag_ && autoware_global_path_flag_ == 1))
        {
            ros::spinOnce();
            rate.sleep();
        }
    }

    /*!
     * \brief search the position of the center of the road side parking
     * \return the position of the center of the area road side parking in the gridmap
     * if there is no, return (-1, -1)
     * \param map the gridmap where the road side parking has to be found
     */
    grid_map::Position findRoadSideParking(grid_map::GridMap map)
    {
        bool is_road_side_parking = false;
        grid_map::Position pos_road_side_parking;
        std::vector<grid_map::Position> array_position;

        for(grid_map::GridMapIterator it(map); !it.isPastEnd(); ++it) {
            if(map.at("RoadSideParking", *it) == ROAD_SIDE_PARKING_VALUE) {
                grid_map::Position pos;
                map.getPosition(*it, pos);
                array_position.push_back(pos);
                is_road_side_parking = true;
            }
        }

        if(is_road_side_parking) {
            // The position to return is the middle of the area
            grid_map::Position pos_begin;
            grid_map::Position pos_end;
            pos_begin = array_position.at(0); // the first position stored in the array
            pos_end = array_position.at((int)array_position.size() - 1); // the last position stored in the array
            pos_road_side_parking.x() = (pos_begin.x() + pos_end.x()) / 2;
            pos_road_side_parking.y() = (pos_begin.y() + pos_end.y()) / 2;

        }
        else {
            pos_road_side_parking = grid_map::Position(-1, -1);
        }
        return pos_road_side_parking;
    }

    /*!
     * \brief search the position of the center of the rest area
     * \return the position of the center of the rest area in the gridmap
     * if there is no, return (-1, -1)
     * \param map the gridmap where the rest area has to be found
     */
    grid_map::Position findRestArea(grid_map::GridMap map)
    {
        bool is_rest_area = false; // parameter to know if there is rest area in the gridmap
        grid_map::Position pos_rest_area; // the position to return
        std::vector<grid_map::Position> array_position; // array that stores all position where there is rest area

        // for all index in the gridmap, test if the cell value is REST_AREA_VALUE
        for(grid_map::GridMapIterator it(map); !it.isPastEnd(); ++it) {
            if(map.at("RestArea", *it) == REST_AREA_VALUE) {
                grid_map::Position pos;
                map.getPosition(*it, pos); // extract the position corresponding to the index
                array_position.push_back(pos); // add the position to the array
                is_rest_area = true;
            }
        }

        if(is_rest_area) {
            // The position to return is the middle of the area
            grid_map::Position pos_begin;
            grid_map::Position pos_end;
            pos_begin = array_position.at(0); // the first position stored in the array
            pos_end = array_position.at((int)array_position.size() - 1); // the last position stored in the array
            pos_rest_area.x() = (pos_begin.x() + pos_end.x()) / 2;
            pos_rest_area.y() = (pos_begin.y() + pos_end.y()) / 2;
        }
        else {
            pos_rest_area = grid_map::Position(-1, -1);
        }
        return pos_rest_area;
    }

public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
    SafetySupervisor(ros::NodeHandle &nh, int argc, char **argv) : nh_(nh), var_switch_(SAFE)
    {   
        // Initialize the node, publishers and subscribers
        pub_switch_ = nh_.advertise<std_msgs::Int32>("/switch_command", 1, true);
        pub_overwrite_behavior_ = nh_.advertise<std_msgs::Int32>("/adeye/overwrite_behavior", 1, true);
        pub_limit_max_speed_ = nh_.advertise<std_msgs::Float32>("/adeye/limit_max_speed", 1, true);
        pub_overwrite_trajectory_eval_ = nh_.advertise<autoware_msgs::LaneArray>("/adeye/overwrite_trajectory_eval", 1, true);
        pub_autoware_goal_ = nh_.advertise<geometry_msgs::PoseStamped>("adeye/overwriteGoal", 1, true);
        pub_trigger_update_global_planner_ = nh_.advertise<std_msgs::Int32>("/adeye/update_global_planner", 1, true);
        pub_critical_area_ = nh_.advertise<visualization_msgs::Marker>("/critical_area", 1, true);  //Used for critical area visualization

        sub_gnss_ = nh_.subscribe<geometry_msgs::PoseStamped>("/ground_truth_pose", 100, &SafetySupervisor::gnssCallback, this);
        sub_gridmap_ = nh_.subscribe<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, &SafetySupervisor::gridmapCallback, this);
        sub_autoware_trajectory_ = nh_.subscribe<autoware_msgs::Lane>("/final_waypoints", 1, &SafetySupervisor::autowareTrajectoryCallback, this);
        sub_autoware_global_plan_ = nh.subscribe("/lane_waypoints_array", 1, &SafetySupervisor::autowareGlobalPlanCallback, this);
        sub_current_velocity_ = nh.subscribe("/current_velocity", 1, &SafetySupervisor::currentVelocityCallback, this);
        sub_switch_request_ = nh.subscribe("safety_channel/switch_request", 1, &SafetySupervisor::switchRequestCallback, this);
        sub_sensor_fov_ = nh.subscribe("/sensor_fov", 1, &SafetySupervisor::sensorFovCallback, this);

        // Initialization loop
        waitForInitialization();

        // Initialize the list of nodes to check
        for(int i = 1; i<argc; i++){
            nodes_to_check_.push_back(argv[i]);
        }
        // std::cout << "number" << nodes_to_check_.front() << std::endl;
        // std::cout << "number" << nodes_to_check_.size() << std::endl;

        
        

    }
    
    /*!
     * \brief The main loop of the Node
     * \details Checks for topics updates, then evaluate
     * the situation and triggers (or not) the safety switch depending of
     * the situation evaluation.
     */
    void run()
    {
        ros::Rate rate(20);
        while(nh_.ok())
        {
            if(!car_size_set_)
            {
                if (nh_.getParam("car_width_", car_width_) && nh_.getParam("car_length_", car_length_))
                {
                    critical_area_length_ = car_length_; //Size of the critical Area
                    critical_area_width_ = car_width_ * 1.2;
                    car_size_set_ = true;
                }
            }

            ros::spinOnce();
            
            // Provide operational design domain coordinates from ROS parameter server, otherwise use default grid map polygon coordinates from ODD
            if (nh_.getParam("/operational_design_domain", ODD_coordinates_))
            {
                defineOperationalDesignDomain(ODD_coordinates_);
            }
            else
            {
                defineOperationalDesignDomain(ODD_default_gridmap_coordinates_);
            }

            performSafetyTests();
            publish();
                 
            rate.sleep();
            //ROS_INFO("Current state: %d", var_switch_);
        
            // Test for functions find safe areas
            if(gridmap_flag_) {
                grid_map::Position pos_road_side_parking = findRoadSideParking(gridmap_);
                grid_map::Position pos_rest_area = findRestArea(gridmap_);

                std::cout << "x position road side parking : " << pos_road_side_parking.x() << std::endl;
                std::cout << "y position road side parking : " << pos_road_side_parking.y() << std::endl;
                std::cout << "x position rest area : " << pos_rest_area.x() << std::endl;
                std::cout << "y position rest area : " << pos_rest_area.y() << std::endl;
            }
        }
    }

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "safetySupervisor");
    ros::NodeHandle nh;
    SafetySupervisor safetySupervisor(nh, argc, argv);
    safetySupervisor.run();
    return 0;
}
