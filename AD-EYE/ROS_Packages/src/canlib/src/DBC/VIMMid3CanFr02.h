#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid3CanFr02_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr02 { "VIMMid3CanFr02" };


// Groups
const std::string OkToClsDoor { "OkToClsDoor" };
const std::string OkToOpenDoor { "OkToOpenDoor" };


// Signals
const std::string CnvincAPIEna_UB { "CnvincAPIEna_UB" };
const std::string CnvincAPIEna { "CnvincAPIEna" };
const std::string OkToOpenDoor_UB { "OkToOpenDoor_UB" };
const std::string OkToClsDoor_UB { "OkToClsDoor_UB" };
const std::string OkToClsDoorOkToClsDoorPassRe { "OkToClsDoorOkToClsDoorPassRe" };
const std::string OkToClsDoorOkToClsDoorPass { "OkToClsDoorOkToClsDoorPass" };
const std::string OkToClsDoorOkToClsDoorDrvrRe { "OkToClsDoorOkToClsDoorDrvrRe" };
const std::string OkToClsDoorOkToClsDoorDrvr { "OkToClsDoorOkToClsDoorDrvr" };
const std::string OkToClsDoorOkToClsDoorCntr { "OkToClsDoorOkToClsDoorCntr" };
const std::string OkToClsDoorOkToClsDoorChks { "OkToClsDoorOkToClsDoorChks" };
const std::string OkToOpenDoorOkToOpenDoorPassRe { "OkToOpenDoorOkToOpenDoorPassRe" };
const std::string OkToOpenDoorOkToOpenDoorPass { "OkToOpenDoorOkToOpenDoorPass" };
const std::string OkToOpenDoorOkToOpenDoorDrvrRe { "OkToOpenDoorOkToOpenDoorDrvrRe" };
const std::string OkToOpenDoorOkToOpenDoorDrvr { "OkToOpenDoorOkToOpenDoorDrvr" };
const std::string OkToOpenDoorOkToOpenDoorCntr { "OkToOpenDoorOkToOpenDoorCntr" };
const std::string OkToOpenDoorOkToOpenDoorChks { "OkToOpenDoorOkToOpenDoorChks" };


}
}
