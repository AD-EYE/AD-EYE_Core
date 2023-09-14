#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid3CanFr01_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr01 { "VIMMid3CanFr01" };


// Groups
const std::string SnsrClngReqIf { "SnsrClngReqIf" };
const std::string WiprFrntReqIf { "WiprFrntReqIf" };


// Signals
const std::string SwtBeamHiFromAPI { "SwtBeamHiFromAPI" };
const std::string HvSysActvReqExt_UB { "HvSysActvReqExt_UB" };
const std::string HvSysActvReqExt { "HvSysActvReqExt" };
const std::string WiprReCmdIf_UB { "WiprReCmdIf_UB" };
const std::string WiprReCmdIf { "WiprReCmdIf" };
const std::string WinWshngCmdIf_UB { "WinWshngCmdIf_UB" };
const std::string WinWshngCmdIf { "WinWshngCmdIf" };
const std::string WipgSpdIntlIf { "WipgSpdIntlIf" };
const std::string WipgSpdIntlIf_UB { "WipgSpdIntlIf_UB" };
const std::string RainSnsrCmdIf_UB { "RainSnsrCmdIf_UB" };
const std::string RainSnsrCmdIf { "RainSnsrCmdIf" };
const std::string HornActvnReqIf_UB { "HornActvnReqIf_UB" };
const std::string HornActvnReqIf { "HornActvnReqIf" };
const std::string SnsrClngReqIf_UB { "SnsrClngReqIf_UB" };
const std::string SwtBeamHiFromAPI_UB { "SwtBeamHiFromAPI_UB" };
const std::string SnsrClngReqIfClngProg { "SnsrClngReqIfClngProg" };
const std::string SnsrClngReqIfSnsrSeld { "SnsrClngReqIfSnsrSeld" };
const std::string WiprFrntReqIf_UB { "WiprFrntReqIf_UB" };
const std::string WiprFrntReqIfFrntWiprLvrQf { "WiprFrntReqIfFrntWiprLvrQf" };
const std::string WiprFrntReqIfFrntWiprLvrCntr { "WiprFrntReqIfFrntWiprLvrCntr" };
const std::string WiprFrntReqIfFrntWiprLvrCmd1 { "WiprFrntReqIfFrntWiprLvrCmd1" };
const std::string WiprFrntReqIfFrntWiprLvrCrc { "WiprFrntReqIfFrntWiprLvrCrc" };


}
}
