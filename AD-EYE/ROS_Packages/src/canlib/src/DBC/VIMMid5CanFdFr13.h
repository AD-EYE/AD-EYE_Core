#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid5CanFdFr13_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid5CanFdFr13 { "VIMMid5CanFdFr13" };


// Groups
const std::string AdPrimSafeStopReqSafe { "AdPrimSafeStopReqSafe" };
const std::string SDSFltMgrStsSafe { "SDSFltMgrStsSafe" };


// Signals
const std::string SDSFltMgrStsSafe_UB { "SDSFltMgrStsSafe_UB" };
const std::string AdPrimSafeStopReqSafe_UB { "AdPrimSafeStopReqSafe_UB" };
const std::string AdPrimSafeStopReqSafeSafeStopReq { "AdPrimSafeStopReqSafeSafeStopReq" };
const std::string AdPrimSafeStopReqSafeCntr { "AdPrimSafeStopReqSafeCntr" };
const std::string AdPrimSafeStopReqSafeChks { "AdPrimSafeStopReqSafeChks" };
const std::string SDSFltMgrStsSafeSDSFltMgrSts { "SDSFltMgrStsSafeSDSFltMgrSts" };
const std::string SDSFltMgrStsSafeCntr { "SDSFltMgrStsSafeCntr" };
const std::string SDSFltMgrStsSafeChks { "SDSFltMgrStsSafeChks" };


}
}
