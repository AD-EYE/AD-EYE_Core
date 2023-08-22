#ifndef __CAN_DUMMY_H__
#define __CAN_DUMMY_H__

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "can_interface.h"


namespace kcan {


using namespace std;


class DUMMYCANController: public CANInterface {
public:
    DUMMYCANController(CANBus b) {
        cout << "Creating DUMMYCANController" << std::endl;
    }

    int send(CANFrame* fptr) {
        stringstream buffer_str;
        fptr->print(buffer_str);
        cout << "Sending frame " << fptr->getId() << ": " << buffer_str.str() << std::endl;
    }

    int receive(CANFrame* fptr) {
        std::cout << "Receiving frame" << std::endl;
    }
private:
    
};


typedef DUMMYCANController PlatformCANConnroller;


}

#endif