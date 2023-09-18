#include "SSMBMid6CanFdFr11.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr11_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecSafeStopActvGroupSafeChks, { AdSecSafeStopActvGroupSafeChks, 24, 8, true, SignalType::E2E_CHKS, 0, AdSecSafeStopActvGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecSafeStopActvGroupSafeCntr, { AdSecSafeStopActvGroupSafeCntr, 16, 4, true, SignalType::E2E_CNTR, 0, AdSecSafeStopActvGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecSafeStopActvGroupSafePlatformSafeStopActv, { AdSecSafeStopActvGroupSafePlatformSafeStopActv, 20, 1, true, SignalType::APP_UNSIGNED, 0, AdSecSafeStopActvGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecWhlAgRateLimEstimdSafeAdWhlAgRate1, { AdSecWhlAgRateLimEstimdSafeAdWhlAgRate1, 88, 15, true, SignalType::APP_UNSIGNED, 14000, AdSecWhlAgRateLimEstimdSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecWhlAgRateLimEstimdSafeChks, { AdSecWhlAgRateLimEstimdSafeChks, 72, 8, true, SignalType::E2E_CHKS, 0, AdSecWhlAgRateLimEstimdSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecWhlAgRateLimEstimdSafeCntr, { AdSecWhlAgRateLimEstimdSafeCntr, 64, 4, true, SignalType::E2E_CNTR, 0, AdSecWhlAgRateLimEstimdSafe, ParentType::GROUP } });
    signals_info.insert({ SecMaxALatEstimdGroupAcceleration, { SecMaxALatEstimdGroupAcceleration, 40, 15, true, SignalType::APP_SIGNED, 0, SecMaxALatEstimdGroup, ParentType::GROUP } });
    signals_info.insert({ SecMaxALatEstimdGroupJerk, { SecMaxALatEstimdGroupJerk, 56, 15, true, SignalType::APP_SIGNED, 0, SecMaxALatEstimdGroup, ParentType::GROUP } });
    signals_info.insert({ AdSecSafeStopActvGroupSafe_UB, { AdSecSafeStopActvGroupSafe_UB, 21, 1, true, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr11, ParentType::FRAME } });
    signals_info.insert({ AdSecWhlAgRateLimEstimdSafe_UB, { AdSecWhlAgRateLimEstimdSafe_UB, 22, 1, true, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr11, ParentType::FRAME } });
    signals_info.insert({ SecMaxALatEstimdGroup_UB, { SecMaxALatEstimdGroup_UB, 39, 1, true, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr11, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecSafeStopActvGroupSafe, { AdSecSafeStopActvGroupSafe, 0x1EC, { AdSecSafeStopActvGroupSafeChks, AdSecSafeStopActvGroupSafeCntr, AdSecSafeStopActvGroupSafePlatformSafeStopActv }, { E2EProfileType::P01a, AdSecSafeStopActvGroupSafeChks, AdSecSafeStopActvGroupSafeCntr }, SSMBMid6CanFdFr11 } } );
    signalgroups_info.insert({ AdSecWhlAgRateLimEstimdSafe, { AdSecWhlAgRateLimEstimdSafe, 0x435, { AdSecWhlAgRateLimEstimdSafeAdWhlAgRate1, AdSecWhlAgRateLimEstimdSafeChks, AdSecWhlAgRateLimEstimdSafeCntr }, { E2EProfileType::P01a, AdSecWhlAgRateLimEstimdSafeChks, AdSecWhlAgRateLimEstimdSafeCntr }, SSMBMid6CanFdFr11 } } );
    signalgroups_info.insert({ SecMaxALatEstimdGroup, { SecMaxALatEstimdGroup, 0x0, { SecMaxALatEstimdGroupAcceleration, SecMaxALatEstimdGroupJerk }, { E2EProfileType::None, "", "" }, SSMBMid6CanFdFr11 } } );

    frames_info.insert({ SSMBMid6CanFdFr11, { SSMBMid6CanFdFr11, 85, 20, 25, { AdSecSafeStopActvGroupSafe, AdSecWhlAgRateLimEstimdSafe, SecMaxALatEstimdGroup }, { AdSecSafeStopActvGroupSafe_UB, SecMaxALatEstimdGroup_UB, AdSecWhlAgRateLimEstimdSafe_UB } } });

    frame_ids.insert({ 85, SSMBMid6CanFdFr11 });
}


}
}
