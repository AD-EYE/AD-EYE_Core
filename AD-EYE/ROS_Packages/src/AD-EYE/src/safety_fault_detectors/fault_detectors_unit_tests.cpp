//
// Created by adeye on 2021-10-08.
//

#include <iostream>
#include <ros/ros.h>
#include <unistd.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <geometry_msgs/PoseStamped.h>

#include "safety_fault_detectors/active_nodes_checker.h"
#include "safety_fault_detectors/geofencing_checker.h"
#include "safety_fault_detectors/car_off_road_checker.h"

void TestSafetyFaultDetector() {
    class SafetyFaultDetectorTester: public SafetyFaultDetector {

    public:
        bool is_failing_test_bool = true;
        SafetyFaultDetectorTester(int increment_value, int decrement_value, int high_threshold, int low_threshold): SafetyFaultDetector(increment_value, decrement_value, high_threshold, low_threshold) {}

    private:
        bool isFailingRightNow() override
        {
            return is_failing_test_bool;
        }
    };

    SafetyFaultDetectorTester sfdt = SafetyFaultDetectorTester(1,1,2,-2);
    sfdt.is_failing_test_bool = true; // simulation that the functionality is malfunctioning so the counter will decrease
    sfdt.updateCounter();
    assert(!sfdt.isFaulty()); // has not reached high threshold so should be still passing
    sfdt.updateCounter();
    assert(sfdt.isFaulty()); // has now reach high threshold so should be failing

    sfdt.is_failing_test_bool = false; // now we simulation the functionality working again so the counter will decrease
    sfdt.updateCounter();
    sfdt.updateCounter();
    sfdt.updateCounter();
    assert(sfdt.isFaulty()); // has not reached low threshold so should be still failing
    sfdt.updateCounter();
    assert(!sfdt.isFaulty()); // has now reached low threshold so should now be passing
}

void TestIncrementNodeChecker(ros::NodeHandle nh) {
    nh.setParam("/critical_nodes_level_one", std::vector<std::string>{"/non_existing_node"});
    ActiveNodeChecker active_node_checker(1,1,4,-4,1);
//    std::cout << "active_node_checker value: " << active_node_checker.isFaulty() << std::endl;
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    bool is_faulty = active_node_checker.isFaulty();
    assert(is_faulty); // since the node to track does not exist, the module should return a fault
}

void TestDecrementNodeChecker(ros::NodeHandle nh) {
    nh.setParam("/critical_nodes_level_one", std::vector<std::string>{"/TesterNode"});
    ActiveNodeChecker active_node_checker(1,1,4,-4,1);
//    std::cout << "active_node_checker value: " << active_node_checker.isFaulty() << std::endl;
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    bool is_faulty = active_node_checker.isFaulty();
    assert(!is_faulty); // since the node to track exists, the module should return no fault
}


void TestGeofencingCheckerIn(ros::NodeHandle nh) {
    GeofencingChecker geofencing_checker(1,1,4,-4);

    nh.setParam("/operational_design_domain", std::vector<double>{0, 0, 10, 0, 10, 10, 0, 10});

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({"StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle", "Lanes", "RoadSideParking", "RestArea", "SensorSectors"});
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

    ros::Duration(0.1).sleep(); // needed to make sure the ROS msgs are received
    ros::spinOnce();

    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();

    bool is_faulty = geofencing_checker.isFaulty();
    assert(!is_faulty);
}

void TestGeofencingCheckerOut(ros::NodeHandle nh) {
    GeofencingChecker geofencing_checker(1,1,4,-4);

    nh.setParam("/operational_design_domain", std::vector<double>{0, 0, 10, 0, 10, 10, 0, 10});

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({"StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle", "Lanes", "RoadSideParking", "RestArea", "SensorSectors"});
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

    ros::Duration(0.1).sleep(); // needed to make sure the ROS msgs are received
    ros::spinOnce();

    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();

    bool is_faulty = geofencing_checker.isFaulty();
    assert(is_faulty);
}

//uses default values for the geofencing area
void TestDecrementGeofencingCheckerDefault(ros::NodeHandle nh) {
    GeofencingChecker geofencing_checker(1,1,4,-4);

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({"StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle", "Lanes", "RoadSideParking", "RestArea", "SensorSectors"});
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

    ros::Duration(0.1).sleep(); // needed to make sure the ROS msgs are received
    ros::spinOnce();

    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();

    bool is_faulty = geofencing_checker.isFaulty();
    assert(!is_faulty);
}

//uses default values for the geofencing area
void TestIncrementGeofencingCheckerDefault(ros::NodeHandle nh) {
    GeofencingChecker geofencing_checker(1,1,4,-4);

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({"StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle", "Lanes", "RoadSideParking", "RestArea", "SensorSectors"});
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

    ros::Duration(0.1).sleep(); // needed to make sure the ROS msgs are received
    ros::spinOnce();

    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();

    bool is_faulty = geofencing_checker.isFaulty();
    assert(is_faulty);
}

