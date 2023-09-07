#ifndef __TYPES_H__
#define __TYPES_H__

#include <string>
#include <vector>
#include <map>

namespace kcan {

using namespace std;


enum class E2EProfileType { None, P01a, P05 };


enum class SignalType { APP_UNSIGNED, APP_SIGNED, E2E_CHKS, E2E_CNTR };


struct E2EProfileSettings {
    E2EProfileType type;
    string checksum_name;
    string counter_name;
};


struct SignalInfo {
    string name;
    uint16_t start_bit;
    uint16_t length;
    SignalType type;
    string parent_name;
};


struct SignalGroupInfo {
    string name;
    uint16_t dataId;
    vector<string> signals;
    E2EProfileSettings e2e_settings;
    string parent_name;
};


struct FrameInfo {
    string name;
    uint32_t id;
    uint16_t length;
    uint32_t period;
    vector<string> signal_groups;
    vector<string> signals;
};


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

    void removeSignal(const string& name) {
        values_.erase(name);
    }

    uint64_t getValue(const string& name, bool no_default = false) const {
            auto found = values_.find(name);
            if (found == values_.end()) {
                if (mode_ == SVMode::EXCEPTION || no_default) {
                    throw invalid_argument("Value is not found!");
                }
                return 0;
            }
            auto i = found->second;
            auto s = found->first;
            return i;
    }

    map<string, uint64_t>::const_iterator begin() const {
        return values_.begin();
    }

    map<string, uint64_t>::const_iterator end() const {
        return values_.end();
    }

private:
    map<string, uint64_t> values_;
    SVMode mode_;
};


}

#endif