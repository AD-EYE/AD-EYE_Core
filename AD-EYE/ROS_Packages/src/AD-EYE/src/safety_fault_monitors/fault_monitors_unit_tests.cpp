//
// Created by adeye on 2021-10-08.
//

#include <iostream>
#include <ros/ros.h>
#include <unistd.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <geometry_msgs/PoseStamped.h>

#include "safety_fault_monitors/active_nodes_checker.h"
#include "safety_fault_monitors/geofencing_checker.h"
#include "safety_fault_monitors/car_off_road_checker.h"
#include "safety_fault_monitors/obstacles_in_critical_area_checker.h"
#include "safety_fault_monitors/sensor_checker.h"

void TestSafetyFaultDetector()
{
    class SafetyFaultDetectorTester : public SafetyFaultMonitor
    {
      public:
        bool is_failing_test_bool = true;
        SafetyFaultDetectorTester(int increment_value, int decrement_value, int high_threshold, int low_threshold)
          : SafetyFaultMonitor(increment_value, decrement_value, high_threshold, low_threshold)
        {
        }

      private:
        bool hasTestFailed() override
        {
            return is_failing_test_bool;
        }
    };

    SafetyFaultDetectorTester sfdt = SafetyFaultDetectorTester(1, 1, 2, -2);
    sfdt.is_failing_test_bool =
        true;  // simulation that the functionality is malfunctioning so the counter will decrease
    sfdt.update();
    assert(!sfdt.isFaultConfirmed());  // has not reached high threshold so should be still passing
    sfdt.update();
    assert(sfdt.isFaultConfirmed());  // has now reach high threshold so should be failing

    sfdt.is_failing_test_bool =
        false;  // now we simulation the functionality working again so the counter will decrease
    sfdt.update();
    sfdt.update();
    sfdt.update();
    assert(sfdt.isFaultConfirmed());  // has not reached low threshold so should be still failing
    sfdt.update();
    assert(!sfdt.isFaultConfirmed());  // has now reached low threshold so should now be passing
}

void TestIncrementNodeChecker(ros::NodeHandle nh)
{
    nh.setParam("/critical_nodes_level_one", std::vector<std::string>{ "/non_existing_node" });
    ActiveNodeChecker active_node_checker(1, 1, 4, -4, 1);
    //    std::cout << "active_node_checker value: " << active_node_checker.isFaultConfirmed() << std::endl;
    active_node_checker.update();
    active_node_checker.update();
    active_node_checker.update();
    active_node_checker.update();
    bool is_faulty = active_node_checker.isFaultConfirmed();
    assert(is_faulty);  // since the node to track does not exist, the module should return a fault
}

void TestDecrementNodeChecker(ros::NodeHandle nh)
{
    nh.setParam("/critical_nodes_level_one", std::vector<std::string>{ "/TesterNode" });
    ActiveNodeChecker active_node_checker(1, 1, 4, -4, 1);
    //    std::cout << "active_node_checker value: " << active_node_checker.isFaultConfirmed() << std::endl;
    active_node_checker.update();
    active_node_checker.update();
    active_node_checker.update();
    active_node_checker.update();
    bool is_faulty = active_node_checker.isFaultConfirmed();
    assert(!is_faulty);  // since the node to track exists, the module should return no fault
}

void TestGeofencingCheckerIn(ros::NodeHandle nh)
{
    GeofencingChecker geofencing_checker(1, 1, 4, -4);

    nh.setParam("/operational_design_domain", std::vector<double>{ 0, 0, 10, 0, 10, 10, 0, 10 });

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({ "StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle",
                                                "Lanes", "RoadSideParking", "RestArea", "SensorSectors" });
    map.setFrameId("test_frame");
    map.setGeometry(grid_map::Length(50, 50), 1, grid_map::Position(0, 0));
    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(map, message);
    pub_grid_map.publish(message);

    ros::Publisher pub_pose = nh.advertise<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, true);
    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 2;
    pose.pose.position.y = 1;
    pub_pose.publish(pose);

    ros::Duration(0.1).sleep();  // needed to make sure the ROS msgs are received
    ros::spinOnce();

    geofencing_checker.update();
    geofencing_checker.update();
    geofencing_checker.update();
    geofencing_checker.update();

    bool is_faulty = geofencing_checker.isFaultConfirmed();
    assert(!is_faulty);
}

