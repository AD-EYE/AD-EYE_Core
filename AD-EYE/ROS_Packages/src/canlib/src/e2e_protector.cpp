#include <vector>
#include <stdexcept>
#include <sstream>

#include "e2e_protector.h"
#include "packer.h"

namespace kcan
{

    using namespace std;

    E2EProtector::E2EProtector(const string &sg_name) : sgi_{DBCReader::getSignalGroupInfo(sg_name)}
    {
        if (sgi_.e2e_profile != E2EProfile::None) {
            calculateGroupParams();
        }
        switch (sgi_.e2e_profile)
        {
        case E2EProfile::P01a:
        {
            e2e_state_ = new E2E_P01State;
            E2E_P01State *state = dynamic_cast<E2E_P01State *>(e2e_state_);
            E2E_P01ProtectInit(&state->protect);
            E2E_P01CheckInit(&state->check);
            break;
        }
        case E2EProfile::P05:
        {
            e2e_state_ = new E2E_P05State;
            E2E_P05State *state = dynamic_cast<E2E_P05State *>(e2e_state_);
            E2E_P05ProtectInit(&state->protect);
            E2E_P05CheckInit(&state->check);
            break;
        }
        }
    }

    void E2EProtector::calculateGroupParams()
    {
        SignalInfo hs{};
        SignalInfo ls{"", 0xFFFF, 0x0, ""};
        for (auto sname : sgi_.signals)
        {
            SignalInfo candidate = DBCReader::getSignalInfo(sname);
            if (hs.start_bit < candidate.start_bit)
            {
                hs = candidate;
            }
            if (ls.start_bit > candidate.start_bit)
            {
                ls = candidate;
            }
        }
        // Signals total length with holes between them
        sg_length_ = (hs.start_bit + hs.length) - ls.start_bit;
        // Add left hole (lowest bits)
        sg_length_ += ls.start_bit % 8;
        // Add right hole (highest bits)
        uint right_hole_size = (hs.start_bit + hs.length) % 8;
        if (right_hole_size > 0)
        {
            sg_length_ += 8 - right_hole_size;
        }

        sg_start_byte_ = ls.start_bit / 8;

        cntr_offset_ = DBCReader::getSignalInfo(sgi_.name + "Cntr").start_bit - ls.start_bit;
        chks_offset_ = DBCReader::getSignalInfo(sgi_.name + "Chks").start_bit - ls.start_bit;
    }

    void E2EProtector::validateData(const vector<uint8_t> &data)
    {
        if (data.size() < sg_start_byte_ + sg_length_ / 8)
        {
            throw invalid_argument("data is too short!");
        }
    }

    void E2EProtector::applyProfile(vector<uint8_t> &data)
    {
        Std_ReturnType status = E2E_E_OK;
        switch (sgi_.e2e_profile)
        {
        case E2EProfile::P01a:
            status = applyProfile01(data);
            break;
        case E2EProfile::P05:
            status = applyProfile05(data);
            break;
        }
        if (status != E2E_E_OK)
        {
            stringstream err_str;
            err_str << "E2E Profile error: " << static_cast<int>(status);
            throw runtime_error(err_str.str());
        }
    }

    Std_ReturnType E2EProtector::applyProfile01(vector<uint8_t> &data)
    {
        validateData(data);

        E2E_P01State *state = dynamic_cast<E2E_P01State *>(e2e_state_);
        /* Declare  E2E profile. Using 1a_both */
        E2E_P01ConfigType profile1a;
        profile1a.CounterOffset = cntr_offset_;
        profile1a.CRCOffset = chks_offset_;
        profile1a.DataID = sgi_.dataId;
        profile1a.DataIDNibbleOffset = 0; // Not used in BOTH configuration
        profile1a.DataIDMode = E2E_P01_DATAID_BOTH;
        profile1a.DataLength = sg_length_;
        profile1a.MaxDeltaCounterInit = 15;
        profile1a.MaxNoNewOrRepeatedData = 15;
        profile1a.SyncCounterInit = 15;


        vector<uint8_t> d(data.size(), 0xFF);

        for (auto s_name : sgi_.signals) {
            const SignalInfo& si = DBCReader::getSignalInfo(s_name);
            uint64_t val = Packer::unpack(data, si.start_bit, si.length);
            Packer::pack(d, si.start_bit, si.length, val);
        }

        Std_ReturnType st = E2E_P01Protect(&profile1a, &state->protect, d.data() + sg_start_byte_);

        data = d;
        return st;
    }

    Std_ReturnType E2EProtector::applyProfile05(vector<uint8_t> &data)
    {
        validateData(data);

        E2E_P05State *state = dynamic_cast<E2E_P05State *>(e2e_state_);
        /* Declare  E2E profile. Using 1a_both */
        E2E_P05ConfigType profile5;
        profile5.Offset = 0;
        profile5.DataID = sgi_.dataId;
        profile5.DataLength = sg_length_;
        profile5.MaxDeltaCounter = 20;

        return E2E_P05Protect(&profile5, &state->protect, data.data() + sg_start_byte_, sg_length_);
    }

}
