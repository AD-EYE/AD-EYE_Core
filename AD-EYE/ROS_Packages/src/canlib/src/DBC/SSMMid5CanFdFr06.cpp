#include "SSMMid5CanFdFr06.h"


namespace kcan {
namespace dbc {


void SSMMid5CanFdFr06_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimSafeStopActvGroupSafeChks, { AdPrimSafeStopActvGroupSafeChks, 8, 8, true, SignalType::E2E_CHKS, 0, AdPrimSafeStopActvGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimSafeStopActvGroupSafeCntr, { AdPrimSafeStopActvGroupSafeCntr, 0, 4, true, SignalType::E2E_CNTR, 0, AdPrimSafeStopActvGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SSMDegradedchks, { SSMDegradedchks, 72, 8, true, SignalType::E2E_CHKS, 0, SSMDegraded, ParentType::GROUP } });
    signals_info.insert({ SSMDegradedcntr, { SSMDegradedcntr, 64, 4, true, SignalType::E2E_CNTR, 0, SSMDegraded, ParentType::GROUP } });
    signals_info.insert({ SSMDegradedssmdegraded, { SSMDegradedssmdegraded, 68, 4, true, SignalType::APP_UNSIGNED, 0, SSMDegraded, ParentType::GROUP } });
    signals_info.insert({ AdPrimSafeStopActvGroupSafePlatformSafeStopActv, { AdPrimSafeStopActvGroupSafePlatformSafeStopActv, 4, 1, true, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr06, ParentType::FRAME } });
    signals_info.insert({ AdPrimSafeStopActvGroupSafe_UB, { AdPrimSafeStopActvGroupSafe_UB, 5, 1, true, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr06, ParentType::FRAME } });
    signals_info.insert({ SSMDegraded_UB, { SSMDegraded_UB, 7, 1, true, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr06, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimSafeStopActvGroupSafe, { AdPrimSafeStopActvGroupSafe, 0x1EB, { AdPrimSafeStopActvGroupSafeChks, AdPrimSafeStopActvGroupSafeCntr, AdPrimSafeStopActvGroupSafePlatformSafeStopActv }, { E2EProfileType::P01a, AdPrimSafeStopActvGroupSafeChks, AdPrimSafeStopActvGroupSafeCntr }, SSMMid5CanFdFr06 } } );
    signalgroups_info.insert({ SSMDegraded, { SSMDegraded, 0x0, { SSMDegradedchks, SSMDegradedcntr, SSMDegradedssmdegraded }, { E2EProfileType::P01a, SSMDegradedchks, SSMDegradedcntr }, SSMMid5CanFdFr06 } } );

    frames_info.insert({ SSMMid5CanFdFr06, { SSMMid5CanFdFr06, 58, 20, 25, { AdPrimSafeStopActvGroupSafe, SSMDegraded }, { AdPrimSafeStopActvGroupSafePlatformSafeStopActv, AdPrimSafeStopActvGroupSafe_UB, SSMDegraded_UB } } });

    frame_ids.insert({ 58, SSMMid5CanFdFr06 });
}


}
}
