#ifndef __CAN_CONTROLLER_H__
#define __CAN_CONTROLLER_H__


#include <memory>
#include <mutex>
#include <iostream>
#include <unistd.h>

#include "INIReader.h"

#if defined(DRIVEWORKS)
    #include "HAL/can_drive.h"
#endif

#include "HAL/can_interface.h"
#include "HAL/can_socketcan.h"
#include "HAL/can_dummy.h"

namespace kcan {


class CANController: public CANInterface {
public:
    CANController(CANBus bus) {
        /*
        Example of INI file:

        [CAN_A]
        type=socketcan
        name=can1
        fd_on=true
        [CAN_B]
        type=drive
        */
        char u[100];
        getcwd(u, 100);
        cout << u << endl;
        string section = busToIniSection(bus);
        INIReader reader("can_config.ini");
            if (reader.ParseError() != 0) {
            throw runtime_error("Can't load can_config.ini");
        }
        string type = reader.Get(section, "type", "");
        if (type == "socketcan") {
            string device_name = reader.Get(section, "name", "");
            bool fd_on = reader.GetBoolean(section, "fd_on", false);
            can_controller_ = std::unique_ptr<SOCKETCANController>(new SOCKETCANController(device_name, fd_on));
        }
        else if (type == "drive") {
            #if defined(DRIVEWORKS)
                can_controller_ = std::unique_ptr<PX2CANController>(new PX2CANController(bus));
            #else
                throw invalid_argument("Unsupported CAN controller!");
            #endif
        }
        else if (type == "dummy") {
            can_controller_ = std::unique_ptr<DUMMYCANController>(new DUMMYCANController(bus));
        }
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

    string busToIniSection(CANBus bus) {
        switch (bus) {
            case CANBus::A: return "CAN_A";
            case CANBus::B: return "CAN_B";
            case CANBus::C: return "CAN_C";
            case CANBus::D: return "CAN_D";
            default: throw invalid_argument("Unknown bus!");
        }
    }
};


}

#endif
