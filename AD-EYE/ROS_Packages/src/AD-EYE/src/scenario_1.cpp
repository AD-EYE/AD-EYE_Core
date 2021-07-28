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
 * \brief Scenario1 node : Manages start and stop of the recording & experiment
 */
class Scenario1: public ScenarioManagerTemplate {

    private:
        ros::Subscriber speed_sub_;
        float SPEED_THRESHOLD_STOP_ = 0.0f;
        float ego_speed_ = 0.0;

        void speedCallback(geometry_msgs::TwistStamped msg)
        {
            ego_speed_ = msg.twist.linear.x;
        }

    public:
        /*!
        * \brief Constructor
        * \param nh A reference to the ros::NodeHandle initialized in the main function.
        * \details Initializes the node and its components such the as subscriber /current_velocity.
        */
        Scenario1(ros::NodeHandle nh, int frequency): ScenarioManagerTemplate(nh, frequency)
        {
            std::cout << "screating Scenario1" << std::endl;
            speed_sub_ = ScenarioManagerTemplate::nh_.subscribe("/current_velocity", 10, &Scenario1::speedCallback, this);
            // ScenarioManagerTemplate::nh_.param<float>("/simulink/rain_intensity", rain_intensity_, 0.0);
        }

        

        /*!
        * \brief Start the recording by calling startSubsciber of point_cloud_to_occupancy_grid class
        */
        void startRecording()
        {
            std::cout << "Scenario1: started recording" << std::endl;
        }


        /*!
        * \brief Stop the recording and prompt the result in the log file with a linux command
        */
        void stopRecording()
        {
            std::cout << "Scenario1: stopped recording" << std::endl;
        }


        /*!
        * \brief Stop the recording and prompt the result in the log file with a linux command
        */
        void stopExperiment()
        {
            std::cout << "Scenario1: stopped experiment" << std::endl;
        }

        /*!
        * \brief Stop the recording and prompt the result in the log file with a linux command
        */
        void startExperiment()
        {
            std::cout << "Scenario1: started experiment" << std::endl;
        }

        bool startRecordingConditionFulfilled()
        {
            return (ego_speed_ > 2);
        }
        bool stopRecordingConditionFulfilled()
        {
            
            return (ego_speed_ < 2);
        }
        bool startExperimentConditionFulfilled()
        {
            return (ego_speed_ > 1);
        }
        bool stopExperimentConditionFulfilled()
        {
            
            return (ego_speed_ < 1);
        }

        


};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "Scenario1");
    ros::NodeHandle private_nh("~");

    std::cout << "Creating Scenario1" << std::endl;
    Scenario1 scenario_1(private_nh, 20);
    scenario_1.run();
}