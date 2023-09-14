#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr29_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMBMid6CanFdFr29 { "VIMBMid6CanFdFr29" };


// Groups
const std::string SecAdWhlLockReq { "SecAdWhlLockReq" };


// Signals
const std::string SecAdWhlLockReq_UB { "SecAdWhlLockReq_UB" };
const std::string SecAdWhlLockReqNoReqApplyRel { "SecAdWhlLockReqNoReqApplyRel" };
const std::string SecAdWhlLockReqCntr { "SecAdWhlLockReqCntr" };
const std::string SecAdWhlLockReqChks { "SecAdWhlLockReqChks" };


}
}
