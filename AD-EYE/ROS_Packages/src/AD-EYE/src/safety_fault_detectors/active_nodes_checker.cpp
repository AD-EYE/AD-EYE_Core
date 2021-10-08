//
// Created by adeye on 2021-10-08.
//


#include <ros/ros.h>
#include "safety_fault_detectors/active_nodes_checker.h"

ActiveNodeChecker::ActiveNodeChecker(int increment_value, int decrement_value, int high_threshold, int low_threshold, int criticality_level, ros::NodeHandle& nh): SafetyFaultDetector(increment_value, decrement_value, high_threshold, low_threshold), nh_(nh)
{
    switch (criticality_level) {
        case 1:
            retrieveNodesToCheckParam("critical_nodes_level_one");
            break;
        case 2:
            retrieveNodesToCheckParam("critical_nodes_level_two");
            break;
        case 3:
            retrieveNodesToCheckParam("critical_nodes_level_three");
            break;
        case 4:
            retrieveNodesToCheckParam("critical_nodes_level_four");
            break;
        default:
            ROS_ERROR("criticality_level is wrong, list of nodes to check will be empty");

    }
}

void ActiveNodeChecker::retrieveNodesToCheckParam(const char* param_name) {
    ros::NodeHandle nh;
    if (nh.hasParam(param_name))
        nh.getParam(param_name, nodes_to_check_);
    else
        ROS_ERROR("Failed to retrieve rosparam %s", param_name);
}

/*!
 * \brief Check if the given nodes are alive
 * \param nodes_to_check vector containing the names of the nodes to check
 */
bool ActiveNodeChecker::areNodesAlive()
{
    ros::V_string nodes_alive;
    ros::master::getNodes(nodes_alive);
    for(auto node : nodes_to_check_){
        if(std::find(nodes_alive.begin(), nodes_alive.end(), node) == nodes_alive.end()){
            std::cout << "ERROR: " << node << " was not found" << '\n';
            return false;
        }
    }
    return true;
}

bool ActiveNodeChecker::isFailingRightNow() {

    return areNodesAlive();
}