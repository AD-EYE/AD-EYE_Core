#include "ros/ros.h"
#include <scenario_manager_template.h>


#include <std_msgs/Bool.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <autoware_msgs/LaneArray.h>
#include "op_planner/PlannerH.h"
#include "op_ros_helpers/op_ROSHelpers.h"
#include <cstdio>
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>

/*!
 * \brief Scenario1 node : Manages start and stop of the recording & experiment for Scenario1
 */
class FaultExperimentManager: public ScenarioManagerTemplate {

private:
    ros::Subscriber speed_sub_;
    ros::Subscriber sub_gnss_;
    ros::Subscriber sub_autoware_global_plan_;
    ros::Subscriber sub_autoware_state_;
    bool has_received_global_plan_ = false;
    ros::Publisher pub_autoware_goal_;
    float ego_speed_ = 0.0;
    geometry_msgs::Pose ego_pose_;
    std::vector<std::vector<PlannerHNS::WayPoint>> autoware_global_path_;

    double autoware_behavior_state_ = 0;

    const double SPEED_STOP_THRESHOLD_ = 0.05;

    const std::string RESULT_FILE_PATH = "/home/adeye/Experiment_Results/FaultExperiments.csv";

    int trigger_distance_ = 0;
    int fault_criticality_level_ = 0;

    ros::Time motion_start_time;
    ros::Time experiment_start_time;
    bool is_motion_start_time_set = false;
    ros::Time motion_stop_time;


    void speedCallback(geometry_msgs::TwistStamped msg)
    {
        ego_speed_ = msg.twist.linear.x;
        if(!is_motion_start_time_set && ego_speed_ > 0)
        {
            motion_start_time = ros::Time::now();
            is_motion_start_time_set = true;
        }
    }


    /*!
     * \brief Gnss Callback : Called when the gnss information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates gnss information of the vehicle position.
     */
    void gnssCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
    {
        geometry_msgs::PoseStamped gnss = *msg;
        ego_pose_ = gnss.pose;
    }


    /*!
     * \brief Autoware global plan Callback : Called when the global plan from autoware has changed.
     * \param msg A smart pointer to the message from the topic.
     */
    void autowareGlobalPlanCallback(const autoware_msgs::LaneArrayConstPtr& msg)
    {
        if(msg->lanes.size() > 0)
        {
            std::vector<PlannerHNS::WayPoint> m_temp_path;
            for(unsigned int i = 0 ; i < msg->lanes.size(); i++)
            {
                PlannerHNS::ROSHelpers::ConvertFromAutowareLaneToLocalLane(msg->lanes.at(i), m_temp_path);
                PlannerHNS::PlanningHelpers::CalcAngleAndCost(m_temp_path);
                autoware_global_path_.push_back(m_temp_path);
            }
        }
        has_received_global_plan_ = true;
    }

    /*!
     * \brief Behavior State Callback : Continuously called to show the vehicle behaviour state information.
     * \param msg The message contains the vehicle state status.
     * \details Stores the autoware behavior state status.
     */
    void behaviorStateCallback(const geometry_msgs::TwistStamped::ConstPtr &msg)
    {
        // Autoware behavior state (2.0 = Forward state and 13.0 = End state)
        autoware_behavior_state_ =  msg -> twist.angular.y;
    }

    void publishOriginalGoal()
    {
        geometry_msgs::PoseStamped newGoal;
        newGoal.header.frame_id = "world";
        newGoal.pose.position.x = -24;
        newGoal.pose.position.y = 113;
        newGoal.pose.position.z = 0;
        newGoal.pose.orientation.x = 0;
        newGoal.pose.orientation.y = 0;
        newGoal.pose.orientation.z = -0.707;
        newGoal.pose.orientation.w = 0.707;
        pub_autoware_goal_.publish(newGoal);
    }


