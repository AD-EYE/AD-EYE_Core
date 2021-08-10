#include <ros/ros.h> // ROS
#include <grid_map_ros/grid_map_ros.hpp> // for ROS gridmap support

//basic libraries used in the node
#include <string>
#include <cmath>
#include <stdlib.h>

// ROS messages
#include <grid_map_msgs/GridMap.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Float32MultiArray.h>

namespace kpi
{
    // Distance of closest encounter
    float dce;
    // Time to closest encounter
    float ttce;

    // Margin to collision
    float mtc;
    // Time to collision
    float ttc;
    // Modified time to collision
    float mttc;
    // Worst time to collision
    float wttc;
    // Extended time to collision
    float ettc;
    // Time to accident
    float ta;

    // Time headway
    float thw;

    // Proportion of stopping distance
    float psd;
    // Time to steer
    float tts;
    // Time to break
    float ttb;

    // Time to kickdown
    float ttk;
}

class RiskEnvelopeComputation
{
private:
    // Publisher and subscribers
    ros::NodeHandle &nh_;
    ros::Publisher pub_kpi_; // Different KPIs will be published in an array, it will be easier to manipulate.
    ros::Subscriber sub_gridmap_;
    ros::Subscriber sub_position_;
    ros::Subscriber sub_current_velocity_;
    // Maybe a topic to have the weather??

    // Number of KPIs
    static const int nb_kpi_ = 13;
    // Array that stores different KPIs
    std_msgs::Float32MultiArray kpi_array_;

    //Ros utils
    ros::Rate rate_;

    void gridmapCallback(const grid_map_msgs::GridMap::ConstPtr& msg) {

    }

    void positionCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {

    }

    void currentVelocityCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {

    }

public:

    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initializes the node and its components such as publishers and subscribers.
     */
    RiskEnvelopeComputation(ros::NodeHandle& nh) : nh_(nh), rate_(1)
    {
        pub_kpi_ = nh.advertise<std_msgs::Float32MultiArray>("/kpi_compute", 1);
        sub_gridmap_ = nh.subscribe<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, &RiskEnvelopeComputation::gridmapCallback, this);
        sub_position_ = nh.subscribe<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, &RiskEnvelopeComputation::positionCallback, this);
        sub_current_velocity_ = nh.subscribe<geometry_msgs::TwistStamped>("/current_velocity", 1, &RiskEnvelopeComputation::currentVelocityCallback, this);

        rate_ = ros::Rate(20);
    }

    void run() {
        while(nh_.ok()) {
            ros::spinOnce();
            pub_kpi_.publish(kpi_array_);
            rate_.sleep();
        }
    }
};

int main(int argc, char** argv) {
    // Initialize node
    ros::init(argc, argv, "computation");
    ros::NodeHandle nh;

    RiskEnvelopeComputation rec(nh);
    rec.run();

    return 0;
}
