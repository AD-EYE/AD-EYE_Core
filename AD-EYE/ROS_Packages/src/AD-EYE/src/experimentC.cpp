#include "ros/ros.h"
#include <std_msgs/Bool.h>
#include <geometry_msgs/TwistStamped.h>
#include <experiment_recording.h>
#include "adeye_utils/point_cloud_to_occupancy_grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>

/*!
 * \brief Experiment C node : Manages start and stop of the recording
 * \details ExperimentC test the lidar sensor while it's raining, and record data from OccupancyGrid.
 * See more here :https://kth.app.box.com/folder/125024838885
 */
class ExperimentC : ExperimentRecording
{
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
    /*!
    * \brief Constructor
    * \param nh A reference to the ros::NodeHandle initialized in the main function.
    * \details Initializes the node and its components such the as subscriber /current_velocity.
    */
    ExperimentC(ros::NodeHandle nh)
      : ExperimentRecording(nh), nh_(nh), point_cloud_to_occupancy_grid_(nh, true), rate_(20)
    {
        speed_sub_ = nh.subscribe("/current_velocity", 10, &ExperimentC::speedCallback, this);
        max_speed_allowed_ = 10.0;

        speed_threshold_start_ = max_speed_allowed_ * 0.9;
        speed_threshold_stop_ = max_speed_allowed_ * 0.8;
        std::cout << "ExperimentC: initialized node" << std::endl;
    }

    /*!
    * \brief The main function of the Node. Contains the main loop, which start and stop the recording
    */
    void run()
    {
        std::cout << "ExperimentC: in run" << std::endl;
        while (ros::ok())
        {
            if (!hasRecordingStarted())
            {
                if (ego_speed_ > speed_threshold_start_)
                {
                    startRecording();
                    std::cout << "ExperimentC: started recording" << std::endl;
                }
            }
            else
            {
                if (ego_speed_ < speed_threshold_stop_)
                {
                    stopRecording();
                    std::cout << "ExperimentC: stopped recording" << std::endl;
                }
            }
            ros::spinOnce();
            rate_.sleep();
        }
    }

    /*!
    * \brief Start the recording by calling startSubsciber of point_cloud_to_occupancy_grid class
    */
    void startRecording()
    {
        ExperimentRecording::startRecording();
        point_cloud_to_occupancy_grid_.startSubsciber(nh_);
    }

    /*!
    * \brief Generate the message that will be in the log file.
    * \details The message include the rain intensity and reflectivity.
    */
    void makeBagName()
    {
        nh_.param<float>("/simulink/rain_intensity", rain_intensity_, 0.0);
        nh_.param<float>("/simulink/reflectivity", rain_reflectivity_, 0.0);
        std::ostringstream ss;
        ss << "ExpC_intensity_" << rain_intensity_ << "_reflectivity_" << rain_reflectivity_;
        bag_name_ = std::string(ss.str());
    }

    /*!
    * \brief Stop the recording and prompt the result in the log file with a linux command
    */
    void stopRecording()
    {
        ExperimentRecording::stopRecording();
        makeBagName();
        std::string recording_command_part_1 = "rosbag record /cost_map -O ~/Experiment_Results/";
        std::string recording_command_part_2 = ".bag __name:=expC_rosbag_recorder &";
        std::string recording_command = recording_command_part_1 + bag_name_ + recording_command_part_2;
        char char_command[recording_command.length()];
        for (int i = 0; i < sizeof(char_command); i++)
        {
            char_command[i] = recording_command[i];
        }
        system(char_command);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        point_cloud_to_occupancy_grid_.publishOccupancyGrid();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        system("rosnode kill /expC_rosbag_recorder &");
        stopExperiment();
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ExperimentC");
    ros::NodeHandle private_nh("~");
    ExperimentC experimentC(private_nh);
    experimentC.run();
}