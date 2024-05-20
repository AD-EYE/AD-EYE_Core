#include <algorithm>
#include <cmath>

#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/Float64.h>
#include "PID.h"

class TwistToVehicle {
public:
    TwistToVehicle(ros::NodeHandle *nh) {
        linear_speed_target_ = 0.0;
        angular_speed_target_ = 0.0;
        linear_speed_current_ = 0.0;
        angular_speed_current_ = 0.0;

        P_ = 1.0;
        I_ = 0.0;
        D_ = 0.0;

        accelPIDController = PIDController<double>(P_, I_, D_, pidSource, pidOutput);
        accelPIDController.registerTimeFunction(pidTimeFunction);

        pub_acceleration = nh->advertise<std_msgs::Float64>("acceleration_command", 1);
    }

    void twistSCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {
        ROS_INFO("Desired TwistS: Long. Vel. = %s, Rot. Spd. = %s", msg->twist.linear.x, msg->twist.angular.z);
        linear_speed_target_ = msg->twist.linear.x;
        angular_speed_target_ = msg->twist.angular.z;

        accelPIDController.setTarget(linear_speed_target_);
    }

    void currentVelocityCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {
        ROS_INFO("Current velocity: Long. Vel. = %s, Rot. Spd. = %s", msg->twist.linear.x, msg->twist.angular.z);
        linear_speed_current_ = msg->twist.linear.x;
        angular_speed_current_ = msg->twist.angular.z;
    }

    void updatePID() {
        accelPIDController.tick();
    }

    void updateSteering() {
        steering(angular_speed_target_);
    }

private:
    void sendAcceleration(double req) {
        pub_acceleration.publish(req);
    }

    void steering(double angular_vel) {
        using namespace std;

        static const double WHEELBASE = 2.984;
        static const double MAX_STEERING_ANGLE = 0.85;
        static const double MAX_STEERING_TAN = tan(MAX_STEERING_ANGLE);

        if (linear_speed_current_ == 0.0)
        {
            double steer_ag_req = 0.0;
        }
        else
        {
            double steer_ag_req = atan(max(min(WHEELBASE * angular_vel / linear_speed_current_, MAX_STEERING_TAN), -MAX_STEERING_TAN));
        }
        // steer_ag_req = update_rate_limiter(steer_ag_req, spd, 10.0);
    }

    double pidSource() {
        return linear_speed_current_;
    }

    void pidOutput(double acceleration) {
        sendAcceleration(acceleration);
    }

    unsigned long pidTimeFunction() {
        unsigned long time = (ros::Time::now().toSec() * 1000);
        return time;
    }

private:
    double linear_speed_target_;
    double angular_speed_target_;
    double linear_speed_current_;
    double angular_speed_current_;

    double P_, I_, D_;

    PIDController<double> accelPIDController;
    ros::Publisher pub_acceleration;
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "twist_to_vehicle");
    ros::NodeHandle nh;
    TwistToVehicle ttv = TwistToVehicle(&nh);
    ros::Subscriber sub_twists = nh.subscribe("TwistS", 2, &TwistToVehicle::twistSCallback, &ttv);
    ros::Subscriber sub_currentv = nh.subscribe("current_velocity", 2, &TwistToVehicle::currentVelocityCallback, &ttv);
    ros::Rate r(50);
    while (1)
    {
        ttv.updatePID();
        ttv.updateSteering();
        ros::spinOnce();
        r.sleep();
    }
    return 0;
}