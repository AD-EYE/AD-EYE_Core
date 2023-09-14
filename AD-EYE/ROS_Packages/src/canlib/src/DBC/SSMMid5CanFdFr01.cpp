#include "SSMMid5CanFdFr01.h"


namespace kcan {
namespace dbc {


void SSMMid5CanFdFr01_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ PinionSteerAg1, { PinionSteerAg1, 16, 15, SignalType::APP_SIGNED, 0, PinionSteerAg1Group, ParentType::GROUP } });
    signals_info.insert({ PinionSteerAg1Qf, { PinionSteerAg1Qf, 0, 2, SignalType::APP_UNSIGNED, 1, PinionSteerAg1Group, ParentType::GROUP } });
    signals_info.insert({ PinionSteerAgSpd1, { PinionSteerAgSpd1, 32, 14, SignalType::APP_SIGNED, 0, PinionSteerAgSpd1Group, ParentType::GROUP } });
    signals_info.insert({ PinionSteerAgSpd1Qf, { PinionSteerAgSpd1Qf, 30, 2, SignalType::APP_UNSIGNED, 1, PinionSteerAgSpd1Group, ParentType::GROUP } });
    signals_info.insert({ PinionSteerAgSpd1Group_UB, { PinionSteerAgSpd1Group_UB, 3, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr01, ParentType::FRAME } });
    signals_info.insert({ PinionSteerAg1Group_UB, { PinionSteerAg1Group_UB, 2, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr01, ParentType::FRAME } });

    signalgroups_info.insert({ PinionSteerAg1Group, { PinionSteerAg1Group, 0x0, { PinionSteerAg1, PinionSteerAg1Qf }, { E2EProfileType::None, "", "" }, SSMMid5CanFdFr01 } } );
    signalgroups_info.insert({ PinionSteerAgSpd1Group, { PinionSteerAgSpd1Group, 0x0, { PinionSteerAgSpd1, PinionSteerAgSpd1Qf }, { E2EProfileType::None, "", "" }, SSMMid5CanFdFr01 } } );

    frames_info.insert({ SSMMid5CanFdFr01, { SSMMid5CanFdFr01, 20, 20, 5, { PinionSteerAg1Group, PinionSteerAgSpd1Group }, { PinionSteerAgSpd1Group_UB, PinionSteerAg1Group_UB } } });

    frame_ids.insert({ 20, SSMMid5CanFdFr01 });
}


}
}
