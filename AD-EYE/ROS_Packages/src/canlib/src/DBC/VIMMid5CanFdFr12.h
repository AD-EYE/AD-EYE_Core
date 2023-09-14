#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid5CanFdFr12_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid5CanFdFr12 { "VIMMid5CanFdFr12" };


// Groups
const std::string AdPrimWhlAgReqGroupSafe { "AdPrimWhlAgReqGroupSafe" };


// Signals
const std::string AdPrimWhlAgReqGroupSafe_UB { "AdPrimWhlAgReqGroupSafe_UB" };
const std::string AdPrimWhlAgReqGroupSafeCntr { "AdPrimWhlAgReqGroupSafeCntr" };
const std::string AdPrimWhlAgReqGroupSafeChks { "AdPrimWhlAgReqGroupSafeChks" };
const std::string AdPrimWhlAgReqGroupSafeWhlAgReq { "AdPrimWhlAgReqGroupSafeWhlAgReq" };


}
}
