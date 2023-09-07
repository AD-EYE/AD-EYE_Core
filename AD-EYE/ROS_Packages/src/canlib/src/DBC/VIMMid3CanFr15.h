#include "../basic_types.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr15_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const string VIMMid3CanFr15 { "VIMMid3CanFr15" };

// Groups
const string AdPrimALgtLimReqGroupSafe { "AdPrimALgtLimReqGroupSafe" };

// Signals
const string AdPrimALgtLimReqGroupSafe_UB { "AdPrimALgtLimReqGroupSafe_UB" };
const string AdPrimALgtLimReqGroupSafeALgtMaxReq { "AdPrimALgtLimReqGroupSafeALgtMaxReq" };
const string AdPrimALgtLimReqGroupSafeALgtMinReq { "AdPrimALgtLimReqGroupSafeALgtMinReq" };
const string AdPrimALgtLimReqGroupSafeChks { "AdPrimALgtLimReqGroupSafeChks" };
const string AdPrimALgtLimReqGroupSafeCntr { "AdPrimALgtLimReqGroupSafeCntr" };

}
}
