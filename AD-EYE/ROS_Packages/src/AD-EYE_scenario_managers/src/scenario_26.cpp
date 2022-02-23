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

/*!
 * \brief scenario26 node : Manages start and stop of the recording & experiment for scenario26
 */
class scenario26 : public ScenarioManagerTemplate
{
  private:
    ros::Subscriber speed_sub_;
    ros::Subscriber speed_sub2_;
    ros::Subscriber speed_sub3_;
    ros::Subscriber speed_sub4_;
    float SPEED_THRESHOLD_STOP_ = 0.0f;
    float ego_speed_ = 0.0;
    float non_ego_speed_ = 0.0;
    float non_ego_angle_ = 0.0;
    float pedestrian_speed_ = 0.0;

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

  public:
    /*!
    * \brief Constructor
    * \param nh ros::NodeHandle initialized in the main function.
    * \param frequency The frequency at which the main loop will be run.
    * \details Initializes the node and its components such the as subscribers.
    */
    scenario26(ros::NodeHandle nh, int frequency) : ScenarioManagerTemplate(nh, frequency)
    {
        speed_sub_ = ScenarioManagerTemplate::nh_.subscribe("/current_velocity", 10, &scenario26::speedCallback, this);
        // ScenarioManagerTemplate::nh_.param<float>("/simulink/rain_intensity", rain_intensity_, 0.0);
        speed_sub2_ =
            ScenarioManagerTemplate::nh_.subscribe("/other_velocity_1", 10, &scenario26::speedCallback2, this);
        speed_sub3_ =
            ScenarioManagerTemplate::nh_.subscribe("/other_velocity_1", 10, &scenario26::speedCallback3, this);
        speed_sub4_ =
            ScenarioManagerTemplate::nh_.subscribe("/other_velocity_2", 10, &scenario26::speedCallback4, this);
    }

    /*!
    * \brief Starts the experiment, contains what needs to be done during the experiment
    */
    void startExperiment()
    {
        std::cout << "scenario26: started experiment" << std::endl;
    }

    /*!
    * \brief Stops the experiment, contains the post experiment cleanups
    */
    void stopExperiment()
    {
        std::cout << "scenario26: stopped experiment" << std::endl;
    }

    /*!
    * \brief Starts the experiment relevant recording
    */
    void startRecording()
    {
        std::cout << "scenario26: started recording" << std::endl;
    }

    /*!
    * \brief Stops the the experiment relevant recording
    */
    void stopRecording()
    {
        std::cout << "scenario26: stopped recording" << std::endl;
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
        return (non_ego_speed_ == 0);
    }

    /*!
    * \brief Checks if the conditions to start the experiment are met
    */
    bool startExperimentConditionFulfilled()
    {
        return (ego_speed_ > 3);
    }

    /*!
    * \brief Checks if the conditions to stop the experiment are met
    */
    bool stopExperimentConditionFulfilled()
    {
        return (non_ego_speed_ == 0);
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "scenario26");
    ros::NodeHandle private_nh("~");

    std::cout << "Analyzing scenario26" << std::endl;
    scenario26 scenario_26(private_nh, 20);
    scenario_26.run();
}