#ifndef __CAN_INTERFACE_H__
#define __CAN_INTERFACE_H__

#include <cstddef>

#include "../can_frame.h"


namespace kcan {


struct CANStatistics {
    uint64_t frames_received;
    uint64_t frames_sent;
};



class CANInterface {
public:
    virtual int send(CANFrame* fptr) = 0;
    virtual int receive(CANFrame* fptr) = 0;
    virtual CANStatistics statistics() = 0;
};


}

#endif
