#include "VIMBMid6CanFdFr28.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr28_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecALgtLimReqGroupSafe_UB, { AdSecALgtLimReqGroupSafe_UB, 4, 1, SignalType::APP_UNSIGNED, VIMBMid6CanFdFr28 } });
    signals_info.insert({ AdSecALgtLimReqGroupSafeALgtMaxReq, { AdSecALgtLimReqGroupSafeALgtMaxReq, 8, 12, SignalType::APP_UNSIGNED, AdSecALgtLimReqGroupSafe } });
    signals_info.insert({ AdSecALgtLimReqGroupSafeALgtMinReq, { AdSecALgtLimReqGroupSafeALgtMinReq, 8, 12, SignalType::APP_UNSIGNED, AdSecALgtLimReqGroupSafe } });
    signals_info.insert({ AdSecALgtLimReqGroupSafeChks, { AdSecALgtLimReqGroupSafeChks, 32, 8, SignalType::E2E_CHKS, AdSecALgtLimReqGroupSafe } });
    signals_info.insert({ AdSecALgtLimReqGroupSafeCntr, { AdSecALgtLimReqGroupSafeCntr, 20, 4, SignalType::E2E_CNTR, AdSecALgtLimReqGroupSafe } });
    signals_info.insert({ SecAdNomALgtReqGroupSafe_UB, { SecAdNomALgtReqGroupSafe_UB, 5, 1, SignalType::APP_UNSIGNED, VIMBMid6CanFdFr28 } });
    signals_info.insert({ SecAdNomALgtReqGroupSafeALgtNomReqMax, { SecAdNomALgtReqGroupSafeALgtNomReqMax, 32, 12, SignalType::APP_UNSIGNED, SecAdNomALgtReqGroupSafe } });
    signals_info.insert({ SecAdNomALgtReqGroupSafeALgtNomReqMin, { SecAdNomALgtReqGroupSafeALgtNomReqMin, 48, 12, SignalType::APP_UNSIGNED, SecAdNomALgtReqGroupSafe } });
    signals_info.insert({ SecAdNomALgtReqGroupSafeChks, { SecAdNomALgtReqGroupSafeChks, 72, 8, SignalType::E2E_CHKS, SecAdNomALgtReqGroupSafe } });
    signals_info.insert({ SecAdNomALgtReqGroupSafeCntr, { SecAdNomALgtReqGroupSafeCntr, 60, 4, SignalType::E2E_CNTR, SecAdNomALgtReqGroupSafe } });
    signals_info.insert({ SecAdNomALgtReqGroupSafeNegLimForJerk, { SecAdNomALgtReqGroupSafeNegLimForJerk, 72, 12, SignalType::APP_UNSIGNED, SecAdNomALgtReqGroupSafe } });
    signals_info.insert({ SecAdNomALgtReqGroupSafePosLimForJerk, { SecAdNomALgtReqGroupSafePosLimForJerk, 88, 12, SignalType::APP_UNSIGNED, SecAdNomALgtReqGroupSafe } });

    signalgroups_info.insert(
    {
        AdSecALgtLimReqGroupSafe,
        {
            AdSecALgtLimReqGroupSafe,
            0x1C5,
            {
                AdSecALgtLimReqGroupSafeALgtMaxReq,
                AdSecALgtLimReqGroupSafeALgtMinReq,
                AdSecALgtLimReqGroupSafeChks,
                AdSecALgtLimReqGroupSafeCntr
            }, 
            { E2EProfileType::P01a, AdSecALgtLimReqGroupSafeChks, AdSecALgtLimReqGroupSafeCntr },
            VIMBMid6CanFdFr28
        }
    });

    signalgroups_info.insert(
    {
        SecAdNomALgtReqGroupSafe,
        {
            SecAdNomALgtReqGroupSafe,
            0x2AA,
            {
                SecAdNomALgtReqGroupSafeALgtNomReqMax,
                SecAdNomALgtReqGroupSafeALgtNomReqMin,
                SecAdNomALgtReqGroupSafeChks,
                SecAdNomALgtReqGroupSafeCntr,
                SecAdNomALgtReqGroupSafeNegLimForJerk,
                SecAdNomALgtReqGroupSafePosLimForJerk
            }, 
            { E2EProfileType::P01a, SecAdNomALgtReqGroupSafeChks, SecAdNomALgtReqGroupSafeCntr },
            VIMBMid6CanFdFr28
        }
    });

    frames_info.insert({ VIMBMid6CanFdFr28, { VIMBMid6CanFdFr28, 80, 16, 10, { AdSecALgtLimReqGroupSafe, SecAdNomALgtReqGroupSafe }, { AdSecALgtLimReqGroupSafe_UB, SecAdNomALgtReqGroupSafe_UB } } });

    frame_ids.insert({ 80, VIMBMid6CanFdFr28 });
}


}
}
