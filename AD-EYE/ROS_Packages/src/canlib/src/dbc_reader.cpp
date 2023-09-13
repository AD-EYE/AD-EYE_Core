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
    SSMBMid6CanFdFr03_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMBMid6CanFdFr04_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMBMid6CanFdFr06_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMBMid6CanFdFr11_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);

    SSMMid3CanFr07_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMMid3CanFr11_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);

    VCU1Mid3CanFr01_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr03_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr08_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr12_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr13_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr25_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr30_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VCU1Mid3CanFr36_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);

    VIMMid3CanFr07_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr08_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr11_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr13_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr14_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid3CanFr15_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr02_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr11_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMMid5CanFdFr12_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);

    SSMMid5CanFdFr03_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    SSMMid5CanFdFr06_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);

    VIMBMid6CanFdFr14_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
    VIMBMid6CanFdFr28_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);
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