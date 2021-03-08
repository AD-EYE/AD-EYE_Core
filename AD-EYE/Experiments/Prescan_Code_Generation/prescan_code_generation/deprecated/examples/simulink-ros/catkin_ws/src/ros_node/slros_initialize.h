#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block ros_node/Publish
extern SimulinkPublisher<std_msgs::UInt8, SL_Bus_ros_node_std_msgs_UInt8> Pub_ros_node_2;

void slros_node_init(int argc, char** argv);

#endif