    static void killSSDCamera1()
    {
        system("rosnode kill /camera_1/vision_ssd_detect");
    }
    static void killSSDCamera2()
    {
        system("rosnode kill /camera_2/vision_ssd_detect");
    }
    static void killTwistFilter()
    {
        system("rosnode kill /twist_filter");
    }
    static void killGoalSequencer()
    {
        system("rosnode kill /goalSequencer");
    }
    static void killRadarBroadcaster()
    {
        system("rosnode kill /radar_broadcaster");
    }
    static void killGlobalPlanner()
    {
        system("rosnode kill /op_global_planner");
    }

public:
    /*!
    * \brief Constructor
    * \param nh ros::NodeHandle initialized in the main function.
    * \param frequency The frequency at which the main loop will be run.
    * \details Initializes the node and its components such the as subscribers.
    */
    FaultExperimentManager(ros::NodeHandle nh, int frequency): ScenarioManagerTemplate(nh, frequency)
    {
        speed_sub_ = ScenarioManagerTemplate::nh_.subscribe("/current_velocity", 10, &FaultExperimentManager::speedCallback, this);
        sub_gnss_ = nh_.subscribe<geometry_msgs::PoseStamped>("/ground_truth_pose", 100, &FaultExperimentManager::gnssCallback, this);
        sub_autoware_global_plan_ = nh.subscribe("/lane_waypoints_array", 1, &FaultExperimentManager::autowareGlobalPlanCallback, this);
        sub_autoware_state_ = nh_.subscribe<geometry_msgs::TwistStamped>("/current_behavior", 1, &FaultExperimentManager::behaviorStateCallback, this);
        pub_autoware_goal_ = nh_.advertise<geometry_msgs::PoseStamped>("/adeye/overwriteGoal", 1, true);


        trigger_distance_ = 15 + 2 * (int) (getExpIndex() / 4);
        fault_criticality_level_ = getExpIndex() % 4 + 1;
        // ScenarioManagerTemplate::nh_.param<float>("/simulink/rain_intensity", rain_intensity_, 0.0);
    }


    int getExpIndex()
    {
        std::ifstream result_file(RESULT_FILE_PATH);
        std::string line;
        int nb_lines = 0;
        while (getline(result_file, line))
            nb_lines++;
        return nb_lines;
    }

    /*!
    * \brief Starts the experiment, contains what needs to be done during the experiment
    */
    void startExperiment() override
    {
        std::cout << "FaultExperimentManager: started experiment" << std::endl;

        experiment_start_time = ros::Time::now();
        switch(fault_criticality_level_)
        {
            case 1:
                killGoalSequencer();
                break;
            case 2:
                killRadarBroadcaster();
//                killSSDCamera2();
                break;
            case 3:
                killGlobalPlanner();
//                killSSDCamera1();
                break;
            case 4:
                killTwistFilter();
                break;
        }
    }

    /*!
    * \brief Stops the experiment, contains the post experiment cleanups
    */
    void stopExperiment() override
    {
        std::cout << "FaultExperimentManager: stopped experiment" << std::endl;
    }

    /*!
    * \brief Starts the experiment relevant recording
    */
    void startRecording() override
    {
        std::cout << "FaultExperimentManager: started recording" << std::endl;
        has_received_global_plan_ = false;
        publishOriginalGoal();
        motion_stop_time = ros::Time::now();
    }

    /*!
    * \brief Stops the the experiment relevant recording
    */
    void stopRecording() override
    {
        std::cout << "FaultExperimentManager: stopped recording" << std::endl;


        double remaining_traj_length = getRemainingTrajectoryLength();
        std::cout << remaining_traj_length << " meters remaining to goal" << std::endl;
        std::ofstream results_file;
        results_file.open(RESULT_FILE_PATH, std::ios::app);
        results_file << fault_criticality_level_ << "," << trigger_distance_ << "," << remaining_traj_length <<
        "," << motion_start_time.toSec() << "," << motion_stop_time.toSec() << "," <<
        motion_stop_time.toSec() - motion_start_time.toSec() << experiment_start_time.toSec() << motion_start_time.toSec() - experiment_start_time.toSec() << "\n";
        results_file.close();
    }

