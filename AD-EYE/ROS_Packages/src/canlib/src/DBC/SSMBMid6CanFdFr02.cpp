#include "SSMBMid6CanFdFr02.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr02_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecMotTqASILThrshldExcdChks, { AdSecMotTqASILThrshldExcdChks, 8, 8, true, SignalType::E2E_CHKS, 0, AdSecMotTqASILThrshldExcd, ParentType::GROUP } });
    signals_info.insert({ AdSecMotTqASILThrshldExcdCntr, { AdSecMotTqASILThrshldExcdCntr, 0, 4, true, SignalType::E2E_CNTR, 0, AdSecMotTqASILThrshldExcd, ParentType::GROUP } });
    signals_info.insert({ AdSecMotTqASILThrshldExcdThrshldExceeded, { AdSecMotTqASILThrshldExcdThrshldExceeded, 4, 1, true, SignalType::APP_UNSIGNED, 0, AdSecMotTqASILThrshldExcd, ParentType::GROUP } });
    signals_info.insert({ AdSecMotTqASILThrshldExcd_UB, { AdSecMotTqASILThrshldExcd_UB, 5, 1, true, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr02, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecMotTqASILThrshldExcd, { AdSecMotTqASILThrshldExcd, 0x728, { AdSecMotTqASILThrshldExcdChks, AdSecMotTqASILThrshldExcdCntr, AdSecMotTqASILThrshldExcdThrshldExceeded }, { E2EProfileType::P01a, AdSecMotTqASILThrshldExcdChks, AdSecMotTqASILThrshldExcdCntr }, SSMBMid6CanFdFr02 } } );

    frames_info.insert({ SSMBMid6CanFdFr02, { SSMBMid6CanFdFr02, 72, 8, 10, { AdSecMotTqASILThrshldExcd }, { AdSecMotTqASILThrshldExcd_UB } } });

    frame_ids.insert({ 72, SSMBMid6CanFdFr02 });
}


}
}
