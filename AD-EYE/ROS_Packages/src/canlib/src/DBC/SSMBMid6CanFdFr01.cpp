#include "SSMBMid6CanFdFr01.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr01_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecSteerStsSafeGroupAdSteerPerf, { AdSecSteerStsSafeGroupAdSteerPerf, 16, 5, true, SignalType::APP_UNSIGNED, 20, AdSecSteerStsSafeGroup, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerStsSafeGroupAdSteerSts, { AdSecSteerStsSafeGroupAdSteerSts, 21, 3, true, SignalType::APP_UNSIGNED, 4, AdSecSteerStsSafeGroup, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerStsSafeGroupChks, { AdSecSteerStsSafeGroupChks, 8, 8, true, SignalType::E2E_CHKS, 0, AdSecSteerStsSafeGroup, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerStsSafeGroupCntr, { AdSecSteerStsSafeGroupCntr, 0, 4, true, SignalType::E2E_CNTR, 0, AdSecSteerStsSafeGroup, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerStsSafeGroup_UB, { AdSecSteerStsSafeGroup_UB, 4, 1, true, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr01, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecSteerStsSafeGroup, { AdSecSteerStsSafeGroup, 0x1A1, { AdSecSteerStsSafeGroupAdSteerPerf, AdSecSteerStsSafeGroupAdSteerSts, AdSecSteerStsSafeGroupChks, AdSecSteerStsSafeGroupCntr }, { E2EProfileType::P01a, AdSecSteerStsSafeGroupChks, AdSecSteerStsSafeGroupCntr }, SSMBMid6CanFdFr01 } } );

    frames_info.insert({ SSMBMid6CanFdFr01, { SSMBMid6CanFdFr01, 23, 8, 10, { AdSecSteerStsSafeGroup }, { AdSecSteerStsSafeGroup_UB } } });

    frame_ids.insert({ 23, SSMBMid6CanFdFr01 });
}


}
}
