//
// Created by adeye on 2021-10-11.
//

#include <cpp_utils/pose_datatypes.h>
#include "safety_fault_monitors/obstacles_in_critical_area_checker.h"

ObstaclesInCriticalAreaChecker::ObstaclesInCriticalAreaChecker(int increment_value, int decrement_value, int high_threshold, int low_threshold):
        SafetyFaultMonitor(increment_value, decrement_value, high_threshold, low_threshold)
{
    sub_gnss_ = nh_.subscribe<geometry_msgs::PoseStamped>("/ground_truth_pose", 100, &ObstaclesInCriticalAreaChecker::gnssCallback, this);
    sub_gridmap_ = nh_.subscribe<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, &ObstaclesInCriticalAreaChecker::gridmapCallback, this);
    sub_autoware_trajectory_ = nh_.subscribe<autoware_msgs::Lane>("/final_waypoints", 1, &ObstaclesInCriticalAreaChecker::autowareTrajectoryCallback, this);
    sub_current_velocity_ = nh_.subscribe("/current_velocity", 1, &ObstaclesInCriticalAreaChecker::currentVelocityCallback, this);
    pub_critical_area_ = nh_.advertise<visualization_msgs::Marker>("/critical_area", 1, true);  //Used for critical area visualization
}

/*!
     * \brief Get distance : Called to calculate the distance between two points
       \param x_one, x_two, y_one, y_two The inputs contains the waypoints coordinates .
     * \return Distance between 2 points
     */
double ObstaclesInCriticalAreaChecker::getDistance(double x_one, double x_two, double y_one, double y_two)
{
    return pow(pow(x_one - x_two, 2) + pow(y_one - y_two, 2), 0.5);
}

/*!
     * \brief Check dynamic objects : Called at every iteration of the main loop
     * \Checks if there is a dynamic object in the critical area
     * \return Boolean indicating the presence of an obstacle in the critical area
     */
bool ObstaclesInCriticalAreaChecker::isObjectInCriticalArea()
{
    updateCriticalAreaSize();

    updateCriticalAreaShape();

    publishCriticalAreaVisualization();

    for(grid_map::PolygonIterator areaIt(gridmap_, critical_area_) ; !areaIt.isPastEnd() ; ++areaIt)
    {
        int value = gridmap_.at("DynamicObjects", *areaIt);
        if(gridmap_.at("DynamicObjects", *areaIt) > 0)
        { //If there is something inside the area
            ROS_WARN_THROTTLE(1, "There is a dynamic object in the critical Area !");
            return true;
        }
    }
    return false;
}

void ObstaclesInCriticalAreaChecker::publishCriticalAreaVisualization() const {
    visualization_msgs::Marker criticalAreaMarker;  //Used for demo critical area visualization
    std_msgs::ColorRGBA color;
    color.r = 1.0;
    color.a = 1.0;
    grid_map::PolygonRosConverter::toLineMarker(critical_area_, color, 0.2, 0.5, criticalAreaMarker);
    criticalAreaMarker.header.frame_id = gridmap_.getFrameId();
    criticalAreaMarker.header.stamp.fromNSec(gridmap_.getTimestamp());
    pub_critical_area_.publish(criticalAreaMarker);
}

void ObstaclesInCriticalAreaChecker::updateCriticalAreaShape() {// Remove critical area vertices
    critical_area_.removeVertices();

    // Initiate the index value and length for getting the critical area length
    int index = 0;
    double length = 0;

    // `For` loop for finding an index value from autoware trajectory to set the critical area length
    for (int k = 0; k < autowareTrajectory_.waypoints.size() - 1; k++)
    {
        // Calculate the distance between two autoware trajectory waypoints through euclidean distance equation
        double distance_between_two_waypoints = getDistance(autowareTrajectory_.waypoints.at(k + 1).pose.pose.position.x, autowareTrajectory_.waypoints.at(k).pose.pose.position.x, autowareTrajectory_.waypoints.at(k + 1).pose.pose.position.y, autowareTrajectory_.waypoints.at(k).pose.pose.position.y);

        // Add the distance between two waypoints into the length
        length += distance_between_two_waypoints;

        // If the length from autoware trajectory is higher than critical area length, store the index value
        if (length >= critical_area_length_)
        {
            // Store the index value and break the loop
            index = k;
            break;
        }
    }
    if (length < critical_area_length_)
    {
        // Store the index value and break the loop
        index = autowareTrajectory_.waypoints.size() - 1;
    }

    // Creating the critical area polygon through two `for` loops
// First `for` loop define the vertices for one side of the critical area
    for (int i = 0; i <= index; i++)
    {
        float yaw = cpp_utils::extract_yaw(autowareTrajectory_.waypoints.at(i).pose.pose.orientation);
        critical_area_.addVertex(grid_map::Position(
                autowareTrajectory_.waypoints.at(i).pose.pose.position.x - sin(yaw) * critical_area_width_ / 2,
                autowareTrajectory_.waypoints.at(i).pose.pose.position.y + cos(yaw) * critical_area_width_ / 2));
    }

    // Second `for` loop define the vertices for other side of the critical area
    for (int j = index; j >= 0; j--)
    {
        float yaw = cpp_utils::extract_yaw(autowareTrajectory_.waypoints.at(j).pose.pose.orientation);
        critical_area_.addVertex(grid_map::Position(
                autowareTrajectory_.waypoints.at(j).pose.pose.position.x + sin(yaw) * critical_area_width_ / 2,
                autowareTrajectory_.waypoints.at(j).pose.pose.position.y - cos(yaw) * critical_area_width_ / 2));
    }
}


void ObstaclesInCriticalAreaChecker::gnssCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    geometry_msgs::PoseStamped gnss = *msg;
    pose_ = gnss.pose;
    gnss_flag_ = true;
}

void ObstaclesInCriticalAreaChecker::gridmapCallback(const grid_map_msgs::GridMap::ConstPtr& msg)
{
    grid_map::GridMapRosConverter::fromMessage(*msg, gridmap_);
    gridmap_flag_ = true;
}


void ObstaclesInCriticalAreaChecker::autowareTrajectoryCallback(const autoware_msgs::Lane::ConstPtr& msg)
{
    autowareTrajectory_ = *msg;
    trajectory_flag_ = true;
}

/*!
     * \brief currentVelocity Callback : Updates the knowledge about the car speed.
     * \param msg A smart pointer to the message from the topic.
     */
void ObstaclesInCriticalAreaChecker::currentVelocityCallback(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
    current_velocity_ = msg->twist.linear.x;
}

bool ObstaclesInCriticalAreaChecker::isFailingRightNow() {
    if(!gridmap_flag_ || !gnss_flag_ || !trajectory_flag_ || autowareTrajectory_.waypoints.empty())
        return true;
    else
        return isObjectInCriticalArea();
}

void ObstaclesInCriticalAreaChecker::updateCriticalAreaSize() {
    const float x = pose_.position.x;    //Center is currently in the front of the car
    const float y = pose_.position.y;
    const float yaw = cpp_utils::extract_yaw(pose_.orientation);
    const grid_map::Position center(x + car_length_ * cos(yaw)/2, y + car_length_ * sin(yaw)/2);
    critical_area_length_ = car_length_  + current_velocity_;

    if(!car_size_set_)
    {
        if (nh_.getParam("car_width_", car_width_) && nh_.getParam("car_length_", car_length_))
        {
            critical_area_length_ = car_length_; //Size of the critical Area
            critical_area_width_ = car_width_ * 1.2;
            car_size_set_ = true;
        }
    }
}
