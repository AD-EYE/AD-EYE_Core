#include "SSMMid3CanFr02.h"


namespace kcan {
namespace dbc {


void SSMMid3CanFr02_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ PrimSafeStopActv1Chks, { PrimSafeStopActv1Chks, 8, 8, true, SignalType::E2E_CHKS, 0, PrimSafeStopActv1, ParentType::GROUP } });
    signals_info.insert({ PrimSafeStopActv1Cntr, { PrimSafeStopActv1Cntr, 0, 4, true, SignalType::E2E_CNTR, 0, PrimSafeStopActv1, ParentType::GROUP } });
    signals_info.insert({ PrimSafeStopActv1PlatformSafeStopActv, { PrimSafeStopActv1PlatformSafeStopActv, 4, 1, true, SignalType::APP_UNSIGNED, 0, PrimSafeStopActv1, ParentType::GROUP } });
    signals_info.insert({ PrimSafeStopActv1_UB, { PrimSafeStopActv1_UB, 5, 1, true, SignalType::APP_UNSIGNED, 0, SSMMid3CanFr02, ParentType::FRAME } });

    signalgroups_info.insert({ PrimSafeStopActv1, { PrimSafeStopActv1, 0x780, { PrimSafeStopActv1Chks, PrimSafeStopActv1Cntr, PrimSafeStopActv1PlatformSafeStopActv }, { E2EProfileType::P01a, PrimSafeStopActv1Chks, PrimSafeStopActv1Cntr }, SSMMid3CanFr02 } } );

    frames_info.insert({ SSMMid3CanFr02, { SSMMid3CanFr02, 55, 8, 10, { PrimSafeStopActv1 }, { PrimSafeStopActv1_UB } } });

    frame_ids.insert({ 55, SSMMid3CanFr02 });
}


}
}
