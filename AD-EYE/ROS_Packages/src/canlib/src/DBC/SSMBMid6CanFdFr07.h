#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr07_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMBMid6CanFdFr07 { "SSMBMid6CanFdFr07" };


// Groups
const std::string SecVehSpdGroupSafe { "SecVehSpdGroupSafe" };


// Signals
const std::string SecVehSpdGroupSafe_UB { "SecVehSpdGroupSafe_UB" };
const std::string SecVehSpdGroupSafeMovDir { "SecVehSpdGroupSafeMovDir" };
const std::string SecVehSpdGroupSafeCntr { "SecVehSpdGroupSafeCntr" };
const std::string SecVehSpdGroupSafeChks { "SecVehSpdGroupSafeChks" };
const std::string SecVehSpdGroupSafeMinMaxQf { "SecVehSpdGroupSafeMinMaxQf" };
const std::string SecVehSpdGroupSafeMax { "SecVehSpdGroupSafeMax" };
const std::string SecVehSpdGroupSafeMovDirQf { "SecVehSpdGroupSafeMovDirQf" };
const std::string SecVehSpdGroupSafeMin { "SecVehSpdGroupSafeMin" };
const std::string SecVehSpdGroupSafeNomQf { "SecVehSpdGroupSafeNomQf" };
const std::string SecVehSpdGroupSafeNom { "SecVehSpdGroupSafeNom" };


}
}
