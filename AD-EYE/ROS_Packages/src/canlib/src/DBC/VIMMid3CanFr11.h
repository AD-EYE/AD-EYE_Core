#include "../basic_types.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr11_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr11 { "VIMMid3CanFr11" };

// Groups
const std::string AdFusedFricEstimn { "AdFusedFricEstimn" };
const std::string AdpLiReqFromAPI { "AdpLiReqFromAPI" };
const std::string SwtExtrLiFromAPI { "SwtExtrLiFromAPI" };

// Singals
const std::string AdFusedFricEstimn_UB { "AdFusedFricEstimn_UB" };
const std::string AdFusedFricEstimnFricEstimn { "AdFusedFricEstimnFricEstimn" };
const std::string AdFusedFricEstimnFricEstimnConf { "AdFusedFricEstimnFricEstimnConf" };
const std::string AdpLiReqFromAPI_UB { "AdpLiReqFromAPI_UB" };
const std::string AdpLiReqFromAPIAhbcActvn { "AdpLiReqFromAPIAhbcActvn" };
const std::string AdpLiReqFromAPIChks { "AdpLiReqFromAPIChks" };
const std::string AdpLiReqFromAPICntr { "AdpLiReqFromAPICntr" };
const std::string AdpLiReqFromAPIHzrdLiActvnReq { "AdpLiReqFromAPIHzrdLiActvnReq" };
const std::string AdpLiReqFromAPIHzrdLiDeactnReq { "AdpLiReqFromAPIHzrdLiDeactnReq" };
const std::string AdpLiReqFromAPIIncrLiRiReq { "AdpLiReqFromAPIIncrLiRiReq" };
const std::string AdpLiReqFromAPIIndcrLeReq { "AdpLiReqFromAPIIndcrLeReq" };
const std::string SwtExtrLiFromAPI_UB { "SwtExtrLiFromAPI_UB" };
const std::string SwtExtrLiFromAPILiExtFctCntr { "SwtExtrLiFromAPILiExtFctCntr" };
const std::string SwtExtrLiFromAPILiExtFctCrc { "SwtExtrLiFromAPILiExtFctCrc" };
const std::string SwtExtrLiFromAPILiExtFctQf { "SwtExtrLiFromAPILiExtFctQf" };
const std::string SwtExtrLiFromAPILiExtFctReq1 { "SwtExtrLiFromAPILiExtFctReq1" };


}
}
