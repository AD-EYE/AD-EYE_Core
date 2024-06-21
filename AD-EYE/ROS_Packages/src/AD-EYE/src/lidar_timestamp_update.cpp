

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <std_msgs/Float64.h>


ros::Publisher pub;

// Globale variable to store the time value
double float_time_value = 0.0;



// Callback function to receive the time value
void floatCallback(const std_msgs::Float64::ConstPtr& msg)
{

    float_time_value = msg->data; // Update global variable

    //ROS_INFO("Received Float64 value: %f", float_time_value);

}



// Callback function to receive the pointcloud
void pointCloudCallback(const sensor_msgs::PointCloud2::ConstPtr& input)
{
    
    sensor_msgs::PointCloud2 output; //Create the output message

    output = *input; //Copy the input message to the output message

    output.header.stamp = ros::Time(float_time_value); //Change the timestamp of the output message

    pub.publish(output); //Publish the output message

    //ROS_INFO("PointCloud2 message received and republished with new timestamp\n");

}



int main(int argc, char** argv)
{
    // Initialize ROS
    ros::init(argc, argv, "pointcloud_republisher");

    // Create the ROS noeud
    ros::NodeHandle nh;

    // Subscribe to the topic that contains the pointcloud
    ros::Subscriber sub_pointcloud = nh.subscribe<sensor_msgs::PointCloud2>("ouster/points", 1, pointCloudCallback);

    // Subscribe to the topic that contains the time value
    ros::Subscriber sub_float = nh.subscribe<std_msgs::Float64>("time_topic", 1, floatCallback);

    // Initialize new publisher with a topic called ouster_updated
    pub = nh.advertise<sensor_msgs::PointCloud2>("ouster_updated", 1);

    // ROS spin
    ros::spin();

    return 0;
}
