#ifndef __CAN_RECEIVER_H__
#define __CAN_RECEIVER_H__


#include <maap>


namespace kcan {


class CANReceiver {
public:
    CANReceiver();
private:
    map<uint32_t> frame_ids_;
        
}


}

#endif