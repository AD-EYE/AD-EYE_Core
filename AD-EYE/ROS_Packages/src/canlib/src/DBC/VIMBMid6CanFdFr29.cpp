#include "VIMBMid6CanFdFr29.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr29_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ SecAdWhlLockReqChks, { SecAdWhlLockReqChks, 8, 8, true, SignalType::E2E_CHKS, 0, SecAdWhlLockReq, ParentType::GROUP } });
    signals_info.insert({ SecAdWhlLockReqCntr, { SecAdWhlLockReqCntr, 0, 4, true, SignalType::E2E_CNTR, 0, SecAdWhlLockReq, ParentType::GROUP } });
    signals_info.insert({ SecAdWhlLockReqNoReqApplyRel, { SecAdWhlLockReqNoReqApplyRel, 4, 2, true, SignalType::APP_UNSIGNED, 0, SecAdWhlLockReq, ParentType::GROUP } });
    signals_info.insert({ SecAdWhlLockReq_UB, { SecAdWhlLockReq_UB, 6, 1, true, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr29, ParentType::FRAME } });

    signalgroups_info.insert({ SecAdWhlLockReq, { SecAdWhlLockReq, 0x710, { SecAdWhlLockReqChks, SecAdWhlLockReqCntr, SecAdWhlLockReqNoReqApplyRel }, { E2EProfileType::P01a, SecAdWhlLockReqChks, SecAdWhlLockReqCntr }, VIMBMid6CanFdFr29 } } );

    frames_info.insert({ VIMBMid6CanFdFr29, { VIMBMid6CanFdFr29, 768, 8, 290, { SecAdWhlLockReq }, { SecAdWhlLockReq_UB } } });

    frame_ids.insert({ 768, VIMBMid6CanFdFr29 });
}


}
}
