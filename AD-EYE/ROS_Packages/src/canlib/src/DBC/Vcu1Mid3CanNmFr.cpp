#include "Vcu1Mid3CanNmFr.h"


namespace kcan {
namespace dbc {


void Vcu1Mid3CanNmFr_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ NM_AW_VCU1, { NM_AW_VCU1, 12, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCEntrance_VCU1, { PNCEntrance_VCU1, 23, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCDriverinfoPoll_VCU1, { PNCDriverinfoPoll_VCU1, 31, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCDriverinfo_VCU1, { PNCDriverinfo_VCU1, 16, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ VehicleAPI_VCU1, { VehicleAPI_VCU1, 34, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ Brake_VCU1, { Brake_VCU1, 33, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_CS_VCU1, { NM_CS_VCU1, 11, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_PNI_VCU1, { NM_PNI_VCU1, 14, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCHVEnergyStorage_VCU1, { PNCHVEnergyStorage_VCU1, 35, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCGSD_VCU1, { PNCGSD_VCU1, 30, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCStart_VCU1, { PNCStart_VCU1, 24, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ Hazard_VCU1, { Hazard_VCU1, 18, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCLocking_VCU1, { PNCLocking_VCU1, 17, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ Diesel_VCU1, { Diesel_VCU1, 32, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCGlobal_VCU1, { PNCGlobal_VCU1, 29, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_RMR_VCU1, { NM_RMR_VCU1, 8, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare3_VCU1, { PNCSpare3_VCU1, 37, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCPreClimatization_VCU1, { PNCPreClimatization_VCU1, 26, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare4_VCU1, { PNCSpare4_VCU1, 36, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCDriving_VCU1, { PNCDriving_VCU1, 27, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCTrailerCaravan_VCU1, { PNCTrailerCaravan_VCU1, 28, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCCharging_VCU1, { PNCCharging_VCU1, 25, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ Body_VCU1, { Body_VCU1, 21, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ Visibility_VCU1, { Visibility_VCU1, 20, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare1_VCU1, { PNCSpare1_VCU1, 39, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ InfotainmentAndHMI_VCU1, { InfotainmentAndHMI_VCU1, 22, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare2_VCU1, { PNCSpare2_VCU1, 38, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_NodeID_VCU1, { NM_NodeID_VCU1, 0, 8, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ WarningSounds_VCU1, { WarningSounds_VCU1, 19, 1, SignalType::APP_UNSIGNED, 0, Vcu1Mid3CanNmFr, ParentType::FRAME } });


    frames_info.insert({ Vcu1Mid3CanNmFr, { Vcu1Mid3CanNmFr, 1283, 8, 0xFFFFFFFF, {  }, { NM_AW_VCU1, PNCEntrance_VCU1, PNCDriverinfoPoll_VCU1, PNCDriverinfo_VCU1, VehicleAPI_VCU1, Brake_VCU1, NM_CS_VCU1, NM_PNI_VCU1, PNCHVEnergyStorage_VCU1, PNCGSD_VCU1, PNCStart_VCU1, Hazard_VCU1, PNCLocking_VCU1, Diesel_VCU1, PNCGlobal_VCU1, NM_RMR_VCU1, PNCSpare3_VCU1, PNCPreClimatization_VCU1, PNCSpare4_VCU1, PNCDriving_VCU1, PNCTrailerCaravan_VCU1, PNCCharging_VCU1, Body_VCU1, Visibility_VCU1, PNCSpare1_VCU1, InfotainmentAndHMI_VCU1, PNCSpare2_VCU1, NM_NodeID_VCU1, WarningSounds_VCU1 } } });

    frame_ids.insert({ 1283, Vcu1Mid3CanNmFr });
}


}
}
