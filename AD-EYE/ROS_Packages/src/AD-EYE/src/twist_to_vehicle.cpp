#include <algorithm>
#include <cmath>

#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/Float64.h>
#include "PID.h"

using namespace std;

// TODO

class TwistToVehicle {
public:
    TwistToVehicle(ros::NodeHandle *nh) {
        linear_speed_target_ = 0.0;
        linear_speed_current_ = 0.0;
        angular_speed_target_ = 0.0;

        P_ = 1.0;
        I_ = 0.0;
        D_ = 0.0;

        pub_acceleration = nh->advertise<std_msgs::Float64>("acceleration_command", 1);
        pub_steering_angle = nh->advertise<std_msgs::Float64>("steering_angle_command", 1);
    }

    void twistSCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {
        ROS_INFO("Desired TwistS: Long. Vel. = %f, Rot. Spd. = %f", msg->twist.linear.x, msg->twist.angular.z);
        linear_speed_target_ = msg->twist.linear.x;
        angular_speed_target_ = msg->twist.angular.z;

        double acceleration_command = (linear_speed_target_ - linear_speed_current_) * P_;
        sendAcceleration(acceleration_command);

        double steering_angle_command = steering(angular_speed_target_);
        sendSteeringAngle(steering(angular_speed_target_));
    }

    void currentVelocityCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {
        ROS_INFO("Current velocity: Long. Vel. = %f, Rot. Spd. = %f", msg->twist.linear.x, msg->twist.angular.z);
        linear_speed_current_ = msg->twist.linear.x;
    }

private:
    void sendAcceleration(double req) {
        std_msgs::Float64 accel;
        accel.data = req;
        pub_acceleration.publish(accel);
    }

    void sendSteeringAngle(double req) {
        std_msgs::Float64 steering;
        steering.data = req;
        pub_steering_angle.publish(steering);
    }

    double steering(double angular_vel) {
        static const double WHEELBASE = 2.984;
        static const double MAX_STEERING_ANGLE = 0.85;
        static const double MAX_STEERING_TAN = tan(MAX_STEERING_ANGLE);

        double steer_ag_req;

        if (linear_speed_current_ == 0.0)
        {
            steer_ag_req = 0.0;
        }
        else
        {
            steer_ag_req = atan(max(min(WHEELBASE * angular_vel / linear_speed_current_, MAX_STEERING_TAN), -MAX_STEERING_TAN));
        }

        return steer_ag_req;
    }

private:
    double linear_speed_target_;
    double linear_speed_current_;
    double angular_speed_target_;

    double P_, I_, D_;

    ros::Publisher pub_acceleration;
    ros::Publisher pub_steering_angle;
};


int main(int argc, char **argv) {
    ros::init(argc, argv, "twist_to_vehicle");
    ros::NodeHandle nh;
    TwistToVehicle ttv = TwistToVehicle(&nh);
    ros::Subscriber sub_twists = nh.subscribe("TwistS", 2, &TwistToVehicle::twistSCallback, &ttv);
    ros::Subscriber sub_currentv = nh.subscribe("current_velocity", 2, &TwistToVehicle::currentVelocityCallback, &ttv);
    ros::Rate r(50);
    while (ros::ok())
    {
        ros::spinOnce();
        r.sleep();
    }
    return 0;
}