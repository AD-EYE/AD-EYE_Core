#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
#include <autoware_msgs/LaneArray.h>

#include <cpp_utils/pose_datatypes.h>

#include <visualization_msgs/Marker.h> //Used for critical area visualization
#include <std_msgs/ColorRGBA.h>        //Used for critical area visualization

#include "op_planner/PlannerH.h"
#include "op_ros_helpers/op_ROSHelpers.h"
#include "op_planner/PlanningHelpers.h"
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>


#include "safety_fault_monitors/active_nodes_checker.h"
#include "safety_fault_monitors/geofencing_checker.h"
#include "safety_fault_monitors/car_off_road_checker.h"
#include "safety_fault_monitors/obstacles_in_critical_area_checker.h"
#include "safety_fault_monitors/sensor_checker.h"

#define ROAD_SIDE_PARKING_VALUE 30
#define REST_AREA_VALUE 40


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
    ros::Publisher pub_road_side_parking_viz_;
    ros::Subscriber sub_gnss_;
    ros::Subscriber sub_gridmap_;
    ros::Subscriber sub_autoware_global_plan_;
    ros::Subscriber sub_switch_request_;
    ros::Subscriber sub_sensor_fov_;
    ros::Subscriber sub_goal_coordinates_;
    ros::Subscriber sub_ssmp_endposes_;


    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;

    std::vector<std::shared_ptr<SafetyFaultMonitor>>  safety_monitors_level_one_;
    std::vector<std::shared_ptr<SafetyFaultMonitor>>  safety_monitors_level_two_;
    std::vector<std::shared_ptr<SafetyFaultMonitor>>  safety_monitors_level_three_;
    std::vector<std::shared_ptr<SafetyFaultMonitor>>  safety_monitors_level_four_;

    visualization_msgs::MarkerArray ssmp_current_endposes_;

    // constants
    const bool SAFE = false;
    const bool UNSAFE = true;
    const int NO_BEHAVIOR_OVERWRITE_ = -1;
    enum STATE_TYPE_ {INITIAL_STATE, WAITING_STATE, FORWARD_STATE, STOPPING_STATE, EMERGENCY_STATE,
	TRAFFIC_LIGHT_STOP_STATE,TRAFFIC_LIGHT_WAIT_STATE, STOP_SIGN_STOP_STATE, STOP_SIGN_WAIT_STATE, FOLLOW_STATE, LANE_CHANGE_STATE, OBSTACLE_AVOIDANCE_STATE, GOAL_STATE, FINISH_STATE, YIELDING_STATE, BRANCH_LEFT_STATE, BRANCH_RIGHT_STATE};

    // The number of the safety test
    enum SAFETY_TESTS_{CHECK_ACTIVE_NODES_LEVEL_ONE, CHECK_ACTIVE_NODES_LEVEL_TWO, CHECK_ACTIVE_NODES_LEVEL_THREE, CHECK_ACTIVE_NODES_LEVEL_FOUR,
        CHECK_CAR_OFF_ROAD, CHECK_DYNAMIC_OBJECT, CHECK_CAR_OFF_ODD, CHECK_RADAR_ACTIVE, CHECK_LIDAR_ACTIVE, CHECK_CAMERA_1_ACTIVE, CHECK_CAMERA_2_ACTIVE, CHECK_CAMERA_TL_ACTIVE};

    bool was_switch_requested_ = false;
    std_msgs::Int32 switch_request_value_;

    geometry_msgs::Pose pose_;
    bool var_switch_;
    int varoverwrite_behavior_;
    bool gnss_flag_ = false;
    bool gridmap_flag_ = false;
    bool autoware_global_path_flag_ = false;

    bool is_rest_area_chosen_ = false;
    bool is_road_side_parking_chosen_ = false;
    geometry_msgs::PoseStamped road_side_parking_pose;

    grid_map::GridMap gridmap_; //({"StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle", "Lanes", "RoadSideParking", "RestArea", "SensorSectors"});
    std::vector<std::vector<PlannerHNS::WayPoint>> autoware_global_path_;
    
    // Safety tests
    int num_safety_tests_ = 12;

    // Set the default threshold value for each pass and fail safety test
    std::vector<int> thresholds_pass_test_ = std::vector<int>(num_safety_tests_,4);
    std::vector<int> thresholds_fail_test_ = std::vector<int>(num_safety_tests_,-4);

    // Set the default increment and decrement value for each pass and fail safety test
    std::vector<int> increments_pass_test_ = std::vector<int>(num_safety_tests_,1);
    std::vector<int> decrements_fail_test_ = std::vector<int>(num_safety_tests_,-1);
   
    // result of the check functions
    double distance_to_lane_;
    double distance_to_road_edge_;

    struct CurvatureExtremum {
        double max;
        double min;
    };

    // enum to identify critical level
    enum CRITICAL_LEVEL_ {INITIAL_GOAL, REST_AREA, ROAD_SIDE_PARKING, IMMEDIATE_STOP};

    // Test for sensor coverage
    enum SENSOR_TYPE_ {radar, lidar, camera1, camera2, cameratl}; // numbers of sensors have to fit with those defined in sensor monitor

    bool broke_at_least_once_ = false; // To know if there already is at least 1 anomaly
    bool is_anomaly_fixed_ = false; // To know if there already is an anomaly and if it is now fixed
    geometry_msgs::PoseStamped initial_goal_coordinates_;

    double current_speed_limit_ = 8.3;

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

        gridmap_flag_ = true;
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


    void storeGoalCoordinatesCallback(const geometry_msgs::PoseStampedConstPtr& msg)
    {
        initial_goal_coordinates_.header.frame_id = "world";
        initial_goal_coordinates_.pose = msg->pose;
    }

    void ssmpEndposesCallback(const visualization_msgs::MarkerArrayConstPtr& msg)
    {
        ssmp_current_endposes_.markers.clear();
        for(auto & marker : msg->markers)
        {
            if(marker.color.a != 0) // the markers with alpha 0 are invisible and thus not endposes
            {
                ssmp_current_endposes_.markers.push_back(marker);
            }
        }
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
    static double getSignedCurvature(const PlannerHNS::WayPoint& P1, const PlannerHNS::WayPoint& P2, const PlannerHNS::WayPoint& P3)
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
    static double getDistance(const PlannerHNS::WayPoint& P1, const PlannerHNS::WayPoint& P2)
    {
        return sqrt((P2.pos.x - P1.pos.x) * (P2.pos.x - P1.pos.x) + (P2.pos.y - P1.pos.y) * (P2.pos.y - P1.pos.y));
    }

    /*!
     * \brief Get distance : Called at every iteration of the main loop
     * \return Distance between 2 points
     */
    static double getDistance(const geometry_msgs::Pose& P1, const geometry_msgs::Pose& P2)
    {
        return sqrt((P2.position.x - P1.position.x) * (P2.position.x - P1.position.x) + (P2.position.y - P1.position.y) * (P2.position.y - P1.position.y));
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
        // else
        // {
        //     std_msgs::Int32 msg_switch;
        //     msg_switch.data = var_switch_;
        //     pub_switch_.publish(msg_switch);
        // }


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
        //newGoal.header.frame_id = "world";
        //newGoal.pose.position.x = 100;
        //newGoal.pose.position.y = 171;
        //newGoal.pose.position.z = 0;
        //newGoal.pose.orientation.x = 0;
        //newGoal.pose.orientation.y = 0;
        //newGoal.pose.orientation.z = 0;
        //newGoal.pose.orientation.w = 1;
        //pub_autoware_goal_.publish(newGoal);

        // std_msgs::Int32 msgTriggerUpdateGlobalPlanner;
        // msgTriggerUpdateGlobalPlanner.data = 1;
        // pub_trigger_update_global_planner_.publish(msgTriggerUpdateGlobalPlanner);

    }

    
    /*!
     * \brief Check non-instantaneous result : Called at every iteration of the main loop
     * \Checks if the instantaneous test results hit the threshold value and updates the non-instantaneous test result as pass and fail
     */
    void updateFaultMonitors()
    {
        // For loop for each safety monitor
        for(int i = 0; i < safety_monitors_level_one_.size(); i++)
        {
            // Update the counter value based on instantaneous test results
            safety_monitors_level_one_.at(i)->update();
        }
        for(int i = 0; i < safety_monitors_level_two_.size(); i++)
        {
            // Update the counter value based on instantaneous test results
            safety_monitors_level_two_.at(i)->update();
        }
        for(int i = 0; i < safety_monitors_level_three_.size(); i++)
        {
            // Update the counter value based on instantaneous test results
            safety_monitors_level_three_.at(i)->update();
        }
        for(int i = 0; i < safety_monitors_level_four_.size(); i++)
        {
            // Update the counter value based on instantaneous test results
            safety_monitors_level_four_.at(i)->update();
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
    CRITICAL_LEVEL_ takeDecisionBasedOnTestsResults() {
        if (ros::param::get("/threshold_vector_pass_test", thresholds_pass_test_) ||
            ros::param::get("/threshold_vector_fail_test", thresholds_fail_test_)
            || ros::param::get("/increment_vector_pass_test_", increments_pass_test_) ||
            ros::param::get("/decrement_vector_fail_test_", decrements_fail_test_)) {
            checkSafetyChecksParameterValidity();
        }

        // Initiate Non-instantaneous test result vector
        updateFaultMonitors();

        bool all_tests_passed = true;
        CRITICAL_LEVEL_ most_critical_level; // The most critical level reached
        most_critical_level = INITIAL_GOAL; // Initialize the most critical level, for the moment no anomaly detected


        for(auto & i : safety_monitors_level_four_) {
            // Update the counter value based on instantaneous test results
            if (i->isFaultConfirmed())
                return CRITICAL_LEVEL_::IMMEDIATE_STOP;
        }
        for(auto & i : safety_monitors_level_three_) {
            // Update the counter value based on instantaneous test results
            if (i->isFaultConfirmed())
                return CRITICAL_LEVEL_::ROAD_SIDE_PARKING;
        }
        for(auto & i : safety_monitors_level_two_) {
            // Update the counter value based on instantaneous test results
            if (i->isFaultConfirmed())
                return CRITICAL_LEVEL_::REST_AREA;
        }
        for(auto & i : safety_monitors_level_one_) {
            // Update the counter value based on instantaneous test results
            if (i->isFaultConfirmed())
                return CRITICAL_LEVEL_::INITIAL_GOAL;
        }
        return CRITICAL_LEVEL_::INITIAL_GOAL;
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



        CRITICAL_LEVEL_ most_critical_level = takeDecisionBasedOnTestsResults();;
        performAction(most_critical_level);
    }

    /*!
     * \brief Returns whether there is a SSMP endpose that is close enough to the given parking
     * \param parking_pose target road side parking pose
     * \return boolean characterizing the whether the pose is reachable by SSMP
     */
    bool isRoadSideParkingReachableBySSMP(geometry_msgs::PoseStamped parking_pose) {
        double DISTANCE_THRESHOLD = 3;
        for(auto endpose: ssmp_current_endposes_.markers)
        {
            geometry_msgs::PoseStamped pose_stamped_out;
            try{
                geometry_msgs::PoseStamped pose_stamped_in;
                pose_stamped_in.header = endpose.header;
                pose_stamped_in.pose = endpose.pose;
                tf_buffer_.transform(pose_stamped_in, pose_stamped_out, "SSMP_map", ros::Duration(0));
            }
            catch (tf2::TransformException &ex) {
                ROS_WARN("%s",ex.what());
                ros::Duration(1.0).sleep();
            }
            if(getDistance(pose_stamped_out.pose, parking_pose.pose) < DISTANCE_THRESHOLD)
            {
//                std::cout << "_________________________________________" << std::endl;
//                std::cout << getDistance(pose_stamped_out.pose, parking_pose.pose) << std::endl;
//                std::cout << pose_stamped_out.pose.position.x<< "   " << pose_stamped_out.pose.position.y << std::endl;
//                std::cout << parking_pose.pose.position.x<< "   " << parking_pose.pose.position.y << std::endl;
//                std::cout << "_________________________________________" << std::endl;
                return true;
            }
        }
        return false;
    }


    /*!
     * \brief Perform the minimal risk condition connected to the decision take
     * \param most_critical_level Decision taken
     */
    void performAction(const CRITICAL_LEVEL_ &most_critical_level) {// Make the decision according to the critical level
        switch(most_critical_level)
        {
            case INITIAL_GOAL:
                // If there is at least 1 anomaly
                if(broke_at_least_once_) {
                    is_anomaly_fixed_ = true;
                    broke_at_least_once_ = false;
                }
                // If there is at least 1 anomaly fixed
                if(is_anomaly_fixed_) {
                    // Redefine the initial goal
                    pub_autoware_goal_.publish(initial_goal_coordinates_);
                    is_rest_area_chosen_ = false;
                    is_road_side_parking_chosen_ = false;
                }
                switchNominalChannel();
                ROS_INFO("Decision: Go to initial goal");
                break;
            case REST_AREA:
                broke_at_least_once_ = true;
                is_anomaly_fixed_ = false;
                if(!is_rest_area_chosen_)
                {
                    if(isThereAValidRestArea())
                    {
                        geometry_msgs::PoseStamped rest_area_pose = findClosestRestArea();
                        is_rest_area_chosen_ = true;
                        pub_autoware_goal_.publish(rest_area_pose);
                        ROS_INFO("Decision: Stop in rest area");
                        break;
                    }
                    else
                    {
                        ROS_INFO("Decision: No rest area available, performing immediate stop");
                    }
                }
                else{
                    ROS_INFO("Decision: rest area chosen");
                    break;
                }
            case ROAD_SIDE_PARKING:
//                    ensureNumberOfSSMPEndposes(15);
                if(!is_road_side_parking_chosen_)
                {
                    if(isThereAValidRoadSideParking())
                    {
                    is_road_side_parking_chosen_ = true;
                    road_side_parking_pose = findClosestRoadSideParking();
                    }
                    else // if there is no valid parking we stop immediately (going one level up in term of criticality)
                    {
                        triggerSafetySwitch();
                        ROS_INFO("Decision: No road side parking available, performing immediate stop");
                    }
                }
                else
                {
                    if (isRoadSideParkingReachableBySSMP(road_side_parking_pose)) // if not we need to wait a bit to be able to park on the parking
                    {
                        ROS_INFO("Decision: Stopping on a road side parking");
                        triggerSafetySwitch();
                    }
                    else
                        ROS_INFO("Decision: Will stop on a road side parking");
                }
                break;
            case IMMEDIATE_STOP:
                triggerSafetySwitch();
                ROS_INFO("Decision: Immediate stop");
                break;
        }
        std_msgs::Int32 msg_switch;
        msg_switch.data = var_switch_;
        pub_switch_.publish(msg_switch);
    };

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

    void ensureNumberOfSSMPEndposes(int target_number_of_enposes)
    {
        double SPEED_INCREMENT = 0.56;
        int EXTRA_POSES_THRESHOLD_TO_INCREASE_SPEED = 6;
        if(ssmp_current_endposes_.markers.size() < current_speed_limit_)
            current_speed_limit_ -= SPEED_INCREMENT;
        else if(ssmp_current_endposes_.markers.size() > current_speed_limit_ + EXTRA_POSES_THRESHOLD_TO_INCREASE_SPEED)
            current_speed_limit_ += SPEED_INCREMENT;

         std_msgs::Float32 msg_limit_max_speed;
         msg_limit_max_speed.data = current_speed_limit_;
         pub_limit_max_speed_.publish(msg_limit_max_speed);
    }

    /*!
     * \brief Returns whether there is a parking that is considered reachable in the gridmap
     * \return boolean characterizing the existence of a reachable road side parking
     */
    bool isThereAValidRoadSideParking()
    {
        double remaining_traj_length = getRemainingTrajectoryLength();
        for(grid_map::GridMapIterator it(gridmap_); !it.isPastEnd(); ++it) {
            if(gridmap_.at("RoadSideParking", *it) != 0) {
                PlannerHNS::WayPoint wp = gridmapIteratorToWaypint(it);
                double distance_ego_to_parking = getRemainingDistanceOnGlobalPlanTo(wp);
                if(isRoadSideParkingValid(distance_ego_to_parking, remaining_traj_length, getPerpendicularDistanceToGlobalPlanFrom(wp)))
                {
//                    std::cout << "distance_ego_to_parking: " << distance_ego_to_parking << "    remaining_traj_length: " << remaining_traj_length << "   perp dist: " << info.perp_distance << std::endl;
                    return true;
                }
            }
        }
        return false;
    }


    static bool isRoadSideParkingValid(double distance_to_parking, double remaining_traj_length, double perpendicular_distance)
    {
        const double PERPENDICULAR_DISTANCE_THRESHOLD = 20;
        const double DISTANCE_TO_PARKING_LOW_THRESHOLD = 30;
        return (DISTANCE_TO_PARKING_LOW_THRESHOLD < distance_to_parking && distance_to_parking < remaining_traj_length && abs(perpendicular_distance) < PERPENDICULAR_DISTANCE_THRESHOLD);
    }

    /*!
     * \brief search the position of the barycenter of the road side parking
     * \return Position of the barycenter of the closest road side parking reachable in the gridmap
     */
    geometry_msgs::PoseStamped findClosestRoadSideParking()
    {
        auto min_distance = DBL_MAX;
        int min_id;
        PlannerHNS::WayPoint min_wp;

        std::unordered_map<int, std::vector<PlannerHNS::WayPoint>> parking_positions_wp_by_id;

       double remaining_traj_length = getRemainingTrajectoryLength();
        for(grid_map::GridMapIterator map_iterator(gridmap_); !map_iterator.isPastEnd(); ++map_iterator) {
            if(gridmap_.at("RoadSideParking", *map_iterator) != 0) {
                PlannerHNS::WayPoint wp = gridmapIteratorToWaypint(map_iterator);
                if (parking_positions_wp_by_id.find(gridmap_.at("RoadSideParking", *map_iterator)) != parking_positions_wp_by_id.end())
                    parking_positions_wp_by_id[gridmap_.at("RoadSideParking", *map_iterator)].push_back(wp);
                else
                    parking_positions_wp_by_id[gridmap_.at("RoadSideParking", *map_iterator)] = std::vector<PlannerHNS::WayPoint>{wp};
                PlannerHNS::RelativeInfo info;
                PlannerHNS::PlanningHelpers::GetRelativeInfo(autoware_global_path_.front(), wp, info);
                int considered_wp_index = getClosestWaypointIndex(autoware_global_path_.front(), wp, 0);
                double distance_ego_to_parking = PlannerHNS::PlanningHelpers::GetDistanceOnTrajectory_obsolete(autoware_global_path_.front(), getEgoWaypointIndexOnGlobalPlan(), wp);
                if(isRoadSideParkingValid(distance_ego_to_parking, remaining_traj_length, info.perp_distance) && distance_ego_to_parking < min_distance)
                {
//                    std::cout << "_______________________________________" << std::endl;
//                    std::cout << "egopos x " << pose_wp.pos.x << "   egopos y " << pose_wp.pos.y << std::endl;
//                    std::cout << "pos x " << pos.x() << "   pos y " << pos.y() << std::endl;
//                    std::cout << "distance on traj " << distance_ego_to_parking << "   from back " << info.from_back_distance << "  to front " << info.to_front_distance << "   perp_distance " << info.perp_distance << std::endl;
//                    std::cout << "_______________________________________" << std::endl;
                    min_distance = distance_ego_to_parking;
                    min_id = gridmap_.at("RoadSideParking", *map_iterator);
                    min_wp = autoware_global_path_.front().at(considered_wp_index);
                }
            }
        }

        //average all the positions of the parking to find the center
        geometry_msgs::PoseStamped average_position;
        average_position.header.frame_id = "/SSMP_map";
        geometry_msgs::Point average_point = getBarycenter(parking_positions_wp_by_id[min_id]);
        average_position.pose.position = average_point;
        average_position.pose.orientation = tf::createQuaternionMsgFromYaw(min_wp.pos.a);

        pub_road_side_parking_viz_.publish(createMarker(average_position, 1.0f, 0.0f, 1.0f));

        return average_position;

    }

    static int getClosestWaypointIndex(const std::vector<PlannerHNS::WayPoint>& trajectory, const PlannerHNS::WayPoint& p, const int& prevIndex = 0)
    {
        double min_dist = DBL_MAX;
        int min_index = 0;
        for(int wp_index = 0; wp_index < trajectory.size(); wp_index++)
        {
            if(getDistance(p, trajectory.at(wp_index)) < min_dist)
            {
                min_dist = getDistance(p, trajectory.at(wp_index));
                min_index = wp_index;
            }
        }
        return min_index;
    }

    int getEgoWaypointIndexOnGlobalPlan()
    {
        PlannerHNS::WayPoint pose_wp(pose_.position.x, pose_.position.y, 0, 0);
        int pose_wp_index = getClosestWaypointIndex(autoware_global_path_.front(), pose_wp, 0);
        return pose_wp_index;
    }

    double getRemainingTrajectoryLength()
    {
        int pose_wp_index = getEgoWaypointIndexOnGlobalPlan();
        double remaining_traj_length = PlannerHNS::PlanningHelpers::GetDistanceOnTrajectory_obsolete(autoware_global_path_.front(), pose_wp_index, autoware_global_path_.front().back());
        return remaining_traj_length;
    }


    static bool isRestAreaValid(double distance_to_parking, double remaining_traj_length, double perpendicular_distance)
    {
        const double PERP_DISTANCE_THRESHOLD = 75;
        const double DISTANCE_ON_TRAJ_LOW_THRESHOLD = 30;
        return (DISTANCE_ON_TRAJ_LOW_THRESHOLD < distance_to_parking && distance_to_parking < remaining_traj_length && abs(perpendicular_distance) < PERP_DISTANCE_THRESHOLD);
    }

    PlannerHNS::WayPoint gridmapIteratorToWaypint(grid_map::GridMapIterator it)
    {
        grid_map::Position pos;
        gridmap_.getPosition(*it, pos);
        PlannerHNS::WayPoint wp(pos.x(), pos.y(), 0, 0);
        return wp;
    }

    double getRemainingDistanceOnGlobalPlanTo(PlannerHNS::WayPoint wp)
    {
        return PlannerHNS::PlanningHelpers::GetDistanceOnTrajectory_obsolete(autoware_global_path_.front(), getEgoWaypointIndexOnGlobalPlan(), wp);
    }

    double getPerpendicularDistanceToGlobalPlanFrom(PlannerHNS::WayPoint wp)
    {
        PlannerHNS::RelativeInfo info;
        PlannerHNS::PlanningHelpers::GetRelativeInfo(autoware_global_path_.front(), wp, info);
        return info.perp_distance;
    }

    /*!
     * \brief Returns whether there is a rest area that is considered reachable in the gridmap
     * \return boolean characterizing the existence of a reachable rest area
     */
    bool isThereAValidRestArea()
    {
        PlannerHNS::WayPoint pose_wp(pose_.position.x, pose_.position.y, 0, 0);
        int pose_wp_index = getClosestWaypointIndex(autoware_global_path_.front(), pose_wp, 0);
        if(pose_wp_index > 520)
            return false;
        double remaining_traj_length = getRemainingTrajectoryLength();
        for(grid_map::GridMapIterator map_iterator(gridmap_); !map_iterator.isPastEnd(); ++map_iterator) {
            PlannerHNS::WayPoint wp = gridmapIteratorToWaypint(map_iterator);
            if(gridmap_.at("RestArea", *map_iterator) != 0) {//                std::cout << "distance_ego_rest_area: " << distance_ego_rest_area << "    remaining_traj_length: " << remaining_traj_length << "   perp dist: " << info.perp_distance << std::endl;
                if(isRestAreaValid(getRemainingDistanceOnGlobalPlanTo(wp), remaining_traj_length, getPerpendicularDistanceToGlobalPlanFrom(wp)))
                {
                    return true;
                }
            }
        }
        return false;
    }


    /*!
     * \brief search the position of the barycenter of the closest rest area
     * \return Position of the barycenter of the closest rest area in the gridmap
     */
    geometry_msgs::PoseStamped findClosestRestArea()
    {
        auto min_distance = DBL_MAX;
        int min_id;
        PlannerHNS::WayPoint min_wp;

        std::unordered_map<int, std::vector<PlannerHNS::WayPoint>> rest_areas_wp_by_id;

//        std::vector<int> id_seen;

        double remaining_traj_length = getRemainingTrajectoryLength();
        for(grid_map::GridMapIterator map_iterator(gridmap_); !map_iterator.isPastEnd(); ++map_iterator) {
            if(gridmap_.at("RestArea", *map_iterator) != 0) {
                PlannerHNS::WayPoint wp = gridmapIteratorToWaypint(map_iterator);
                if (rest_areas_wp_by_id.find(gridmap_.at("RestArea", *map_iterator)) != rest_areas_wp_by_id.end())
                    rest_areas_wp_by_id[gridmap_.at("RestArea", *map_iterator)].push_back(wp);
                else
                    rest_areas_wp_by_id[gridmap_.at("RestArea", *map_iterator)] = std::vector<PlannerHNS::WayPoint>{wp};
                int considered_wp_index = getClosestWaypointIndex(autoware_global_path_.front(), wp, 0);
                double distance_ego_rest_area = PlannerHNS::PlanningHelpers::GetDistanceOnTrajectory_obsolete(autoware_global_path_.front(), getEgoWaypointIndexOnGlobalPlan(), wp);
//                if (std::find(id_seen.begin(), id_seen.end(), gridmap_.at("RestArea", *map_iterator)) == id_seen.end()) {
//                    std::cout << "_______________________________________" << std::endl;
//                    std::cout << "egopos x " << pose_wp.pos.x << "   egopos y " << pose_wp.pos.y << std::endl;
//                    std::cout << "pos x " << pos.x() << "   pos y " << pos.y() << std::endl;
//                    std::cout << "distance on traj " << distance_ego_rest_area << "   from back " << info.from_back_distance << "  to front " << info.to_front_distance << "   perp_distance " << info.perp_distance << std::endl;
//                    std::cout << "_______________________________________" << std::endl;
//                    id_seen.push_back(gridmap_.at("RestArea", *map_iterator));
//                }
                if(isRestAreaValid(distance_ego_rest_area, remaining_traj_length, getPerpendicularDistanceToGlobalPlanFrom(wp)) && distance_ego_rest_area < min_distance)
                {
                    min_distance = distance_ego_rest_area;
                    min_id = gridmap_.at("RestArea", *map_iterator);
                    min_wp = autoware_global_path_.front().at(considered_wp_index);
                }
            }
        }

        //average all the positions of the rest area to find the center
        geometry_msgs::PoseStamped average_position;
        geometry_msgs::Point average_point = getBarycenter(rest_areas_wp_by_id[min_id]);
        average_position.header.frame_id = "/SSMP_map";
        average_position.pose.position = average_point;
        average_position.pose.orientation = tf::createQuaternionMsgFromYaw(min_wp.pos.a);

        pub_road_side_parking_viz_.publish(createMarker(average_position, 0.0f, 0.0f, 1.0f));

        return average_position;

    }

    static geometry_msgs::Point getBarycenter(const std::vector<PlannerHNS::WayPoint>& positions_wp)
    {
        geometry_msgs::Point average_point;
        for(auto wp: positions_wp)
        {
            average_point.x += wp.pos.x;
            average_point.y += wp.pos.y;
        }
        average_point.x /= positions_wp.size();
        average_point.y /= positions_wp.size();
        return average_point;
    }

    static visualization_msgs::Marker createMarker(const geometry_msgs::PoseStamped& pose, double r, double g, double b)
    {
        visualization_msgs::Marker marker;
        marker.header.frame_id = pose.header.frame_id;
        marker.header.stamp = ros::Time::now();
        marker.id = 0;
        marker.action = visualization_msgs::Marker::ADD;
        marker.type = visualization_msgs::Marker::CUBE;
        marker.pose = pose.pose;
        marker.scale.x = 3.0;
        marker.scale.y = 3.0;
        marker.scale.z = 1.0;
        marker.color.r = r;
        marker.color.g = g;
        marker.color.b = b;
        marker.color.a = 1.0;
        marker.lifetime = ros::Duration();
        return marker;
    }


public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initialize the node and its components such as publishers and subscribers.
     */
    SafetySupervisor(ros::NodeHandle &nh, int argc, char **argv) : nh_(nh), var_switch_(SAFE), tf_listener_(tf_buffer_)
    {   
        // Initialize the node, publishers and subscribers
        pub_switch_ = nh_.advertise<std_msgs::Int32>("/switch_command", 1, true);
        pub_overwrite_behavior_ = nh_.advertise<std_msgs::Int32>("/adeye/overwrite_behavior", 1, true);
        pub_limit_max_speed_ = nh_.advertise<std_msgs::Float32>("/adeye/limit_max_speed", 1, true);
        pub_overwrite_trajectory_eval_ = nh_.advertise<autoware_msgs::LaneArray>("/adeye/overwrite_trajectory_eval", 1, true);
        pub_autoware_goal_ = nh_.advertise<geometry_msgs::PoseStamped>("adeye/overwriteGoal", 1, true);
        pub_trigger_update_global_planner_ = nh_.advertise<std_msgs::Int32>("/adeye/update_global_planner", 1, true);
        pub_road_side_parking_viz_ = nh_.advertise<visualization_msgs::Marker>("selected_road_side_parking", 1, true);

        sub_gnss_ = nh_.subscribe<geometry_msgs::PoseStamped>("/ground_truth_pose", 100, &SafetySupervisor::gnssCallback, this);
        sub_gridmap_ = nh_.subscribe<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, &SafetySupervisor::gridmapCallback, this);
        sub_autoware_global_plan_ = nh.subscribe("/lane_waypoints_array", 1, &SafetySupervisor::autowareGlobalPlanCallback, this);
        sub_switch_request_ = nh.subscribe("safety_channel/switch_request", 1, &SafetySupervisor::switchRequestCallback, this);
        sub_goal_coordinates_ = nh_.subscribe<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, &SafetySupervisor::storeGoalCoordinatesCallback, this);
        sub_ssmp_endposes_ = nh_.subscribe<visualization_msgs::MarkerArray>("/safe_stop_endposes_vis", 1, &SafetySupervisor::ssmpEndposesCallback, this);

        createFaultMonitors();

        // Initialization loop
        waitForInitialization();
    }

    void createFaultMonitors() {
        safety_monitors_level_one_.emplace_back(make_shared<ActiveNodeChecker>(1, 1, 4, -4, 1));

        safety_monitors_level_two_.emplace_back(make_shared<ActiveNodeChecker>(1, 1, 4, -4, 2));
//        safety_monitors_level_two_.emplace_back(make_shared<SensorChecker>(1, 1, 4, -4, SENSOR_TYPE::camera2));

        safety_monitors_level_three_.emplace_back(make_shared<ActiveNodeChecker>(1, 1, 4, -4, 3));
//        safety_monitors_level_three_.emplace_back(make_shared<SensorChecker>(1, 1, 4, -4, SENSOR_TYPE::camera1));

        safety_monitors_level_four_.emplace_back(make_shared<ActiveNodeChecker>(1, 1, 4, -4, 4));
//        safety_monitors_level_four_.emplace_back(make_shared<SensorChecker>(1, 1, 4, -4, SENSOR_TYPE::cameratl));
        safety_monitors_level_four_.emplace_back(make_shared<SensorChecker>(1, 1, 4, -4, SENSOR_TYPE::lidar));
        safety_monitors_level_four_.emplace_back(make_shared<SensorChecker>(1, 1, 4, -4, SENSOR_TYPE::radar));
        safety_monitors_level_four_.emplace_back(make_shared<CarOffRoadChecker>(1, 1, 15, -15));
//        safety_monitors_level_four_.emplace_back(make_shared<ObstaclesInCriticalAreaChecker>(1, 1, 4, -4));
        safety_monitors_level_four_.emplace_back(make_shared<GeofencingChecker>(1, 1, 4, -4));
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

            ros::spinOnce();


            performSafetyTests();
            publish();


            rate.sleep();
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
