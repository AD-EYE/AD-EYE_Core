#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "sys/time.h"

struct timeval end_cam;

void imageCallback(const sensor_msgs::Image::ConstPtr& msg)
{
    /*Display sequence number that is received from publisher*/
    std::cout<<unsigned(msg->data.front())<<std::endl;
    /*Get the timestamp at the subscriber*/
    gettimeofday(&end_cam, 0);
    long int end_time = end_cam.tv_sec;
    /*Display timestamp for the given sequence number*/
    std::cout<<end_time<<std::endl;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_subscriber");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("camera_1/image_raw", 1000, imageCallback);
    ros::spin();
    return 0;
}