#include <ros/ros.h> // ROS
#include <grid_map_ros/grid_map_ros.hpp> // for ROS gridmap support

//basic libraries used in the node
#include <string>
#include <cmath>
#include <stdlib.h>

// ROS messages
#include <grid_map_msgs/GridMap.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Float32MultiArray.h>
#include <autoware_msgs/Lane.h>

namespace kpi
{
    // Distance of closest encounter
    float dce;
    // Time to closest encounter
    float ttce;
    // Margin to collision
    float mtc;
    // Time to collision
    float ttc;
    // Modified time to collision
    float mttc;
    // Worst time to collision
    float wttc;
    // Extended time to collision
    float ettc;
    // Time to accident
    float ta;
    // Time headway
    float thw;
    // Proportion of stopping distance
    float psd;
    // Time to steer
    float tts;
    // Time to break
    float ttb;
    // Time to kickdown
    float ttk;
}

class RiskEnvelopeComputation
{
private:
    // Publisher and subscribers
    ros::NodeHandle &nh_;
    ros::Publisher pub_kpi_; // Different KPIs will be published in an array, it will be easier to manipulate.
    ros::Subscriber sub_gridmap_;
    ros::Subscriber sub_position_;
    ros::Subscriber sub_velocity_;
    ros::Subscriber sub_trajectory_ego_;
    ros::Subscriber sub_other_cars_;

    // Array that stores information of different KPIs
    std_msgs::Float32MultiArray kpi_array_;

    // Parameters for the update of KPIs
    bool ttc_first_callback_ = true;

    // Time parameters
    float time_ = 0;
    float time_old_ = 0;

    // Velocity of the ego car
    float velocity_ego_ = 0;
    float velocity_ego_old_ = 0;
    float acceleration_ego_ = 0;
    bool velocity_ego_callback_ = false;

    // Position of the ego car
    float x_ego_;
    float y_ego_;
    float x_ego_old_;
    float y_ego_old_;
    bool position_ego_callback_ = false;

    // The trajectory of the ego car
    autoware_msgs::Lane trajectory_;
    bool trajectory_callback_ = false;

    // For the Dynamic and Static objects
    grid_map_msgs::GridMap map_;
    bool gridmap_callback_ = false;

    // For other cars
    geometry_msgs::PoseArray other_cars_;
    float x_other_cars_;
    float y_other_cars_;
    float x_other_cars_old_;
    float y_other_cars_old_;
    float velocity_other_cars_;
    bool other_cars_callback_ = false;

    //Dimensions
    float length_ego_ = 4.6;
    float width_ego_ = 2.2;

    //Ros utils
    ros::Rate rate_;

    /*!
     * \brief Update the value of KPI Time to Collision.
     * \details TTC is defined as D/dV,
     * D the distance between ego car and the other car,
     * dV the difference of velocitybetween two vehicles.
     */
    void ttcUpdate() {
        // the distance between other cars and the ego car
        float d;
        // the difference between the velocity of the ego car and the other car
        float delta_v;
        // The number of other cars
        size_t N_other = other_cars_.poses.size();
        // Search the closest other car in the trajectory of the ego car
        d = pow(pow(other_cars_.poses.at(0).position.x - x_ego_, 2) + pow(other_cars_.poses.at(0).position.y - y_ego_, 2), 0.5);
        for(int i = 0; i < (int)N_other; i++) {
            grid_map::Position pos_other;
            pos_other.x() = other_cars_.poses.at(i).position.x;
            pos_other.y() = other_cars_.poses.at(i).position.y;
            grid_map::Position pos_trajectory;
            pos_trajectory.x() = trajectory_.waypoints.at(i).pose.pose.position.x;
            pos_trajectory.y() = trajectory_.waypoints.at(i).pose.pose.position.y;
            // If the other car is in the trajectory
            if((pos_other.x() = pos_trajectory.x()) && (pos_other.y() = pos_trajectory.y())){
                // If the other car is the closest of all already tested other cars
                if(pow(pow(other_cars_.poses.at(i).position.x - x_ego_, 2) + pow(other_cars_.poses.at(i).position.y - y_ego_, 2), 0.5) < d) {
                    d = pow(pow(other_cars_.poses.at(i).position.x - x_ego_, 2) + pow(other_cars_.poses.at(i).position.y - y_ego_, 2), 0.5);
                    x_other_cars_ = other_cars_.poses.at(i).position.x;
                    y_other_cars_ = other_cars_.poses.at(i).position.y;
                }
            }
            
        }
        // If this is the first time the function is called, the velocity can't be computed.
        if(!ttc_first_callback_) {
            // The value of the velocity of other cars
            velocity_other_cars_ = pow(pow((x_other_cars_ - x_other_cars_old_)/(time_ - time_old_), 2) + pow((y_other_cars_ - y_other_cars_old_)/(time_ - time_old_), 2), 0.5);
            delta_v = velocity_other_cars_ - velocity_ego_;
        }

        kpi::ttc = d / delta_v;

        // Update the position of other car
        x_other_cars_old_ = x_other_cars_;
        y_other_cars_old_ = y_other_cars_;
    }
    
