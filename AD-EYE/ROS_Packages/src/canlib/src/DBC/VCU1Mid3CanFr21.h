#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr21_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr21 { "VCU1Mid3CanFr21" };


// Groups
const std::string PtTqAtWhlReActGroup { "PtTqAtWhlReActGroup" };


// Signals
const std::string PtTqAtWhlReActGroup_UB { "PtTqAtWhlReActGroup_UB" };
const std::string PtTqAtWhlsReQly { "PtTqAtWhlsReQly" };
const std::string PtTqAtWhlReRiAct { "PtTqAtWhlReRiAct" };
const std::string PtTqAtWhlReLeAct { "PtTqAtWhlReLeAct" };
const std::string PtTqAtAxleReAct { "PtTqAtAxleReAct" };


}
}
