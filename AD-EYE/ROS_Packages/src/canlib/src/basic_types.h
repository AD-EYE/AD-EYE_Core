#ifndef __TYPES_H__
#define __TYPES_H__

#include <string>
#include <vector>
#include <map>

namespace kcan {

using namespace std;


enum class E2EProfile { None, P01a, P05 };


struct SignalInfo {
    string name;
    uint16_t start_bit;
    uint16_t length;
    string parent_name;
};


struct SignalGroupInfo {
    string name;
    uint16_t dataId;
    vector<string> signals;
    E2EProfile e2e_profile;
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

}

#endif