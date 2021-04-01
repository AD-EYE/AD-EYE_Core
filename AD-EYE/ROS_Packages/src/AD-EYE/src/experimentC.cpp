#include "ros/ros.h"
#include <std_msgs/Bool.h>
#include <geometry_msgs/TwistStamped.h>
#include <experiment_recording.h>
#include <point_cloud_to_occupancy_grid.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>



class ExperimentC: ExperimentRecording {

    private:
        ros::NodeHandle nh_;
        ros::Subscriber speed_sub_;
        PointsToOccupancyGrid point_cloud_to_occupancy_grid_;
        float ego_speed_ = 0.0;
        float max_speed_allowed_ = 0.0;
        float rain_intensity_ = 0.0;
        float rain_reflectivity_ = 0.0;
        float speed_threshold_start_ = 0.0;
        float speed_threshold_stop_ = 0.0;
        ros::Rate rate_;
        std::string bag_name_;

        void speedCallback(geometry_msgs::TwistStamped msg)
        {
            ego_speed_ = msg.twist.linear.x;
        }

    public:
        ExperimentC(ros::NodeHandle nh): ExperimentRecording(nh), nh_(nh), point_cloud_to_occupancy_grid_(nh, true), rate_(20)
        {
            speed_sub_ = nh.subscribe("/current_velocity", 10, &ExperimentC::speedCallback, this);
            max_speed_allowed_ = 10.0;
            
            speed_threshold_start_ = max_speed_allowed_ * 0.9;
            speed_threshold_stop_ = max_speed_allowed_ * 0.8;
            std::cout << "ExperimentC: initialized node" << std::endl;
            
        }

        void run() 
        {
            
            std::cout << "ExperimentC: in run" << std::endl;
            while (ros::ok())
            {
                if(!hasRecordingStarted())
                {
                    if(ego_speed_ > speed_threshold_start_)
                    {
                        startRecording();
                        std::cout << "ExperimentC: started recording" << std::endl;
                    }
                }
                else
                {
                    if(ego_speed_ < speed_threshold_stop_)
                    {
                        stopRecording();
                        std::cout << "ExperimentC: stopped recording" << std::endl;
                    }
                }
                ros::spinOnce();
                rate_.sleep();
            }
        }

        void startRecording()
        {
            ExperimentRecording::startRecording();
            point_cloud_to_occupancy_grid_.startSubsciber(nh_);
        }

        void makeBagName() {
            nh_.param<float>("/simulink/rain_intensity", rain_intensity_, 0.0);
            nh_.param<float>("/simulink/reflectivity", rain_reflectivity_, 0.0);
            std::ostringstream ss;
            ss << "ExpC_intensity_" << rain_intensity_ << "_reflectivity_" << rain_reflectivity_;
            bag_name_ = std::string(ss.str());
        }

        void stopRecording()
        {
            ExperimentRecording::stopRecording();
            makeBagName();
            //TODO start rosbag
            std::string recording_command_part_1 = "rosbag record /cost_map -O ~/Experiment_Results/";
            std::string recording_command_part_2 = ".bag __name:=expC_rosbag_recorder &";
            std::string recording_command = recording_command_part_1 + bag_name_ + recording_command_part_2;
            char char_command[recording_command.length()];
            for (int i = 0; i < sizeof(char_command); i++) {
                char_command[i] = recording_command[i];
            }
            system(char_command);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            point_cloud_to_occupancy_grid_.publishOccupancyGrid();
            //TODO wait a bit and stop rosbag
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            system("rosnode kill /expC_rosbag_recorder &");
            stopExperiment();

        }

        


};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "ExperimentC");
    ros::NodeHandle private_nh("~");
    ExperimentC experimentC(private_nh);
    experimentC.run();
}