#include "VCU1Mid3CanFr11.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr11_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ BltLockStAtDrvrForBltLockSt1, { BltLockStAtDrvrForBltLockSt1, 60, 1, true, SignalType::APP_UNSIGNED, 1, BltLockStAtDrvr, ParentType::GROUP } });
    signals_info.insert({ BltLockStAtDrvrForDevErrSts2, { BltLockStAtDrvrForDevErrSts2, 59, 1, true, SignalType::APP_UNSIGNED, 0, BltLockStAtDrvr, ParentType::GROUP } });
    signals_info.insert({ BltLockStAtPassForBltLockSt1, { BltLockStAtPassForBltLockSt1, 63, 1, true, SignalType::APP_UNSIGNED, 1, BltLockStAtPass, ParentType::GROUP } });
    signals_info.insert({ BltLockStAtPassForBltLockSts, { BltLockStAtPassForBltLockSts, 62, 1, true, SignalType::APP_UNSIGNED, 0, BltLockStAtPass, ParentType::GROUP } });
    signals_info.insert({ BltLockStAtRowSecLeForBltLockEquid, { BltLockStAtRowSecLeForBltLockEquid, 51, 1, true, SignalType::APP_UNSIGNED, 1, BltLockStAtRowSecLe, ParentType::GROUP } });
    signals_info.insert({ BltLockStAtRowSecLeForBltLockSt1, { BltLockStAtRowSecLeForBltLockSt1, 50, 1, true, SignalType::APP_UNSIGNED, 0, BltLockStAtRowSecLe, ParentType::GROUP } });
    signals_info.insert({ BltLockStAtRowSecLeForBltLockSts, { BltLockStAtRowSecLeForBltLockSts, 49, 1, true, SignalType::APP_UNSIGNED, 1, BltLockStAtRowSecLe, ParentType::GROUP } });
    signals_info.insert({ BltLockStAtRowSecRiForBltLockEquid, { BltLockStAtRowSecRiForBltLockEquid, 55, 1, true, SignalType::APP_UNSIGNED, 1, BltLockStAtRowSecRi, ParentType::GROUP } });
    signals_info.insert({ BltLockStAtRowSecRiForBltLockSt1, { BltLockStAtRowSecRiForBltLockSt1, 54, 1, true, SignalType::APP_UNSIGNED, 0, BltLockStAtRowSecRi, ParentType::GROUP } });
    signals_info.insert({ BltLockStAtRowSecRiForBltLockSts, { BltLockStAtRowSecRiForBltLockSts, 53, 1, true, SignalType::APP_UNSIGNED, 1, BltLockStAtRowSecRi, ParentType::GROUP } });
    signals_info.insert({ DoorPassRePosnStsToAPIPassReDoorPosnSts, { DoorPassRePosnStsToAPIPassReDoorPosnSts, 4, 4, true, SignalType::APP_UNSIGNED, 0, DoorPassRePosnStsToAPI, ParentType::GROUP } });
    signals_info.insert({ DoorPassRePosnStsToAPIPassReDoorPosnStsChks, { DoorPassRePosnStsToAPIPassReDoorPosnStsChks, 8, 8, true, SignalType::E2E_CHKS, 0, DoorPassRePosnStsToAPI, ParentType::GROUP } });
    signals_info.insert({ DoorPassRePosnStsToAPIPassReDoorPosnStsCntr, { DoorPassRePosnStsToAPIPassReDoorPosnStsCntr, 0, 4, true, SignalType::E2E_CNTR, 0, DoorPassRePosnStsToAPI, ParentType::GROUP } });
    signals_info.insert({ AhbcIndcnToAPI, { AhbcIndcnToAPI, 46, 2, true, SignalType::APP_UNSIGNED, 2, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ AhbcIndcnToAPI_UB, { AhbcIndcnToAPI_UB, 39, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ BltLockStAtDrvr_UB, { BltLockStAtDrvr_UB, 58, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ BltLockStAtPass_UB, { BltLockStAtPass_UB, 61, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ BltLockStAtRowSecLe_UB, { BltLockStAtRowSecLe_UB, 48, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ BltLockStAtRowSecRi_UB, { BltLockStAtRowSecRi_UB, 52, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ DoorDrvrMovmtFailNotif, { DoorDrvrMovmtFailNotif, 16, 6, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ DoorDrvrMovmtFailNotif_UB, { DoorDrvrMovmtFailNotif_UB, 22, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ DoorDrvrReMovmtFailNotif, { DoorDrvrReMovmtFailNotif, 32, 6, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ DoorDrvrReMovmtFailNotif_UB, { DoorDrvrReMovmtFailNotif_UB, 31, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ DoorPassMovmtFailNotif, { DoorPassMovmtFailNotif, 24, 6, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ DoorPassMovmtFailNotif_UB, { DoorPassMovmtFailNotif_UB, 30, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ DoorPassReMovmtFailNotif, { DoorPassReMovmtFailNotif, 40, 6, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ DoorPassReMovmtFailNotif_UB, { DoorPassReMovmtFailNotif_UB, 38, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ DoorPassRePosnStsToAPI_UB, { DoorPassRePosnStsToAPI_UB, 23, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr11, ParentType::FRAME } });

    signalgroups_info.insert({ BltLockStAtDrvr, { BltLockStAtDrvr, 0x0, { BltLockStAtDrvrForBltLockSt1, BltLockStAtDrvrForDevErrSts2 }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr11 } } );
    signalgroups_info.insert({ BltLockStAtPass, { BltLockStAtPass, 0x0, { BltLockStAtPassForBltLockSt1, BltLockStAtPassForBltLockSts }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr11 } } );
    signalgroups_info.insert({ BltLockStAtRowSecLe, { BltLockStAtRowSecLe, 0x0, { BltLockStAtRowSecLeForBltLockEquid, BltLockStAtRowSecLeForBltLockSt1, BltLockStAtRowSecLeForBltLockSts }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr11 } } );
    signalgroups_info.insert({ BltLockStAtRowSecRi, { BltLockStAtRowSecRi, 0x0, { BltLockStAtRowSecRiForBltLockEquid, BltLockStAtRowSecRiForBltLockSt1, BltLockStAtRowSecRiForBltLockSts }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr11 } } );
    signalgroups_info.insert({ DoorPassRePosnStsToAPI, { DoorPassRePosnStsToAPI, 0x41E, { DoorPassRePosnStsToAPIPassReDoorPosnSts, DoorPassRePosnStsToAPIPassReDoorPosnStsChks, DoorPassRePosnStsToAPIPassReDoorPosnStsCntr }, { E2EProfileType::P01a, DoorPassRePosnStsToAPIPassReDoorPosnStsChks, DoorPassRePosnStsToAPIPassReDoorPosnStsCntr }, VCU1Mid3CanFr11 } } );

    frames_info.insert({ VCU1Mid3CanFr11, { VCU1Mid3CanFr11, 305, 8, 260, { BltLockStAtDrvr, BltLockStAtPass, BltLockStAtRowSecLe, BltLockStAtRowSecRi, DoorPassRePosnStsToAPI }, { DoorDrvrReMovmtFailNotif, BltLockStAtRowSecRi_UB, BltLockStAtRowSecLe_UB, DoorPassRePosnStsToAPI_UB, DoorPassReMovmtFailNotif_UB, BltLockStAtPass_UB, DoorDrvrMovmtFailNotif_UB, DoorPassMovmtFailNotif, AhbcIndcnToAPI, DoorPassReMovmtFailNotif, DoorDrvrReMovmtFailNotif_UB, BltLockStAtDrvr_UB, DoorPassMovmtFailNotif_UB, DoorDrvrMovmtFailNotif, AhbcIndcnToAPI_UB } } });

    frame_ids.insert({ 305, VCU1Mid3CanFr11 });
}


}
}
