#include "VimMid3CanNmFr.h"


namespace kcan {
namespace dbc {


void VimMid3CanNmFr_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ Brake_VIM, { Brake_VIM, 33, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_AW_VIM, { NM_AW_VIM, 12, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_NodeID_VIM, { NM_NodeID_VIM, 0, 8, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare1_VIM, { PNCSpare1_VIM, 39, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare3_VIM, { PNCSpare3_VIM, 37, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_PNI_VIM, { NM_PNI_VIM, 14, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCCharging_VIM, { PNCCharging_VIM, 25, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCDriverinfo_VIM, { PNCDriverinfo_VIM, 16, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ Body_VIM, { Body_VIM, 21, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ WarningSounds_VIM, { WarningSounds_VIM, 19, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_RMR_VIM, { NM_RMR_VIM, 8, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ Hazard_VIM, { Hazard_VIM, 18, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCEntrance_VIM, { PNCEntrance_VIM, 23, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ Visibility_VIM, { Visibility_VIM, 20, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare4_VIM, { PNCSpare4_VIM, 36, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ Diesel_VIM, { Diesel_VIM, 32, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ VehicleAPI_VIM, { VehicleAPI_VIM, 34, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_CS_VIM, { NM_CS_VIM, 11, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCStart_VIM, { PNCStart_VIM, 24, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCTrailerCaravan_VIM, { PNCTrailerCaravan_VIM, 28, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCGlobal_VIM, { PNCGlobal_VIM, 29, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCDriverinfoPoll_VIM, { PNCDriverinfoPoll_VIM, 31, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCPreClimatization_VIM, { PNCPreClimatization_VIM, 26, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCHVEnergyStorage_VIM, { PNCHVEnergyStorage_VIM, 35, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ InfotainmentAndHMI_VIM, { InfotainmentAndHMI_VIM, 22, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCDriving_VIM, { PNCDriving_VIM, 27, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare2_VIM, { PNCSpare2_VIM, 38, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCLocking_VIM, { PNCLocking_VIM, 17, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCGSD_VIM, { PNCGSD_VIM, 30, 1, SignalType::APP_UNSIGNED, 0, VimMid3CanNmFr, ParentType::FRAME } });


    frames_info.insert({ VimMid3CanNmFr, { VimMid3CanNmFr, 1288, 8, 0xFFFFFFFF, {  }, { Brake_VIM, NM_AW_VIM, NM_NodeID_VIM, PNCSpare1_VIM, PNCSpare3_VIM, NM_PNI_VIM, PNCCharging_VIM, PNCDriverinfo_VIM, Body_VIM, WarningSounds_VIM, NM_RMR_VIM, Hazard_VIM, PNCEntrance_VIM, Visibility_VIM, PNCSpare4_VIM, Diesel_VIM, VehicleAPI_VIM, NM_CS_VIM, PNCStart_VIM, PNCTrailerCaravan_VIM, PNCGlobal_VIM, PNCDriverinfoPoll_VIM, PNCPreClimatization_VIM, PNCHVEnergyStorage_VIM, InfotainmentAndHMI_VIM, PNCDriving_VIM, PNCSpare2_VIM, PNCLocking_VIM, PNCGSD_VIM } } });

    frame_ids.insert({ 1288, VimMid3CanNmFr });
}


}
}
