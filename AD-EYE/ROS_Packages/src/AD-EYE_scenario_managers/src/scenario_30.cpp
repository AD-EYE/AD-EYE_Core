#include "ros/ros.h"
#include <scenario_manager_template.h>

#include <std_msgs/Bool.h>
#include <geometry_msgs/TwistStamped.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <fstream>

/*!
 * \brief scenario30 node : Manages start and stop of the recording & experiment for scenario30
 */
class Scenario30 : public ScenarioManagerTemplate
{
  private:
    ros::Subscriber speed_sub_;
    ros::Subscriber speed_sub2_;
    ros::Subscriber speed_sub3_;
    ros::Subscriber speed_sub4_;
    ros::Subscriber collision_distance_sub5_;
    ros::NodeHandle nh;
    double distance_;
    double initial_ego_speed_;
    double initial_non_ego_speed_;
    float SPEED_THRESHOLD_STOP_ = 0.0f;
    float ego_speed_ = 0.0;
    float non_ego_speed_ = 0.0;
    float non_ego_angle_ = 0.0;
    float pedestrian_speed_ = 0.0;
    float distance_ego_actor_ = 0.0;
    float collision_distance_ = 0.0;

    void speedCallback(geometry_msgs::TwistStamped msg)
    {
        ego_speed_ = msg.twist.linear.x;
    }

    void speedCallback2(geometry_msgs::TwistStamped msg)
    {
        non_ego_speed_ = msg.twist.linear.x;
    }

    void speedCallback3(geometry_msgs::TwistStamped msg)
    {
        non_ego_angle_ = msg.twist.angular.z;
    }

    void speedCallback4(geometry_msgs::TwistStamped msg)
    {
        pedestrian_speed_ = msg.twist.linear.x;
    }

    void speedCallback5(geometry_msgs::TwistStamped msg)
    {
        collision_distance_ = msg.twist.linear.x;
    }

  public:
    /*!
    * \brief Constructor
    * \param nh ros::NodeHandle initialized in the main function.
    * \param frequency The frequency at which the main loop will be run.
    * \details Initializes the node and its components such the as subscribers.
    */
    Scenario30(ros::NodeHandle nh, int frequency) : ScenarioManagerTemplate(nh, frequency)
    {
        speed_sub_ = ScenarioManagerTemplate::nh_.subscribe("/current_velocity", 10, &Scenario30::speedCallback, this);
        // ScenarioManagerTemplate::nh_.param<float>("/simulink/rain_intensity", rain_intensity_, 0.0);
        speed_sub2_ =
            ScenarioManagerTemplate::nh_.subscribe("/other_velocity_1", 10, &Scenario30::speedCallback2, this);
        speed_sub3_ =
            ScenarioManagerTemplate::nh_.subscribe("/other_velocity_1", 10, &Scenario30::speedCallback3, this);
        speed_sub4_ =
            ScenarioManagerTemplate::nh_.subscribe("/other_velocity_2", 10, &Scenario30::speedCallback4, this);
        collision_distance_sub5_ =
            ScenarioManagerTemplate::nh_.subscribe("/distance_to_ego_1", 10, &Scenario30::speedCallback5, this);
        nh.getParam("/ConditionROS_1_1", distance_);
        nh.getParam("/initial_speed_0", initial_ego_speed_);
        nh.getParam("/initial_speed_1", initial_non_ego_speed_);
    }

    /*!
    * \brief Starts the experiment, contains what needs to be done during the experiment
    */
    void startExperiment()
    {
        // std::cout << "scenario30: started experiment" << std::endl;
        std::fstream myfile;
        myfile.open("/home/adeye/Experiment_Results/Pedestrian_Action/Pedestrian.csv", std::ios_base::app);
        myfile << "\n New experiment\n";
        myfile << "Initial speed of the ego car:," << initial_ego_speed_ << "\n";
        myfile << "Iniatial speed of the non ego car:," << initial_non_ego_speed_ << "\n";
        myfile << "Trigger distance between the pedestrian and the non ego car:," << distance_ << "\n";
        myfile.close();
    }

    /*!
    * \brief Stops the experiment, contains the post experiment cleanups
    */
    void stopExperiment()
    {
        // std::cout << "scenario30: stopped experiment" << std::endl;
    }

    /*!
    * \brief Starts the experiment relevant recording
    */
    void startRecording()
    {
        // std::cout << "scenario30: started recording" << std::endl;
    }

    /*!
    * \brief Stops the the experiment relevant recording
    */
    void stopRecording()
    {
        // std::cout << "scenario30: stopped recording" << std::endl;

        if (collision_distance_ < 6)
        {
            std::ofstream myfile;
            myfile.open("/home/adeye/Experiment_Results/Pedestrian_Action/Pedestrian.csv", std::ios_base::app);
            std::cout << "scenario30: stopped recording" << std::endl;
            myfile << "Speed of the ego car at collision:," << ego_speed_ << "\n";
            myfile.close();
        }
    }

    /*!
    * \brief Checks if the conditions to start recording are met
    */
    bool startRecordingConditionFulfilled()
    {
        return (pedestrian_speed_ > 0);
    }

    /*!
    * \brief Checks if the conditions to stop recording are met
    */
    bool stopRecordingConditionFulfilled()
    {
        return (ego_speed_ < 1.2);
    }

    /*!
    * \brief Checks if the conditions to start the experiment are met
    */
    bool startExperimentConditionFulfilled()
    {
        return (ego_speed_ > 5);
    }

    /*!
    * \brief Checks if the conditions to stop the experiment are met
    */
    bool stopExperimentConditionFulfilled()
    {
        return (ego_speed_ < 1 || collision_distance_ < 5);
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "scenario30");
    ros::NodeHandle private_nh("~");

    // std::cout << "Analyzing scenario30" << std::endl;
    Scenario30 scenario_30(private_nh, 20);
    scenario_30.run();
}
