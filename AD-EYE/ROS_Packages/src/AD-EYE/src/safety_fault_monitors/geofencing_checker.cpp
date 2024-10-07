//
// Created by adeye on 2021-10-08.
//

#include "safety_fault_monitors/geofencing_checker.h"

GeofencingChecker::GeofencingChecker(int increment_value, int decrement_value, int high_threshold, int low_threshold)
  : SafetyFaultMonitor(increment_value, decrement_value, high_threshold, low_threshold)
{
    name_ = "GeofencingChecker";
    sub_gnss_ =
        nh_.subscribe<geometry_msgs::PoseStamped>("/ground_truth_pose", 100, &GeofencingChecker::gnssCallback, this);
    sub_gridmap_ =
        nh_.subscribe<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, &GeofencingChecker::gridmapCallback, this);
}

bool GeofencingChecker::hasTestFailed()
{
    //    ros::spinOnce();
    if (!gridmap_flag_ || !gnss_flag_)
        return true;
    if (nh_.getParam("/operational_design_domain", ODD_coordinates_))
    {
        defineOperationalDesignDomain(ODD_coordinates_);
    }
    else
    {
        defineOperationalDesignDomain(ODD_default_gridmap_coordinates_);
    }

    if (!gridmap_.isInside(grid_map::Position(pose_.position.x, pose_.position.y)))
    {
        ROS_WARN("The Vehicle is outside the gridmap");
        return true;  // we are out of the gridmap so for sure out of the ODD
    }
    else
    {
        // Extract the polygon area and send true if the vehicle is not in the polygon area
        float odd_value_at_ego_position =
            gridmap_.atPosition("ODD", grid_map::Position(pose_.position.x, pose_.position.y));

        if (odd_value_at_ego_position == 0)
        {
            ROS_WARN("The Vehicle is outside the geofenced polygon");
            return true;
        }
        else
        {
            ROS_INFO("The vehicle is inside the geofenced polygon");
            return false;
        }
    }
}

void GeofencingChecker::gnssCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    geometry_msgs::PoseStamped gnss = *msg;
    pose_ = gnss.pose;
    gnss_flag_ = true;
}

void GeofencingChecker::gridmapCallback(const grid_map_msgs::GridMap::ConstPtr& msg)
{
    grid_map::GridMapRosConverter::fromMessage(*msg, gridmap_);

    // Operational design domain default polygon coordinates are same as full grid map
    ODD_default_gridmap_coordinates_ = {
        gridmap_.getPosition().x() - gridmap_.getLength().x() * 0.5,
        gridmap_.getPosition().y() - gridmap_.getLength().y() * 0.5,
        gridmap_.getPosition().x() - gridmap_.getLength().x() * 0.5,
        gridmap_.getLength().y() - (gridmap_.getPosition().y() - gridmap_.getLength().y() * 0.5),
        gridmap_.getLength().x() - (gridmap_.getPosition().x() - gridmap_.getLength().x() * 0.5),
        gridmap_.getLength().y() - (gridmap_.getPosition().y() - gridmap_.getLength().y() * 0.5),
        gridmap_.getLength().x() - (gridmap_.getPosition().x() - gridmap_.getLength().x() * 0.5),
        gridmap_.getPosition().y() - gridmap_.getLength().y() * 0.5
    };
    gridmap_flag_ = true;
}

bool GeofencingChecker::isPolygonValid(std::vector<double> polygon_coordinates)
{
    if (polygon_coordinates.size() % 2 != 0)
    {
        ROS_WARN("Invalid polygon, the list defining the polygon contains an odd number of values");
        return false;
    }
    return true;
}

void GeofencingChecker::defineOperationalDesignDomain(std::vector<double> polygon_coordinates)
{
    const double ODD_LAYER_OUT_VALUE = 0.0;

    // Add new layer called ODD (Operational design domain)
    gridmap_.add("ODD", ODD_LAYER_OUT_VALUE);

    if (isPolygonValid(polygon_coordinates))
    {
        writeGeofencingOnGridmap(polygon_coordinates);
    }
}

void GeofencingChecker::writeGeofencingOnGridmap(const std::vector<double>& polygon_coordinates)
{  // Initiate the grid map ODD polygon
    // The operational design domain values
    const double ODD_LAYER_IN_VALUE = 5.0;

    grid_map::Polygon polygon;
    // Define ODD Polygon area through coordinates from ROS parameter server
    for (int i = 0; i < polygon_coordinates.size(); i += 2)
    {
        polygon.addVertex(grid_map::Position(polygon_coordinates[i], polygon_coordinates[i + 1]));
    }

    // Add again the first coordinates from the vector to close down the polygon area
    polygon.addVertex(grid_map::Position(polygon_coordinates[0], polygon_coordinates[1]));

    // Polygon Interator
    for (grid_map::PolygonIterator iterator(gridmap_, polygon); !iterator.isPastEnd(); ++iterator)
    {
        gridmap_.at("ODD", *iterator) = ODD_LAYER_IN_VALUE;
    }
}

GeofencingChecker::~GeofencingChecker()
{
}
