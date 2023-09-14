#include "VIMMid5CanFdFr12.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr12_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimWhlAgReqGroupSafeChks, { AdPrimWhlAgReqGroupSafeChks, 8, 8, SignalType::E2E_CHKS, 0, AdPrimWhlAgReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimWhlAgReqGroupSafeCntr, { AdPrimWhlAgReqGroupSafeCntr, 0, 4, SignalType::E2E_CNTR, 0, AdPrimWhlAgReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimWhlAgReqGroupSafeWhlAgReq, { AdPrimWhlAgReqGroupSafeWhlAgReq, 8, 15, SignalType::APP_UNSIGNED, 16194, AdPrimWhlAgReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimWhlAgReqGroupSafe_UB, { AdPrimWhlAgReqGroupSafe_UB, 7, 1, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr12, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimWhlAgReqGroupSafe, { AdPrimWhlAgReqGroupSafe, 0x1B2, { AdPrimWhlAgReqGroupSafeChks, AdPrimWhlAgReqGroupSafeCntr, AdPrimWhlAgReqGroupSafeWhlAgReq }, { E2EProfileType::P01a, AdPrimWhlAgReqGroupSafeChks, AdPrimWhlAgReqGroupSafeCntr }, VIMMid5CanFdFr12 } } );

    frames_info.insert({ VIMMid5CanFdFr12, { VIMMid5CanFdFr12, 34, 20, 10, { AdPrimWhlAgReqGroupSafe }, { AdPrimWhlAgReqGroupSafe_UB } } });

    frame_ids.insert({ 34, VIMMid5CanFdFr12 });
}


}
}
