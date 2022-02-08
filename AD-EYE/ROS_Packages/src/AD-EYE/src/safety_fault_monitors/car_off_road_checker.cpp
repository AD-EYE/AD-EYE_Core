//
// Created by adeye on 2021-10-11.
//

#include "safety_fault_monitors/car_off_road_checker.h"

CarOffRoadChecker::CarOffRoadChecker(int increment_value, int decrement_value, int high_threshold, int low_threshold):
        SafetyFaultMonitor(increment_value, decrement_value, high_threshold, low_threshold)
{
    sub_gnss_ = nh_.subscribe<geometry_msgs::PoseStamped>("/ground_truth_pose", 100, &CarOffRoadChecker::gnssCallback, this);
    sub_gridmap_ = nh_.subscribe<grid_map_msgs::GridMap>("safety_planner_gridmap", 1, &CarOffRoadChecker::gridmapCallback, this);
}


bool CarOffRoadChecker::hasTestFailed() {
    if(!gridmap_flag_ || !gnss_flag_)
        return true;
    else
        return isCarOffRoad();
}

bool CarOffRoadChecker::isCarOffRoad()
{
    float current_lane_value = gridmap_.atPosition("Lanes", grid_map::Position(pose_.position.x, pose_.position.y));
    if (current_lane_value == 0) {
        ROS_WARN_THROTTLE(1, "The center of the car is not on the road");
        return true;
    }
    else
        return false;
}


void CarOffRoadChecker::gnssCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    geometry_msgs::PoseStamped gnss = *msg;
    pose_ = gnss.pose;
    gnss_flag_ = true;
}

void CarOffRoadChecker::gridmapCallback(const grid_map_msgs::GridMap::ConstPtr& msg)
{
    grid_map::GridMapRosConverter::fromMessage(*msg, gridmap_);
    gridmap_flag_ = true;
}

CarOffRoadChecker::~CarOffRoadChecker() {

}
