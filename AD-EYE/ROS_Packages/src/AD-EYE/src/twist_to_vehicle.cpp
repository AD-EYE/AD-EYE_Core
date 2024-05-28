#include <algorithm>
#include <cmath>

#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/Float64.h>
#include "PID.h"
// #include <PID.h>
#include <functional>

/*ADD*/
template <class T>
/*END ADD*/

/* //VERSION 1
class TwistToVehicle {
public:
    TwistToVehicle(ros::NodeHandle *nh) {
        linear_speed_target_ = 0.0;
        linear_speed_current_ = 0.0;
        angular_speed_target_ = 0.0;

        P_ = 1.0;
        I_ = 0.0;
        D_ = 0.0;

        //accelPIDController = PIDController<double>(P_, I_, D_, pidSource, pidOutput); 
        PIDController <double> accelPIDController(P_, I_, D_, pidSource, pidOutput); 
        accelPIDController.registerTimeFunction(pidTimeFunction);
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
        std_msgs::Float64 msg;
        msg.data = req;
        pub_acceleration.publish(req);
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
    //ADD
    std::function<T()> pidSource_; // Fonction pour récupérer la valeur actuelle du capteur
    std::function<void(T output)> pidOutput_; // Fonction pour définir la sortie de l'actionneur
    //END ADD

    double linear_speed_target_;
    double angular_speed_target_;
    double linear_speed_current_;
    double angular_speed_current_;

    double P_, I_, D_;

    PIDController<double> accelPIDController;
    ros::Publisher pub_acceleration;
};*/


/* VERSION 2 
class TwistToVehicle {
public:
    TwistToVehicle(ros::NodeHandle *nh)
        : P_(10.0), I_(0.0), D_(0.0), accelPIDController(P_, I_, D_, std::bind(&TwistToVehicle::pidSource, this), std::bind(&TwistToVehicle::pidOutput, this, std::placeholders::_1)) {
        
        linear_speed_target_ = 0.0;
        angular_speed_target_ = 0.0;
        linear_speed_current_ = 0.0;
        angular_speed_current_ = 0.0;

        accelPIDController.registerTimeFunction(&pidTimeFunction);
        pub_acceleration = nh->advertise<std_msgs::Float64>("acceleration_command", 1);
    }

    void twistSCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {
        ROS_INFO("Desired TwistS: Long. Vel. = %f, Rot. Spd. = %f", msg->twist.linear.x, msg->twist.angular.z);
        linear_speed_target_ = msg->twist.linear.x;
        angular_speed_target_ = msg->twist.angular.z;

        accelPIDController.setTarget(linear_speed_target_);
    }

    void currentVelocityCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {
        ROS_INFO("Current velocity: Long. Vel. = %f, Rot. Spd. = %f", msg->twist.linear.x, msg->twist.angular.z);
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
        std_msgs::Float64 msg;
        msg.data = req;
        pub_acceleration.publish(msg);
    }

    void steering(double angular_vel) {
        using namespace std;

        static const double WHEELBASE = 2.984;
        static const double MAX_STEERING_ANGLE = 0.85;
        static const double MAX_STEERING_TAN = tan(MAX_STEERING_ANGLE);

        double steer_ag_req = 0.0;
        if (linear_speed_current_ != 0.0) {
            steer_ag_req = atan(max(min(WHEELBASE * angular_vel / linear_speed_current_, MAX_STEERING_TAN), -MAX_STEERING_TAN));
        }
        //steer_ag_req = update_rate_limiter(steer_ag_req, spd, 10.0);
    }

    double pidSource() {
        return linear_speed_current_;
    }

    void pidOutput(double acceleration) {
        sendAcceleration(acceleration);
    }

    static unsigned long pidTimeFunction() {
        unsigned long time = (ros::Time::now().toSec() * 1000);
        return time;
    }

private:

    //ADD
    //std::function<T()> pidSource_; // Fonction pour récupérer la valeur actuelle du capteur
    //std::function<void(T output)> pidOutput_; // Fonction pour définir la sortie de l'actionneur
    //END ADD

    double linear_speed_target_;
    double linear_speed_current_;
    double angular_speed_target_;

    double P_, I_, D_;

    ros::Publisher pub_acceleration;
    ros::Publisher pub_steering_angle;
};




int main(int argc, char** argv)
{
    ros::init(argc, argv, "twist_to_vehicle");
    ros::NodeHandle nh;
    //TwistToVehicle ttv = TwistToVehicle(&nh);//We need to specify the type of the arguments we want to instantiate
    TwistToVehicle<ros::NodeHandle> ttv(&nh);
    //ros::Subscriber sub_twists = nh.subscribe("TwistS", 2, &TwistToVehicle::twistSCallback, &ttv);//Same 
    ros::Subscriber sub_twists = nh.subscribe("TwistS", 2, &TwistToVehicle<ros::NodeHandle>::twistSCallback, &ttv);
    //ros::Subscriber sub_currentv = nh.subscribe("current_velocity", 2, &TwistToVehicle::currentVelocityCallback, &ttv);//Same
    ros::Subscriber sub_currentv = nh.subscribe("current_velocity", 2, &TwistToVehicle<ros::NodeHandle>::currentVelocityCallback, &ttv);
    ros::Rate r(50);
    while (ros::ok())
    {
        ros::spinOnce();
        r.sleep();
    }
    return 0;

}

*/

class TwistToVehicle {
public:
    TwistToVehicle(ros::NodeHandle *nh)
        : P_(10.0), I_(0.0), D_(0.0), accelPIDController(P_, I_, D_, std::bind(&TwistToVehicle::pidSource, this), std::bind(&TwistToVehicle::pidOutput, this, std::placeholders::_1)) {
        
        linear_speed_target_ = 0.0;
        angular_speed_target_ = 0.0;
        linear_speed_current_ = 0.0;
        angular_speed_current_ = 0.0;

        accelPIDController.registerTimeFunction(&TwistToVehicle::pidTimeFunction);
        pub_acceleration = nh->advertise<std_msgs::Float64>("acceleration_command", 1);
        pub_steering_angle = nh->advertise<std_msgs::Float64>("steering_angle_command", 1);
    }

    void twistSCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {
        ROS_INFO("Desired TwistS: Long. Vel. = %f, Rot. Spd. = %f", msg->twist.linear.x, msg->twist.angular.z);
        linear_speed_target_ = msg->twist.linear.x;
        angular_speed_target_ = msg->twist.angular.z;

        accelPIDController.setTarget(linear_speed_target_);
    }

    void currentVelocityCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {
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
    TwistToVehicle<ros::NodeHandle> ttv(&nh);
    ros::Subscriber sub_twists = nh.subscribe("TwistS", 2, &TwistToVehicle<ros::NodeHandle>::twistSCallback, &ttv);
    ros::Subscriber sub_currentv = nh.subscribe("current_velocity", 2, &TwistToVehicle<ros::NodeHandle>::currentVelocityCallback, &ttv);
    ros::Rate r(50);
    while (ros::ok()) {
        ros::spinOnce();
        ttv.updatePID();
        ttv.updateSteering();
        r.sleep();
    }
    return 0;
}



