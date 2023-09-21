#ifndef __CAN_DUMMY_H__
#define __CAN_DUMMY_H__

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include <queue>
#include <chrono>

#include "can_interface.h"


namespace kcan {


using namespace std;


class DUMMYCANController: public CANInterface {
public:
    DUMMYCANController(CANBus b) {
        cout << "Creating DUMMYCANController" << std::endl;
    }

    int send(CANFrame* fptr) {
        fptr->print("Sending frame:\n");
        frames_.push(*fptr);
    }

    int receive(CANFrame* fptr) {
        if (frames_.empty()) {
            std::chrono::milliseconds(500);
            return 0;
        }
        *fptr = frames_.front();
        frames_.pop();
        fptr->print("Receiving frame:\n");
    }

    CANStatistics statistics() {
        CANStatistics s;
        s.frames_received = 0;
        s.frames_sent = 0;
        return s;
    }

private:
    queue<CANFrame> frames_;
    
};


}

#endif