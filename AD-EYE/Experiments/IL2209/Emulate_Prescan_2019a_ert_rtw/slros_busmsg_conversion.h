#ifndef _SLROS_BUSMSG_CONVERSION_H_
#define _SLROS_BUSMSG_CONVERSION_H_

#include <ros/ros.h>
#include <std_msgs/UInt16.h>
#include "Emulate_Prescan_2019a_types.h"
#include "slros_msgconvert_utils.h"


void convertFromBus(std_msgs::UInt16* msgPtr, SL_Bus_Emulate_Prescan_2019a_std_msgs_UInt16 const* busPtr);
void convertToBus(SL_Bus_Emulate_Prescan_2019a_std_msgs_UInt16* busPtr, std_msgs::UInt16 const* msgPtr);


#endif
