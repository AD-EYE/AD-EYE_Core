//
// Created by adeye on 2021-10-08.
//

#include <iostream>
#include <ros/ros.h>
#include <unistd.h>

#include "safety_fault_detectors/active_nodes_checker.h"

void TestIncrement(ros::NodeHandle nh) {
    nh.setParam("/critical_nodes_level_one", std::vector<std::string>{"/non_existing_node"});
    ActiveNodeChecker active_node_checker(1,1,4,4,1, nh);
//    std::cout << "active_node_checker value: " << active_node_checker.isFaulty() << std::endl;
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
//    std::cout << "active_node_checker value: " << active_node_checker.isFaulty() << std::endl;
    assert(active_node_checker.isFaulty() == 0); // since the node to track does not exist, the module should return a fault

}

void TestDecrement(ros::NodeHandle nh) {
    nh.setParam("/critical_nodes_level_one", std::vector<std::string>{"/TesterNode"});
    ActiveNodeChecker active_node_checker(1,1,4,4,1, nh);
//    std::cout << "active_node_checker value: " << active_node_checker.isFaulty() << std::endl;
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    assert(active_node_checker.isFaulty() == 1); // since the node to track exists, the module should return no fault
//    std::cout << "active_node_checker value: " << active_node_checker.isFaulty() << std::endl;

}


int main(int argc, char **argv) {
    ros::init(argc, argv, "TesterNode");
    ros::NodeHandle nh;
    TestIncrement(nh);
    TestDecrement(nh);
}