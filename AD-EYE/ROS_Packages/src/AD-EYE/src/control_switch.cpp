#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>
#include <rcv_common_msgs/current_traj_info.h>
#include <rcv_common_msgs/SSMP_control.h>
#include <cpp_utils/pose_datatypes.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>

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
        ros::Publisher pub_SSMP_control_;
        ros::Publisher pub_out_command_;
        ros::Publisher sub_adeye_local_planner_replan_;
        ros::Subscriber sub_safe_stop_trajectory_;
        ros::Subscriber sub_autoware_command_;
        ros::Subscriber sub_switch_control_;

        // variables
        double SSMP_twist_lin_x_;
        double SSMP_twist_ang_z_;
        double autoware_twist_lin_x_;
        double autoware_twist_ang_z_;

        bool new_command_message_ = false;
        int switch_command_ = AUTOWARE;

        ros::Rate rate_;
        geometry_msgs::TwistStamped out_twist_command_;


        /*!
        * \brief SSMP Traj Callback : Called when the SSMP velocities has changed
        * \param msg A smart pointer to the message from the topic.
        * \details Stores the SSMP velocities information.
        */
        void safeStopTrajectoryCallback(const rcv_common_msgs::current_traj_info::ConstPtr& traj){
            SSMP_twist_lin_x_ = traj->v_lin;
            SSMP_twist_ang_z_ = traj->v_ang;
            if(SSMP_twist_lin_x_ < 0){
                SSMP_twist_lin_x_ = 0;
                SSMP_twist_ang_z_ = 0;
            }
            new_command_message_ = true;
        }

        /*!
        * \brief Autoware Callback : Called when the Autoware velocities has changed
        * \param msg A smart pointer to the message from the topic.
        * \details Stores the Autoware velocities information.
        */
        void autowareCommandCallback(const geometry_msgs::TwistStamped::ConstPtr& carVel){
            autoware_twist_lin_x_ = carVel->twist.linear.x;
            autoware_twist_ang_z_ = carVel->twist.angular.z;
            new_command_message_ = true;
        }

        /*!
        * \brief Switch Callback : Called when the switch command has changed
        * \param msg A smart pointer to the message from the topic.
        * \details Stores the switch command
        * The command is:  0 for Autoware control ; 1 for SSMP control
        */
        void switchCommandCallback(const std_msgs::Int32::ConstPtr& msg){
            switch_command_ = msg->data;
        }

        /*!
        * \brief Tells SSMP node that the current trajectory will be followed
        */
        void lockSSMP() const {
            rcv_common_msgs::SSMP_control SSMPcontrol;
            SSMPcontrol.header.stamp = ros::Time::now();
            SSMPcontrol.SSMP_control = 2;
            pub_SSMP_control_.publish(SSMPcontrol);
        }

        /*!
        * \brief Tells SSMP node that the current trajectory will not be followed anymore
        */
        void unlockSSMP() const {
            rcv_common_msgs::SSMP_control SSMPcontrol;
            SSMPcontrol.header.stamp = ros::Time::now();
            SSMPcontrol.SSMP_control = 1;
            pub_SSMP_control_.publish(SSMPcontrol);
        }

    public:

        /*!
        * \brief Constructor
        * \param nh A reference to the ros::NodeHandle initialized in the main function.
        * \details Initializes the node and its components such as publishers and subscribers.
        */
        controlSwitch(ros::NodeHandle &nh) : nh_(nh), rate_(40)
        {
            // Initialize node and publishers
            pub_SSMP_control_ = nh_.advertise<rcv_common_msgs::SSMP_control>("/SSMP_control", 1, true);
            pub_out_command_ = nh_.advertise<geometry_msgs::TwistStamped>("/TwistS", 1, true);
            sub_adeye_local_planner_replan_ = nh_.advertise<std_msgs::Bool>("/adeye/local_planner_replan", 1, true);
            sub_safe_stop_trajectory_ = nh_.subscribe<rcv_common_msgs::current_traj_info>("/safe_stop_traj", 100, &controlSwitch::safeStopTrajectoryCallback, this);
            sub_autoware_command_ = nh_.subscribe<geometry_msgs::TwistStamped>("/autowareTwist", 100, &controlSwitch::autowareCommandCallback, this);
            sub_switch_control_ = nh_.subscribe<std_msgs::Int32>("/switch_command", 1, &controlSwitch::switchCommandCallback, this);

            // the velocities that will be send to prescan
            out_twist_command_.header.frame_id = "base_link";
        }


    void autowareLocalReplan() const {
        std_msgs::Bool bool_msg;
        bool_msg.data = true;
        sub_adeye_local_planner_replan_.publish(bool_msg);
    }

/*!
        * \brief The main function of the Node. Contains the main loop
        * \details First checks if the switch is for Autoware or SSMP control,
        * then publishes the right controls command.
        */
        void run() {
            bool ssmp_trajectory_locked = false;

            while (nh_.ok()) {
                ros::spinOnce();

                switch (switch_command_) {
                    case AUTOWARE:
                        unlockSSMP();
                        if(ssmp_trajectory_locked) {
                            ROS_INFO("Switched back to the nominal channel");
                            autowareLocalReplan();
                        }
                        ssmp_trajectory_locked = false;
                        if(new_command_message_){
                            out_twist_command_.header.stamp = ros::Time::now();
                            out_twist_command_.twist.linear.x = autoware_twist_lin_x_;
                            out_twist_command_.twist.angular.z = autoware_twist_ang_z_;
                        }
                        break;

                    case SSMP:
                        if(!ssmp_trajectory_locked){
                            ROS_INFO("Switched to safety channel!");
                        }
                        lockSSMP();
                        ssmp_trajectory_locked = true;
                        if(new_command_message_){
                            out_twist_command_.header.stamp = ros::Time::now();
                            out_twist_command_.twist.linear.x = SSMP_twist_lin_x_;
                            out_twist_command_.twist.angular.z = SSMP_twist_ang_z_;
                        }
                        break;
                }

                new_command_message_ = false;
                pub_out_command_.publish(out_twist_command_);
                rate_.sleep();
            }
        }



};

int main(int argc, char** argv)
{
    // Initialize node
    ros::init(argc, argv, "controlSwitch");
    ros::NodeHandle nh;
    controlSwitch control_switch(nh);
    control_switch.run();
    return 0;
}
