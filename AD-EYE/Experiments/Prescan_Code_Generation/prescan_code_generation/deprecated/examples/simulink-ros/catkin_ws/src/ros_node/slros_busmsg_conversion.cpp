#include "slros_busmsg_conversion.h"


// Conversions between SL_Bus_ros_node_std_msgs_UInt8 and std_msgs::UInt8

void convertFromBus(std_msgs::UInt8* msgPtr, SL_Bus_ros_node_std_msgs_UInt8 const* busPtr)
{
  const std::string rosMessageType("std_msgs/UInt8");

  msgPtr->data =  busPtr->Data;
}

void convertToBus(SL_Bus_ros_node_std_msgs_UInt8* busPtr, std_msgs::UInt8 const* msgPtr)
{
  const std::string rosMessageType("std_msgs/UInt8");

  busPtr->Data =  msgPtr->data;
}

