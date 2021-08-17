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

using namespace grid_map;

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

    //Ros utils
    ros::Rate rate_;
    float frequency_ = 20; // this value should be aligned with the frequency value used in the GridMapCreator_node

    // Array that stores information of different KPIs
    std_msgs::Float32MultiArray kpi_array_;

    // Parameters for the update of KPIs
    bool ttc_first_callback_ = true;
    bool mttc_first_callback_ = true;
    bool mttc_second_callback_ = true;

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
    GridMap map_;
    bool gridmap_callback_ = false;

    // For other cars
    geometry_msgs::PoseArray other_cars_;
    float x_other_cars_;
    float y_other_cars_;
    float x_other_cars_old_;
    float y_other_cars_old_;
    float velocity_other_cars_;
    float velocity_other_cars_old_;
    float acceleration_other_cars_;
    bool other_cars_callback_ = false;
    // parameter to know if there is other car in the trajectory
    bool car_in_trajectory_ = false;
    bool object_in_trajectory_ = false;

    //Dimensions
    float length_ego_ = 4.6;
    float width_ego_ = 2.2;

    // Time range useful to compute velocity of other cars and acceleration.
    float dt_ = 1 / frequency_;

    /*!
     * \brief Update the value of KPI Time to Collision.
     * \details TTC is defined as D/dV,
     * D the distance between ego car and the other car,
     * dV the difference of velocity between the two vehicles.
     */
    void ttcUpdate() {
        // the distance between other cars and the ego car
        float d;
        // the difference between the velocity of the ego car and the other car
        float delta_v;
        // Reset the value
        car_in_trajectory_ = false;

        // The number of points in the trajectory
        size_t N_pts_traj = trajectory_.waypoints.size();
        // For all points in trajectory, check if the position of other car is in it.
        for(int i = 0; i < (int)N_pts_traj; i++) {
            float x_pos_trajectory = trajectory_.waypoints.at(i).pose.pose.position.x; // x coordinate of the trajectory point to compare with the position of other car
            float y_pos_trajectory = trajectory_.waypoints.at(i).pose.pose.position.y; // y coordinate of the trajectory point to compare with the position of other car

            float pose_x; // x coordinate of other car to compare with the trajectory
            float pose_y; // y coordinate of other car to compare with the trajectory

            // Initialize the values to compare
            pose_x = other_cars_.poses.at(0).position.x;
            pose_y = other_cars_.poses.at(0).position.y;
            d = pow(pow(pose_x - x_ego_, 2) + pow(pose_y - y_ego_,2), 0.5);

            // The number of other cars
            size_t N_other = other_cars_.poses.size();
            // Search the closest other car in the trajectory of the ego car
            for(int j = 0; j < (int)N_other; j++) {
                pose_x = other_cars_.poses.at(j).position.x;
                pose_y = other_cars_.poses.at(j).position.y;
                float distance_to_traj = pow(pow(x_pos_trajectory - pose_x, 2) + pow(y_pos_trajectory - pose_y, 2), 0.5);
                if(distance_to_traj <= width_ego_ / 2) { // If the car is close enough of the trajectory of the ego car.
                    float distance_to_ego = pow(pow(pose_x - x_ego_, 2) + pow(pose_y - y_ego_,2), 0.5);
                    if(distance_to_ego < d) { // If the other car is the closest of all other cars tested
                        d = distance_to_ego;
                        x_other_cars_ = pose_x;
                        y_other_cars_ = pose_y;
                    }
                    car_in_trajectory_ = true;
                }
            }
        }

        // If there is no car in the trajectory of the ego car, TTC can't be computed.
        if(!car_in_trajectory_) {
            kpi::ttc = -1; // Default value if TTC can't be computed.
        }
        else {
            // If this is the first time the function is called, the velocity can't be computed.
            if(!ttc_first_callback_) {
                // The value of the velocity of other cars is obtained by derivation of the position
                float v_x = (x_other_cars_ - x_other_cars_old_)/dt_; // x component of the velocity
                float v_y = (y_other_cars_ - y_other_cars_old_)/dt_; // y component of the velocity
                velocity_other_cars_ = pow(pow(v_x, 2) + pow(v_y, 2), 0.5);
                delta_v = velocity_ego_ - velocity_other_cars_;

                kpi::ttc = d / delta_v; // If the time is negative, it means that there is no risk of collision, the other car drive fatser than the ego.
            }
            else {
                kpi::ttc = -1; // Default value if TTC can't be computed.
            }
            ttc_first_callback_ = false;
        }

        // Update the position of other car and ego car
        x_other_cars_old_ = x_other_cars_;
        y_other_cars_old_ = y_other_cars_;
        x_ego_old_ = x_ego_;
        y_ego_old_ = y_ego_;
    }

    /*!
     * \brief Update the value of KPI Modified Time to Collision.
     * \details MTTC is defined as (+/-(dV^2 + 2*da*D)^0.5 - dV) / da
     * D is the distance between ego car and the other car,
     * dV is the difference of velocity between ego and other car,
     * da is the difference of acceleration between ego and other car.
     * If da = 0, MTTC = TTC.
     */
    void mttcUpdate() {
        // the distance between other cars and the ego car
        float d;
        // the difference between the velocity of the ego car and the other car
        float delta_v;
        // the difference between the acceleration of the ego car and the other car
        float delta_a;
        // Reset the value
        car_in_trajectory_ = false;

        // The number of points in the trajectory
        size_t N_pts_traj = trajectory_.waypoints.size();
        // For all points in trajectory, check if the position of other car is in it.
        for(int i = 0; i < (int)N_pts_traj; i++) {
            float x_pos_trajectory = trajectory_.waypoints.at(i).pose.pose.position.x; // x coordinate of the trajectory point to compare with the position of other car
            float y_pos_trajectory = trajectory_.waypoints.at(i).pose.pose.position.y; // y coordinate of the trajectory point to compare with the position of other car

            float pose_x; // x coordinate of other car to compare with the trajectory
            float pose_y; // y coordinate of other car to compare with the trajectory

            // Initialize the values to compare
            pose_x = other_cars_.poses.at(0).position.x;
            pose_y = other_cars_.poses.at(0).position.y;
            d = pow(pow(pose_x - x_ego_, 2) + pow(pose_y - y_ego_,2), 0.5);

            // The number of other cars
            size_t N_other = other_cars_.poses.size();
            // Search the closest other car in the trajectory of the ego car
            for(int j = 0; j < (int)N_other; j++) {
                pose_x = other_cars_.poses.at(j).position.x;
                pose_y = other_cars_.poses.at(j).position.y;
                float distance_to_traj = pow(pow(x_pos_trajectory - pose_x, 2) + pow(y_pos_trajectory - pose_y, 2), 0.5);
                if(distance_to_traj <= width_ego_ / 2) { // If the car is close enough of the trajectory of the ego car.
                    float distance_to_ego = pow(pow(pose_x - x_ego_, 2) + pow(pose_y - y_ego_,2), 0.5);
                    if(distance_to_ego < d) { // If the other car is the closest of all other cars tested
                        d = distance_to_ego;
                        x_other_cars_ = pose_x;
                        y_other_cars_ = pose_y;
                    }
                    car_in_trajectory_ = true;
                }
            }
        }

        // If there is no car in the trajectory of the ego car, MTTC can't be computed.
        if(!car_in_trajectory_) {
            kpi::mttc = -1; // Default value if MTTC can't be computed.
        }
        else {
            // If this is the first time the function is called, the velocity can't be computed.
            if(!mttc_first_callback_) {
                // The value of the velocity of other cars is obtained by derivation of the position
                float v_x = (x_other_cars_ - x_other_cars_old_)/dt_; // x component of the velocity
                float v_y = (y_other_cars_ - y_other_cars_old_)/dt_; // y component of the velocity
                velocity_other_cars_ = pow(pow(v_x, 2) + pow(v_y, 2), 0.5);
                delta_v = velocity_ego_ - velocity_other_cars_;

                // If this is the second callback of the function, the acceleration can't be computed.
                if(!mttc_second_callback_) {
                    // The value of the acceleration of the other cars and the ego car
                    acceleration_other_cars_ = (velocity_other_cars_ - velocity_other_cars_old_) / dt_;
                    acceleration_ego_ = (velocity_ego_ - velocity_ego_old_) / dt_;
                    delta_a = acceleration_ego_ - acceleration_other_cars_;

                    if(delta_a == 0) {
                        kpi::mttc = kpi:: ttc;
                    }
                    else {
                        // MTTC is calculated from an equation, there is 2 solutions. The minimum non negative one will be MTTC, if they are both negative, there is no risk of collision.
                        float mttc_1 = (- delta_v + pow(pow(delta_v, 2) + 2 * delta_a * d, 0.5)) / delta_a;
                        float mttc_2 = (- delta_v - pow(pow(delta_v, 2) + 2 * delta_a * d, 0.5)) / delta_a;
                        if(mttc_1 >= 0 && mttc_2 >= 0) {
                            if(mttc_1 < mttc_2) {
                                kpi::mttc = mttc_1;
                            }
                            else {
                                kpi::mttc = mttc_2;
                            }
                        }
                        else if(mttc_1 >= 0) {
                            kpi::mttc = mttc_1;
                        }
                        else if(mttc_2 >= 0) {
                            kpi::mttc = mttc_2;
                        }
                        else {
                            kpi::mttc = -1; // Default value if there is no solutions.
                        }
                    }
                }
                else {
                    kpi::mttc = -1; // Default value if MTTC can't be computed.
                }
                mttc_second_callback_ = false;
            }
            else {
                kpi::mttc = -1; // Default value if MTTC can't be computed.
            }
            mttc_first_callback_ = false;
        }

        // Update the position of other car and ego car
        x_other_cars_old_ = x_other_cars_;
        y_other_cars_old_ = y_other_cars_;
        x_ego_old_ = x_ego_;
        y_ego_old_ = y_ego_;

    }

    // /*!
    //  * \brief Update the value of KPI Proportion of Stopping Distance.
    //  * \details PSD is defined as D/(V^2/2d),
    //  * D the remaining distance to the potential point of collision,
    //  * V the velocity of the ego car.
    //  * d the maximum acceptable deceleration rate. We will take 0.47g for the moment.
    //  */
    // void psdUpdate() {
    //     // The remaining distance to the potential point of collision
    //     float rd;
    //     // Maximum acceptable deceleration rate
    //     float d = 0.47 * 9.81;

    //     object_in_trajectory_ = false;

    //     rd = pow(pow(trajectory_.waypoints.at(0).pose.pose.position.x - x_ego_, 2) + pow(trajectory_.waypoints.at(0).pose.pose.position.y - y_ego_, 2), 0.5);
    //     size_t N_traj = trajectory_.waypoints.size();
    //     for(int i=0; i<(int)N_traj; i++) {
    //         grid_map::Position position;
    //         position.x() = trajectory_.waypoints.at(i).pose.pose.position.x;
    //         position.y() = trajectory_.waypoints.at(i).pose.pose.position.y;
    //         for(GridMapIterator it(map_); !it.isPastEnd(); ++it) {
    //             if(map_.atPosition("StaticObjects", position) == map_.at("StaticObjects", *it)) {
    //                 float distance;
    //                 distance = pow(pow(position.x() - x_ego_, 2) + pow(position.y() - y_ego_, 2), 0.5);
    //                 if(distance < rd) {
    //                     rd = distance;
    //                     std::cout<<"rd = "<<rd<<std::endl;
    //                 }
    //                 object_in_trajectory_ = true;
    //             }
    //         }
    //     }

    //     kpi::psd = rd / (pow(velocity_ego_, 2) / (2 * d));

    // }

    /*!
     * \brief gridmapCallback: called when information of the gridmap has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Extracts and stores information from the layers DynamicObjects and StaticObjects.
     */
    void gridmapCallback(const grid_map_msgs::GridMap::ConstPtr& msg) {
        GridMapRosConverter::fromMessage(*msg, map_);
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
        
        rate_ = ros::Rate(frequency_);
    }

    void run() {
        while(nh_.ok()) {
            ros::spinOnce();

            if(other_cars_callback_) {
                ttcUpdate();
                mttcUpdate();
                other_cars_callback_ = false;
            }
            else {
                kpi::ttc = -1; // Value if there is no other cars detected, default value if TTC can't be computed.
                kpi::mttc = -1; // Value if there is no other cars detected, default value if MTTC can't be computed.
            }

            // if(gridmap_callback_) {
            //     psdUpdate();
            //     gridmap_callback_ = false;

            //     if(!object_in_trajectory_) {
            //         kpi::psd = -1;
            //     }
            // }

            std::cout<<"TTC = "<<kpi::ttc<<std::endl;
            std::cout<<"MTTC = "<<kpi::mttc<<std::endl; // Test if the mttc is well updated.

            // This array contains information about all KPIs
            kpi_array_.data = {kpi::dce, kpi::ttce, kpi::mtc, kpi::ttc, kpi::mttc, kpi::wttc, kpi::ettc, kpi::ta, kpi::thw, kpi::psd, kpi::tts, kpi::ttb, kpi::ttk};
            pub_kpi_.publish(kpi_array_);

            rate_.sleep();
        }
    }
};

int main(int argc, char** argv) {
    // Initialize node
    ros::init(argc, argv, "kpi_computation");
    ros::NodeHandle nh;

    RiskEnvelopeComputation rec(nh);
    rec.run();

    return 0;
}
