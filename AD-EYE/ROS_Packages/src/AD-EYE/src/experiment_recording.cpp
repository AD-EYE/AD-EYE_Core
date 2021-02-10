#include <experiment_recording.h>
#include <std_msgs/Bool.h>

void ExperimentRecording::startRecording() {
    recording_started_ = true;
}


void ExperimentRecording::stopRecording() {
    recording_started_ = false;
}


bool ExperimentRecording::hasRecordingStarted() {
    return recording_started_;
}

void ExperimentRecording::stopExperiment(ros::NodeHandle nh) {
    ros::Publisher pub = nh.advertise<std_msgs::Bool> ("/simulink/stop_experiment", 1);
    std_msgs::Bool msg;
    msg.data = false;
    pub.publish(msg);
}