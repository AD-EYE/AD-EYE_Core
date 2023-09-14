#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid3CanFr08_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr08 { "VIMMid3CanFr08" };


// Groups
const std::string VehOperStReq { "VehOperStReq" };


// Signals
const std::string VehOperStReqChecksum { "VehOperStReqChecksum" };
const std::string VehOperStReqCounter { "VehOperStReqCounter" };
const std::string VehOperStReqVehOperStReq { "VehOperStReqVehOperStReq" };
const std::string VehOperStReq_UB { "VehOperStReq_UB" };


}
}
