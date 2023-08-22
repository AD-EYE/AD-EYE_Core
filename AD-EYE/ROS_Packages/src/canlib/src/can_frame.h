#ifndef __CAN_FRAME__H__
#define __CAN_FRAME__H__

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <iomanip>
#include <mutex>
#include <thread>
#include <stdexcept>

#include "packer.h"
#include "dbc_reader.h"
#include "e2e_protector.h"


namespace kcan {


enum class SVMode { EXCEPTION, ZERO };


class SignalValues {
public:
    SignalValues(SVMode mode = SVMode::EXCEPTION) {
        mode_ = mode;
    }
    void addSignal(const string& name, uint64_t val) {
        auto res = values_.insert({ name, val });
        if (!res.second) {
            (*res.first).second = val;
        }
    }
    uint64_t getValue(const string& name) {
            auto found = values_.find(name);
            if (found == values_.end()) {
                if (mode_ == SVMode::EXCEPTION) {
                    throw invalid_argument("Value is not found!");
                }
                return 0;
            }
            auto i = found->second;
            auto s = found->first;
            return i;
    }

    const map<string, uint64_t>::iterator begin() {
        return values_.begin();
    }

    const map<string, uint64_t>::iterator end() {
        return values_.end();
    }

private:
    map<string, uint64_t> values_;
    SVMode mode_;
};


class CANFrame {
    public:
        CANFrame(const string& name)
        : name_ { name } {
            frame_info_ = DBCReader::getFrameInfo(name_);
            data_.resize(frame_info_.length);
            for (auto sg_name : frame_info_.signal_groups) {
                e2e_protectors_.insert({ sg_name, new E2EProtector(sg_name) });
            }
        }

        ~CANFrame() {
            if (th_ != nullptr) {
                th_->join();
                delete th_;
            }
        }

        void setSignalGroup(const string& name, SignalValues& values) {
            kcan::SignalGroupInfo sgi = DBCReader::getSignalGroupInfo(name);
            for (auto s_name : sgi.signals) {
                setSignal(s_name, values.getValue(s_name));
            }
            
            e2e_protectors_.find(sgi.name)->second->applyProfile(data_);
        }

        void setSignals(SignalValues& values) {
            string signal_name = values.begin()->first;
            kcan::SignalInfo si = DBCReader::getSignalInfo(signal_name);
            kcan::SignalGroupInfo sgi = DBCReader::getSignalGroupInfo(si.parent_name);
            for (auto el : values) {
                setSignal(el.first, el.second);
            }
            e2e_protectors_.find(sgi.name)->second->applyProfile(data_);
        }

        void setSignal(const string& name, uint64_t val) {
            const SignalInfo& si = DBCReader::getSignalInfo(name);
            Packer::pack(data_, si.start_bit, si.length, val);
            active_signals_.insert(si.name);
        }

        const string& getName() {
            return name_;
        }

        uint32_t getId() {
            return frame_info_.id;
        }

        time_t getPeriod() {
            return frame_info_.period;
        }

        const uint8_t* getData() {
            return data_.data();
        }

        size_t getDataSize() {
            return data_.size();
        }

        void print(ostream& o=cout) {
            for (int i = 0; i < data_.size(); i++) {
                o << hex << setfill('0') << setw(2) << (int)data_[i] << " ";
            }
            o << endl;
        }

    private:
        void validateSignal(SignalInfo& si) {
            if (si.parent_name != name_) {
                throw "Signal doesn't belong to the frame!";
            }
        }

        string name_;
        FrameInfo frame_info_;
        set<string> active_signals_;
        thread* th_  { nullptr };
        bool alive_ { true };
        bool suspended_ { false };
        vector<uint8_t> data_;
        map<std::string, E2EProtector*> e2e_protectors_;
};


}

#endif
