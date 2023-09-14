#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr34_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr34 { "VCU1Mid3CanFr34" };


// Groups
const std::string StandStillMgrStsForHldSafe { "StandStillMgrStsForHldSafe" };
const std::string SwtIndcrToAPI { "SwtIndcrToAPI" };


// Signals
const std::string SwtLiHzrdWarnToAPI_UB { "SwtLiHzrdWarnToAPI_UB" };
const std::string SwtIndcrToAPI_UB { "SwtIndcrToAPI_UB" };
const std::string SwtIndcrToAPIIndcrTypExtReq { "SwtIndcrToAPIIndcrTypExtReq" };
const std::string SwtIndcrToAPIIndcrTypExtReqCntr { "SwtIndcrToAPIIndcrTypExtReqCntr" };
const std::string SwtIndcrToAPIIndcrTypExtReqToUpdQf { "SwtIndcrToAPIIndcrTypExtReqToUpdQf" };
const std::string SwtIndcrToAPIIndcrTypExtReqChks { "SwtIndcrToAPIIndcrTypExtReqChks" };
const std::string SwtLiHzrdWarnToAPI { "SwtLiHzrdWarnToAPI" };
const std::string SwtBeamHiToAPI_UB { "SwtBeamHiToAPI_UB" };
const std::string SwtBeamHiToAPI { "SwtBeamHiToAPI" };
const std::string StandStillMgrStsForHldSafe_UB { "StandStillMgrStsForHldSafe_UB" };
const std::string StandStillMgrStsForHldSafeStandStillSts { "StandStillMgrStsForHldSafeStandStillSts" };
const std::string StandStillMgrStsForHldSafeCntr { "StandStillMgrStsForHldSafeCntr" };
const std::string StandStillMgrStsForHldSafeChks { "StandStillMgrStsForHldSafeChks" };


}
}
