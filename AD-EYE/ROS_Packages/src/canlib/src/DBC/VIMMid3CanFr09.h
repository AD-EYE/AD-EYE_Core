#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid3CanFr09_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr09 { "VIMMid3CanFr09" };


// Groups
const std::string AdDirReq { "AdDirReq" };
const std::string AdStandStillReq { "AdStandStillReq" };


// Signals
const std::string VehUsgStReq_UB { "VehUsgStReq_UB" };
const std::string VehUsgStReq { "VehUsgStReq" };
const std::string AdStandStillReq_UB { "AdStandStillReq_UB" };
const std::string AdDirReq_UB { "AdDirReq_UB" };
const std::string AdDirReqDirReq { "AdDirReqDirReq" };
const std::string AdDirReqCntr { "AdDirReqCntr" };
const std::string AdDirReqChks { "AdDirReqChks" };
const std::string AdStandStillReqReq { "AdStandStillReqReq" };
const std::string AdStandStillReqCntr { "AdStandStillReqCntr" };
const std::string AdStandStillReqChks { "AdStandStillReqChks" };


}
}
