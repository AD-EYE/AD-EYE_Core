#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr11_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr11 { "VCU1Mid3CanFr11" };


// Groups
const std::string BltLockStAtDrvr { "BltLockStAtDrvr" };
const std::string BltLockStAtPass { "BltLockStAtPass" };
const std::string BltLockStAtRowSecLe { "BltLockStAtRowSecLe" };
const std::string BltLockStAtRowSecRi { "BltLockStAtRowSecRi" };
const std::string DoorPassRePosnStsToAPI { "DoorPassRePosnStsToAPI" };


// Signals
const std::string DoorPassRePosnStsToAPIPassReDoorPosnSts { "DoorPassRePosnStsToAPIPassReDoorPosnSts" };
const std::string DoorPassRePosnStsToAPIPassReDoorPosnStsCntr { "DoorPassRePosnStsToAPIPassReDoorPosnStsCntr" };
const std::string DoorPassRePosnStsToAPIPassReDoorPosnStsChks { "DoorPassRePosnStsToAPIPassReDoorPosnStsChks" };
const std::string DoorPassRePosnStsToAPI_UB { "DoorPassRePosnStsToAPI_UB" };
const std::string DoorDrvrMovmtFailNotif_UB { "DoorDrvrMovmtFailNotif_UB" };
const std::string DoorDrvrMovmtFailNotif { "DoorDrvrMovmtFailNotif" };
const std::string DoorDrvrReMovmtFailNotif_UB { "DoorDrvrReMovmtFailNotif_UB" };
const std::string DoorPassMovmtFailNotif_UB { "DoorPassMovmtFailNotif_UB" };
const std::string DoorPassMovmtFailNotif { "DoorPassMovmtFailNotif" };
const std::string AhbcIndcnToAPI_UB { "AhbcIndcnToAPI_UB" };
const std::string DoorPassReMovmtFailNotif_UB { "DoorPassReMovmtFailNotif_UB" };
const std::string DoorDrvrReMovmtFailNotif { "DoorDrvrReMovmtFailNotif" };
const std::string AhbcIndcnToAPI { "AhbcIndcnToAPI" };
const std::string DoorPassReMovmtFailNotif { "DoorPassReMovmtFailNotif" };
const std::string BltLockStAtRowSecRiForBltLockEquid { "BltLockStAtRowSecRiForBltLockEquid" };
const std::string BltLockStAtRowSecRiForBltLockSt1 { "BltLockStAtRowSecRiForBltLockSt1" };
const std::string BltLockStAtRowSecRiForBltLockSts { "BltLockStAtRowSecRiForBltLockSts" };
const std::string BltLockStAtRowSecRi_UB { "BltLockStAtRowSecRi_UB" };
const std::string BltLockStAtRowSecLeForBltLockEquid { "BltLockStAtRowSecLeForBltLockEquid" };
const std::string BltLockStAtRowSecLeForBltLockSt1 { "BltLockStAtRowSecLeForBltLockSt1" };
const std::string BltLockStAtRowSecLeForBltLockSts { "BltLockStAtRowSecLeForBltLockSts" };
const std::string BltLockStAtRowSecLe_UB { "BltLockStAtRowSecLe_UB" };
const std::string BltLockStAtPassForBltLockSt1 { "BltLockStAtPassForBltLockSt1" };
const std::string BltLockStAtPassForBltLockSts { "BltLockStAtPassForBltLockSts" };
const std::string BltLockStAtPass_UB { "BltLockStAtPass_UB" };
const std::string BltLockStAtDrvrForBltLockSt1 { "BltLockStAtDrvrForBltLockSt1" };
const std::string BltLockStAtDrvrForDevErrSts2 { "BltLockStAtDrvrForDevErrSts2" };
const std::string BltLockStAtDrvr_UB { "BltLockStAtDrvr_UB" };


}
}
