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
const string VIMMid3CanFr07 { "VIMMid3CanFr07" };

// Groups
const string AutnmsDrvStReq { "AutnmsDrvStReq" };

// Signals
const string AutnmsDrvStReq_UB { "AutnmsDrvStReq_UB" };
const string AutnmsDrvStReqAutnmsDrvStReq { "AutnmsDrvStReqAutnmsDrvStReq" };
const string AutnmsDrvStReqChecksum { "AutnmsDrvStReqChecksum" };
const string AutnmsDrvStReqCounter { "AutnmsDrvStReqCounter" };

}
}
