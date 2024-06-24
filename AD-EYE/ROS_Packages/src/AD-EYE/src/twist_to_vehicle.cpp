#include <algorithm>
#include <cmath>

#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/Float64.h>
#include "PID.h"
// #include <PID.h>
#include <functional>

class TwistToVehicle {
public:
    TwistToVehicle(ros::NodeHandle *nh)
        : P_(0.1), I_(0.0), D_(0.0), accelPIDController(P_, I_, D_, std::bind(&TwistToVehicle::pidSource, this), std::bind(&TwistToVehicle::pidOutput, this, std::placeholders::_1)) {

        linear_speed_target_ = 0.0;
        angular_speed_target_ = 0.0;
        linear_speed_current_ = 0.0;
        angular_speed_current_ = 0.0;

        accelPIDController.registerTimeFunction(&TwistToVehicle::pidTimeFunction);
        pub_acceleration = nh->advertise<std_msgs::Float64>("vehicle_acceleration_requested", 1);
        pub_steering_angle = nh->advertise<std_msgs::Float64>("steering_angle_command", 1);
    }

    void velocityRequestedCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {
        ROS_INFO("Desired TwistS: Long. Vel. = %f, Rot. Spd. = %f", msg->twist.linear.x, msg->twist.angular.z);
        linear_speed_target_ = msg->twist.linear.x;
        angular_speed_target_ = msg->twist.angular.z;

        accelPIDController.setTarget(linear_speed_target_);
    }

    void velocityCurrentCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {
        ROS_INFO("Current velocity: Long. Vel. = %f, Rot. Spd. = %f", msg->twist.linear.x, msg->twist.angular.z);
        linear_speed_current_ = msg->twist.linear.x;
        angular_speed_current_ = msg->twist.angular.z;
    }

    void updatePID() {
        accelPIDController.tick();
    }

    void updateSteering() {
        double steering_angle_command = steering(angular_speed_target_);
        sendSteeringAngle(steering_angle_command);
    }

private:
    void sendAcceleration(double req) {
        std_msgs::Float64 msg;
        msg.data = req;
        pub_acceleration.publish(msg);
    }

    void sendSteeringAngle(double req) {
        std_msgs::Float64 msg;
        msg.data = req;
        pub_steering_angle.publish(msg);
    }

    double steering(double angular_vel) {
        using namespace std;

        static const double WHEELBASE = 2.984;
        static const double MAX_STEERING_ANGLE = 0.85;
        static const double MAX_STEERING_TAN = tan(MAX_STEERING_ANGLE);

        double steer_ag_req = 0.0;
        if (linear_speed_current_ != 0.0) {
            steer_ag_req = atan(max(min(WHEELBASE * angular_vel / linear_speed_current_, MAX_STEERING_TAN), -MAX_STEERING_TAN));
        }
        return steer_ag_req;
    }

    double pidSource() {
        return linear_speed_current_;
    }

    void pidOutput(double acceleration) {
        sendAcceleration(acceleration);
    }

    static unsigned long pidTimeFunction() {
        return static_cast<unsigned long>(ros::Time::now().toSec() * 1000);
    }

private:
    double linear_speed_target_;
    double linear_speed_current_;
    double angular_speed_target_;
    double angular_speed_current_;

    double P_, I_, D_;

    ros::Publisher pub_acceleration;
    ros::Publisher pub_steering_angle;
    PIDController<double> accelPIDController;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "twist_to_vehicle");
    ros::NodeHandle nh;
    TwistToVehicle ttv(&nh);
    ros::Subscriber sub_velocity_requested = nh.subscribe("vehice_velocity_requested", 2, &TwistToVehicle::velocityRequestedCallback, &ttv);
    ros::Subscriber sub_velocity_current = nh.subscribe("vehicle_velocity_current", 2, &TwistToVehicle::velocityCurrentCallback, &ttv);
    ros::Rate r(10);
    while (ros::ok()) {
        ros::spinOnce();
        ttv.updatePID();
        ttv.updateSteering();
        r.sleep();
    }
    return 0;
}
