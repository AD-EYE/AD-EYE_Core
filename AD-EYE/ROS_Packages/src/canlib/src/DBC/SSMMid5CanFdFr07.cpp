#include "SSMMid5CanFdFr07.h"


namespace kcan {
namespace dbc {


void SSMMid5CanFdFr07_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ SteerMechMonSts, { SteerMechMonSts, 5, 2, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr07, ParentType::FRAME } });
    signals_info.insert({ SteerMechMonSts_UB, { SteerMechMonSts_UB, 7, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr07, ParentType::FRAME } });


    frames_info.insert({ SSMMid5CanFdFr07, { SSMMid5CanFdFr07, 257, 8, 160, {  }, { SteerMechMonSts, SteerMechMonSts_UB } } });

    frame_ids.insert({ 257, SSMMid5CanFdFr07 });
}


}
}
