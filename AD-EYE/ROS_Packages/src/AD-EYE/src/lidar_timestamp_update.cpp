

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <std_msgs/Float64.h>


ros::Publisher pub;

// Globale variable to store the time value
double float_time_value = 0.0;

// Callback function to receive the time value
void floatCallback(const std_msgs::Float64::ConstPtr& msg)
{
    float_time_value = msg->data; 
    //ROS_INFO("Received Float64 value: %f", float_time_value);
}

// Callback function to receive the pointcloud
void pointCloudCallback(const sensor_msgs::PointCloud2::ConstPtr& input)
{  
    sensor_msgs::PointCloud2 output;
    output = *input;
    uint32_t second = (uint32_t)float_time_value; //Extract the seconds from the global variable
    uint32_t nanosecond = (uint32_t)((float_time_value - (double)second) * 1000000000); //Extract the nanoseconds from the global variable
    output.header.stamp.sec = second; //Change the seconds of the timestamp of the output message   
    output.header.stamp.nsec = nanosecond; //Change the nanoseconds of the timestamp of the output message
    pub.publish(output);
    //ROS_INFO("PointCloud2 message received and republished with new timestamp\n");
}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "pointcloud_republisher");
    ros::NodeHandle nh;

    ros::Subscriber sub_pointcloud = nh.subscribe<sensor_msgs::PointCloud2>("ouster/points", 1, pointCloudCallback); // Topic that contains the pointcloud
    ros::Subscriber sub_float = nh.subscribe<std_msgs::Float64>("time_topic", 1, floatCallback); // Topic that contains the time value

    pub = nh.advertise<sensor_msgs::PointCloud2>("ouster_updated", 1); // Publisher with the updated topic called ouster_updated

    ros::spin();

    return 0;
}
