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
const string VIMBMid6CanFdFr14 { "VIMBMid6CanFdFr14" };

// Groups
const string AdSecWhlAgReqGroupSafe { "AdSecWhlAgReqGroupSafe" };

// Signals
const string AdSecWhlAgReqGroupSafe_UB { "AdSecWhlAgReqGroupSafe_UB" };
const string AdSecWhlAgReqGroupSafeChks { "AdSecWhlAgReqGroupSafeChks" };
const string AdSecWhlAgReqGroupSafeCntr { "AdSecWhlAgReqGroupSafeCntr" };
const string AdSecWhlAgReqGroupSafeWhlAgReq { "AdSecWhlAgReqGroupSafeWhlAgReq" };

}
}
