#include <map>
#include <stdexcept>

#include "dbc_reader.h"
#include "dbc.h"


namespace kcan {

namespace dbc {

std::map<string, SignalInfo> g_signals_info;
std::map<string, SignalGroupInfo> g_signalgroups_info;
std::map<string, FrameInfo> g_frames_info;

std::map<uint32_t, string> g_frame_ids;

}


void DBCReader::init() {
    using namespace dbc;
    VIMMid3CanFr11_Init(g_frames_info, g_signalgroups_info, g_signals_info);
}


const FrameInfo& DBCReader::getFrameInfo(const string& name) {
    using namespace dbc;
    auto found = g_frames_info.find(name);
    if (found == g_frames_info.end()) {
        throw invalid_argument("Frame not found!");
    }
    return found->second;
}


const SignalGroupInfo& DBCReader::getSignalGroupInfo(const string& name) {
    using namespace dbc;
    auto found = g_signalgroups_info.find(name);
    if (found == g_signalgroups_info.end()) {
        throw invalid_argument("Signal group not found!");
    }
    return found->second;
}


const SignalInfo& DBCReader::getSignalInfo(const string& name) {
    using namespace dbc;
    auto found = g_signals_info.find(name);
    if (found == g_signals_info.end()) {
        throw invalid_argument("Signal not found!");
    }
    return found->second;
}

}