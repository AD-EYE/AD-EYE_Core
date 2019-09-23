#include <ros/ros.h>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <limits>

#include <geometry_msgs/PolygonStamped.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>
#include <rcv_common_msgs/trajectory_reference.h>
#include <rcv_common_msgs/current_traj_info.h>
#include <rcv_common_msgs/SSMP_control.h>
#include <nav_msgs/Odometry.h>
#include <cpp_utils/pose_datatypes.h>
#include <std_msgs/Int32.h>

#define AUTOWARE 0
#define SSMP 1

class controlSwitch
{
private:
    // publishers and subscribers
    ros::NodeHandle &nh_;
    ros::Publisher pubSSMP_control;
    ros::Publisher pubPrescan;
    ros::Subscriber subTraj;
    ros::Subscriber subAutoware;
    ros::Subscriber subControl;

    // variables
    double SSMP_v_lin;
    double SSMP_v_ang;
    double autoware_v_lin;
    double autoware_v_ang;

    bool prescanPub = false;
    int switchCommand = -1;

    ros::Rate rate;
    geometry_msgs::TwistStamped Prescandata;

public:

    controlSwitch(ros::NodeHandle &nh) : nh_(nh), rate(40)
    {
        // Initialize node and publishers
        pubSSMP_control = nh_.advertise<rcv_common_msgs::SSMP_control>("/SSMP_control", 1, true);
        pubPrescan = nh_.advertise<geometry_msgs::TwistStamped>("/TwistS", 1, true);
        subTraj = nh_.subscribe<rcv_common_msgs::current_traj_info>("/safe_stop_traj", 100, &controlSwitch::traj_callback, this);
        subAutoware = nh_.subscribe<geometry_msgs::TwistStamped>("/autowareTwist", 100, &controlSwitch::autoware_callback, this);
        subControl = nh_.subscribe<std_msgs::Int32>("/switchCommand", 1, &controlSwitch::switchCommand_callback, this);

        // the velocities that will be send to prescan
        Prescandata.header.frame_id = "base_link";
    }

    // this callback gives the SSMP velocities to the switch
    void traj_callback(const rcv_common_msgs::current_traj_info::ConstPtr& traj){
        SSMP_v_lin = traj->v_lin;
        SSMP_v_ang = traj->v_ang;
        if(SSMP_v_lin < 0){
            SSMP_v_lin = 0;
            SSMP_v_ang = 0;
        }
        prescanPub = true;
    }

    // this callback gives the autoware velocities to the switch
    void autoware_callback(const geometry_msgs::TwistStamped::ConstPtr& carVel){
        autoware_v_lin = carVel->twist.linear.x;
        autoware_v_ang = carVel->twist.angular.z;
        prescanPub = true;
    }

    // this callback gives the command for autoware control or SSMP control (a 0 or a 1)
    void switchCommand_callback(const std_msgs::Int32::ConstPtr& msg){
        switchCommand = msg->data;
    }

    void run() {
        bool initialSwitch = false;

        while (nh_.ok()) {
            ros::spinOnce();

            if(switchCommand == AUTOWARE){
                if(prescanPub){
                    prescanPub = false;
                    initialSwitch = false;
                    Prescandata.header.stamp = ros::Time::now();
                    Prescandata.twist.linear.x = autoware_v_lin;
                    Prescandata.twist.angular.z = autoware_v_ang;
                }
            }
            else if(switchCommand == SSMP){
                // when switched, first a signal needs to be send to the safety planner that its current trajectory will be activated
                if(initialSwitch == false){
                    ROS_INFO("switched to safety channel!");
                    Prescandata.header.stamp = ros::Time::now();
                    rcv_common_msgs::SSMP_control SSMPcontrol;
                    SSMPcontrol.header.stamp = ros::Time::now();
                    SSMPcontrol.SSMP_control = 2;
                    pubSSMP_control.publish(SSMPcontrol);
                    initialSwitch = true;
                }
                if(prescanPub){
                    prescanPub = false;
                    Prescandata.header.stamp = ros::Time::now();
                    Prescandata.twist.linear.x = SSMP_v_lin;
                    Prescandata.twist.angular.z = SSMP_v_ang;
                }
            }
            pubPrescan.publish(Prescandata);
            rate.sleep();
        }
    }

};

int main(int argc, char** argv)
{
    // Initialize node
    ros::init(argc, argv, "controlSwitch");
    ros::NodeHandle nh;
    controlSwitch cs(nh);
    cs.run();
    return 0;
}
