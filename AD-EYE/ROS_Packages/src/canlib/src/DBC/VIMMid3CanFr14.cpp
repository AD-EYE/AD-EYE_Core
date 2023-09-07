#include "VIMMid3CanFr14.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr14_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdNomALgtReqGroupSafe_UB, { AdNomALgtReqGroupSafe_UB, 4, 1, SignalType::APP_UNSIGNED, VIMMid3CanFr14 } });
    signals_info.insert({ AdNomALgtReqGroupSafeALgtNomReqMax, { AdNomALgtReqGroupSafeALgtNomReqMax, 8, 12, SignalType::APP_UNSIGNED, AdNomALgtReqGroupSafe } });
    signals_info.insert({ AdNomALgtReqGroupSafeALgtNomReqMin, { AdNomALgtReqGroupSafeALgtNomReqMin, 16, 12, SignalType::APP_UNSIGNED, AdNomALgtReqGroupSafe } });
    signals_info.insert({ AdNomALgtReqGroupSafeChks, { AdNomALgtReqGroupSafeChks, 16, 8, SignalType::E2E_CHKS, AdNomALgtReqGroupSafe } });
    signals_info.insert({ AdNomALgtReqGroupSafeCntr, { AdNomALgtReqGroupSafeCntr, 28, 4, SignalType::E2E_CNTR, AdNomALgtReqGroupSafe } });
    signals_info.insert({ AdNomALgtReqGroupSafeNegLimForJerk, { AdNomALgtReqGroupSafeNegLimForJerk, 36, 12, SignalType::APP_UNSIGNED, AdNomALgtReqGroupSafe } });
    signals_info.insert({ AdNomALgtReqGroupSafePosLimForJerk, { AdNomALgtReqGroupSafePosLimForJerk, 40, 12, SignalType::APP_UNSIGNED, AdNomALgtReqGroupSafe } });

    signalgroups_info.insert(
    {
        AdNomALgtReqGroupSafe,
        {
            AdNomALgtReqGroupSafe,
            0x1C1,
            {
                AdNomALgtReqGroupSafeALgtNomReqMax,
                AdNomALgtReqGroupSafeALgtNomReqMin,
                AdNomALgtReqGroupSafeChks,
                AdNomALgtReqGroupSafeCntr,
                AdNomALgtReqGroupSafeNegLimForJerk,
                AdNomALgtReqGroupSafePosLimForJerk
            }, 
            { E2EProfileType::P01a, AdNomALgtReqGroupSafeChks, AdNomALgtReqGroupSafeCntr },
            VIMMid3CanFr14
        }
    });

    frames_info.insert({ VIMMid3CanFr14, { VIMMid3CanFr14, 86, 8, 10, { AdNomALgtReqGroupSafe }, { AdNomALgtReqGroupSafe_UB } } });

    frame_ids.insert({ 86, VIMMid3CanFr14 });
}


}
}
