#include "VIMMid3CanFr15.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr15_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimALgtLimReqGroupSafeALgtMaxReq, { AdPrimALgtLimReqGroupSafeALgtMaxReq, 8, 12, SignalType::APP_UNSIGNED, 3840, AdPrimALgtLimReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimALgtLimReqGroupSafeALgtMinReq, { AdPrimALgtLimReqGroupSafeALgtMinReq, 24, 12, SignalType::APP_UNSIGNED, 0, AdPrimALgtLimReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimALgtLimReqGroupSafeChks, { AdPrimALgtLimReqGroupSafeChks, 32, 8, SignalType::E2E_CHKS, 0, AdPrimALgtLimReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimALgtLimReqGroupSafeCntr, { AdPrimALgtLimReqGroupSafeCntr, 20, 4, SignalType::E2E_CNTR, 0, AdPrimALgtLimReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimALgtLimReqGroupSafe_UB, { AdPrimALgtLimReqGroupSafe_UB, 4, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr15, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimALgtLimReqGroupSafe, { AdPrimALgtLimReqGroupSafe, 0x1C2, { AdPrimALgtLimReqGroupSafeALgtMaxReq, AdPrimALgtLimReqGroupSafeALgtMinReq, AdPrimALgtLimReqGroupSafeChks, AdPrimALgtLimReqGroupSafeCntr }, { E2EProfileType::P01a, AdPrimALgtLimReqGroupSafeChks, AdPrimALgtLimReqGroupSafeCntr }, VIMMid3CanFr15 } } );

    frames_info.insert({ VIMMid3CanFr15, { VIMMid3CanFr15, 87, 8, 10, { AdPrimALgtLimReqGroupSafe }, { AdPrimALgtLimReqGroupSafe_UB } } });

    frame_ids.insert({ 87, VIMMid3CanFr15 });
}


}
}
