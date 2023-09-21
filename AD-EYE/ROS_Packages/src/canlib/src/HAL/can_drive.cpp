#include <iostream>
#include <sstream>
#include <stdexcept>

#include <dw/core/Logger.h>
#include <dw/core/Context.h>
#include <dw/core/VersionCurrent.h>
#include <dw/sensors/canbus/CAN.h>

#include "can_px2.h"

namespace kcan {


const char* busToParam(CANBus bus) {
    switch (bus) {
        case CANBus::A: return "bus=a";
        case CANBus::B: return "bus=b";
        case CANBus::C: return "bus=c";
        case CANBus::D: return "bus=d";
        case CANBus::E: return "device=can0";
        case CANBus::F: return "device=can1";
        default: return "";
    }
}


PX2CANController::PX2CANController(CANBus b) {
    dwContextHandle_t sdk;
    dwSALHandle_t hal;
    dwContextParameters sdkParams {};

    dwInitialize(&sdk, DW_VERSION, &sdkParams);
    dwSAL_initialize(&hal, sdk);

    dwSensorParams params {};
    char parameters[100] {};
    strcat(parameters, busToParam(b));
    switch (b) {
        case CANBus::A:
        case CANBus::B:
        case CANBus::C:
        case CANBus::D:
            params.protocol = "can.aurix";
            strcat(parameters, ",ip=10.42.0.146");
            strcat(parameters, ",config-file=/home/nvidia/canlib/EasyCanConfigFile.conf");
            break;
        case CANBus::E:
        case CANBus::F:
            params.protocol = "can.socket";
            break;
    }
    params.parameters = parameters;
    // char parameters[100] = "ip=10.42.0.146,bus=";  // -driver=can.socket --params=device=can0

    dwStatus sensor_status;
    if ((sensor_status = dwSAL_createSensor(&canSensor_, params, hal)) != DW_SUCCESS)
    {
        std::cerr << " Cannot create sensor (" << dwGetStatusName(sensor_status) << ")"
                    << params.protocol << " with " << params.parameters << std::endl;
        dwSAL_release(&hal);
        dwRelease(&sdk);
    }

    dwSensor_start(canSensor_);
 }


int PX2CANController::send(CANFrame* fptr) {
    dwCANMessage dw_frame;
    if (fptr->getDataSize() > DW_SENSORS_CAN_MAX_MESSAGE_LEN) {
        throw std::length_error { "buffer_size is to big!" };
    }
    
    dw_frame.timestamp_us = 0;
    dw_frame.id = fptr->getFrameInfo().id;
    dw_frame.size = fptr->getDataSize();
    memcpy(dw_frame.data, fptr->getData(), dw_frame.size);

    stringstream buffer_str;
    fptr->print(buffer_str);
    cout << "Sending frame " << fptr->getFrameInfo().id << ": " << buffer_str.str() << std::endl;

    return dwSensorCAN_sendMessage(&dw_frame, 100000, canSensor_);
}


int PX2CANController::receive(CANFrame* fptr) {
    dwCANMessage dw_frame;
    dwStatus s = dwSensorCAN_readMessage(&dw_frame, 400000, canSensor_);
    if (s == DW_SUCCESS) {
        try {
            fptr->setRawData(dw_frame.data, dw_frame.size);
            fptr->setId(dw_frame.id);
            return dw_frame.size;
        } catch (out_of_range) {
            return 0;
        }
    }
    else {
        cout << dwGetStatusName(s) << endl;
        return 0;
    }
}


CANStatistics statistics() {
    CANStatistics s;
    s.frames_received = 0;
    s.frames_sent = 0;
    return s;
}


}
