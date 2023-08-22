#ifndef __CAN_INTERFACE_H__
#define __CAN_INTERFACE_H__

#include <cstddef>

#include "../can_frame.h"


namespace kcan {


enum class CANBus { A, B, C, D, E, F };


class CANInterface {
public:
    virtual int send(CANFrame* fptr) = 0;
    virtual int receive(CANFrame* fptr) = 0;
};


}

#endif