void TestGeofencingCheckerNoGridmap(ros::NodeHandle nh) {
    GeofencingChecker geofencing_checker(1,1,4,-4);

    ros::Publisher pub_pose = nh.advertise<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, true);
    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 2;
    pose.pose.position.y = 1;
    pub_pose.publish(pose);

    ros::Duration(0.1).sleep(); // needed to make sure the ROS msgs are received
    ros::spinOnce();

    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();

    bool is_faulty = geofencing_checker.isFaulty();
    assert(is_faulty);
}


void TestGeofencingCheckerNoGNSS(ros::NodeHandle nh) {
    GeofencingChecker geofencing_checker(1,1,4,-4);

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({"StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle", "Lanes", "RoadSideParking", "RestArea", "SensorSectors"});
    map.setFrameId("test_frame");
    map.setGeometry(grid_map::Length(50, 50), 1, grid_map::Position(0, 0));
    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(map, message);
    pub_grid_map.publish(message);

    ros::Duration(0.1).sleep(); // needed to make sure the ROS msgs are received
    ros::spinOnce();

    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();
    geofencing_checker.updateCounter();

    bool is_faulty = geofencing_checker.isFaulty();
    assert(is_faulty);
}




void TestIncrementCarOffRoadChecker(ros::NodeHandle nh) {
    CarOffRoadChecker car_off_road_checker(1,1,4,-4);

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({"StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle", "Lanes", "RoadSideParking", "RestArea", "SensorSectors"});
    map.setFrameId("test_frame");
    map.setGeometry(grid_map::Length(50, 50), 1, grid_map::Position(0, 0));
    grid_map::Polygon polygon;
    polygon.addVertex(grid_map::Position(0, 0));
    polygon.addVertex(grid_map::Position(50, 0));
    polygon.addVertex(grid_map::Position(50, 50));
    polygon.addVertex(grid_map::Position(0, 50));
    // Polygon Interator
    for (grid_map::PolygonIterator iterator(map, polygon);
         !iterator.isPastEnd(); ++iterator) {
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

    ros::Duration(0.1).sleep(); // needed to make sure the ROS msgs are received
    ros::spinOnce();

    car_off_road_checker.updateCounter();
    car_off_road_checker.updateCounter();
    car_off_road_checker.updateCounter();
    car_off_road_checker.updateCounter();

    bool is_faulty = car_off_road_checker.isFaulty();
    assert(is_faulty);
}

//uses default values for the geofencing area
void TestDecrementCarOffRoadChecker(ros::NodeHandle nh) {
    CarOffRoadChecker car_off_road_checker(1,1,4,-4);

    ros::Publisher pub_grid_map = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
    grid_map::GridMap map = grid_map::GridMap({"StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle", "Lanes", "RoadSideParking", "RestArea", "SensorSectors"});
    map.setFrameId("test_frame");
    map.setGeometry(grid_map::Length(50, 50), 1, grid_map::Position(0, 0));
    grid_map::Polygon polygon;
    polygon.addVertex(grid_map::Position(0, 0));
    polygon.addVertex(grid_map::Position(10, 0));
    polygon.addVertex(grid_map::Position(10, 10));
    polygon.addVertex(grid_map::Position(0, 10));
    // Polygon Interator
    for (grid_map::PolygonIterator iterator(map, polygon);
         !iterator.isPastEnd(); ++iterator) {
        map.at("Lanes", *iterator) = 1; // lane
    }
    grid_map_msgs::GridMap message;
    grid_map::GridMapRosConverter::toMessage(map, message);
    pub_grid_map.publish(message);

    ros::Publisher pub_pose = nh.advertise<geometry_msgs::PoseStamped>("/ground_truth_pose", 1, true);
    geometry_msgs::PoseStamped pose;
    pose.header.frame_id = "test_frame";
    pose.pose.position.x = 2;
    pose.pose.position.y = 10;
    pub_pose.publish(pose); // vehicle should be on the lane area we defined earlier

    ros::Duration(0.1).sleep(); // needed to make sure the ROS msgs are received
    ros::spinOnce();

    car_off_road_checker.updateCounter();
    car_off_road_checker.updateCounter();
    car_off_road_checker.updateCounter();
    car_off_road_checker.updateCounter();

    bool is_faulty = car_off_road_checker.isFaulty();
    assert(!is_faulty);
}


int main(int argc, char **argv) {
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
    std::cout << "All tests passed (the error messages above, if any, are printed by the different modules to indicate faults that they have detected which were set up for these tests)" << std::endl;
}