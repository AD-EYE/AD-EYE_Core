#ifndef SCENARIO_MANAGER_TEMPLATE_H
#define SCENARIO_MANAGER_TEMPLATE_H

#include "ros/ros.h"
#include <std_msgs/Bool.h>

class ScenarioManagerTemplate {

private:
    bool experiment_started_ = false;
    bool recording_started_ = false;
    bool experiment_running_ = false;
    bool recording_running_ = false;
    ros::Publisher stop_pub_;

protected:
    ros::NodeHandle nh_;
    ros::Rate rate_;

public:

    ScenarioManagerTemplate(ros::NodeHandle nh, int frequency): nh_(nh), rate_(frequency)
    {
        stop_pub_ = nh_.advertise<std_msgs::Bool> ("/simulink/stop_experiment", 1);
    }


    /*!
    * \brief Starts the recording
    * \details This method only affect the state
    */
    virtual void startRecording() = 0;

    /*!
    * \brief Stops the recording
    * \details This method only affect the state
    */
    virtual void stopRecording() = 0;

    /*!
    * \brief Getter to know if the recording has been started
    */
    virtual bool isRecordingRunning() {return recording_running_;};

    /*!
    * \brief Getter to know if the experiment has been started
    */
    virtual bool isExperimentRunning() {return experiment_running_;};

    /*!
    * \brief Getter to know if the recording has been started
    */
    virtual bool hasRecordingStarted() {return recording_started_;};

    /*!
    * \brief Getter to know if the experiment has been started
    */
    virtual bool hasExperimentStarted() {return experiment_started_;};

    /*!
    * \brief Sends a message to stop the experiment
    * \details This method sends a ROS message that once received by Simulink should stop the simulation
    */
    virtual void stopExperiment() = 0;
    virtual void startExperiment() = 0;

    void stopSimulinkExperiment() {
        std_msgs::Bool msg;
        msg.data = true;
        stop_pub_.publish(msg);
    }

    virtual bool startRecordingConditionFulfilled() = 0;
    virtual bool stopRecordingConditionFulfilled() = 0;
    virtual bool startExperimentConditionFulfilled() = 0;
    virtual bool stopExperimentConditionFulfilled() = 0;

    /*!
    * \brief Contains the main loop, which runs the state machine of the scenario manager
    */
    void run()
    {
        while (ros::ok())
        {
            if(hasExperimentStarted())
            {
                if(!hasRecordingStarted()){
                    if(startRecordingConditionFulfilled())
                    {
                        recording_started_ = true;
                        recording_running_ = true;
                        startRecording();
                    }
                }
                else {
                    if(stopRecordingConditionFulfilled())
                    {
                        recording_running_ = false;
                        stopRecording();
                    }
                }

                if(stopExperimentConditionFulfilled() && !isRecordingRunning()) // stop condition of the experiment
                {
                    experiment_running_ = false;
                    stopExperiment();
                    stopSimulinkExperiment();
                }
            }
            else
            {
                if(startExperimentConditionFulfilled()) // start condition of the experiment
                {
                    experiment_started_ = true;
                    experiment_running_ = true;
                    startExperiment();

                }
            }
            ros::spinOnce();
            rate_.sleep();
        }
    }


};


#endif
