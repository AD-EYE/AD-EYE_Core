#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "e2e_protector.h"
#include "packer.h"


namespace kcan {
using namespace std;

E2EProtector::E2EProtector(const string &sg_name, uint cntr_init)
    : sgi_(DBCReader::getSignalGroupInfo(sg_name)) {
    initProfile(sgi_.e2e_settings.type, cntr_init);
}

E2EProtector::E2EProtector(E2EProfileType profile, uint cntr_init) {
    initProfile(profile, cntr_init);
}

void E2EProtector::calculateGroupParams() {
    SignalInfo hs{};
    SignalInfo ls{"", 0xFFFF, 0x0, SignalType::APP_UNSIGNED, 0x0, ""};
    for (auto sname : sgi_.signals) {
        SignalInfo candidate = DBCReader::getSignalInfo(sname);
        if (hs.start_bit < candidate.start_bit) {
            hs = candidate;
        }
        if (ls.start_bit > candidate.start_bit) {
            ls = candidate;
        }
    }
    // Signals total length with holes between them
    sg_length_ = (hs.start_bit + hs.length) - ls.start_bit;
    // Add left hole (lowest bits)
    sg_length_ += ls.start_bit % 8;
    // Add right hole (highest bits)
    uint right_hole_size = (hs.start_bit + hs.length) % 8;
    if (right_hole_size > 0) {
        sg_length_ += 8 - right_hole_size;
    }

    sg_start_byte_ = ls.start_bit / 8;

    cntr_offset_ = DBCReader::getSignalInfo(sgi_.name + "Cntr").start_bit - ls.start_bit;
    chks_offset_ = DBCReader::getSignalInfo(sgi_.name + "Chks").start_bit - ls.start_bit;
}

void E2EProtector::validateData(const vector<uint8_t> &data) {
    if (data.size() < sg_start_byte_ + sg_length_ / 8) {
        throw invalid_argument("data is too short!");
    }
}

E2EResult E2EProtector::applyProfile(const SignalValues &sv) {
    Std_ReturnType status = E2E_E_OK;
    switch (sgi_.e2e_settings.type) {
    case E2EProfileType::P01a:
        return applyProfile01(sv);
    case E2EProfileType::P05:
        return applyProfile05(sv);
    }
    /*
    if (status != E2E_E_OK)
    {
        stringstream err_str;
        err_str << "E2E Profile error: " << static_cast<int>(status);
        throw runtime_error(err_str.str());
    }
    */
}

E2EResult E2EProtector::applyProfile01(const SignalValues &sv, const E2E_P01ConfigType *config) {
    // validateData(data);

    E2E_P01State *state = dynamic_cast<E2E_P01State *>(e2e_state_);

    // Arrange data elements for CRC caclulation
    vector<uint8_t> signals{0x0, state->protect.Counter};
    packSignals(sv, signals, 1);
    state->protect.Counter = signals[1];

    E2E_P01ConfigType profile1a;
    if (config != nullptr) {
        profile1a = *config;
    } else {
        profile1a.CounterOffset = 8;
        profile1a.CRCOffset = 0;
        profile1a.DataID = sgi_.dataId;
        profile1a.DataIDNibbleOffset = 0; // Not used in BOTH configuration
        profile1a.DataIDMode = E2E_P01_DATAID_BOTH;
        profile1a.DataLength = signals.size() * 8;
        profile1a.MaxDeltaCounterInit = 15;
        profile1a.MaxNoNewOrRepeatedData = 15;
        profile1a.SyncCounterInit = 15;
    }

    Std_ReturnType status = E2E_P01Protect(&profile1a, &state->protect, signals.data());
    if (status != E2E_E_OK) {
        throw runtime_error("E2E Error");
    }

    E2EResult res;
    res.checksum = signals[0];
    res.counter = signals[1];
    return res;
    /*
            vector<uint8_t> d(data.size(), 0xFF);

            for (auto s_name : sgi_.signals) {
                const SignalInfo& si = DBCReader::getSignalInfo(s_name);
                uint64_t val = Packer::unpack(data, si.start_bit, si.length);
                Packer::pack(d, si.start_bit, si.length, val);
            }

            uint8_t r[32];
            for (int i = sg_start_byte_ + sg_length_ / 8 - 1, j = 0; i >= sg_start_byte_; i--, j++)
       { r[j] = d[i];
            }
    */
    // Std_ReturnType st = E2E_P01Protect(&profile1a, &state->protect, data.data() +
    // sg_start_byte_); Std_ReturnType st = E2E_P01Protect(&profile1a, &state->protect, data.data()
    // + 0);
    //        data = d;
    // return st;
}

E2EResult E2EProtector::applyProfile05(const SignalValues &sv, const E2E_P05ConfigType *config) {
    // validateData(data);
    E2E_P05State *state = dynamic_cast<E2E_P05State *>(e2e_state_);

    // Arrange data elements for CRC caclulation
    vector<uint8_t> signals{0x0, 0x0, state->protect.Counter};
    packSignals(sv, signals, 2);
    state->protect.Counter = signals[2];

    E2E_P05ConfigType profile5;
    if (config != nullptr) {
        profile5 = *config;
    } else {
        profile5.Offset = 0;
        profile5.DataID = sgi_.dataId;
        profile5.DataLength = signals.size() * 8;
        profile5.MaxDeltaCounter = 20;
    }

    Std_ReturnType status =
        E2E_P05Protect(&profile5, &state->protect, signals.data(), signals.size());
    if (status != E2E_E_OK) {
        throw runtime_error("E2E Error");
    }

    E2EResult res;
    res.checksum = static_cast<uint>(signals[1]) << 8 | signals[0];
    res.counter = signals[2];
    return res;
}


void E2EProtector::initProfile(E2EProfileType profile, uint cntr_init) {
    switch (profile) {
    case E2EProfileType::P01a: {
        e2e_state_ = new E2E_P01State;
        E2E_P01State *state = dynamic_cast<E2E_P01State *>(e2e_state_);
        E2E_P01ProtectInit(&state->protect);
        E2E_P01CheckInit(&state->check);
        state->protect.Counter = cntr_init;
        break;
    }
    case E2EProfileType::P05: {
        e2e_state_ = new E2E_P05State;
        E2E_P05State *state = dynamic_cast<E2E_P05State *>(e2e_state_);
        E2E_P05ProtectInit(&state->protect);
        E2E_P05CheckInit(&state->check);
        state->protect.Counter = cntr_init;
        break;
    }
    }
}

void E2EProtector::packSignals(const SignalValues &sv, vector<uint8_t> &signals,
                               uint counter_pos) {
    for (auto &el : sv) {
        const string &sig_name = el.first;
        uint64_t sig_value = el.second;
        const SignalInfo &si{DBCReader::getSignalInfo(sig_name)};
        if (si.type == SignalType::E2E_CHKS) {
            continue;
        }
        if (si.type == SignalType::E2E_CNTR) {
            signals[counter_pos] = static_cast<uint8_t>(sig_value);
            continue;
        }

        uint sig_size{};
        if (si.type == SignalType::APP_SIGNED) {
            sig_size = (si.length + 7) / 8;
        } else {
            sig_size = (si.length + 7) / 8;
        }

        bool is_ones_padding =
            false; //(1UL << (si.length - 1) & sig_value) && si.type != SignalType::APP_SIGNED;

        if (si.type == SignalType::APP_SIGNED) {
            // cout << "---------------SIGNED:" << (int)sig_value << endl;
            // sig_value = ~sig_value + 1;
            // cout << sig_name << " " << sig_value << endl;
        }

        vector<uint8_t> signal(sig_size, is_ones_padding ? 0xFF : 0x0);

        /*
                    cout << sig_name << " " << hex << sig_value << ": ";
                    for (int i = 0; i < signal.size(); i++) {
                        cout << hex << (int)signal[i] << " ";
                    }
                    cout  << endl;
        */
        Packer::pack(signal, 0, si.length, sig_value);
        signals.insert(signals.end(), signal.begin(), signal.end());
    }
}
} // namespace kcan
