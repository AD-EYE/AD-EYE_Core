#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr31_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr31 { "VCU1Mid3CanFr31" };


// Groups
const std::string VehOpReqInVehDynGroupSafe { "VehOpReqInVehDynGroupSafe" };


// Signals
const std::string EstimdCoastALgtCpby_UB { "EstimdCoastALgtCpby_UB" };
const std::string VehOpReqInVehDynGroupSafe_UB { "VehOpReqInVehDynGroupSafe_UB" };
const std::string VehOpReqInVehDynGroupSafeVehOpReq { "VehOpReqInVehDynGroupSafeVehOpReq" };
const std::string VehOpReqInVehDynGroupSafeCntr { "VehOpReqInVehDynGroupSafeCntr" };
const std::string VehOpReqInVehDynGroupSafeChks { "VehOpReqInVehDynGroupSafeChks" };
const std::string EstimdCoastALgtCpby { "EstimdCoastALgtCpby" };


}
}
