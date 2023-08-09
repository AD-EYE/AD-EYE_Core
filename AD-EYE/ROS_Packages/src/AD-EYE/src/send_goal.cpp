#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>
#include <cmath>
#include <iostream>
#include <tf/transform_broadcaster.h>
#include <stdlib.h>
#include <tuple>

class SendGoal
{
  private:
    ros::NodeHandle& nh_;
    ros::Publisher pub_goal_;

    double x_position_world_coordinate_ = 126.5, y_position_world_coordinate_ = 171.0, z_position_world_coordinate_ = 0;
    // Orientation Coordinates, harcoded for now //
    
    double cr = cos(x_position_world_coordinate_ * 0.5);
    double sr = sin(x_position_world_coordinate_ * 0.5);
    double cp = cos(y_position_world_coordinate_ * 0.5);
    double sp = sin(y_position_world_coordinate_ * 0.5);
    double cy = 1;
    double sy = 0;
    
    // double w_orientation_world_coordinate_ = cr * cp * cy + sr * sp * sy, x_orientation_world_coordinate_ = sr * cp * cy - cr * sp * sy,
    //        y_orientation_world_coordinate_ = cr * sp * cy + sr * cp * sy, z_orientation_world_coordinate_ = cr * cp * sy - sr * sp * cy;

    double w_orientation_world_coordinate_ = 1, x_orientation_world_coordinate_ = 0,
        y_orientation_world_coordinate_ = 0, z_orientation_world_coordinate_ = 0;

    geometry_msgs::PoseStamped pose_stamped_;

    ros::Rate rate_;

  public:
    SendGoal(ros::NodeHandle& nh) : nh_(nh), rate_(50)
    {
        // Initialize node and publishers
        pub_goal_ = nh_.advertise<geometry_msgs::PoseStamped>("/adeye/goals", 1, true);
    }

    void run()
    {
        bool test = true;
        while (nh_.ok())
        {
            rate_.sleep();
            ros::spinOnce();
            if (test) {
                test = false;
                pose_stamped_.header.frame_id = "world";
                pose_stamped_.pose.position.x = round(x_position_world_coordinate_);
                pose_stamped_.pose.position.y = round(y_position_world_coordinate_);
                pose_stamped_.pose.position.z = z_position_world_coordinate_;

                // Orientation coordinates
                pose_stamped_.pose.orientation.x = x_orientation_world_coordinate_;
                pose_stamped_.pose.orientation.y = y_orientation_world_coordinate_;
                pose_stamped_.pose.orientation.z = z_orientation_world_coordinate_;
                pose_stamped_.pose.orientation.w = w_orientation_world_coordinate_;

                pub_goal_.publish(pose_stamped_);
            }
        }
    }
};

int main(int argc, char** argv)
{
    // Initialize node
    ros::init(argc, argv, "sendgoal");
    ros::NodeHandle nh;
    SendGoal goal(nh);
    goal.run();
    return 0;
}
