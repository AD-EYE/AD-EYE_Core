#include <ros/ros.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/String.h>
#include <sstream>
#include <geometry_msgs/PoseStamped.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Array_pub");
    ros::NodeHandle nh;
 
    ros::Publisher chatter_pub = nh.advertise<std_msgs::Int16MultiArray>("/goal_pixels_coordinates", 1,true);
    //ros::Publisher chatter_pub2 = nh.advertise<std_msgs::String>("chatter", 1000);

    ros::Rate loop_rate(20);
    
    /* std_msgs::String msg2;
    std::stringstream ss;
    ss << "hello world ";
    msg2.data = ss.str();
    chatter_pub2.publish(msg2); */



    //while (ros::ok())
    //{
        //ros::spinOnce();
        ROS_INFO("Got it");
        std_msgs::Int16MultiArray msg;
        msg.data.push_back(100.0);
        msg.data.push_back(200.0);   
        chatter_pub.publish(msg);
        //loop_rate.sleep();
    //}
    ros::spin();
    
    
    return 0;
}
