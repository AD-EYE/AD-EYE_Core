#include <iostream>
#include <ros/ros.h>
#include <adeye_msgs/NewTwistS.h>


int main(int argc, char**argv){
    ros::init(argc, argv, "NewTwistS");
    ros::NodeHandle nh;

    ros::Publisher pub_NewTwistS = nh.advertise<adeye_msgs::NewTwistS>("NewTwistS", 10);

    ros::Rate rate(10); //10Hz

    while(ros::ok()){
        adeye_msgs::NewTwistS msg;
        float acceleration = 1.67;
        float steering_angle = 2.008;
        msg.x = acceleration;
        msg.theta = steering_angle;

        ROS_INFO("Publishing: [%f, %f]", msg.x, msg.theta);
        pub_NewTwistS.publish(msg);
        ros::spinOnce();

        rate.sleep();
    }
    return 0;
}
