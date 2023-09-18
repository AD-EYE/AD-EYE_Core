#include "VimbMid6CanFdCanNmFr.h"


namespace kcan {
namespace dbc {


void VimbMid6CanFdCanNmFr_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ Body_VIMB, { Body_VIMB, 21, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ Brake_VIMB, { Brake_VIMB, 33, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ Diesel_VIMB, { Diesel_VIMB, 32, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ Hazard_VIMB, { Hazard_VIMB, 18, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ InfotainmentAndHMI_VIMB, { InfotainmentAndHMI_VIMB, 22, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_AW_VIMB, { NM_AW_VIMB, 12, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_CS_VIMB, { NM_CS_VIMB, 11, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_NodeID_VIMB, { NM_NodeID_VIMB, 0, 8, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_PNI_VIMB, { NM_PNI_VIMB, 14, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_RMR_VIMB, { NM_RMR_VIMB, 8, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCCharging_VIMB, { PNCCharging_VIMB, 25, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCDriverinfoPoll_VIMB, { PNCDriverinfoPoll_VIMB, 31, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCDriverinfo_VIMB, { PNCDriverinfo_VIMB, 16, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCDriving_VIMB, { PNCDriving_VIMB, 27, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCEntrance_VIMB, { PNCEntrance_VIMB, 23, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCGSD_VIMB, { PNCGSD_VIMB, 30, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCGlobal_VIMB, { PNCGlobal_VIMB, 29, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCHVEnergyStorage_VIMB, { PNCHVEnergyStorage_VIMB, 35, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCLocking_VIMB, { PNCLocking_VIMB, 17, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCPreClimatization_VIMB, { PNCPreClimatization_VIMB, 26, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare1_VIMB, { PNCSpare1_VIMB, 39, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare2_VIMB, { PNCSpare2_VIMB, 38, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare3_VIMB, { PNCSpare3_VIMB, 37, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare4_VIMB, { PNCSpare4_VIMB, 36, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCStart_VIMB, { PNCStart_VIMB, 24, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCTrailerCaravan_VIMB, { PNCTrailerCaravan_VIMB, 28, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ VehicleAPI_VIMB, { VehicleAPI_VIMB, 34, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ Visibility_VIMB, { Visibility_VIMB, 20, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ WarningSounds_VIMB, { WarningSounds_VIMB, 19, 1, true, SignalType::APP_UNSIGNED, 0, VimbMid6CanFdCanNmFr, ParentType::FRAME } });


    frames_info.insert({ VimbMid6CanFdCanNmFr, { VimbMid6CanFdCanNmFr, 1290, 8, 0xFFFFFFFF, {  }, { NM_NodeID_VIMB, VehicleAPI_VIMB, PNCSpare3_VIMB, Hazard_VIMB, PNCGSD_VIMB, PNCGlobal_VIMB, InfotainmentAndHMI_VIMB, PNCEntrance_VIMB, NM_PNI_VIMB, PNCCharging_VIMB, PNCSpare4_VIMB, PNCSpare1_VIMB, Visibility_VIMB, Brake_VIMB, PNCHVEnergyStorage_VIMB, Diesel_VIMB, NM_RMR_VIMB, NM_CS_VIMB, PNCPreClimatization_VIMB, Body_VIMB, PNCSpare2_VIMB, PNCLocking_VIMB, PNCDriverinfo_VIMB, WarningSounds_VIMB, PNCDriverinfoPoll_VIMB, PNCStart_VIMB, NM_AW_VIMB, PNCDriving_VIMB, PNCTrailerCaravan_VIMB } } });

    frame_ids.insert({ 1290, VimbMid6CanFdCanNmFr });
}


}
}
