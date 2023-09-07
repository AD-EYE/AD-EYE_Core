#include "../basic_types.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr14_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const string VIMMid3CanFr14 { "VIMMid3CanFr14" };

// Groups
const string AdNomALgtReqGroupSafe { "AdNomALgtReqGroupSafe" };

// Signals
const string AdNomALgtReqGroupSafe_UB { "AdNomALgtReqGroupSafe_UB" };
const string AdNomALgtReqGroupSafeALgtNomReqMax { "AdNomALgtReqGroupSafeALgtNomReqMax" };
const string AdNomALgtReqGroupSafeALgtNomReqMin { "AdNomALgtReqGroupSafeALgtNomReqMin" };
const string AdNomALgtReqGroupSafeChks { "AdNomALgtReqGroupSafeChks" };
const string AdNomALgtReqGroupSafeCntr { "AdNomALgtReqGroupSafeCntr" };
const string AdNomALgtReqGroupSafeNegLimForJerk { "AdNomALgtReqGroupSafeNegLimForJerk" };
const string AdNomALgtReqGroupSafePosLimForJerk { "AdNomALgtReqGroupSafePosLimForJerk" };

}
}
