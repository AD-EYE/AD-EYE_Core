#ifndef __E2E_PROTECTOR_H__
#define __E2E_PROTECTOR_H__


#include <utility>

extern "C" {
#include "E2E/inc/E2E_P01.h"
#include "E2E/inc/E2E_P05.h"
}

#include "basic_types.h"
#include "dbc.h"
#include "dbc_reader.h"
#include "signal_values.h"


namespace kcan {


struct E2E_State {
    virtual ~E2E_State() {} // make it polymorphic
};


struct E2E_P01State : E2E_State {
    E2E_P01ProtectStateType protect;
    E2E_P01CheckStateType check;
};


struct E2E_P05State : E2E_State {
    E2E_P05ProtectStateType protect;
    E2E_P05CheckStateType check;
};


struct E2EResult {
    uint checksum;
    uint counter;
};


class E2EProtector {
  public:
    E2EProtector(const SignalGroupInfo &sgi, uint cntr_init = 0);
    E2EProtector(E2EProfileType profile, uint cntr_init = 0);

    E2EResult applyProfile(const SignalValues &sv);
    E2EResult applyProfile01(const SignalValues &sv, const E2E_P01ConfigType *config = nullptr);
    E2EResult applyProfile05(const SignalValues &sv, const E2E_P05ConfigType *config = nullptr);
    // Std_ReturnType checkProfile(vector<uint8_t>& data);

  private:
    void calculateGroupParams();
    void initProfile(E2EProfileType profile, uint cntr_init);
    void validateData(const vector<uint8_t> &data);
    void packSignals(const SignalValues &sv, vector<uint8_t> &signals, uint counter_pos);

    SignalGroupInfo sgi_;
    uint sg_length_;
    uint sg_start_byte_;
    uint cntr_offset_;
    uint chks_offset_;
    E2E_State *e2e_state_;
};


} // namespace kcan


#endif