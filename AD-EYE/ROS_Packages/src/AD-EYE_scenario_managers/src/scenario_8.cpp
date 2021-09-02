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
 * \brief scenario8 node : Manages start and stop of the recording & experiment for scenario8
 */
class scenario8: public ScenarioManagerTemplate {

    private:
        ros::Subscriber speed_sub_;
        ros::Subscriber speed_sub2_;
        ros::Subscriber speed_sub3_;
        float SPEED_THRESHOLD_STOP_ = 0.0f;
        float ego_speed_ = 0.0;
        float non_ego_speed_ = 0.0;
        float non_ego_angle_ = 0.0;

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

    public:
        /*!
        * \brief Constructor
        * \param nh ros::NodeHandle initialized in the main function.
        * \param frequency The frequency at which the main loop will be run.
        * \details Initializes the node and its components such the as subscribers.
        */
        scenario8(ros::NodeHandle nh, int frequency): ScenarioManagerTemplate(nh, frequency)
        {
            speed_sub_ = ScenarioManagerTemplate::nh_.subscribe("/current_velocity", 10, &scenario8::speedCallback, this);
            // ScenarioManagerTemplate::nh_.param<float>("/simulink/rain_intensity", rain_intensity_, 0.0);
            speed_sub2_ = ScenarioManagerTemplate::nh_.subscribe("/other_velocity", 10, &scenario8::speedCallback2, this);
            speed_sub3_ = ScenarioManagerTemplate::nh_.subscribe("/other_velocity", 10, &scenario8::speedCallback3, this);
        }

        

        /*!
        * \brief Starts the experiment, contains what needs to be done during the experiment
        */
        void startExperiment()
        {
            std::cout << "scenario8: started experiment" << std::endl;
        }

        /*!
        * \brief Stops the experiment, contains the post experiment cleanups
        */
        void stopExperiment()
        {
            std::cout << "scenario8: stopped experiment" << std::endl;
        }

        /*!
        * \brief Starts the experiment relevant recording
        */
        void startRecording()
        {
            std::cout << "scenario8: started recording" << std::endl;
        }

        /*!
        * \brief Stops the the experiment relevant recording
        */
        void stopRecording()
        {
            std::cout << "scenario8: stopped recording" << std::endl;
        }






        /*!
        * \brief Checks if the conditions to start recording are met
        */
        bool startRecordingConditionFulfilled()
        {
            return (non_ego_angle_ > 0);
        }

        /*!
        * \brief Checks if the conditions to stop recording are met
        */
        bool stopRecordingConditionFulfilled()
        {
            
            return (non_ego_angle_ > 0 && ego_speed_ <1);
        }

        /*!
        * \brief Checks if the conditions to start the experiment are met
        */
        bool startExperimentConditionFulfilled()
        {
            return (non_ego_speed_ > 0);
        }

        /*!
        * \brief Checks if the conditions to stop the experiment are met
        */
        bool stopExperimentConditionFulfilled()
        {
            
            return (ego_speed_ >5);
        }

        


};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "scenario8");
    ros::NodeHandle private_nh("~");

    std::cout << "Analyzing scenario8" << std::endl;
    scenario8 scenario_8(private_nh, 20);
    scenario_8.run();
}