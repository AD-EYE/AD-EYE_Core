//
// Created by adeye on 2021-10-08.
//

#ifndef ADEYE_GEOFENCING_CHECKER_H
#define ADEYE_GEOFENCING_CHECKER_H

#include <ros/ros.h>
#include "safety_fault_monitor.h"
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <geometry_msgs/PoseStamped.h>

class GeofencingChecker: public SafetyFaultMonitor {
private:
    ros::NodeHandle nh_;
    ros::Subscriber sub_gnss_;
    ros::Subscriber sub_gridmap_;
    geometry_msgs::Pose pose_;
    grid_map::GridMap gridmap_;
    bool gnss_flag_ = false;
    bool gridmap_flag_ = false;

    // ODD Polygon coordinates
    // Format:- ODD_coordinates_ = {x1, y1, x2, y2, x3, y3, x4, y4}
    std::vector<double> ODD_coordinates_, ODD_default_gridmap_coordinates_;

    bool hasTestFailed() override;

    /*!
     * \brief Gnss Callback : Called when the gnss information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates gnss information of the vehicle position.
     */
    void gnssCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);

    /*!
     * \brief Gridmap Callback : Called when the gridmap information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Updates the gridmap information.
     */
    void gridmapCallback(const grid_map_msgs::GridMap::ConstPtr& msg);

    /*!
     * \brief Check if the vector of operational design domain polygon coordinates is valid.
     * \return Boolean indicating true if the operational design domain polygon coordinates are exactly into pairs.
     * \param polygon_coordinates The function takes one input parameter which contains polygon coordinates.
     */
    bool isPolygonValid(std::vector<double> polygon_coordinates);

    /*!
 * \brief The function where the operational design domain polygon has been created.
 * \details Polygon iterator creates the polygon according to given coordinates.
 * \param polygon_coordinates The function takes one input parameter which contains polygon coordinates.
 */
    void defineOperationalDesignDomain(std::vector<double> polygon_coordinates);

public:
    GeofencingChecker(int increment_value, int decrement_value, int high_threshold, int low_threshold);
    ~GeofencingChecker();
    void writeGeofencingOnGridmap(const std::vector<double> &polygon_coordinates);
};


#endif //ADEYE_GEOFENCING_CHECKER_H
