#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

using namespace std;

ros::Publisher string_pub;

void float64Callback(const std_msgs::Float64 msg)
{
    std_msgs::String str_msg;
    uint32_t size;
    
    str_msg.data = std::to_string(std::round(msg.data * 100.0) / 100.0); // Round to 2 decimals

    size = str_msg.data.size(); // For some reasons, the conversion of float to string gives a string with 6 decimals
    if ( size > 6){ // 6 in case of the conversion doesn't give the 6 decimals
        str_msg.data.resize(size -4); // That line remove the 4 last 0 to get the string with 2 decimals
    }

    str_msg.data = "ACCELERATE_command=" + str_msg.data;

    string_pub.publish(str_msg);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "float64_to_string_converter");
    ros::NodeHandle nh;
    ros::Subscriber float64_sub = nh.subscribe("/acceleration_requested_phy", 1, float64Callback);
    string_pub = nh.advertise<std_msgs::String>("/vehicle_commands", 1);
    ros::spin();

    return 0;
}