void TestGeofencingCheckerOut(ros::NodeHandle nh)
{
    GeofencingChecker geofencing_checker(1, 1, 4, -4);

    nh.setParam("/operational_design_domain", std::vector<double>{ 0, 0, 10, 0, 10, 10, 0, 10 });

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({ "StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle",
                                                "Lanes", "RoadSideParking", "RestArea", "SensorSectors" });
    map.setFrameId("test_frame");
    map.setGeometry(grid_map::Length(50, 50), 1, grid_map::Position(0, 0));
    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(map, message);
    pub_grid_map.publish(message);

    ros::Publisher pub_pose = nh.advertise<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, true);
    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 20;
    pose.pose.position.y = 15;
    pub_pose.publish(pose);

    ros::Duration(0.1).sleep();  // needed to make sure the ROS msgs are received
    ros::spinOnce();

    geofencing_checker.update();
    geofencing_checker.update();
    geofencing_checker.update();
    geofencing_checker.update();

    bool is_faulty = geofencing_checker.isFaultConfirmed();
    assert(is_faulty);
}

// uses default values for the geofencing area
void TestDecrementGeofencingCheckerDefault(ros::NodeHandle nh)
{
    GeofencingChecker geofencing_checker(1, 1, 4, -4);

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({ "StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle",
                                                "Lanes", "RoadSideParking", "RestArea", "SensorSectors" });
    map.setFrameId("test_frame");
    map.setGeometry(grid_map::Length(50, 50), 1, grid_map::Position(0, 0));
    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(map, message);
    pub_grid_map.publish(message);

    ros::Publisher pub_pose = nh.advertise<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, true);
    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 2;
    pose.pose.position.y = 1;
    pub_pose.publish(pose);

    ros::Duration(0.1).sleep();  // needed to make sure the ROS msgs are received
    ros::spinOnce();

    geofencing_checker.update();
    geofencing_checker.update();
    geofencing_checker.update();
    geofencing_checker.update();

    bool is_faulty = geofencing_checker.isFaultConfirmed();
    assert(!is_faulty);
}

// uses default values for the geofencing area
void TestIncrementGeofencingCheckerDefault(ros::NodeHandle nh)
{
    GeofencingChecker geofencing_checker(1, 1, 4, -4);

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({ "StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle",
                                                "Lanes", "RoadSideParking", "RestArea", "SensorSectors" });
    map.setFrameId("test_frame");
    map.setGeometry(grid_map::Length(50, 50), 1, grid_map::Position(0, 0));
    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(map, message);
    pub_grid_map.publish(message);

    ros::Publisher pub_pose = nh.advertise<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, true);
    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 2;
    pose.pose.position.y = -100;
    pub_pose.publish(pose);

    ros::Duration(0.1).sleep();  // needed to make sure the ROS msgs are received
    ros::spinOnce();

    geofencing_checker.update();
    geofencing_checker.update();
    geofencing_checker.update();
    geofencing_checker.update();

    bool is_faulty = geofencing_checker.isFaultConfirmed();
    assert(is_faulty);
}

void TestGeofencingCheckerNoGridmap(ros::NodeHandle nh)
{
    GeofencingChecker geofencing_checker(1, 1, 4, -4);

    ros::Publisher pub_pose = nh.advertise<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, true);
    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 2;
    pose.pose.position.y = 1;
    pub_pose.publish(pose);

    ros::Duration(0.1).sleep();  // needed to make sure the ROS msgs are received
    ros::spinOnce();

    geofencing_checker.update();
    geofencing_checker.update();
    geofencing_checker.update();
    geofencing_checker.update();

    bool is_faulty = geofencing_checker.isFaultConfirmed();
    assert(is_faulty);
}

void TestGeofencingCheckerNoGNSS(ros::NodeHandle nh)
{
    GeofencingChecker geofencing_checker(1, 1, 4, -4);

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({ "StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle",
                                                "Lanes", "RoadSideParking", "RestArea", "SensorSectors" });
    map.setFrameId("test_frame");
    map.setGeometry(grid_map::Length(50, 50), 1, grid_map::Position(0, 0));
    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(map, message);
    pub_grid_map.publish(message);

    ros::Duration(0.1).sleep();  // needed to make sure the ROS msgs are received
    ros::spinOnce();

    geofencing_checker.update();
    geofencing_checker.update();
    geofencing_checker.update();
    geofencing_checker.update();

    bool is_faulty = geofencing_checker.isFaultConfirmed();
    assert(is_faulty);
}

