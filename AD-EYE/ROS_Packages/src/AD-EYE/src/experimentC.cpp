#include "ros/ros.h"
#include <std_msgs/Bool.h>

class ExperimentC {

    private:
        bool recording_started_ = false;

    public:
        void startRecording() {
            recording_started_ = true;
        }

        void stopRecording() {
            recording_started_ = false;
        }

        bool hasRecordingStarted() {
            return recording_started_;
        }

        void stopExperiment(ros::NodeHandle nh) {
            ros::Publisher pub = nh.advertise<std_msgs::Bool> ("/simulink/stop_experiment", 1);
            std_msgs::Bool msg;
            msg.data = false;
            pub.publish(msg);
        }


};