#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <jsk_recognition_msgs/PolygonArray.h>

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


class ScenarioPresentation
{
private:
    ros::NodeHandle &nh_;
    ros::Subscriber sub_current_pose_;

    geometry_msgs::Pose pose_ego_car_;

    // For the first test: lidar failure
    bool first_test_started_ = false;
    bool first_test_done_ = false;
    double duration_first_test_;
    double begin_time_first_test_;

    // For the second test: camera 1 failure
    bool second_test_started_ = false;
    bool second_test_done_ = false;
    double duration_second_test_;
    double begin_time_second_test_;

    // For the third test: camera 2 failure
    bool third_test_started_ = false;
    bool third_test_done_ = false;
    double duration_third_test_;
    double begin_time_third_test_;

    // For the fourth test: critical node level 1
    bool fourth_test_started_ = false; // boolean that indicates if the fourth test has started or not
    bool fourth_test_done_ = false; // boolean that indicates if the fourth test is done or not
    double duration_fourth_test_; // time elapsed from the moment when the fourth anomaly began.
    double begin_time_fourth_test_; // beginning time of the fourth anomaly

    /*!
     * \brief this function is called when the position changed
     * \param msg a smart pointer to the topic message
     */
    void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg)
    {
        pose_ego_car_ = msg->pose;
    }

    /*!
     * \brief this function disables the lidar and re-activates it when conditions are respected
     */
    void testAnomaly1()
    {
        // Position for condition to disable and re-enable the node that manage lidar.
        grid_map::Position position_lidar_killed;
        position_lidar_killed = grid_map::Position(36, 76);
        // The margin of error for the position
        double error_margin_lidar = 10;
        // The duration during when the lidar has to be disabled.
        double duration_lidar_killed = 5; // to verify

        if((pose_ego_car_.position.x >= (position_lidar_killed.x() - error_margin_lidar)) && (pose_ego_car_.position.x <= (position_lidar_killed.x() + error_margin_lidar))
            && (pose_ego_car_.position.y >= (position_lidar_killed.y() - error_margin_lidar)) && (pose_ego_car_.position.y <= (position_lidar_killed.y() + error_margin_lidar))
            && (!first_test_started_ && !first_test_done_))
        {
            // Kill the node that send message from the lidar.
            system("rosnode kill /point_cloud_receiver");
            first_test_started_ = true;
            begin_time_first_test_ = ros::Time::now().toSec();
        }
        if(first_test_started_)
        {
            duration_first_test_ = ros::Time::now().toSec() - begin_time_first_test_;
            // Condition of time
            if(duration_first_test_ >= duration_lidar_killed)
            {
                if(fork() == 0) {
                    system("rosrun adeye point_cloud_receiver.py"); // restart the node in parallel
                }
                ROS_INFO("Restart lidar");
                first_test_started_ = false;
                first_test_done_ = true;
            }
        }
    }

    /*!
     * \brief this function disables the camera 1 and re-activates it when conditions are respected
     */
    void testAnomaly2()
    {
        // Position for condition to disable and re-enable the node that manage camera 1.
        grid_map::Position position_camera1_killed;
        position_camera1_killed = grid_map::Position(73, 75);
        // The margin of error for the position
        double error_margin_camera1 = 10;
        // The duration during when the camera1 is disabled
        double duration_camera1_killed = 10;

        if((pose_ego_car_.position.x >= (position_camera1_killed.x() - error_margin_camera1)) && (pose_ego_car_.position.x <= (position_camera1_killed.x() + error_margin_camera1))
            && (pose_ego_car_.position.y >= (position_camera1_killed.y() - error_margin_camera1)) && (pose_ego_car_.position.y <= (position_camera1_killed.y() + error_margin_camera1))
            && first_test_done_ && (!second_test_started_ && !second_test_done_))
        {
            // Kill the node for detection of camera 1 objects
            system("rosnode kill /camera_1/vision_ssd_detect");
            second_test_started_ = true;
            begin_time_second_test_ = ros::Time::now().toSec();
        }
        if(second_test_started_)
        {
            duration_second_test_ = ros::Time::now().toSec() - begin_time_second_test_;
            // Condition of time
            if(duration_second_test_ >= duration_camera1_killed)
            {
                if(fork() == 0) {
                    // restart the node in parallel
                    system("roslaunch adeye activate_camera_1.launch");
                }
                ROS_INFO("Restart camera 1 detection");
                second_test_started_ = false;
                second_test_done_ = true;
            }
        }
    }

    /*!
     * \brief this function disables the camera 2 and restarts it when conditions are respected
     */
    void testAnomaly3()
    {
        // Position for condition to disable and re-enable the node that manage camera 2.
        grid_map::Position position_camera2_killed;
        position_camera2_killed = grid_map::Position(50, 75);
        // The margin of error for the position
        double error_margin_camera2 = 10;
        // The duration during when the camera 2 is disabled
        double duration_camera2_killed = 10;

        if((pose_ego_car_.position.x >= (position_camera2_killed.x() - error_margin_camera2)) && (pose_ego_car_.position.x <= (position_camera2_killed.x() + error_margin_camera2))
            && (pose_ego_car_.position.y >= (position_camera2_killed.y() - error_margin_camera2)) && (pose_ego_car_.position.y <= (position_camera2_killed.y() + error_margin_camera2))
            && first_test_done_ && second_test_done_ && (!third_test_started_ && !third_test_done_))
        {
            // Kill the node for detection of camera 2 objects
            system("rosnode kill /camera_2/vision_ssd_detect");
            third_test_started_ = true;
            begin_time_third_test_ = ros::Time::now().toSec();
        }
        if(third_test_started_)
        {
            duration_third_test_ = ros::Time::now().toSec() - begin_time_third_test_;
            // Condition of time
            if(duration_third_test_ >= duration_camera2_killed)
            {
                if(fork() == 0) {
                    // restart the node in parallel
                    system("roslaunch adeye activate_camera_2.launch");
                }
                ROS_INFO("Restart camera 2");
                third_test_started_ = false;
                third_test_done_ = true;
            }
        }
    }

    /*!
     * \brief this function disables a critical node and restarts it when conditions are respected
     */
    void testAnomaly4()
    {
        // Position for condition to disable and re-enable the critical node.
        grid_map::Position position_critical_node_killed;
        position_critical_node_killed = grid_map::Position(80, 150);
        // The margin of error for the position
        double error_margin_critical_node = 10;
        // The duration during when the node is disabled
        double duration_critical_node_killed = 5;

        if((pose_ego_car_.position.x >= (position_critical_node_killed.x() - error_margin_critical_node)) && (pose_ego_car_.position.x <= (position_critical_node_killed.x() + error_margin_critical_node))
            && (pose_ego_car_.position.y >= (position_critical_node_killed.y() - error_margin_critical_node)) && (pose_ego_car_.position.y <= (position_critical_node_killed.y() + error_margin_critical_node))
            && first_test_done_ && second_test_done_ && third_test_done_ && (!fourth_test_started_ && !fourth_test_done_))
        {
            // Kill the critical node level 1
            system("rosnode kill /visualization");
            fourth_test_started_ = true;
            begin_time_fourth_test_ = ros::Time::now().toSec();
        }
        if(fourth_test_started_)
        {
            duration_fourth_test_ = ros::Time::now().toSec() - begin_time_fourth_test_;
            // Condition of time
            if(duration_fourth_test_ >= duration_critical_node_killed)
            {
                if(fork() == 0) {
                    system("rosrun adeye_utils layerVisualizer /safety_planner_gridmap SensorSectors"); // restart the node in parallel
                }
                ROS_INFO("Restart critical node");
                fourth_test_started_ = false;
                fourth_test_done_ = true;
            }
        }
    }

public:

    /*!
    * \brief Constructor
    */
    ScenarioPresentation(ros::NodeHandle &nh, int argc, char **argv): nh_(nh)
    {
        sub_current_pose_ = nh_.subscribe<geometry_msgs::PoseStamped>("/ground_truth_pose", 100, &ScenarioPresentation::poseCallback, this);
    }

    void run()
    {
        ros::Rate rate(20);
        while(nh_.ok())
        {
            ros::spinOnce();

            first_test_done_ = true;
            second_test_done_ = true;
            // testAnomaly1();
            // testAnomaly2();
            testAnomaly3();
            // testAnomaly4();

            rate.sleep();
        }

    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "scenarioPresentation");
    ros::NodeHandle nh;
    ScenarioPresentation scenarioPresentation(nh, argc, argv);
    scenarioPresentation.run();
    return 0;
}