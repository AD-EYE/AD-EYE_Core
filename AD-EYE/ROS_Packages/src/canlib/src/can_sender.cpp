#include "can_sender.h"


namespace kcan {


CANSender::CANSender(CANController &can_controller) : can_controller_(can_controller) {}


CANSender::~CANSender() {
    stopAndFreeResources();
}


void CANSender::sendFrame(const string &name, const SignalValues& sv, bool override_ub, bool auto_counter, uint8_t filling) {
    const FrameInfo &fi = DBCReader::getFrameInfo(can_controller_.getBus(), name);
    FrameCtrl *fc_ptr = getScheduled(fi.name);
    if (fc_ptr != nullptr) {
        lock_guard<mutex> lock{fc_ptr->frame_mutex};
        fc_ptr->fptr->setFrame(fi.name, sv, override_ub);
    } else {
        CANFrame *fptr = new CANFrame(can_controller_.getBus(), fi.name, filling);
        fptr->setFrame(fi.name, sv, override_ub);
        fc_ptr = scheduleFrame(fptr);
    }
    
    for (auto &sg_name : fi.signal_groups) {
        if (auto_counter) {
            fc_ptr->auto_counter_groups.insert(sg_name);
        } else {
            fc_ptr->auto_counter_groups.erase(name);
        }
    }
}


void CANSender::sendSignalGroup(const string &name, SignalValues &sv, bool auto_counter, const string &ub) {
    const SignalGroupInfo &sgi = DBCReader::getSignalGroupInfo(can_controller_.getBus(), name);
    FrameCtrl *fc_ptr = getScheduled(sgi.parent_name);
    if (fc_ptr != nullptr) {
        lock_guard<mutex> lock{fc_ptr->frame_mutex};
        fc_ptr->fptr->setSignalGroup(sgi.name, sv);
        if (ub != dbc::NoName) {
            fc_ptr->fptr->setSignal(ub, 1);
        }
    } else {
        CANFrame *fptr = new CANFrame(can_controller_.getBus(), sgi.parent_name);
        fptr->setSignalGroup(sgi.name, sv);
        if (ub != dbc::NoName) {
            fptr->setSignal(ub, 1);
        }
        fc_ptr = scheduleFrame(fptr);
    }

    if (auto_counter) {
        fc_ptr->auto_counter_groups.insert(name);
    } else {
        fc_ptr->auto_counter_groups.erase(name);
    }
}


void CANSender::sendSignals(SignalValues &sv) {
    const string signal_name = sv.begin()->first;
    const SignalInfo &si = DBCReader::getSignalInfo(can_controller_.getBus(), signal_name);
    const SignalGroupInfo &sgi = DBCReader::getSignalGroupInfo(can_controller_.getBus(), si.parent_name);
    FrameCtrl *fc_ptr = getScheduled(sgi.parent_name);
    if (fc_ptr != nullptr) {
        lock_guard<mutex> lock{fc_ptr->frame_mutex};
        fc_ptr->fptr->setSignals(sv);
    } else {
        CANFrame *fptr = new CANFrame(can_controller_.getBus(), sgi.parent_name);
        fptr->setSignals(sv);
        scheduleFrame(fptr);
    }
}


void CANSender::sendSignal(const string &name, uint64_t val) {
    SignalValues sv;
    sv.addSignal(name, val);
    const SignalInfo &si = DBCReader::getSignalInfo(can_controller_.getBus(), name);
    try {
        DBCReader::getSignalGroupInfo(can_controller_.getBus(), si.parent_name);
        sendSignals(sv);
    } catch (invalid_argument) {
        FrameCtrl *fc_ptr = getScheduled(si.parent_name);
        if (fc_ptr != nullptr) {
            lock_guard<mutex> lock{fc_ptr->frame_mutex};
            fc_ptr->fptr->setSignal(name, val);
        } else {
            CANFrame *fptr = new CANFrame(can_controller_.getBus(), si.parent_name);
            fptr->setSignal(name, val);
            scheduleFrame(fptr);
        }
    }
}


void CANSender::stopSignalGroup(const string &name) {
    const SignalGroupInfo &sgi = DBCReader::getSignalGroupInfo(can_controller_.getBus(), name);
    FrameCtrl *fc_ptr = getScheduled(sgi.parent_name);
    if (fc_ptr != nullptr) {
        unscheduleFrame(fc_ptr);
    }
}


void CANSender::stopAll() {
    stopAndFreeResources();
}


void CANSender::stopAndFreeResources() {
    for (auto el : scheduled_) {
        FrameCtrl *fc_ptr = el.second;
        deleteFrameCtrl(fc_ptr);
    }

    for (FrameCtrl *fc_ptr : unscheduled_) {
        deleteFrameCtrl(fc_ptr);
    }

    scheduled_.clear();
    unscheduled_.clear();
}


FrameCtrl *CANSender::getScheduled(const string &name) {
    auto found = scheduled_.find(name);
    if (found != scheduled_.end()) {
        return found->second;
    }
    return nullptr;
}


FrameCtrl *CANSender::scheduleFrame(CANFrame *fptr) {
    FrameCtrl *fc_ptr = new FrameCtrl;

    fc_ptr->status = FrameStatus::ACTIVE;
    fc_ptr->fptr = fptr;
    fc_ptr->th = new thread(&CANSender::sendCyclicly, this, fc_ptr);
    scheduled_.insert({fptr->getName(), fc_ptr});

    return fc_ptr;
}


void CANSender::unscheduleFrame(FrameCtrl *fc_ptr) {
    fc_ptr->status = FrameStatus::STOPPED;
    scheduled_.erase(fc_ptr->fptr->getName());
    unscheduled_.push_back(fc_ptr);
}


void CANSender::suspendFrame(const string &name) {
    FrameCtrl *fc_ptr = getScheduled(name);
    if (fc_ptr != nullptr) {
        fc_ptr->status = FrameStatus::SUSPENDED;
    }
}


void CANSender::resumeFrame(const string &name) {
    FrameCtrl *fc_ptr = getScheduled(name);
    if (fc_ptr != nullptr) {
        fc_ptr->status = FrameStatus::ACTIVE;
    }
}


void CANSender::clearUnscheduled() {}


void CANSender::sendCyclicly(FrameCtrl *fc_ptr) {
    while (fc_ptr->isActive()) {
        if (fc_ptr->status != FrameStatus::SUSPENDED) {
            lock_guard<mutex> lock{fc_ptr->frame_mutex};
            can_controller_.send(fc_ptr->fptr);
            if (fc_ptr->auto_counter_groups.size()) {
                SignalValues sv{SVMode::EXCEPTION};
                for (auto sg_name : fc_ptr->auto_counter_groups) {
                    fc_ptr->fptr->setSignalGroup(sg_name, sv);
                }
            }
        }

        auto period = fc_ptr->fptr->getFrameInfo().period;
        if (period <= 100) {
            this_thread::sleep_for(chrono::milliseconds(period));
        } else {
            uint64_t nap = 100;
            while (period > 0 && fc_ptr->isActive()) {
                this_thread::sleep_for(chrono::milliseconds(nap));
                period -= nap;
                nap = period < 100 ? period : 100;
            }
        }
    }
}


void CANSender::sendOnce(const CANFrame &fptr) {
    can_controller_.send(const_cast<CANFrame *>(&fptr));
}


void CANSender::deleteFrameCtrl(FrameCtrl *fc_ptr) {
    fc_ptr->status = FrameStatus::STOPPED;
    fc_ptr->th->join();
    delete fc_ptr->th;
    delete fc_ptr->fptr;
    delete fc_ptr;
}


} // namespace kcan