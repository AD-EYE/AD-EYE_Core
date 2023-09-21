#ifndef __SIGNAL_VALUES__H__
#define __SIGNAL_VALUES__H__


#include <string>
#include <map>

#include "basic_types.h"
#include "dbc_reader.h"


namespace kcan {


using namespace std;


enum class SVMode { EXCEPTION, ZERO, INITIAL };


class SignalValues {
  public:
    SignalValues(SVMode mode = SVMode::EXCEPTION, CANBus bus = CANBus::NONE) {
        mode_ = mode;
        bus_ = bus;
    }

    SignalValues(CANBus bus) {
        mode_ = SVMode::EXCEPTION;
        bus_ = bus;
    }

    void addSignal(const string &name, uint64_t val) {
        auto res = values_.insert({name, val});
        if (!res.second) {
            (*res.first).second = val;
        }
    }

    void removeSignal(const string &name) { values_.erase(name); }

    uint64_t getValue(const string &name) const {
        auto found = values_.find(name);
        if (found == values_.end()) {
            if (mode_ == SVMode::EXCEPTION) {
                throw invalid_argument("Value is not found!");
            }
            
            if (mode_ == SVMode::INITIAL) {
                if (bus_ == CANBus::NONE) {
                    throw invalid_argument("SVMode::INITIAL mode error: CAN bus is not set!");
                }
                auto &si = DBCReader::getSignalInfo(bus_, name);
                return si.initial;
            }

            if (mode_ == SVMode::ZERO) {
                return 0;
            }

            throw runtime_error("Unknown SVMode!");
        }
        auto i = found->second;
        auto s = found->first;
        return i;
    }

    CANBus getBus() const {
        return bus_;
    }

    map<string, uint64_t>::const_iterator begin() const { return values_.begin(); }

    map<string, uint64_t>::const_iterator end() const { return values_.end(); }

  private:
    map<string, uint64_t> values_;
    SVMode mode_;
    CANBus bus_;
};


}


#endif