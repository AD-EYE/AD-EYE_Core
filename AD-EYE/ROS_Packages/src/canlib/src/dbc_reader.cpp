#include <map>
#include <stdexcept>

#include "fmt/core.h"

#include "dbc.h"
#include "dbc_reader.h"


namespace kcan {
namespace dbc {

std::map<CANBus, std::map<string, SignalInfo>> g_signals_info;
std::map<CANBus, std::map<string, SignalGroupInfo>> g_signalgroups_info;
std::map<CANBus, std::map<string, FrameInfo>> g_frames_info;
std::map<CANBus, std::map<uint, string>> g_frame_ids;

} // namespace dbc


void DBCReader::init() {
    using namespace dbc;

    auto &frame_ids_A = g_frame_ids[CANBus::A];
    auto &frame_ids_B = g_frame_ids[CANBus::B];
    auto &frame_ids_C = g_frame_ids[CANBus::C];

    auto &frames_info_A = g_frames_info[CANBus::A];
    auto &frames_info_B = g_frames_info[CANBus::B];
    auto &frames_info_C = g_frames_info[CANBus::C];

    auto &signalgroups_info_A = g_signalgroups_info[CANBus::A];
    auto &signalgroups_info_B = g_signalgroups_info[CANBus::B];
    auto &signalgroups_info_C = g_signalgroups_info[CANBus::C];

    auto &signals_info_A = g_signals_info[CANBus::A];
    auto &signals_info_B = g_signals_info[CANBus::B];
    auto &signals_info_C = g_signals_info[CANBus::C];

    SSMBMid6CanFdFr01_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    SSMBMid6CanFdFr02_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    SSMBMid6CanFdFr03_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    SSMBMid6CanFdFr04_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    SSMBMid6CanFdFr05_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    SSMBMid6CanFdFr06_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    SSMBMid6CanFdFr07_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    SSMBMid6CanFdFr08_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    SSMBMid6CanFdFr11_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    SSMMid3CanFr01_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    SSMMid3CanFr02_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    SSMMid3CanFr07_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    SSMMid3CanFr11_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    SSMMid5CanFdFr01_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    SSMMid5CanFdFr03_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    SSMMid5CanFdFr04_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    SSMMid5CanFdFr06_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    SSMMid5CanFdFr07_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VCU1Mid3CanFr01_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr03_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr04_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr05_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr06_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr08_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr09_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr10_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr11_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr12_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr13_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr15_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr17_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr18_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr20_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr21_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr22_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr23_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr24_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr25_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr28_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr30_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr31_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr34_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr35_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VCU1Mid3CanFr36_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMBMid6CanFdFr01_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr03_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr04_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr14_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr19_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr20_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr21_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr22_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr23_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr24_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr25_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr26_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr27_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr28_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMBMid6CanFdFr29_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VIMMid3CanFr01_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr02_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr03_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr04_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr05_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr06_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr07_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr08_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr09_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr10_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr11_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr12_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr13_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr14_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid3CanFr15_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VIMMid5CanFdFr02_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VIMMid5CanFdFr03_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VIMMid5CanFdFr04_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VIMMid5CanFdFr05_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VIMMid5CanFdFr06_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VIMMid5CanFdFr07_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VIMMid5CanFdFr08_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VIMMid5CanFdFr09_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VIMMid5CanFdFr10_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VIMMid5CanFdFr11_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VIMMid5CanFdFr12_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VIMMid5CanFdFr13_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VIMPrototypeMid5CanFdFr13_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    Vcu1ToAllFuncMid3DiagReqFrame_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VimMid3CanNmFr_Init(frame_ids_A, frames_info_A, signalgroups_info_A, signals_info_A);
    VimMid5CanFdCanNmFr_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VimMid5CanFdTimeSynchFr_Init(frame_ids_B, frames_info_B, signalgroups_info_B, signals_info_B);
    VimbMid6CanFdCanNmFr_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
    VimbMid6CanFdTimeSynchFr_Init(frame_ids_C, frames_info_C, signalgroups_info_C, signals_info_C);
}


const FrameInfo &DBCReader::getFrameInfo(CANBus bus, const string &name) {
    using namespace dbc;
    auto &frames_info = g_frames_info[bus];
    auto found = frames_info.find(name);
    if (found == frames_info.end()) {
        throw invalid_argument(fmt::format("Frame [{}] not found!", name));
    }
    return found->second;
}


const FrameInfo &DBCReader::getFrameInfo(CANBus bus, uint id) {
    using namespace dbc;
    auto &frame_ids = g_frame_ids[bus];
    auto &frames_info = g_frames_info[bus];
    try {
        string &frame_name = frame_ids.at(id);
        auto found = frames_info.find(frame_name);
        if (found == frames_info.end()) {
            throw invalid_argument(fmt::format("Frame [{}] not found!", id));
        }
        return found->second;
    } catch (out_of_range) {
        throw invalid_argument("Frame not found!");
    }
}


const SignalGroupInfo &DBCReader::getSignalGroupInfo(CANBus bus, const string &name) {
    using namespace dbc;
    auto &signalgroups_info = g_signalgroups_info[bus];
    auto found = signalgroups_info.find(name);
    if (found == signalgroups_info.end()) {
        throw invalid_argument(fmt::format("Signal group [{}] not found!", name));
    }
    return found->second;
}


const SignalInfo &DBCReader::getSignalInfo(CANBus bus, const string &name) {
    using namespace dbc;
    auto &signals_info = g_signals_info[bus];
    auto found = signals_info.find(name);
    if (found == signals_info.end()) {
        throw invalid_argument(fmt::format("Signal [{}] not found!", name));
    }
    return found->second;
}

} // namespace kcan