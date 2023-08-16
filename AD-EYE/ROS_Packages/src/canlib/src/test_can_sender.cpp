


#include "can_sender.h"
#include <iostream>

SignalValues sv;
sv.addSignal(AdPrimSteerStsSafeGroup_UB, 0x0);
sv.addSignal(AdPrimSteerStsSafeGroupAdSteerPerf, 0x14);
sv.addSignal(AdPrimSteerStsSafeGroupAdSteerSts, 0x0);
sv.addSignal(AdPrimSteerStsSafeGroupChks, 0x0);
sv.addSignal(AdPrimSteerStsSafeGroupCntr, 0x0);
sv.addSignal(CarModInCrashStsSafe_UB, 0x0);
sv.addSignal(CarModInCrashStsSafeChks, 0x0);
sv.addSignal(CarModInCrashStsSafeCntr, 0x0);
sv.addSignal(CarModInCrashStsSafeSts, 0x0);


int main{
    kcan::DBCReader::init();
    vector<uint8_t> data = {0x54, 0x00, 0x00, 0x00, 0x50, 0x02, 0x00, 0x00};
    E2EProtector p(kcan::dbc::CarModInCrashStsSafe);
    CANSender send(A);
    send.sendSignalGroup(CarModInCrashStsSafe, sv);


    return 0;
}