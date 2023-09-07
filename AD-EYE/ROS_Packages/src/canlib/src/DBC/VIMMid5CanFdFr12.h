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
const string VIMMid5CanFdFr12 { "VIMMid5CanFdFr12" };

// Groups
const string AdPrimWhlAgReqGroupSafe { "AdPrimWhlAgReqGroupSafe" };

// Signals
const string AdPrimWhlAgReqGroupSafe_UB { "AdPrimWhlAgReqGroupSafe_UB" };
const string AdPrimWhlAgReqGroupSafeChks { "AdPrimWhlAgReqGroupSafeChks" };
const string AdPrimWhlAgReqGroupSafeCntr { "AdPrimWhlAgReqGroupSafeCntr" };
const string AdPrimWhlAgReqGroupSafeWhlAgReq { "AdPrimWhlAgReqGroupSafeWhlAgReq" };

}
}
