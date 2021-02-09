#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "ros_subsystem";

// For Block ros_subsystem/Publish
SimulinkPublisher<std_msgs::Float32, SL_Bus_ros_subsystem_std_msgs_Float32> Pub_ros_subsystem_5;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

