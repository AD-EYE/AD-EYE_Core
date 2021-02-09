#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "Emulate_Prescan_2019a";

// For Block Emulate_Prescan_2019a/Publish
SimulinkPublisher<std_msgs::UInt16, SL_Bus_Emulate_Prescan_2019a_std_msgs_UInt16> Pub_Emulate_Prescan_2019a_12;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

