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
const string VIMMid3CanFr08 { "VIMMid3CanFr08" };

// Groups
const string VehOperStReq { "VehOperStReq" };

// Signals
const string VehOperStReq_UB { "VehOperStReq_UB" };
const string VehOperStReqChecksum { "VehOperStReqChecksum" };
const string VehOperStReqCounter { "VehOperStReqCounter" };
const string VehOperStReqVehOperStReq { "VehOperStReqVehOperStReq" };

}
}
