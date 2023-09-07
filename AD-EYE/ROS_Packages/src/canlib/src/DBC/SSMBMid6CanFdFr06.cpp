#include "SSMBMid6CanFdFr06.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr06_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ SecYawRateSafe_UB, { SecYawRateSafe_UB, 330, 1, SignalType::APP_UNSIGNED, SSMBMid6CanFdFr06 } });
    signals_info.insert({ SecYawRateSafeChks, { SecYawRateSafeChks, 344, 8, SignalType::E2E_CHKS, SecYawRateSafe } });
    signals_info.insert({ SecYawRateSafeCntr, { SecYawRateSafeCntr, 336, 4, SignalType::E2E_CNTR, SecYawRateSafe } });
    signals_info.insert({ SecYawRateSafeMax, { SecYawRateSafeMax, 360, 15, SignalType::APP_SIGNED, SecYawRateSafe } });
    signals_info.insert({ SecYawRateSafeMin, { SecYawRateSafeMin, 376, 15, SignalType::APP_SIGNED, SecYawRateSafe } });
    signals_info.insert({ SecYawRateSafeMinMaxQf, { SecYawRateSafeMinMaxQf, 341, 2, SignalType::APP_UNSIGNED, SecYawRateSafe } });
    signals_info.insert({ SecYawRateSafeNom, { SecYawRateSafeNom, 392, 15, SignalType::APP_SIGNED, SecYawRateSafe } });
    signals_info.insert({ SecYawRateSafeNomQf, { SecYawRateSafeNomQf, 328, 2, SignalType::APP_UNSIGNED, SecYawRateSafe } });
    
    signalgroups_info.insert(
    {
        SecYawRateSafe,
        {
            SecYawRateSafe,
            0x215,
            {
                SecYawRateSafeNomQf,
                SecYawRateSafeNom,
                SecYawRateSafeMinMaxQf,   
                SecYawRateSafeMin,
                SecYawRateSafeMax,
                SecYawRateSafeChks,
                SecYawRateSafeCntr
            }, 
            { E2EProfileType::P01a, SecYawRateSafeChks, SecYawRateSafeCntr },
            SSMBMid6CanFdFr06
        }
    });

    frames_info.insert({ SSMBMid6CanFdFr06, { SSMBMid6CanFdFr06, 49, 64, 100, { SecYawRateSafe }, { SecYawRateSafe_UB } } });

    frame_ids.insert({ 49, SSMBMid6CanFdFr06 });
}


}
}