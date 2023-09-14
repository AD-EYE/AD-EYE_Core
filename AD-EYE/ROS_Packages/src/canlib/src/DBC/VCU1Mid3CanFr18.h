#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr18_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr18 { "VCU1Mid3CanFr18" };


// Groups
const std::string AccrPedlPsd { "AccrPedlPsd" };
const std::string BrkPedlPsdSafeGroup { "BrkPedlPsdSafeGroup" };
const std::string OvrdDecelByDrvr { "OvrdDecelByDrvr" };


// Signals
const std::string AccrPedlPsdAccrPedlPsdChks { "AccrPedlPsdAccrPedlPsdChks" };
const std::string AccrPedlPsdAccrPedlPsdCntr { "AccrPedlPsdAccrPedlPsdCntr" };
const std::string AccrPedlPsdAccrPedlPsd { "AccrPedlPsdAccrPedlPsd" };
const std::string AccrPedlPsdAccrPedlPsdSts { "AccrPedlPsdAccrPedlPsdSts" };
const std::string AccrPedlPsd_UB { "AccrPedlPsd_UB" };
const std::string BrkPedlPsdSafeGroup_UB { "BrkPedlPsdSafeGroup_UB" };
const std::string AsySftyBrkDlyEstimd_UB { "AsySftyBrkDlyEstimd_UB" };
const std::string AsySftyBrkDlyEstimd { "AsySftyBrkDlyEstimd" };
const std::string BrkPedlNotPsdSafe { "BrkPedlNotPsdSafe" };
const std::string BrkPedlPsd { "BrkPedlPsd" };
const std::string BrkPedlPsdQf { "BrkPedlPsdQf" };
const std::string BrkPedlPsdCntr { "BrkPedlPsdCntr" };
const std::string BrkPedlPsdChks { "BrkPedlPsdChks" };
const std::string HvSysActvStsExt1_UB { "HvSysActvStsExt1_UB" };
const std::string HvSysActvStsExt1 { "HvSysActvStsExt1" };
const std::string OvrdDecelByDrvr_UB { "OvrdDecelByDrvr_UB" };
const std::string OvrdDecelByDrvrOvrdDecelByDrvr { "OvrdDecelByDrvrOvrdDecelByDrvr" };
const std::string OvrdDecelByDrvrOvrdDecelByDrvrCntr { "OvrdDecelByDrvrOvrdDecelByDrvrCntr" };
const std::string OvrdDecelByDrvrOvrdDecelByDrvrChks { "OvrdDecelByDrvrOvrdDecelByDrvrChks" };


}
}
