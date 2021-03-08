#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "ros_node";

// For Block ros_node/Publish
SimulinkPublisher<std_msgs::UInt8, SL_Bus_ros_node_std_msgs_UInt8> Pub_ros_node_2;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

