#ifndef __CAN_FRAME__H__
#define __CAN_FRAME__H__

#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include "spdlog/spdlog.h"

#include "dbc.h"
#include "dbc_reader.h"
#include "e2e_protector.h"
#include "packer.h"
#include "signal_values.h"


namespace kcan {


class CANFrame {
  public:
    CANFrame() = default;
    CANFrame(CANBus bus, const string &name, uint8_t filling = 0x0) {
        name_ = name;
        bus_ = bus;
        frame_info_ = DBCReader::getFrameInfo(bus_, name_);
        data_.assign(frame_info_.length, filling);
        for (auto sg_name : frame_info_.signal_groups) {
            const SignalGroupInfo &sgi { DBCReader::getSignalGroupInfo(bus_, sg_name) };
            if (sgi.e2e_settings.type != E2EProfileType::None) {
                e2e_protectors_.insert({sg_name, new E2EProtector(sgi)});
            }
        }
    }

    ~CANFrame() {
        if (th_ != nullptr) {
            th_->join();
            delete th_;
        }
    }

    void setFrame(const string &name, const SignalValues& sv, bool override_ub) {
        for (auto &group_name : frame_info_.signal_groups) {
            SignalValues group_sv;
            auto &sgi = DBCReader::getSignalGroupInfo(bus_, group_name);
            for (auto &sig_name : sgi.signals) {
                try {
                    group_sv.addSignal(sig_name, sv.getValue(sig_name));
                } catch (invalid_argument) {
                    auto &si = DBCReader::getSignalInfo(bus_, sig_name);
                    group_sv.addSignal(sig_name, si.initial);
                }
            }
            setSignalGroup(group_name, group_sv);
        }

        for (auto &sig_name : frame_info_.signals) {
            auto &si = DBCReader::getSignalInfo(bus_, sig_name);
            if (override_ub && sig_name.size() > 3) {
                if (sig_name.substr(sig_name.size() - 3, 3) == "_UB") {
                    setSignal(sig_name, 1);
                    continue;
                }
            }
            try {
                setSignal(sig_name, sv.getValue(sig_name));
            } catch (invalid_argument) {
                setSignal(sig_name, si.initial);
            }
        }
    }

    void setSignalGroup(const string &name, const SignalValues &values) {
        kcan::SignalGroupInfo sgi = DBCReader::getSignalGroupInfo(bus_, name);
        SignalValues sv(bus_);
        for (auto s_name : sgi.signals) {
            try {
                sv.addSignal(s_name, values.getValue(s_name));
            } catch (invalid_argument) {
                auto &si = DBCReader::getSignalInfo(bus_, s_name);
                if (si.type != SignalType::E2E_CHKS && si.type != SignalType::E2E_CNTR) {
                    sv.addSignal(s_name, getSignal(si));
                }
            }
        }

        auto e2e_protector = e2e_protectors_.find(sgi.name);
        if (e2e_protector != e2e_protectors_.end()) {
            E2EResult res = e2e_protector->second->applyProfile(sv);
            sv.addSignal(sgi.e2e_settings.checksum_name, res.checksum);
            sv.addSignal(sgi.e2e_settings.counter_name, res.counter);
        }

        for (auto &signal_el : sv) {
            const SignalInfo &si = DBCReader::getSignalInfo(bus_, signal_el.first);
            Packer::pack(data_, signal_el.second, si.start_bit, si.length, si.big_endian);
        }
    }

    void setSignals(SignalValues &values) {
        string signal_name = values.begin()->first;
        kcan::SignalInfo si = DBCReader::getSignalInfo(bus_, signal_name);
        kcan::SignalGroupInfo sgi = DBCReader::getSignalGroupInfo(bus_, si.parent_name);
        for (auto el : values) {
            setSignal(el.first, el.second);
        }
    }

    void setSignal(const string &name, uint64_t val) {
        const SignalInfo &si = DBCReader::getSignalInfo(bus_, name);
        Packer::pack(data_, val, si.start_bit, si.length, si.big_endian);
        active_signals_.insert(si.name);
    }

    void setRawData(const vector<uint8_t> &data) {
        if (data_.size() != data.size()) {
            throw invalid_argument("Data size doesn't match frame size!");
        }
        data_ = data;
    }

    void setRawData(const uint8_t *data, size_t size) {
        data_.resize(size);
        data_.assign(data, data + size);
    }

    void setId(uint32_t id) { frame_info_.id = id; }

    void resolveFrameInfo(CANBus bus) {
        frame_info_ = DBCReader::getFrameInfo(bus, frame_info_.id);
    }

    SignalValues getSignalGroup(const string &name) {
        SignalValues sv;
        auto &sgi = DBCReader::getSignalGroupInfo(bus_, name);
        for (auto &s_name : sgi.signals) {
            auto &si = DBCReader::getSignalInfo(bus_, s_name);
            uint64_t s_value = Packer::unpack(data_, si.start_bit, si.length, si.big_endian);
            sv.addSignal(s_name, s_value);
        }
        return sv;
    }

    SignalValues getSignal(const string &name) {
        SignalValues sv;
        auto &si = DBCReader::getSignalInfo(bus_, name);
        uint64_t s_value = Packer::unpack(data_, si.start_bit, si.length, si.big_endian);
        sv.addSignal(name, s_value);
        return sv;
    }

    const string &getName() { return name_; }

    const FrameInfo &getFrameInfo() { return frame_info_; }

    const uint8_t *getData() { return data_.data(); }

    size_t getDataSize() { return data_.size(); }

    void print(const string &title = "", ostream &o = cout) {
        o << title;
        o << hex << setfill('0') << setw(3) << frame_info_.id << ": ";
        for (int i = 0; i < data_.size(); i++) {
            o << hex << setfill('0') << setw(2) << (int)data_[i] << " ";
        }
        o << endl;
    }

    void log(const string &title = "") {
        stringstream buff;
        buff << title;
        buff << hex << setfill('0') << setw(3) << frame_info_.id << ": ";
        for (int i = 0; i < data_.size(); i++) {
            buff << hex << setfill('0') << setw(2) << (int)data_[i] << " ";
        }
        spdlog::info(buff.str());
    }

  private:
    void validateSignal(SignalInfo &si) {
        if (si.parent_name != name_) {
            throw "Signal doesn't belong to the frame!";
        }
    }

    uint64_t getSignal(const SignalInfo &si) { 
        Packer::unpack(data_, si.start_bit, si.length, si.big_endian); 
    }

    string name_;
    CANBus bus_;
    FrameInfo frame_info_;
    set<string> active_signals_;
    thread *th_{nullptr};
    bool alive_{true};
    bool suspended_{false};
    vector<uint8_t> data_;
    map<std::string, E2EProtector *> e2e_protectors_;
};


} // namespace kcan

#endif
