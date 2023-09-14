#include "../basic_types.h"

namespace kcan {
namespace dbc {


void Vcu1Mid3CanNmFr_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string Vcu1Mid3CanNmFr { "Vcu1Mid3CanNmFr" };


// Groups


// Signals
const std::string NM_NodeID_VCU1 { "NM_NodeID_VCU1" };
const std::string NM_PNI_VCU1 { "NM_PNI_VCU1" };
const std::string NM_AW_VCU1 { "NM_AW_VCU1" };
const std::string NM_CS_VCU1 { "NM_CS_VCU1" };
const std::string NM_RMR_VCU1 { "NM_RMR_VCU1" };
const std::string PNCEntrance_VCU1 { "PNCEntrance_VCU1" };
const std::string InfotainmentAndHMI_VCU1 { "InfotainmentAndHMI_VCU1" };
const std::string Body_VCU1 { "Body_VCU1" };
const std::string Visibility_VCU1 { "Visibility_VCU1" };
const std::string WarningSounds_VCU1 { "WarningSounds_VCU1" };
const std::string Hazard_VCU1 { "Hazard_VCU1" };
const std::string PNCLocking_VCU1 { "PNCLocking_VCU1" };
const std::string PNCDriverinfo_VCU1 { "PNCDriverinfo_VCU1" };
const std::string PNCDriverinfoPoll_VCU1 { "PNCDriverinfoPoll_VCU1" };
const std::string PNCGSD_VCU1 { "PNCGSD_VCU1" };
const std::string PNCGlobal_VCU1 { "PNCGlobal_VCU1" };
const std::string PNCTrailerCaravan_VCU1 { "PNCTrailerCaravan_VCU1" };
const std::string PNCDriving_VCU1 { "PNCDriving_VCU1" };
const std::string PNCPreClimatization_VCU1 { "PNCPreClimatization_VCU1" };
const std::string PNCCharging_VCU1 { "PNCCharging_VCU1" };
const std::string PNCStart_VCU1 { "PNCStart_VCU1" };
const std::string PNCSpare1_VCU1 { "PNCSpare1_VCU1" };
const std::string PNCSpare2_VCU1 { "PNCSpare2_VCU1" };
const std::string PNCSpare3_VCU1 { "PNCSpare3_VCU1" };
const std::string PNCSpare4_VCU1 { "PNCSpare4_VCU1" };
const std::string PNCHVEnergyStorage_VCU1 { "PNCHVEnergyStorage_VCU1" };
const std::string VehicleAPI_VCU1 { "VehicleAPI_VCU1" };
const std::string Brake_VCU1 { "Brake_VCU1" };
const std::string Diesel_VCU1 { "Diesel_VCU1" };


}
}
