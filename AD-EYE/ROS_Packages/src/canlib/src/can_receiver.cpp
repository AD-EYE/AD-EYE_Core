#include <thread>

#include "can_receiver.h"


namespace kcan {


void CANReceiver::monitorSignal(const string& name) {
    const SignalInfo& si = DBCReader::getSignalInfo(name);
    FrameInfo fi;
    try {
        auto& sgi = DBCReader::getSignalGroupInfo(si.parent_name);
        fi = DBCReader::getFrameInfo(sgi.parent_name);
    }
    catch (invalid_argument& e) {
        fi = DBCReader::getFrameInfo(si.parent_name);
    }

    FrameReceiveCtrl* fc_ptr = getMonitored(fi.name);
    if (fc_ptr == nullptr) {
        FrameReceiveCtrl* fc_ptr = new FrameReceiveCtrl;
        fc_ptr->fptr = new CANFrame(fi.name);
        monitored_.insert({ fi.name, fc_ptr });
    }
}


SignalValues CANReceiver::getSignalGroup(const string& name) {
    const string& f_name = DBCReader::getSignalGroupInfo(name).parent_name;
    FrameReceiveCtrl* fc_ptr = getMonitored(f_name);
    if (fc_ptr != nullptr) {
        return fc_ptr->fptr->getSignalGroup(name);
    }
    throw invalid_argument("Singal group is not monitored!");
}


SignalValues CANReceiver::getSignal(const string& name) {
    const SignalInfo& si = DBCReader::getSignalInfo(name);
    bool isInSignalGroup = false;
    SignalGroupInfo sgi;
    try {
        sgi = DBCReader::getSignalGroupInfo(si.parent_name);
        isInSignalGroup = true;
    } catch (invalid_argument) { }

    const string& frame_name = isInSignalGroup ? sgi.parent_name : si.parent_name;

    FrameReceiveCtrl* fc_ptr = getMonitored(frame_name);
    if (fc_ptr != nullptr) {
        return fc_ptr->fptr->getSignal(name);
    }
    throw invalid_argument("Singal is not monitored!");
}


void CANReceiver::receive() {
    CANFrame frame;
    for (;;) {
        if (can_controller_.receive(&frame) > 0) {
            try {
                FrameReceiveCtrl* fc_ptr = monitored_.at(frame.getFrameInfo().name);
                fc_ptr->fptr->setRawData(frame.getData(), frame.getDataSize());
                frame.print();
            } catch (out_of_range) {
                continue;
            }
        }
    }
}


FrameReceiveCtrl* CANReceiver::getMonitored(const string& name) {
        auto found = monitored_.find(name);
        if (found != monitored_.end()) {
            return found->second;
        }
        return nullptr;
}


void CANReceiver::start() {
    th_ = new thread(&CANReceiver::receive, this);
}

}