#include "../basic_types.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr13_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr13 { "VIMMid3CanFr13" };

// Groups
const std::string AdFreeDst { "AdFreeDst" };
const std::string AdWhlLockReq { "AdWhlLockReq" };

// Singals
const std::string AdFreeDst_UB { "AdFreeDst_UB" };
const std::string AdFreeDstChks { "AdFreeDstChks" };
const std::string AdFreeDstCntr { "AdFreeDstCntr" };
const std::string AdFreeDstFreeDstFwd { "AdFreeDstFreeDstFwd" };
const std::string AdFreeDstFreeDstRvs { "AdFreeDstFreeDstRvs" };
const std::string AdSetSpd { "AdSetSpd" };
const std::string AdSetSpd_UB { "AdSetSpd_UB" };
const std::string AdWhlLockReq_UB { "AdWhlLockReq_UB" };
const std::string AdWhlLockReqChks { "AdWhlLockReqChks" };
const std::string AdWhlLockReqCntr { "AdWhlLockReqCntr" };
const std::string AdWhlLockReqNoReqApplyRel { "AdWhlLockReqNoReqApplyRel" };


}
}
