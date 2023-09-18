#include <map>
#include <stdexcept>

#include "fmt/core.h"

#include "dbc.h"
#include "dbc_reader.h"


namespace kcan {
namespace dbc {

std::map<string, SignalInfo> g_signals_info;
std::map<string, SignalGroupInfo> g_signalgroups_info;
std::map<string, FrameInfo> g_frames_info;
std::map<uint, string> g_frame_ids;

} // namespace dbc


void DBCReader::init() {
    using namespace dbc;

    SSMBMid6CanFdFr01_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMBMid6CanFdFr02_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMBMid6CanFdFr03_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMBMid6CanFdFr04_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMBMid6CanFdFr05_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMBMid6CanFdFr06_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMBMid6CanFdFr07_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMBMid6CanFdFr08_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMBMid6CanFdFr11_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMMid3CanFr01_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMMid3CanFr02_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMMid3CanFr07_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMMid3CanFr11_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMMid5CanFdFr01_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMMid5CanFdFr03_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMMid5CanFdFr04_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMMid5CanFdFr06_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMMid5CanFdFr07_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr01_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr03_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr04_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr05_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr06_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr08_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr09_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr10_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr11_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr12_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr13_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr15_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr17_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr18_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr20_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr21_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr22_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr23_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr24_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr25_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr28_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr30_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr31_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr34_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr35_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr36_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr01_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr03_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr04_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr14_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr19_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr20_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr21_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr22_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr23_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr24_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr25_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr26_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr27_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr28_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr29_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VimbMid6CanFdCanNmFr_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr01_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr02_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr03_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr04_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr05_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr06_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr07_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr08_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr09_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr10_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr11_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr12_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr13_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr14_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr15_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VimMid3CanNmFr_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr02_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr03_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr04_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr05_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr06_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr07_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr08_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr09_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr10_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr11_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr12_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr13_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VimMid5CanFdCanNmFr_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMPrototypeMid5CanFdFr13_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    Vcu1ToAllFuncMid3DiagReqFrame_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VimMid5CanFdTimeSynchFr_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VimbMid6CanFdTimeSynchFr_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
}


const FrameInfo &DBCReader::getFrameInfo(const string &name) {
    using namespace dbc;
    auto found = g_frames_info.find(name);
    if (found == g_frames_info.end()) {
        throw invalid_argument(fmt::format("Frame [{}] not found!", name));
    }
    return found->second;
}


const FrameInfo &DBCReader::getFrameInfo(uint id) {
    using namespace dbc;
    try {
        string &frame_name = g_frame_ids.at(id);
        auto found = g_frames_info.find(frame_name);
        if (found == g_frames_info.end()) {
            throw invalid_argument(fmt::format("Frame [{}] not found!", id));
        }
        return found->second;
    } catch (out_of_range) {
        throw invalid_argument("Frame not found!");
    }
}


const SignalGroupInfo &DBCReader::getSignalGroupInfo(const string &name) {
    using namespace dbc;
    auto found = g_signalgroups_info.find(name);
    if (found == g_signalgroups_info.end()) {
        throw invalid_argument(fmt::format("Signal group [{}] not found!", name));
    }
    return found->second;
}


const SignalInfo &DBCReader::getSignalInfo(const string &name) {
    using namespace dbc;
    auto found = g_signals_info.find(name);
    if (found == g_signals_info.end()) {
        throw invalid_argument(fmt::format("Signal [{}] not found!", name));
    }
    return found->second;
}

} // namespace kcan