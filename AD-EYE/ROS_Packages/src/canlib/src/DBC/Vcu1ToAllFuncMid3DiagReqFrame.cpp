#include "Vcu1ToAllFuncMid3DiagReqFrame.h"


namespace kcan {
namespace dbc {


void Vcu1ToAllFuncMid3DiagReqFrame_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ Vcu1ToAllFuncMid3DiagReqNpdu, { Vcu1ToAllFuncMid3DiagReqNpdu, 56, 64, SignalType::APP_UNSIGNED, 0, Vcu1ToAllFuncMid3DiagReqFrame, ParentType::FRAME } });


    frames_info.insert({ Vcu1ToAllFuncMid3DiagReqFrame, { Vcu1ToAllFuncMid3DiagReqFrame, 2047, 8, 0xFFFFFFFF, {  }, { Vcu1ToAllFuncMid3DiagReqNpdu } } });

    frame_ids.insert({ 2047, Vcu1ToAllFuncMid3DiagReqFrame });
}


}
}
