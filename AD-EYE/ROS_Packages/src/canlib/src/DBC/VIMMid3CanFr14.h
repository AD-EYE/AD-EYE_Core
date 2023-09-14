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
const std::string VIMMid3CanFr14 { "VIMMid3CanFr14" };


// Groups
const std::string AdNomALgtReqGroupSafe { "AdNomALgtReqGroupSafe" };


// Signals
const std::string AdNomALgtReqGroupSafe_UB { "AdNomALgtReqGroupSafe_UB" };
const std::string AdNomALgtReqGroupSafeALgtNomReqMax { "AdNomALgtReqGroupSafeALgtNomReqMax" };
const std::string AdNomALgtReqGroupSafeChks { "AdNomALgtReqGroupSafeChks" };
const std::string AdNomALgtReqGroupSafeCntr { "AdNomALgtReqGroupSafeCntr" };
const std::string AdNomALgtReqGroupSafeALgtNomReqMin { "AdNomALgtReqGroupSafeALgtNomReqMin" };
const std::string AdNomALgtReqGroupSafeNegLimForJerk { "AdNomALgtReqGroupSafeNegLimForJerk" };
const std::string AdNomALgtReqGroupSafePosLimForJerk { "AdNomALgtReqGroupSafePosLimForJerk" };


}
}
