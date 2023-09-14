#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr09_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr09 { "VCU1Mid3CanFr09" };


// Groups
const std::string AdSteerPaddlPsdGroupSafe { "AdSteerPaddlPsdGroupSafe" };
const std::string SteerWhlSnsr { "SteerWhlSnsr" };


// Signals
const std::string SteerWhlSnsr_UB { "SteerWhlSnsr_UB" };
const std::string SteerWhlAgSafe { "SteerWhlAgSafe" };
const std::string SteerWhlSnsrQf { "SteerWhlSnsrQf" };
const std::string SteerWhlAgSpdSafe { "SteerWhlAgSpdSafe" };
const std::string SteerWhlSnsrSafeChks { "SteerWhlSnsrSafeChks" };
const std::string SteerWhlSnsrSafeCntr { "SteerWhlSnsrSafeCntr" };
const std::string WhlMotSysCluSts_UB { "WhlMotSysCluSts_UB" };
const std::string WhlMotSysCluSts { "WhlMotSysCluSts" };
const std::string AdSteerPaddlPsdGroupSafe_UB { "AdSteerPaddlPsdGroupSafe_UB" };
const std::string AdSteerPaddlPsdGroupSafeLe { "AdSteerPaddlPsdGroupSafeLe" };
const std::string AdSteerPaddlPsdGroupSafeLeSts { "AdSteerPaddlPsdGroupSafeLeSts" };
const std::string AdSteerPaddlPsdGroupSafeRi { "AdSteerPaddlPsdGroupSafeRi" };
const std::string AdSteerPaddlPsdGroupSafeRiSts { "AdSteerPaddlPsdGroupSafeRiSts" };
const std::string AdSteerPaddlPsdGroupSafeCntr { "AdSteerPaddlPsdGroupSafeCntr" };
const std::string AdSteerPaddlPsdGroupSafeChks { "AdSteerPaddlPsdGroupSafeChks" };


}
}
