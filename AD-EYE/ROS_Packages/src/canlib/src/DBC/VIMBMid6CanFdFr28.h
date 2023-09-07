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
const string VIMBMid6CanFdFr28 { "VIMBMid6CanFdFr28" };

// Groups
const string AdSecALgtLimReqGroupSafe { "AdSecALgtLimReqGroupSafe" };
const string SecAdNomALgtReqGroupSafe { "SecAdNomALgtReqGroupSafe" };

// Signals
const string AdSecALgtLimReqGroupSafe_UB { "AdSecALgtLimReqGroupSafe_UB" };
const string AdSecALgtLimReqGroupSafeALgtMaxReq { "AdSecALgtLimReqGroupSafeALgtMaxReq" };
const string AdSecALgtLimReqGroupSafeALgtMinReq { "AdSecALgtLimReqGroupSafeALgtMinReq" };
const string AdSecALgtLimReqGroupSafeChks { "AdSecALgtLimReqGroupSafeChks" };
const string AdSecALgtLimReqGroupSafeCntr { "AdSecALgtLimReqGroupSafeCntr" };
const string SecAdNomALgtReqGroupSafe_UB { "SecAdNomALgtReqGroupSafe_UB" };
const string SecAdNomALgtReqGroupSafeALgtNomReqMax { "SecAdNomALgtReqGroupSafeALgtNomReqMax" };
const string SecAdNomALgtReqGroupSafeALgtNomReqMin { "SecAdNomALgtReqGroupSafeALgtNomReqMin" };
const string SecAdNomALgtReqGroupSafeChks { "SecAdNomALgtReqGroupSafeChks" };
const string SecAdNomALgtReqGroupSafeCntr { "SecAdNomALgtReqGroupSafeCntr" };
const string SecAdNomALgtReqGroupSafeNegLimForJerk { "SecAdNomALgtReqGroupSafeNegLimForJerk" };
const string SecAdNomALgtReqGroupSafePosLimForJerk { "SecAdNomALgtReqGroupSafePosLimForJerk" };

}
}
