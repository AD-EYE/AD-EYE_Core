#ifndef __CAN_NODE_H__
#define __CAN_NODE_H__

#include <map>

#include "can_receiver.h"
#include "can_sender.h"
#include "can_controller.h"


namespace kcan {


class CANNode: public CANReceiver, public CANSender  {
public:
    CANNode(CANController &can_controller) : CANReceiver(can_controller), CANSender(can_controller) { }
};


}


#endif