    double getRemainingTrajectoryLength()
    {
        PlannerHNS::WayPoint pose_wp(ego_pose_.position.x, ego_pose_.position.y, 0, 0);
        int current_wp_index = getClosestWaypointIndex(autoware_global_path_.front(), pose_wp, 0);
//        int current_wp_index = PlannerHNS::PlanningHelpers::GetClosestNextPointIndexFastV2(autoware_global_path_.front(), pose_wp, 0);
        double remaining_traj_length = PlannerHNS::PlanningHelpers::GetDistanceOnTrajectory_obsolete(autoware_global_path_.front(), current_wp_index, autoware_global_path_.front().back());
        return remaining_traj_length;
    }
    double getGlobalPathLength()
    {
        return PlannerHNS::PlanningHelpers::GetDistanceOnTrajectory_obsolete(autoware_global_path_.front(), 0, autoware_global_path_.front().back());
    }


    static double getDistance(const PlannerHNS::WayPoint& P1, const PlannerHNS::WayPoint& P2)
    {
        return sqrt((P2.pos.x - P1.pos.x) * (P2.pos.x - P1.pos.x) + (P2.pos.y - P1.pos.y) * (P2.pos.y - P1.pos.y));
    }

    static int getClosestWaypointIndex(const std::vector<PlannerHNS::WayPoint>& trajectory, const PlannerHNS::WayPoint& p, const int& prevIndex = 0)
    {
        double min_dist = DBL_MAX;
        int min_index = 0;
        for(int wp_index = 0; wp_index < trajectory.size(); wp_index++)
        {
            if(getDistance(p, trajectory.at(wp_index)) < min_dist)
            {
                min_dist = getDistance(p, trajectory.at(wp_index));
                min_index = wp_index;
            }
        }
        return min_index;
    }


    void displayRemainingDistance()
    {

        if(has_received_global_plan_)
        {

            PlannerHNS::WayPoint pose_wp(ego_pose_.position.x, ego_pose_.position.y, 0, 0);
            int current_wp_index = getClosestWaypointIndex(autoware_global_path_.front(), pose_wp, 0);
            double remaining_traj_length = PlannerHNS::PlanningHelpers::GetDistanceOnTrajectory_obsolete(autoware_global_path_.front(), current_wp_index, autoware_global_path_.front().back());
            std::cout << "    " << getRemainingTrajectoryLength() << "  " << current_wp_index << "\t\r" << std::flush;
        }
    }




    /*!
    * \brief Checks if the conditions to start recording are met
    */
    bool startRecordingConditionFulfilled() override
    {
        displayRemainingDistance();
        return (hasExperimentStarted() && ego_speed_ < SPEED_STOP_THRESHOLD_ && autoware_behavior_state_ != 9);
    }

    /*!
    * \brief Checks if the conditions to stop recording are met
    */
    bool stopRecordingConditionFulfilled() override
    {
        displayRemainingDistance();
        return (ego_speed_ < SPEED_STOP_THRESHOLD_);
//        return (has_received_global_plan_);
    }

    /*!
    * \brief Checks if the conditions to start the experiment are met
    */
    bool startExperimentConditionFulfilled() override
    {
        displayRemainingDistance();
        return (ego_speed_ > 1 && getGlobalPathLength() - trigger_distance_ > getRemainingTrajectoryLength());
    }

    /*!
    * \brief Checks if the conditions to stop the experiment are met
    */
    bool stopExperimentConditionFulfilled() override
    {
        displayRemainingDistance();
        return (ego_speed_ < SPEED_STOP_THRESHOLD_);
    }




};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "FaultExperimentManager");
    ros::NodeHandle private_nh("~");
    FaultExperimentManager fem(private_nh, 20);
    fem.run();
}