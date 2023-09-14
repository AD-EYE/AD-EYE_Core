#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr04_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr04 { "VCU1Mid3CanFr04" };


// Groups
const std::string FricEstimnFromVehDynGroup { "FricEstimnFromVehDynGroup" };
const std::string PrpsnTqDirCpby { "PrpsnTqDirCpby" };
const std::string SwtExtrLiToAPI { "SwtExtrLiToAPI" };


// Signals
const std::string SwtExtrLiToAPI_UB { "SwtExtrLiToAPI_UB" };
const std::string SwtExtrLiToAPILiExtFctCntr { "SwtExtrLiToAPILiExtFctCntr" };
const std::string SwtExtrLiToAPILiExtFctQf { "SwtExtrLiToAPILiExtFctQf" };
const std::string SwtExtrLiToAPILiExtFctReq1 { "SwtExtrLiToAPILiExtFctReq1" };
const std::string SwtExtrLiToAPILiExtFctCrc { "SwtExtrLiToAPILiExtFctCrc" };
const std::string PrpsnTqDirCpby_UB { "PrpsnTqDirCpby_UB" };
const std::string PrpsnTqDirCpbySts { "PrpsnTqDirCpbySts" };
const std::string PrpsnTqDirCpbyCntr { "PrpsnTqDirCpbyCntr" };
const std::string PrpsnTqDirCpbyChks { "PrpsnTqDirCpbyChks" };
const std::string FricEstimnFromVehDynGroup_UB { "FricEstimnFromVehDynGroup_UB" };
const std::string FricEstimnFromVehDynQly { "FricEstimnFromVehDynQly" };
const std::string FricEstimnFromVehDyn { "FricEstimnFromVehDyn" };


}
}
