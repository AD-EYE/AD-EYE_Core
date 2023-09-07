#ifndef __CAN_SENDER_H__
#define __CAN_SENDER_H__

#include <thread>
#include <map>
#include <vector>
#include <utility>
#include <memory>
#include <mutex>

#include "basic_types.h"
#include "can_frame.h"
#include "dbc_reader.h"
#include "can_controller.h"


namespace kcan {


enum class FrameStatus { ACTIVE, SUSPENDED, STOPPED };


struct FrameCtrl {
    thread* th;
    mutex frame_mutex;
    CANFrame* fptr;
    FrameStatus status;
    bool e2e_auto_counter;
};


class CANSender {
public:
    CANSender(CANInterface& can_controller);

    void sendSignalGroup(const string& name, SignalValues& sv);

    void sendSignal(const string& name, uint64_t val);

    void sendSignals(SignalValues& sv);

    void stopSignalGroup(const string& name);

    void sendOnce(const CANFrame& fptr);

    void suspendFrame(const string& name);

    void resumeFrame(const string& name);

private:
    FrameCtrl* getScheduled(const string& name);

    void scheduleFrame(CANFrame* fptr);

    void unscheduleFrame(FrameCtrl* fptr);

    void suspend(const string& name);

    void resume(const string& name);

    void clearUnscheduled();

    void sendCyclicly(FrameCtrl* fc);

    map<string, FrameCtrl*> scheduled_;
    vector<FrameCtrl*> unscheduled_;
    CANInterface& can_controller_;
};


}

#endif