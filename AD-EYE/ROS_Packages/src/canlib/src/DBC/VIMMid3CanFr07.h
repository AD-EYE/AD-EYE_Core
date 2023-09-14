#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid3CanFr07_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr07 { "VIMMid3CanFr07" };


// Groups
const std::string AutnmsDrvStReq { "AutnmsDrvStReq" };


// Signals
const std::string AutnmsDrvStReqChecksum { "AutnmsDrvStReqChecksum" };
const std::string AutnmsDrvStReqCounter { "AutnmsDrvStReqCounter" };
const std::string AutnmsDrvStReqAutnmsDrvStReq { "AutnmsDrvStReqAutnmsDrvStReq" };
const std::string AutnmsDrvStReq_UB { "AutnmsDrvStReq_UB" };


}
}
