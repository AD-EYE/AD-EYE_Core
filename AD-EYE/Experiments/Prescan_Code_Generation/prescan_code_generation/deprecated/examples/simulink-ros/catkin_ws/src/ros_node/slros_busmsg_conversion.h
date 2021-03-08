#ifndef _SLROS_BUSMSG_CONVERSION_H_
#define _SLROS_BUSMSG_CONVERSION_H_

#include <ros/ros.h>
#include <std_msgs/UInt8.h>
#include "ros_node_types.h"
#include "slros_msgconvert_utils.h"


void convertFromBus(std_msgs::UInt8* msgPtr, SL_Bus_ros_node_std_msgs_UInt8 const* busPtr);
void convertToBus(SL_Bus_ros_node_std_msgs_UInt8* busPtr, std_msgs::UInt8 const* msgPtr);


#endif
