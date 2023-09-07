#ifndef __CAN_PX2_H__
#define __CAN_PX2_H__

#include <dw/sensors/Sensors.h>

#include "can_interface.h"


namespace kcan {


class PX2CANController: public kcan::CANInterface {
public:
    PX2CANController(CANBus b);
    int send(CANFrame* fptr);
    int receive(CANFrame* fptr);
private:
    dwSensorHandle_t canSensor_;
};


}

#endif