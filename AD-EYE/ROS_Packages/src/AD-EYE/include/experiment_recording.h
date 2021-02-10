#ifndef EXPERIMENT_RECORDING_H
#define EXPERIMENT_RECORDING_H

#include "ros/ros.h"


class ExperimentRecording {

    private:
        bool recording_started_ = false;

    public:
        /*!
        * \brief Starts the recording
        * \details This method only affect the state
        */
        virtual void startRecording();

        /*!
        * \brief Stops the recording
        * \details This method only affect the state
        */
        virtual void stopRecording();

        /*!
        * \brief Getter to know if the recording is started
        */
        virtual bool hasRecordingStarted();

        /*!
        * \brief Sends a message to stop the experiment
        * \details This method sends a ROS message that once received by Simulink should stop the simulation
        */
        virtual void stopExperiment(ros::NodeHandle nh);


};


#endif