    /*!
     * \brief gridmapCallback: called when information of the gridmap has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Extracts and stores information from the layers DynamicObjects and StaticObjects.
     */
    void gridmapCallback(const grid_map_msgs::GridMap::ConstPtr& msg) {
        map_ = *msg;
        gridmap_callback_ = true;
    }

    /*!
     * \brief positionCallback: called when position of the ego car has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Extracts and stores the position of the ego car.
     */
    void positionCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
        x_ego_ = msg->pose.position.x;
        y_ego_ = msg->pose.position.y;
        position_ego_callback_ = true;
    }

    /*!
     * \brief currentVelocityCallback: called when velocity of the ego car has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Extracts and stores the velocity of the ego car.
     */
    void velocityCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {
        velocity_ego_ = pow(pow(msg->twist.linear.x, 2) + pow(msg->twist.linear.y, 2), 0.5);
        velocity_ego_callback_ = true;
    }

    /*!
     * \brief trajectoryCallback: called when trajectory of the ego car has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the trajectory of the ego car.
     */
    void trajectoryEgoCallback(const autoware_msgs::Lane::ConstPtr& msg) {
        trajectory_ = *msg;
        trajectory_callback_ = true;
    }

    /*!
     * \brief trajectoryCallback: called when trajectory of the ego car has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the trajectory of the ego car.
     */
    void otherCarsCallback(const geometry_msgs::PoseArray::ConstPtr& msg) {
        other_cars_ = *msg;
        other_cars_callback_ = true;
    }

public:

    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initializes the node and its components such as publishers and subscribers.
     */
    RiskEnvelopeComputation(ros::NodeHandle& nh) : nh_(nh), rate_(1)
    {
        pub_kpi_ = nh_.advertise<std_msgs::Float32MultiArray>("/kpi_compute", 1);
        sub_position_ = nh_.subscribe<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, &RiskEnvelopeComputation::positionCallback, this);
        sub_velocity_ = nh_.subscribe<geometry_msgs::TwistStamped>("/current_velocity", 1, &RiskEnvelopeComputation::velocityCallback, this);
        sub_trajectory_ego_ = nh_.subscribe<autoware_msgs::Lane>("/final_waypoints", 1, &RiskEnvelopeComputation::trajectoryEgoCallback, this);
        sub_other_cars_ = nh_.subscribe<geometry_msgs::PoseArray>("/pose_otherCar", 1, &RiskEnvelopeComputation::otherCarsCallback, this);
        sub_gridmap_ = nh_.subscribe<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, &RiskEnvelopeComputation::gridmapCallback, this);
        
        rate_ = ros::Rate(20);
    }

    void run() {
        while(nh_.ok()) {
            ros::spinOnce();

                if(other_cars_callback_) {
                    ttcUpdate();
                }
                else {
                    kpi::ttc = -1; // Value if there is no other cars on the trajectory
                }

                std::cout<<"TTC = "<<kpi::ttc<<std::endl; // Test if the ttc is well updated.

            // This array contains information about all KPIs
            kpi_array_.data = {kpi::dce, kpi::ttce, kpi::mtc, kpi::ttc, kpi::mttc, kpi::wttc, kpi::ettc, kpi::ta, kpi::thw, kpi::psd, kpi::tts, kpi::ttb, kpi::ttk};
            pub_kpi_.publish(kpi_array_);

            rate_.sleep();
        }
    }
};

int main(int argc, char** argv) {
    // Initialize node
    ros::init(argc, argv, "computation");
    ros::NodeHandle nh;

    RiskEnvelopeComputation rec(nh);
    rec.run();

    return 0;
}
