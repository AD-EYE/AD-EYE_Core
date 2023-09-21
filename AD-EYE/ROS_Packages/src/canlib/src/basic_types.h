#ifndef __TYPES_H__
#define __TYPES_H__

#include <map>
#include <string>
#include <vector>

namespace kcan {

using namespace std;


enum class CANBus { NONE, A, B, C, D, E, F };


enum class E2EProfileType { None, P01a, P05 };


enum class SignalType { APP_UNSIGNED, APP_SIGNED, E2E_CHKS, E2E_CNTR };


enum class ParentType { GROUP, FRAME };


struct E2EProfileSettings {
    E2EProfileType type;
    string checksum_name;
    string counter_name;
};


struct SignalInfo {
    string name;
    uint16_t start_bit;
    uint16_t length;
    bool big_endian;
    SignalType type;
    uint64_t initial;
    string parent_name;
    ParentType parent_type;
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


} // namespace kcan

#endif