#include "VIMMid3CanFr14.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr14_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdNomALgtReqGroupSafeALgtNomReqMax, { AdNomALgtReqGroupSafeALgtNomReqMax, 8, 12, true, SignalType::APP_UNSIGNED, 3840, AdNomALgtReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdNomALgtReqGroupSafeALgtNomReqMin, { AdNomALgtReqGroupSafeALgtNomReqMin, 32, 12, true, SignalType::APP_UNSIGNED, 0, AdNomALgtReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdNomALgtReqGroupSafeChks, { AdNomALgtReqGroupSafeChks, 16, 8, true, SignalType::E2E_CHKS, 0, AdNomALgtReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdNomALgtReqGroupSafeCntr, { AdNomALgtReqGroupSafeCntr, 28, 4, true, SignalType::E2E_CNTR, 0, AdNomALgtReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdNomALgtReqGroupSafeNegLimForJerk, { AdNomALgtReqGroupSafeNegLimForJerk, 52, 12, true, SignalType::APP_UNSIGNED, 0, AdNomALgtReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdNomALgtReqGroupSafePosLimForJerk, { AdNomALgtReqGroupSafePosLimForJerk, 56, 12, true, SignalType::APP_UNSIGNED, 4000, AdNomALgtReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdNomALgtReqGroupSafe_UB, { AdNomALgtReqGroupSafe_UB, 4, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr14, ParentType::FRAME } });

    signalgroups_info.insert({ AdNomALgtReqGroupSafe, { AdNomALgtReqGroupSafe, 0x1C1, { AdNomALgtReqGroupSafeALgtNomReqMax, AdNomALgtReqGroupSafeALgtNomReqMin, AdNomALgtReqGroupSafeChks, AdNomALgtReqGroupSafeCntr, AdNomALgtReqGroupSafeNegLimForJerk, AdNomALgtReqGroupSafePosLimForJerk }, { E2EProfileType::P01a, AdNomALgtReqGroupSafeChks, AdNomALgtReqGroupSafeCntr }, VIMMid3CanFr14 } } );

    frames_info.insert({ VIMMid3CanFr14, { VIMMid3CanFr14, 86, 8, 10, { AdNomALgtReqGroupSafe }, { AdNomALgtReqGroupSafe_UB } } });

    frame_ids.insert({ 86, VIMMid3CanFr14 });
}


}
}
