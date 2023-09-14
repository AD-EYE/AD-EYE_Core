#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr01_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMBMid6CanFdFr01 { "VIMBMid6CanFdFr01" };


// Groups
const std::string AdSecSafeStopReqSafe { "AdSecSafeStopReqSafe" };
const std::string SDSFltMgrStsRdnt { "SDSFltMgrStsRdnt" };


// Signals
const std::string SDSFltMgrStsRdnt_UB { "SDSFltMgrStsRdnt_UB" };
const std::string AdSecSafeStopReqSafe_UB { "AdSecSafeStopReqSafe_UB" };
const std::string AdSecSafeStopReqSafeSafeStopReq { "AdSecSafeStopReqSafeSafeStopReq" };
const std::string AdSecSafeStopReqSafeCntr { "AdSecSafeStopReqSafeCntr" };
const std::string AdSecSafeStopReqSafeChks { "AdSecSafeStopReqSafeChks" };
const std::string SDSFltMgrStsRdntSDSFltMgrStsRdnt { "SDSFltMgrStsRdntSDSFltMgrStsRdnt" };
const std::string SDSFltMgrStsRdntCntr { "SDSFltMgrStsRdntCntr" };
const std::string SDSFltMgrStsRdntChks { "SDSFltMgrStsRdntChks" };


}
}
