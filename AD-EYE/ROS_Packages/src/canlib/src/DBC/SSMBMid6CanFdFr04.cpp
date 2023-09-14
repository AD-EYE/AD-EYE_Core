#include "SSMBMid6CanFdFr04.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr04_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ BrkDegradedRdntChks, { BrkDegradedRdntChks, 8, 8, SignalType::E2E_CHKS, 0, BrkDegradedRdnt, ParentType::GROUP } });
    signals_info.insert({ BrkDegradedRdntCntr, { BrkDegradedRdntCntr, 0, 4, SignalType::E2E_CNTR, 0, BrkDegradedRdnt, ParentType::GROUP } });
    signals_info.insert({ BrkDegradedRdntSts, { BrkDegradedRdntSts, 8, 16, SignalType::APP_UNSIGNED, 0, BrkDegradedRdnt, ParentType::GROUP } });
    signals_info.insert({ BrkDegradedRdnt_UB, { BrkDegradedRdnt_UB, 4, 1, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr04, ParentType::FRAME } });

    signalgroups_info.insert({ BrkDegradedRdnt, { BrkDegradedRdnt, 0x255, { BrkDegradedRdntChks, BrkDegradedRdntCntr, BrkDegradedRdntSts }, { E2EProfileType::P01a, BrkDegradedRdntChks, BrkDegradedRdntCntr }, SSMBMid6CanFdFr04 } } );

    frames_info.insert({ SSMBMid6CanFdFr04, { SSMBMid6CanFdFr04, 21, 8, 5, { BrkDegradedRdnt }, { BrkDegradedRdnt_UB } } });

    frame_ids.insert({ 21, SSMBMid6CanFdFr04 });
}


}
}
