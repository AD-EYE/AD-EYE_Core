#include "can_sender.h"


namespace kcan {


CANSender::CANSender(CANBus bus): can_controller_(bus) { }


void CANSender::sendSignalGroup(const string& name, SignalValues& sv) {
    const SignalGroupInfo& sgi = DBCReader::getSignalGroupInfo(name);
    FrameCtrl* fc_ptr = getScheduled(sgi.parent_name);
    if (fc_ptr != nullptr) {
        lock_guard<mutex> lock { fc_ptr->frame_mutex };
        fc_ptr->fptr->setSignalGroup(sgi.name, sv);
    }
    else {
        CANFrame* fptr = new CANFrame(sgi.parent_name);
        fptr->setSignalGroup(sgi.name, sv);
        scheduleFrame(fptr);
    }
}

void CANSender::sendSignals(SignalValues& sv) {
    const string signal_name = sv.begin()->first;
    const SignalInfo& si = DBCReader::getSignalInfo(signal_name);
    const SignalGroupInfo& sgi = DBCReader::getSignalGroupInfo(si.parent_name);
    FrameCtrl* fc_ptr = getScheduled(sgi.parent_name);
    if (fc_ptr != nullptr) {
        lock_guard<mutex> lock { fc_ptr->frame_mutex };
        fc_ptr->fptr->setSignals(sv);
    }
    else {
        CANFrame* fptr = new CANFrame(sgi.parent_name);
        fptr->setSignals(sv);
        scheduleFrame(fptr);
    }
}


void CANSender::sendSignal(const string& name, uint64_t val) {
    const SignalInfo& si = DBCReader::getSignalInfo(name);
    FrameCtrl* fc_ptr = getScheduled(si.parent_name);
    if (fc_ptr == nullptr) {
        if (si.parent_name == dbc::NO_NAME) {
            // scedule frame
        }
        else {
            throw "Signal is part of signal group, send signal group first";
        }
    }
    lock_guard<mutex> lock { fc_ptr->frame_mutex };
    fc_ptr->fptr->setSignal(name, val);
}


void CANSender::stopSignalGroup(const string& name) {
    const SignalGroupInfo& sgi = DBCReader::getSignalGroupInfo(name);
    FrameCtrl* fc_ptr = getScheduled(sgi.parent_name);
    if (fc_ptr != nullptr) {
        unscheduleFrame(fc_ptr);
    }
}


FrameCtrl* CANSender::getScheduled(const string& name) {
        auto found = scheduled_.find(name);
        if (found != scheduled_.end()) {
            return found->second;
        }
        return nullptr;
}
   

void CANSender::scheduleFrame(CANFrame* fptr) {
    FrameCtrl* fc_ptr = new FrameCtrl;

    fc_ptr->status = FrameStatus::ACTIVE;
    fc_ptr->fptr = fptr;
    fc_ptr->th = new thread(&CANSender::sendCyclicly, this, fc_ptr);

    scheduled_.insert({ fptr->getName(), fc_ptr });
}


void CANSender::unscheduleFrame(FrameCtrl* fc_ptr) {
    fc_ptr->status = FrameStatus::STOPPED;
    scheduled_.erase(fc_ptr->fptr->getName());
    unscheduled_.push_back(fc_ptr);
}


void CANSender::suspendFrame(const string& name) {
    FrameCtrl* fc_ptr = getScheduled(name);
    if (fc_ptr != nullptr) {
        fc_ptr->status = FrameStatus::SUSPENDED;
    }
}


void CANSender::resumeFrame(const string& name) {
    FrameCtrl* fc_ptr = getScheduled(name);
    if (fc_ptr != nullptr) {
        fc_ptr->status = FrameStatus::ACTIVE;
    }
}


void CANSender::clearUnscheduled() {
}


void CANSender::sendCyclicly(FrameCtrl* fc_ptr) {
    while (fc_ptr->status == FrameStatus::ACTIVE || fc_ptr->status == FrameStatus::SUSPENDED) {
        if (fc_ptr->status != FrameStatus::SUSPENDED) {
            lock_guard<mutex> lock { fc_ptr->frame_mutex };   
            can_controller_.send(fc_ptr->fptr);
        }
        this_thread::sleep_for(std::chrono::milliseconds(fc_ptr->fptr->getPeriod()));
    }
}


void CANSender::sendOnce(CANFrame* fptr) {
    can_controller_.send(fptr);
}


}