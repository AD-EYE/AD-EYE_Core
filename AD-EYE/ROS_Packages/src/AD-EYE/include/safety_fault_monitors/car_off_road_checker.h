//
// Created by adeye on 2021-10-11.
//

#ifndef ADEYE_CAR_OFF_ROAD_CHECKER_H
#define ADEYE_CAR_OFF_ROAD_CHECKER_H


#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <geometry_msgs/PoseStamped.h>

#include "safety_fault_monitor.h"


class CarOffRoadChecker: public SafetyFaultMonitor {
private:
    ros::NodeHandle nh_;
    ros::Subscriber sub_gnss_;
    ros::Subscriber sub_gridmap_;
    geometry_msgs::Pose pose_;
    grid_map::GridMap gridmap_;
    bool gnss_flag_ = false;
    bool gridmap_flag_ = false;

    bool isFailingRightNow() override;

    /*!
     * \brief Check car off road : Called at every iteration of the main loop
     * \return Boolean indicating if the center of the car is off the road
     */
    bool isCarOffRoad();

    /*!
     * \brief Gridmap Callback : Called when the gridmap information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates the gridmap information.
     */
    void gridmapCallback(const grid_map_msgs::GridMap::ConstPtr& msg);

    /*!
     * \brief Gnss Callback : Called when the gnss information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates gnss information of the vehicle position.
     */
    void gnssCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);

public:
    CarOffRoadChecker(int increment_value, int decrement_value, int high_threshold, int low_threshold);
};


#endif //ADEYE_CAR_OFF_ROAD_CHECKER_H
