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
        
    }

    /*!
     * \brief this function disables the camera 1 and re-activates it when conditions are respected
     */
    void testAnomaly2()
    {

    }

    /*!
     * \brief this function disables the camera 2 and restarts it when conditions are respected
     */
    void testAnomaly3()
    {

    }

    /*!
     * \brief this function disables a critical node and restarts it when conditions are respected
     */
    void testAnomaly4()
    {

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

            testAnomaly1();
            testAnomaly2();
            testAnomaly3();
            testAnomaly4();

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