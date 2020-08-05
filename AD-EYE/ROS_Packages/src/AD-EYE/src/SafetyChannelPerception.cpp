#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>

class SafetyChannelPerception {

    private:
        ros::NodeHandle &nh_;
        ros::Subscriber sub_Lidar;

        void Lidar_callback(const std_msgs::Float32MultiArray::ConstPtr& msg) {

        }

    public:
        SafetyChannelPerception(ros::NodeHandle& nh): nh_(nh)
        {
            sub_Lidar = nh.subscribe<std_msgs::Float32MultiArray>("/points_raw_float32", 1, &SafetyChannelPerception::Lidar_callback, this);
        }

}