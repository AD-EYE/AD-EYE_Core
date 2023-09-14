#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr14_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMBMid6CanFdFr14 { "VIMBMid6CanFdFr14" };


// Groups
const std::string AdSecWhlAgReqGroupSafe { "AdSecWhlAgReqGroupSafe" };


// Signals
const std::string AdSecWhlAgReqGroupSafe_UB { "AdSecWhlAgReqGroupSafe_UB" };
const std::string AdSecWhlAgReqGroupSafeCntr { "AdSecWhlAgReqGroupSafeCntr" };
const std::string AdSecWhlAgReqGroupSafeWhlAgReq { "AdSecWhlAgReqGroupSafeWhlAgReq" };
const std::string AdSecWhlAgReqGroupSafeChks { "AdSecWhlAgReqGroupSafeChks" };


}
}
