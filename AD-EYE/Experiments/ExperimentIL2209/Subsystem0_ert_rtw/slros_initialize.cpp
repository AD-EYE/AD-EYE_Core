#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "Subsystem0";

// For Block Subsystem0/Publish
SimulinkPublisher<std_msgs::Float32, SL_Bus_Subsystem0_std_msgs_Float32> Pub_Subsystem0_5;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

