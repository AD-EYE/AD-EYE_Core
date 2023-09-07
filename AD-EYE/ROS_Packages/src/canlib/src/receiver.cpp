#include <iostream>
#include <iomanip>
#include <string>
#include <unistd.h>

#include "can_controller.h"
#include "can_receiver.h"
#include "can_frame.h"
#include "dbc.h"


using namespace kcan;
using namespace kcan::dbc;


void test3() {
    CANController ctrl(CANBus::A);
    CANReceiver can_receiver(ctrl);
    can_receiver.monitorSignal(AdpLiReqFromAPIHzrdLiActvnReq);
    while (true) {
        sleep(1);
        SignalValues sv = can_receiver.getSignalGroup(AdpLiReqFromAPI);
        cout << (int)sv.getValue(AdpLiReqFromAPIHzrdLiActvnReq) << endl;
    }
}


int main(int argc, char* argv[]) {
    DBCReader::init();
    test3();
}