void TestIncrementCarOffRoadChecker(ros::NodeHandle nh)
{
    CarOffRoadChecker car_off_road_checker(1, 1, 4, -4);

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({ "StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle",
                                                "Lanes", "RoadSideParking", "RestArea", "SensorSectors" });
    map.setFrameId("test_frame");
    map.setGeometry(grid_map::Length(50, 50), 1, grid_map::Position(0, 0));
    grid_map::Polygon polygon;
    polygon.addVertex(grid_map::Position(0, 0));
    polygon.addVertex(grid_map::Position(50, 0));
    polygon.addVertex(grid_map::Position(50, 50));
    polygon.addVertex(grid_map::Position(0, 50));
    // Polygon Interator
    for (grid_map::PolygonIterator iterator(map, polygon); !iterator.isPastEnd(); ++iterator)
    {
        map.at("Lanes", *iterator) = 0;
    }
    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(map, message);
    pub_grid_map.publish(message);

    ros::Publisher pub_pose = nh.advertise<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, true);
    geometry_msgs::PoseStamped pose;
    pose.header.frame_id = "test_frame";
    pose.pose.position.x = 2;
    pose.pose.position.y = 10;
    pub_pose.publish(pose);

    ros::Duration(0.1).sleep();  // needed to make sure the ROS msgs are received
    ros::spinOnce();

    car_off_road_checker.update();
    car_off_road_checker.update();
    car_off_road_checker.update();
    car_off_road_checker.update();

    bool is_faulty = car_off_road_checker.isFaultConfirmed();
    assert(is_faulty);
}

void TestDecrementCarOffRoadChecker(ros::NodeHandle nh)
{
    CarOffRoadChecker car_off_road_checker(1, 1, 4, -4);

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({ "StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle",
                                                "Lanes", "RoadSideParking", "RestArea", "SensorSectors" });
    map.setFrameId("test_frame");
    map.setGeometry(grid_map::Length(50, 50), 1, grid_map::Position(0, 0));
    grid_map::Polygon polygon;
    polygon.addVertex(grid_map::Position(0, 0));
    polygon.addVertex(grid_map::Position(10, 0));
    polygon.addVertex(grid_map::Position(10, 10));
    polygon.addVertex(grid_map::Position(0, 10));
    // Polygon Interator
    for (grid_map::PolygonIterator iterator(map, polygon); !iterator.isPastEnd(); ++iterator)
    {
        map.at("Lanes", *iterator) = 1;  // lane
    }
    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(map, message);
    pub_grid_map.publish(message);

    ros::Publisher pub_pose = nh.advertise<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, true);
    geometry_msgs::PoseStamped pose;
    pose.header.frame_id = "test_frame";
    pose.pose.position.x = 2;
    pose.pose.position.y = 10;
    pub_pose.publish(pose);  // vehicle should be on the lane area we defined earlier

    ros::Duration(0.1).sleep();  // needed to make sure the ROS msgs are received
    ros::spinOnce();

    car_off_road_checker.update();
    car_off_road_checker.update();
    car_off_road_checker.update();
    car_off_road_checker.update();

    bool is_faulty = car_off_road_checker.isFaultConfirmed();
    assert(!is_faulty);
}

