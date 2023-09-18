#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VimbMid6CanFdCanNmFr_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VimbMid6CanFdCanNmFr { "VimbMid6CanFdCanNmFr" };


// Groups


// Signals
const std::string NM_NodeID_VIMB { "NM_NodeID_VIMB" };
const std::string NM_PNI_VIMB { "NM_PNI_VIMB" };
const std::string NM_AW_VIMB { "NM_AW_VIMB" };
const std::string NM_CS_VIMB { "NM_CS_VIMB" };
const std::string NM_RMR_VIMB { "NM_RMR_VIMB" };
const std::string PNCEntrance_VIMB { "PNCEntrance_VIMB" };
const std::string InfotainmentAndHMI_VIMB { "InfotainmentAndHMI_VIMB" };
const std::string Body_VIMB { "Body_VIMB" };
const std::string Visibility_VIMB { "Visibility_VIMB" };
const std::string WarningSounds_VIMB { "WarningSounds_VIMB" };
const std::string Hazard_VIMB { "Hazard_VIMB" };
const std::string PNCLocking_VIMB { "PNCLocking_VIMB" };
const std::string PNCDriverinfo_VIMB { "PNCDriverinfo_VIMB" };
const std::string PNCDriverinfoPoll_VIMB { "PNCDriverinfoPoll_VIMB" };
const std::string PNCGSD_VIMB { "PNCGSD_VIMB" };
const std::string PNCGlobal_VIMB { "PNCGlobal_VIMB" };
const std::string PNCTrailerCaravan_VIMB { "PNCTrailerCaravan_VIMB" };
const std::string PNCDriving_VIMB { "PNCDriving_VIMB" };
const std::string PNCPreClimatization_VIMB { "PNCPreClimatization_VIMB" };
const std::string PNCCharging_VIMB { "PNCCharging_VIMB" };
const std::string PNCStart_VIMB { "PNCStart_VIMB" };
const std::string PNCSpare1_VIMB { "PNCSpare1_VIMB" };
const std::string PNCSpare2_VIMB { "PNCSpare2_VIMB" };
const std::string PNCSpare3_VIMB { "PNCSpare3_VIMB" };
const std::string PNCSpare4_VIMB { "PNCSpare4_VIMB" };
const std::string PNCHVEnergyStorage_VIMB { "PNCHVEnergyStorage_VIMB" };
const std::string VehicleAPI_VIMB { "VehicleAPI_VIMB" };
const std::string Brake_VIMB { "Brake_VIMB" };
const std::string Diesel_VIMB { "Diesel_VIMB" };


}
}
