#ifndef __E2E_PROTECTOR_H__
#define __E2E_PROTECTOR_H__

extern "C" {

#include "E2E/inc/E2E_P01.h"
#include "E2E/inc/E2E_P05.h"

}

#include "dbc.h"
#include "dbc_reader.h"

namespace kcan {


struct E2E_State {
    virtual ~E2E_State() {} //make it polymorphic
};


struct E2E_P01State: E2E_State {
    E2E_P01ProtectStateType protect;
    E2E_P01CheckStateType check;
};


struct E2E_P05State: E2E_State {
    E2E_P05ProtectStateType protect;
    E2E_P05CheckStateType check;
};


class E2EProtector {
public:
    E2EProtector(const string& sg_name);

    void applyProfile(vector<uint8_t>& data);
    //Std_ReturnType checkProfile(vector<uint8_t>& data);

private:
    void calculateGroupParams();
    void validateData(const vector<uint8_t>& data);
    Std_ReturnType applyProfile05(vector<uint8_t>& data);
    Std_ReturnType applyProfile01(vector<uint8_t>& data);

    const kcan::SignalGroupInfo sgi_;
    uint sg_length_;
    uint sg_start_byte_;
    uint cntr_offset_;
    uint chks_offset_;
    E2E_State* e2e_state_;  
};

}

#endif