void TestNoObstacleInCriticalArea(ros::NodeHandle nh)
{
    ObstaclesInCriticalAreaChecker obstacle_checker(1, 1, 4, -4);

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({ "StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle",
                                                "Lanes", "RoadSideParking", "RestArea", "SensorSectors" });
    map.setFrameId("test_frame");
    map.setGeometry(grid_map::Length(50, 50), 1, grid_map::Position(0, 0));
    grid_map::Polygon polygon;
    polygon.addVertex(grid_map::Position(0, 0));
    polygon.addVertex(grid_map::Position(10, 0));
    polygon.addVertex(grid_map::Position(10, 10));
    polygon.addVertex(grid_map::Position(0, 10));
    // Polygon Interator
    for (grid_map::PolygonIterator iterator(map, polygon); !iterator.isPastEnd(); ++iterator)
    {
        map.at("DynamicObjects", *iterator) = 1;  // lane
    }
    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(map, message);
    pub_grid_map.publish(message);

    ros::Publisher pub_pose = nh.advertise<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, true);
    geometry_msgs::PoseStamped pose;
    pose.header.frame_id = "test_frame";
    pose.pose.position.x = 2;
    pose.pose.position.y = 15;
    pub_pose.publish(pose);  // vehicle should be on the lane area we defined earlier

    ros::Publisher pub_velocity = nh.advertise<geometry_msgs::TwistStamped>("/current_velocity", 1, true);
    geometry_msgs::TwistStamped twist;
    twist.twist.linear.x = 0.5;
    pub_velocity.publish(twist);

    ros::Publisher pub_trajectory = nh.advertise<autoware_msgs::Lane>("/final_waypoints", 1, true);
    autoware_msgs::Lane trajectory_msg;
    autoware_msgs::Waypoint wp1;
    wp1.pose = pose;
    wp1.pose.pose.orientation.w = 1;
    trajectory_msg.waypoints.push_back(wp1);
    autoware_msgs::Waypoint wp2 = wp1;
    wp2.pose.pose.position.x = pose.pose.position.x + 2;
    trajectory_msg.waypoints.push_back(wp2);
    autoware_msgs::Waypoint wp3 = wp1;
    wp3.pose.pose.position.x = pose.pose.position.x + 4;
    trajectory_msg.waypoints.push_back(wp3);
    pub_trajectory.publish(trajectory_msg);

    ros::Duration(0.1).sleep();  // needed to make sure the ROS msgs are received
    ros::spinOnce();

    obstacle_checker.update();
    obstacle_checker.update();
    obstacle_checker.update();
    obstacle_checker.update();

    bool is_faulty = obstacle_checker.isFaultConfirmed();
    assert(!is_faulty);
}

void TestObstacleInCriticalArea(ros::NodeHandle nh)
{
    ObstaclesInCriticalAreaChecker obstacle_checker(1, 1, 4, -4);

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({ "StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle",
                                                "Lanes", "RoadSideParking", "RestArea", "SensorSectors" });
    map.setFrameId("test_frame");
    map.setGeometry(grid_map::Length(50, 50), 1, grid_map::Position(0, 0));
    grid_map::Polygon polygon;
    polygon.addVertex(grid_map::Position(15, 15));
    polygon.addVertex(grid_map::Position(25, 15));
    polygon.addVertex(grid_map::Position(25, 25));
    polygon.addVertex(grid_map::Position(15, 25));
    // Polygon Interator
    for (grid_map::PolygonIterator iterator(map, polygon); !iterator.isPastEnd(); ++iterator)
    {
        map.at("DynamicObjects", *iterator) = 1;  // lane
    }
    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(map, message);
    pub_grid_map.publish(message);

    ros::Publisher pub_pose = nh.advertise<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, true);
    geometry_msgs::PoseStamped pose;
    pose.header.frame_id = "test_frame";
    pose.pose.position.x = 16;
    pose.pose.position.y = 17;
    pose.pose.orientation.w = 1;
    pub_pose.publish(pose);  // vehicle should be on the lane area we defined earlier

    ros::Publisher pub_velocity = nh.advertise<geometry_msgs::TwistStamped>("/current_velocity", 1, true);
    geometry_msgs::TwistStamped twist;
    twist.twist.linear.x = 0.5;
    pub_velocity.publish(twist);

    ros::Publisher pub_trajectory = nh.advertise<autoware_msgs::Lane>("/final_waypoints", 1, true);
    autoware_msgs::Lane trajectory_msg;
    autoware_msgs::Waypoint wp1;
    wp1.pose = pose;
    wp1.pose.pose.orientation.w = 1;
    trajectory_msg.waypoints.push_back(wp1);
    autoware_msgs::Waypoint wp2 = wp1;
    wp2.pose.pose.position.x = pose.pose.position.x + 2;
    trajectory_msg.waypoints.push_back(wp2);
    autoware_msgs::Waypoint wp3 = wp1;
    wp3.pose.pose.position.x = pose.pose.position.x + 4;
    trajectory_msg.waypoints.push_back(wp3);
    pub_trajectory.publish(trajectory_msg);

    ros::Duration(0.1).sleep();  // needed to make sure the ROS msgs are received
    ros::spinOnce();

    obstacle_checker.update();
    obstacle_checker.update();
    obstacle_checker.update();
    obstacle_checker.update();

    bool is_faulty = obstacle_checker.isFaultConfirmed();
    assert(is_faulty);
}

