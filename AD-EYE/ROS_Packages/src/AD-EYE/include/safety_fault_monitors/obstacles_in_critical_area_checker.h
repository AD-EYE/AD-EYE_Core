//
// Created by adeye on 2021-10-11.
//

#ifndef ADEYE_OBSTACLES_IN_CRITICAL_AREA_CHECKER_H
#define ADEYE_OBSTACLES_IN_CRITICAL_AREA_CHECKER_H


#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <geometry_msgs/PoseStamped.h>
#include <autoware_msgs/Lane.h>


#include "safety_fault_monitor.h"

class ObstaclesInCriticalAreaChecker: public SafetyFaultMonitor {
private:
    ros::NodeHandle nh_;
    ros::Subscriber sub_gnss_;
    ros::Subscriber sub_gridmap_;
    ros::Subscriber sub_autoware_trajectory_;
    ros::Subscriber sub_current_velocity_;
    ros::Publisher pub_critical_area_;  //Used for critical area visualization
    autoware_msgs::Lane autowareTrajectory_;
    geometry_msgs::Pose pose_;
    grid_map::GridMap gridmap_;
    bool gnss_flag_ = false;
    bool gridmap_flag_ = false;
    bool trajectory_flag_ = false;
    float current_velocity_ = 0;

    //Critical area
    float car_length_ = 5;
    float car_width_ = 2;
    bool car_size_set_ = false;
    float critical_area_length_ = car_length_; //Size of the critical Area
    float critical_area_width_ = car_width_ * 1.2;
    grid_map::Polygon critical_area_;


    bool isFailingRightNow() override;


    /*!
     * \brief Check dynamic objects : Called at every iteration of the main loop
     * \Checks if there is a dynamic object in the critical area
     * \return Boolean indicating the presence of an obstacle in the critical area
     */
    bool isObjectInCriticalArea();

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

    /*!
     * \brief Autoware trajectory Callback : Called when the trajectory from autoware has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates the autoware trajectory information.
     */
    void autowareTrajectoryCallback(const autoware_msgs::Lane::ConstPtr& msg);

    /*!
     * \brief currentVelocity Callback : Updates the knowledge about the car speed.
     * \param msg A smart pointer to the message from the topic.
     */
    void currentVelocityCallback(const geometry_msgs::TwistStamped::ConstPtr& msg);

    static double getDistance(double x_one, double x_two, double y_one, double y_two);

    void updateCriticalAreaSize();

    void updateCriticalAreaShape();

    void publishCriticalAreaVisualization() const;


public:

    ObstaclesInCriticalAreaChecker(int increment_value, int decrement_value, int high_threshold, int low_threshold);

};


#endif //ADEYE_OBSTACLES_IN_CRITICAL_AREA_CHECKER_H
