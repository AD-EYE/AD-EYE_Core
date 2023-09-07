#include "SSMMid5CanFdFr06.h"


namespace kcan {
namespace dbc {


void SSMMid5CanFdFr06_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimSafeStopActvGroupSafe_UB, { AdPrimSafeStopActvGroupSafe_UB, 5, 1, SignalType::APP_UNSIGNED, SSMMid5CanFdFr06 } });
    signals_info.insert({ AdPrimSafeStopActvGroupSafeChks, { AdPrimSafeStopActvGroupSafeChks, 8, 8, SignalType::E2E_CHKS, AdPrimSafeStopActvGroupSafe } });
    signals_info.insert({ AdPrimSafeStopActvGroupSafeCntr, { AdPrimSafeStopActvGroupSafeCntr, 0, 4, SignalType::E2E_CNTR, AdPrimSafeStopActvGroupSafe } });
    signals_info.insert({ AdPrimSafeStopActvGroupSafePlatf, { AdPrimSafeStopActvGroupSafePlatf, 4, 1, SignalType::APP_UNSIGNED, AdPrimSafeStopActvGroupSafe } });
    signals_info.insert({ SSMDegraded_UB, { SSMDegraded_UB, 7, 1, SignalType::APP_UNSIGNED, SSMMid5CanFdFr06 } });
    signals_info.insert({ SSMDegradedchks, { SSMDegradedchks, 72, 8, SignalType::E2E_CHKS, SSMDegraded } });
    signals_info.insert({ SSMDegradedcntr, { SSMDegradedcntr, 64, 4, SignalType::E2E_CNTR, SSMDegraded } });
    signals_info.insert({ SSMDegradedssmdegraded, { SSMDegradedssmdegraded, 68, 4, SignalType::APP_UNSIGNED, SSMDegraded } });

    
    signalgroups_info.insert(
    {
        AdPrimSafeStopActvGroupSafe,
        {
            AdPrimSafeStopActvGroupSafe,
            0x1EB,
            {
                AdPrimSafeStopActvGroupSafeChks,
                AdPrimSafeStopActvGroupSafeCntr,
                AdPrimSafeStopActvGroupSafePlatf
            }, 
            E2EProfileType::None,
            SSMMid5CanFdFr06
        }
    });

    signalgroups_info.insert(
    {
        SSMDegraded,
        {
            SSMDegraded,
            0xEE,
            {
                SSMDegradedchks,
                SSMDegradedcntr, 
                SSMDegradedssmdegraded
            }, 
            { E2EProfileType::P01a, SSMDegradedchks, SSMDegradedcntr },
            SSMMid5CanFdFr06
        }
    });


    frames_info.insert({ SSMMid5CanFdFr06, { SSMMid5CanFdFr06, 58, 20, 0, { AdPrimSafeStopActvGroupSafe, SSMDegraded }, { AdPrimSafeStopActvGroupSafe_UB, SSMDegraded_UB } } });

    frame_ids.insert({ 58, SSMMid5CanFdFr06 });
}


}
}