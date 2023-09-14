#include "VIMBMid6CanFdFr14.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr14_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecWhlAgReqGroupSafeChks, { AdSecWhlAgReqGroupSafeChks, 24, 8, SignalType::E2E_CHKS, 0, AdSecWhlAgReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecWhlAgReqGroupSafeCntr, { AdSecWhlAgReqGroupSafeCntr, 0, 4, SignalType::E2E_CNTR, 0, AdSecWhlAgReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecWhlAgReqGroupSafeWhlAgReq, { AdSecWhlAgReqGroupSafeWhlAgReq, 0, 15, SignalType::APP_UNSIGNED, 16194, AdSecWhlAgReqGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecWhlAgReqGroupSafe_UB, { AdSecWhlAgReqGroupSafe_UB, 4, 1, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr14, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecWhlAgReqGroupSafe, { AdSecWhlAgReqGroupSafe, 0x1B1, { AdSecWhlAgReqGroupSafeChks, AdSecWhlAgReqGroupSafeCntr, AdSecWhlAgReqGroupSafeWhlAgReq }, { E2EProfileType::P01a, AdSecWhlAgReqGroupSafeChks, AdSecWhlAgReqGroupSafeCntr }, VIMBMid6CanFdFr14 } } );

    frames_info.insert({ VIMBMid6CanFdFr14, { VIMBMid6CanFdFr14, 38, 16, 10, { AdSecWhlAgReqGroupSafe }, { AdSecWhlAgReqGroupSafe_UB } } });

    frame_ids.insert({ 38, VIMBMid6CanFdFr14 });
}


}
}
