#include "slros_busmsg_conversion.h"


// Conversions between SL_Bus_Emulate_Prescan_2019a_std_msgs_UInt16 and std_msgs::UInt16

void convertFromBus(std_msgs::UInt16* msgPtr, SL_Bus_Emulate_Prescan_2019a_std_msgs_UInt16 const* busPtr)
{
  const std::string rosMessageType("std_msgs/UInt16");

  msgPtr->data =  busPtr->Data;
}

void convertToBus(SL_Bus_Emulate_Prescan_2019a_std_msgs_UInt16* busPtr, std_msgs::UInt16 const* msgPtr)
{
  const std::string rosMessageType("std_msgs/UInt16");

  busPtr->Data =  msgPtr->data;
}

