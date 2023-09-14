#include "../basic_types.h"

namespace kcan {
namespace dbc {


void Vcu1ToAllFuncMid3DiagReqFrame_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string Vcu1ToAllFuncMid3DiagReqFrame { "Vcu1ToAllFuncMid3DiagReqFrame" };


// Groups


// Signals
const std::string Vcu1ToAllFuncMid3DiagReqNpdu { "Vcu1ToAllFuncMid3DiagReqNpdu" };


}
}
