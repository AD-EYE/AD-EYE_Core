#ifndef __CAN_CONTROLLER_H__
#define __CAN_CONTROLLER_H__


#include <memory>
#include <mutex>


#ifdef CAN_HAL_PX2
    #include "HAL/can_px2.h"
#else  // CAN_HAL_DUMMY
    #include "HAL/can_dummy.h"
#endif


#include "HAL/can_interface.h"


namespace kcan {


class CANController: public CANInterface {
public:
    CANController(CANBus bus) {
        can_controller_ = std::unique_ptr<PlatformCANConnroller>(new PlatformCANConnroller(bus));
    }
    int send(CANFrame* fptr) {
        std::lock_guard<std::mutex> lock { send_mutex_ };
        return can_controller_->send(fptr);
    }
    int receive(CANFrame* fptr) {
        std::lock_guard<std::mutex> lock { receive_mutex_ };
        return can_controller_->receive(fptr);
    }

private:
    std::unique_ptr<CANInterface> can_controller_;
    std::mutex send_mutex_;
    std::mutex receive_mutex_;
};


}

#endif