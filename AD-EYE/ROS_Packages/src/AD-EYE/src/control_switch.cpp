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

/*!
 * \brief This class is the Switch that selects which channel control the car.
 * \details This switch can be triggered by the SafetySupervisor. Then, the switch
 * gives to the car the order either from Autoware or the safety channel, depending
 * the switch state.
 */
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
        int switchCommand = AUTOWARE;

        ros::Rate rate;
        geometry_msgs::TwistStamped Prescandata;


        /*!
        * \brief SSMP Traj Callback : Called when the SSMP velocities has changed
        * \param msg A smart pointer to the message from the topic.
        * \details Stores the SSMP velocities information.
        */
        void traj_callback(const rcv_common_msgs::current_traj_info::ConstPtr& traj){
            SSMP_v_lin = traj->v_lin;
            SSMP_v_ang = traj->v_ang;
            if(SSMP_v_lin < 0){
                SSMP_v_lin = 0;
                SSMP_v_ang = 0;
            }
            prescanPub = true;
        }

        /*!
        * \brief Autoware Callback : Called when the Autoware velocities has changed
        * \param msg A smart pointer to the message from the topic.
        * \details Stores the Autoware velocities information.
        */
        void autoware_callback(const geometry_msgs::TwistStamped::ConstPtr& carVel){
            autoware_v_lin = carVel->twist.linear.x;
            autoware_v_ang = carVel->twist.angular.z;
            prescanPub = true;
        }

        /*!
        * \brief Switch Callback : Called when the switch command has changed
        * \param msg A smart pointer to the message from the topic.
        * \details Stores the switch command
        * The command is:  0 for Autoware control ; 1 for SSMP control
        */
        void switchCommand_callback(const std_msgs::Int32::ConstPtr& msg){
            switchCommand = msg->data;
        }

    public:

        /*!
        * \brief Constructor
        * \param nh A reference to the ros::NodeHandle initialized in the main function.
        * \details Initializes the node and its components such as publishers and subscribers.
        */
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


        /*!
        * \brief The main function of the Node. Contains the main loop
        * \details First checks if the switch is for Autoware or SSMP control,
        * then publishes the right controls command.
        */
        void run() {
            bool initialSwitch = false;

            while (nh_.ok()) {
                ros::spinOnce();

                if(switchCommand == AUTOWARE){
                    if(prescanPub){
                        prescanPub = false;
                        if(initialSwitch) {
                            ROS_INFO("Switched back to the nominal channel");
                            initialSwitch = false;
                        }
                        Prescandata.header.stamp = ros::Time::now();
                        Prescandata.twist.linear.x = autoware_v_lin;
                        Prescandata.twist.angular.z = autoware_v_ang;
                    }
                }
                else if(switchCommand == SSMP){
                    // when switched, first a signal needs to be send to the safety planner that its current trajectory will be activated
                    if(initialSwitch == false){
                        ROS_INFO("Switched to safety channel!");
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
