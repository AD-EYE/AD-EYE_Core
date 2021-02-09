#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block Emulate_Prescan_2019a/Publish
extern SimulinkPublisher<std_msgs::UInt16, SL_Bus_Emulate_Prescan_2019a_std_msgs_UInt16> Pub_Emulate_Prescan_2019a_12;

void slros_node_init(int argc, char** argv);

#endif