void TestSensorCheckerNoSensorMsg(ros::NodeHandle nh)
{
    SensorChecker sensor_checker(1, 1, 4, -4, SENSOR_TYPE::lidar);

    sensor_checker.update();
    sensor_checker.update();
    sensor_checker.update();
    sensor_checker.update();
    assert(sensor_checker.isFaultConfirmed());  // since no sensor msg was published, the module should return fault
}

void TestSensorCheckerGoodSensorMsg(ros::NodeHandle nh)
{
    SensorChecker sensor_checker(1, 1, 4, -4, SENSOR_TYPE::lidar);

    ros::Publisher sensor_poly_pub = nh.advertise<jsk_recognition_msgs::PolygonArray>("sensor_fov", 1, true);
    jsk_recognition_msgs::PolygonArray poly_array_msg;
    geometry_msgs::PolygonStamped poly;
    geometry_msgs::Point32 pt;
    poly.polygon.points.push_back(pt);
    poly.polygon.points.push_back(pt);
    poly_array_msg.polygons.push_back(poly);
    poly_array_msg.polygons.push_back(poly);
    poly_array_msg.polygons.push_back(poly);
    poly_array_msg.polygons.push_back(poly);
    poly_array_msg.polygons.push_back(poly);
    sensor_poly_pub.publish(poly_array_msg);

    ros::Duration(0.1).sleep();  // needed to make sure the ROS msgs are received
    ros::spinOnce();

    sensor_checker.update();
    sensor_checker.update();
    sensor_checker.update();
    sensor_checker.update();
    assert(!sensor_checker.isFaultConfirmed());  // since no sensor msg was published, the module should return fault
}

void TestSensorCheckerBadSensorMsg(ros::NodeHandle nh)
{
    SensorChecker sensor_checker(1, 1, 4, -4, SENSOR_TYPE::lidar);

    ros::Publisher sensor_poly_pub = nh.advertise<jsk_recognition_msgs::PolygonArray>("sensor_fov", 1, true);
    jsk_recognition_msgs::PolygonArray poly_array_msg;
    geometry_msgs::PolygonStamped poly;
    geometry_msgs::Point32 pt;
    poly.polygon.points.push_back(pt);
    poly.polygon.points.push_back(pt);
    poly_array_msg.polygons.push_back(poly);
    geometry_msgs::PolygonStamped empty_poly;
    poly_array_msg.polygons.push_back(empty_poly);
    poly_array_msg.polygons.push_back(empty_poly);
    poly_array_msg.polygons.push_back(empty_poly);
    poly_array_msg.polygons.push_back(empty_poly);
    sensor_poly_pub.publish(poly_array_msg);

    ros::Duration(0.1).sleep();  // needed to make sure the ROS msgs are received
    ros::spinOnce();

    sensor_checker.update();
    sensor_checker.update();
    sensor_checker.update();
    sensor_checker.update();
    assert(sensor_checker.isFaultConfirmed());  // since no sensor msg was published, the module should return fault
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "TesterNode");
    ros::NodeHandle nh;
    TestSafetyFaultDetector();
    TestIncrementNodeChecker(nh);
    TestDecrementNodeChecker(nh);
    TestGeofencingCheckerIn(nh);
    TestGeofencingCheckerOut(nh);
    TestIncrementGeofencingCheckerDefault(nh);
    TestDecrementGeofencingCheckerDefault(nh);
    TestGeofencingCheckerNoGridmap(nh);
    TestGeofencingCheckerNoGNSS(nh);
    TestIncrementCarOffRoadChecker(nh);
    TestDecrementCarOffRoadChecker(nh);
    TestNoObstacleInCriticalArea(nh);
    TestObstacleInCriticalArea(nh);
    TestSensorCheckerNoSensorMsg(nh);
    TestSensorCheckerGoodSensorMsg(nh);
    TestSensorCheckerBadSensorMsg(nh);
    std::cout << "All tests passed (the error messages above, if any, are printed by the different modules to indicate "
                 "faults that they have detected which were set up for these tests)"
              << std::endl;
}