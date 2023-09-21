#ifndef __CAN_RECEIVER_H__
#define __CAN_RECEIVER_H__

#include <map>

#include "can_controller.h"
#include "signal_values.h"

namespace kcan {


struct FrameReceiveCtrl {
    mutex frame_mutex;
    CANFrame *fptr;
};


class CANReceiver {
  public:
    CANReceiver(CANController &can_controller) : can_controller_(can_controller) {
        active_ = true;
        start();
    }
    ~CANReceiver();
    void monitorSignal(const string &name);
    SignalValues getSignalGroup(const string &name);
    uint64_t getSignal(const string &name);

  private:
    void start();
    void receive();
    FrameReceiveCtrl *getMonitored(const string &name);

    thread *th_;
    bool active_;
    map<string, FrameReceiveCtrl *> monitored_;
    CANController &can_controller_;
};


} // namespace kcan

#endif