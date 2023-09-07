#include "SSMBMid6CanFdFr11.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr11_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecSafeStopActvGroupSafe_UB , { AdSecSafeStopActvGroupSafe_UB, 20, 1, SignalType::APP_UNSIGNED, SSMBMid6CanFdFr11} });
    signals_info.insert({ AdSecSafeStopActvGroupSafeChks , { AdSecSafeStopActvGroupSafeChks, 24, 8, SignalType::APP_UNSIGNED, AdSecSafeStopActvGroupSafe } });
    signals_info.insert({ AdSecSafeStopActvGroupSafeCntr, { AdSecSafeStopActvGroupSafeCntr, 16, 4, SignalType::APP_UNSIGNED, AdSecSafeStopActvGroupSafe } });
    signals_info.insert({ AdSecSafeStopActvGroupSafePlatformSafeStopActv, { AdSecSafeStopActvGroupSafePlatformSafeStopActv, 20, 1, SignalType::APP_UNSIGNED, AdSecSafeStopActvGroupSafe } });
    signals_info.insert({ AdSecWhlAgRateLimEstimdSafe_UB, { AdSecWhlAgRateLimEstimdSafe_UB, 22, 1, SignalType::APP_UNSIGNED, SSMBMid6CanFdFr11} });
    signals_info.insert({ AdSecWhlAgRateLimEstimdSafeAdWhlAgRate1, { AdSecWhlAgRateLimEstimdSafeAdWhlAgRate1, 88, 15, SignalType::APP_UNSIGNED, AdSecWhlAgRateLimEstimdSafe } });
    signals_info.insert({ AdSecWhlAgRateLimEstimdSafeChks, { AdSecWhlAgRateLimEstimdSafeChks, 72, 8, SignalType::APP_UNSIGNED, AdSecWhlAgRateLimEstimdSafe } });
    signals_info.insert({ AdSecWhlAgRateLimEstimdSafeCntr, { AdSecWhlAgRateLimEstimdSafeCntr, 64, 4, SignalType::APP_UNSIGNED, AdSecWhlAgRateLimEstimdSafe } });
    signals_info.insert({ SecMaxALatEstimdGroup_UB, { SecMaxALatEstimdGroup_UB, 39, 1, SignalType::APP_UNSIGNED, SSMBMid6CanFdFr11 } });
    signals_info.insert({ SecMaxALatEstimdGroupAcceleration, { SecMaxALatEstimdGroupAcceleration, 24, 15, SignalType::APP_SIGNED, SecMaxALatEstimdGroup } });
    signals_info.insert({ SecMaxALatEstimdGroupJerk, { SecMaxALatEstimdGroupJerk, 40, 15, SignalType::APP_SIGNED, SecMaxALatEstimdGroup } });

    
    signalgroups_info.insert(
    {
        AdSecSafeStopActvGroupSafe,
        {
            AdSecSafeStopActvGroupSafe,
            0x1EC,
            {
                AdSecSafeStopActvGroupSafePlatformSafeStopActv,
                AdSecSafeStopActvGroupSafeChks,
                AdSecSafeStopActvGroupSafeCntr
            }, 
            { E2EProfileType::P01a, AdSecSafeStopActvGroupSafeChks, AdSecSafeStopActvGroupSafeCntr },
            SSMBMid6CanFdFr11
        }
    });

    signalgroups_info.insert(
    {
        AdSecWhlAgRateLimEstimdSafe,
        {
            AdSecWhlAgRateLimEstimdSafe,
            0x435,
            {
                AdSecWhlAgRateLimEstimdSafeAdWhlAgRate1,
                AdSecWhlAgRateLimEstimdSafeChks,
                AdSecWhlAgRateLimEstimdSafeCntr
            },
            { E2EProfileType::P01a, AdSecWhlAgRateLimEstimdSafeChks, AdSecWhlAgRateLimEstimdSafeCntr },
            SSMBMid6CanFdFr11
        }
    });

    signalgroups_info.insert(
    {
        SecMaxALatEstimdGroup,
        {
            SecMaxALatEstimdGroup,
            0x0,
            {
                SecMaxALatEstimdGroupAcceleration,
                SecMaxALatEstimdGroupJerk
            },
            { E2EProfileType::None, "", "" },
            SSMBMid6CanFdFr11
        }
    });

    frames_info.insert(
    { 
        SSMBMid6CanFdFr11,
        {
            SSMBMid6CanFdFr11,
            85,
            20,
            100, 
            { 
                AdSecSafeStopActvGroupSafe,
                AdSecWhlAgRateLimEstimdSafe,
                SecMaxALatEstimdGroup
            },
            { 
                AdSecSafeStopActvGroupSafe_UB,
                AdSecWhlAgRateLimEstimdSafe_UB,
                SecMaxALatEstimdGroup_UB
            } 
        }
    });

    frame_ids.insert({ 85, SSMBMid6CanFdFr11 });
}


}
}