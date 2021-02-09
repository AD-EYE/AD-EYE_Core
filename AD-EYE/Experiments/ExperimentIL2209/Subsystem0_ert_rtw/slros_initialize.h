#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block Subsystem0/Publish
extern SimulinkPublisher<std_msgs::Float32, SL_Bus_Subsystem0_std_msgs_Float32> Pub_Subsystem0_5;

void slros_node_init(int argc, char** argv);

#endif
