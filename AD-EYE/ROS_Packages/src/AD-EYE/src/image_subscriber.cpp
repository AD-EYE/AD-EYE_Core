#include "ros/ros.h"
#include "sensor_msgs/Image.h"

void imageCallback(const sensor_msgs::Image::ConstPtr& msg)
{
    ROS_INFO("I heard: [%s]", msg -> data.header);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_subscriber");
    ros::NodeHandle n;
    ros::Subcriber sub = n.subscribe("chatter", 1000, imageCallback);
    ros::spin();
    return 0;
}