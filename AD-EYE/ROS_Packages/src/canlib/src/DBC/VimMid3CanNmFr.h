#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VimMid3CanNmFr_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VimMid3CanNmFr { "VimMid3CanNmFr" };


// Groups


// Signals
const std::string NM_NodeID_VIM { "NM_NodeID_VIM" };
const std::string NM_PNI_VIM { "NM_PNI_VIM" };
const std::string NM_AW_VIM { "NM_AW_VIM" };
const std::string NM_CS_VIM { "NM_CS_VIM" };
const std::string NM_RMR_VIM { "NM_RMR_VIM" };
const std::string PNCEntrance_VIM { "PNCEntrance_VIM" };
const std::string InfotainmentAndHMI_VIM { "InfotainmentAndHMI_VIM" };
const std::string Body_VIM { "Body_VIM" };
const std::string Visibility_VIM { "Visibility_VIM" };
const std::string WarningSounds_VIM { "WarningSounds_VIM" };
const std::string Hazard_VIM { "Hazard_VIM" };
const std::string PNCLocking_VIM { "PNCLocking_VIM" };
const std::string PNCDriverinfo_VIM { "PNCDriverinfo_VIM" };
const std::string PNCDriverinfoPoll_VIM { "PNCDriverinfoPoll_VIM" };
const std::string PNCGSD_VIM { "PNCGSD_VIM" };
const std::string PNCGlobal_VIM { "PNCGlobal_VIM" };
const std::string PNCTrailerCaravan_VIM { "PNCTrailerCaravan_VIM" };
const std::string PNCDriving_VIM { "PNCDriving_VIM" };
const std::string PNCPreClimatization_VIM { "PNCPreClimatization_VIM" };
const std::string PNCCharging_VIM { "PNCCharging_VIM" };
const std::string PNCStart_VIM { "PNCStart_VIM" };
const std::string PNCSpare1_VIM { "PNCSpare1_VIM" };
const std::string PNCSpare2_VIM { "PNCSpare2_VIM" };
const std::string PNCSpare3_VIM { "PNCSpare3_VIM" };
const std::string PNCSpare4_VIM { "PNCSpare4_VIM" };
const std::string PNCHVEnergyStorage_VIM { "PNCHVEnergyStorage_VIM" };
const std::string VehicleAPI_VIM { "VehicleAPI_VIM" };
const std::string Brake_VIM { "Brake_VIM" };
const std::string Diesel_VIM { "Diesel_VIM" };


}
}
