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
const std::string VIMMid3CanFr15 { "VIMMid3CanFr15" };


// Groups
const std::string AdPrimALgtLimReqGroupSafe { "AdPrimALgtLimReqGroupSafe" };


// Signals
const std::string AdPrimALgtLimReqGroupSafe_UB { "AdPrimALgtLimReqGroupSafe_UB" };
const std::string AdPrimALgtLimReqGroupSafeALgtMaxReq { "AdPrimALgtLimReqGroupSafeALgtMaxReq" };
const std::string AdPrimALgtLimReqGroupSafeCntr { "AdPrimALgtLimReqGroupSafeCntr" };
const std::string AdPrimALgtLimReqGroupSafeALgtMinReq { "AdPrimALgtLimReqGroupSafeALgtMinReq" };
const std::string AdPrimALgtLimReqGroupSafeChks { "AdPrimALgtLimReqGroupSafeChks" };


}
}
