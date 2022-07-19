#include <experiment_recording.h>
#include <std_msgs/Bool.h>

ExperimentRecording::ExperimentRecording(ros::NodeHandle nh)
{
    stop_pub_ = nh.advertise<std_msgs::Bool>("/simulink/stop_experiment", 1);
}

void ExperimentRecording::startRecording()
{
    recording_started_ = true;
}

void ExperimentRecording::stopRecording()
{
    recording_started_ = false;
}

bool ExperimentRecording::hasRecordingStarted()
{
    return recording_started_;
}

void ExperimentRecording::stopExperiment()
{
    std_msgs::Bool msg;
    msg.data = true;
    stop_pub_.publish(msg);
}