#include "VimMid5CanFdCanNmFr.h"


namespace kcan {
namespace dbc {


void VimMid5CanFdCanNmFr_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    using namespace NVimMid5CanFdCanNmFr;
    
    signals_info.insert({ Body_VIM, { Body_VIM, 21, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ Brake_VIM, { Brake_VIM, 33, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ Diesel_VIM, { Diesel_VIM, 32, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ Hazard_VIM, { Hazard_VIM, 18, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ InfotainmentAndHMI_VIM, { InfotainmentAndHMI_VIM, 22, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_AW_VIM, { NM_AW_VIM, 12, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_CS_VIM, { NM_CS_VIM, 11, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_NodeID_VIM, { NM_NodeID_VIM, 0, 8, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_PNI_VIM, { NM_PNI_VIM, 14, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ NM_RMR_VIM, { NM_RMR_VIM, 8, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCCharging_VIM, { PNCCharging_VIM, 25, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCDriverinfoPoll_VIM, { PNCDriverinfoPoll_VIM, 31, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCDriverinfo_VIM, { PNCDriverinfo_VIM, 16, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCDriving_VIM, { PNCDriving_VIM, 27, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCEntrance_VIM, { PNCEntrance_VIM, 23, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCGSD_VIM, { PNCGSD_VIM, 30, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCGlobal_VIM, { PNCGlobal_VIM, 29, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCHVEnergyStorage_VIM, { PNCHVEnergyStorage_VIM, 35, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCLocking_VIM, { PNCLocking_VIM, 17, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCPreClimatization_VIM, { PNCPreClimatization_VIM, 26, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare1_VIM, { PNCSpare1_VIM, 39, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare2_VIM, { PNCSpare2_VIM, 38, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare3_VIM, { PNCSpare3_VIM, 37, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCSpare4_VIM, { PNCSpare4_VIM, 36, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCStart_VIM, { PNCStart_VIM, 24, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ PNCTrailerCaravan_VIM, { PNCTrailerCaravan_VIM, 28, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ VehicleAPI_VIM, { VehicleAPI_VIM, 34, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ Visibility_VIM, { Visibility_VIM, 20, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });
    signals_info.insert({ WarningSounds_VIM, { WarningSounds_VIM, 19, 1, true, SignalType::APP_UNSIGNED, 0, VimMid5CanFdCanNmFr, ParentType::FRAME } });


    frames_info.insert({ VimMid5CanFdCanNmFr, { VimMid5CanFdCanNmFr, 1286, 8, 0xFFFFFFFF, {  }, { PNCDriverinfo_VIM, PNCDriverinfoPoll_VIM, PNCSpare4_VIM, Diesel_VIM, NM_AW_VIM, PNCSpare2_VIM, Hazard_VIM, Visibility_VIM, Brake_VIM, Body_VIM, PNCGlobal_VIM, VehicleAPI_VIM, PNCGSD_VIM, NM_NodeID_VIM, PNCStart_VIM, PNCSpare3_VIM, PNCDriving_VIM, PNCPreClimatization_VIM, PNCTrailerCaravan_VIM, WarningSounds_VIM, InfotainmentAndHMI_VIM, NM_RMR_VIM, PNCHVEnergyStorage_VIM, PNCSpare1_VIM, NM_CS_VIM, NM_PNI_VIM, PNCEntrance_VIM, PNCLocking_VIM, PNCCharging_VIM } } });

    frame_ids.insert({ 1286, VimMid5CanFdCanNmFr });
}


}
}
