#ifndef __CAN_SENDER_H__
#define __CAN_SENDER_H__

#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

#include "basic_types.h"
#include "can_controller.h"
#include "can_frame.h"
#include "dbc_reader.h"
#include "signal_values.h"


namespace kcan {


enum class FrameStatus { ACTIVE, SUSPENDED, STOPPED };


struct FrameCtrl {
    thread *th;
    mutex frame_mutex;
    CANFrame *fptr;
    FrameStatus status;
    set<string> auto_counter_groups;

    bool isActive() {
        return this->status == FrameStatus::ACTIVE || this->status == FrameStatus::SUSPENDED;
    }
};


class CANSender {
  public:
    CANSender(CANController &can_controller);
    ~CANSender();

    void sendFrame(const string &name, const SignalValues& sv, bool override_ub, bool auto_counter, uint8_t filling = 0x00);

    void sendSignalGroup(const string &name, SignalValues &sv, bool auto_counter = false, const string &ub = dbc::NoName);

    void sendSignal(const string &name, uint64_t val);

    void sendSignals(SignalValues &sv);

    void stopSignalGroup(const string &name);

    void stopAll();

    void sendOnce(const CANFrame &fptr);

    void suspendFrame(const string &name);

    void resumeFrame(const string &name);

  private:
    FrameCtrl *getScheduled(const string &name);

    FrameCtrl *scheduleFrame(CANFrame *fptr);

    void unscheduleFrame(FrameCtrl *fptr);

    void suspend(const string &name);

    void resume(const string &name);

    void stopAndFreeResources();

    void clearUnscheduled();

    void deleteFrameCtrl(FrameCtrl *fc_ptr);

    void sendCyclicly(FrameCtrl *fc);

    map<string, FrameCtrl *> scheduled_;
    vector<FrameCtrl *> unscheduled_;
    CANController &can_controller_;
};


} // namespace kcan

#endif