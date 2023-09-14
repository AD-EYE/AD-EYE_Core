#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr28_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMBMid6CanFdFr28 { "VIMBMid6CanFdFr28" };


// Groups
const std::string AdSecALgtLimReqGroupSafe { "AdSecALgtLimReqGroupSafe" };
const std::string SecAdNomALgtReqGroupSafe { "SecAdNomALgtReqGroupSafe" };


// Signals
const std::string SecAdNomALgtReqGroupSafe_UB { "SecAdNomALgtReqGroupSafe_UB" };
const std::string AdSecALgtLimReqGroupSafe_UB { "AdSecALgtLimReqGroupSafe_UB" };
const std::string AdSecALgtLimReqGroupSafeALgtMaxReq { "AdSecALgtLimReqGroupSafeALgtMaxReq" };
const std::string AdSecALgtLimReqGroupSafeCntr { "AdSecALgtLimReqGroupSafeCntr" };
const std::string AdSecALgtLimReqGroupSafeALgtMinReq { "AdSecALgtLimReqGroupSafeALgtMinReq" };
const std::string AdSecALgtLimReqGroupSafeChks { "AdSecALgtLimReqGroupSafeChks" };
const std::string SecAdNomALgtReqGroupSafeALgtNomReqMax { "SecAdNomALgtReqGroupSafeALgtNomReqMax" };
const std::string SecAdNomALgtReqGroupSafeCntr { "SecAdNomALgtReqGroupSafeCntr" };
const std::string SecAdNomALgtReqGroupSafeALgtNomReqMin { "SecAdNomALgtReqGroupSafeALgtNomReqMin" };
const std::string SecAdNomALgtReqGroupSafeChks { "SecAdNomALgtReqGroupSafeChks" };
const std::string SecAdNomALgtReqGroupSafeNegLimForJerk { "SecAdNomALgtReqGroupSafeNegLimForJerk" };
const std::string SecAdNomALgtReqGroupSafePosLimForJerk { "SecAdNomALgtReqGroupSafePosLimForJerk" };


}
}
