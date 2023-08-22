#include <iostream>
#include <stdexcept>

#include <dw/core/Logger.h>
#include <dw/core/Context.h>
#include <dw/core/VersionCurrent.h>
#include <dw/sensors/canbus/CAN.h>

#include "can_px2.h"

namespace kcan {


const char* busTobus(CANBus bus) {
    switch (bus) {
        case CANBus::A: return "a";
        case CANBus::B: return "b";
        case CANBus::C: return "c";
        case CANBus::D: return "d";
        default: return "";
    }
}


PX2CANController::PX2CANController(CANBus b) {
    dwContextHandle_t sdk;
    dwSALHandle_t hal;
    
    dwContextParameters sdkParams {};

    dwInitialize(&sdk, DW_VERSION, &sdkParams);
    // create HAL module of the SDK
    dwSAL_initialize(&hal, sdk);
    // create sensor
    dwSensorParams params{};

    char parameters[32] = "ip=10.42.0.146,bus=";
    strcat(parameters, busTobus(b));
    params.protocol = "can.aurix";
    params.parameters = parameters;

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
    if (buffer_size > DW_SENSORS_CAN_MAX_MESSAGE_LEN) {
        throw std::length_error { "buffer_size is to big!" };
    }
    
    dw_frame.timestamp_us = 0;
    dw_frame.id = fptr->getId();
    dw_frame.size = fptr->getDataSize();
    memcpy(dw_frame.data, fptr->getData(), dw_frame.size);

    return dwSensorCAN_sendMessage(&dw_frame, 100000, canSensor_);
}


int PX2CANController::receive(uint8_t* buffer, uint16_t buffer_size) {
}


}