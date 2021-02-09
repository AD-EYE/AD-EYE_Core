#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block ros_subsystem/Publish
extern SimulinkPublisher<std_msgs::Float32, SL_Bus_ros_subsystem_std_msgs_Float32> Pub_ros_subsystem_5;

void slros_node_init(int argc, char** argv);

#endif
