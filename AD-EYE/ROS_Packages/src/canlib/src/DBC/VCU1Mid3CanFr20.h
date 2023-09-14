#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr20_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr20 { "VCU1Mid3CanFr20" };


// Groups
const std::string PtTqAtWhlFrntActGroup { "PtTqAtWhlFrntActGroup" };


// Signals
const std::string PtTqAtWhlFrntActGroup_UB { "PtTqAtWhlFrntActGroup_UB" };
const std::string PtTqAtWhlsFrntQly { "PtTqAtWhlsFrntQly" };
const std::string PtTqAtWhlFrntRiAct { "PtTqAtWhlFrntRiAct" };
const std::string PtTqAtWhlFrntLeAct { "PtTqAtWhlFrntLeAct" };
const std::string PtTqAtAxleFrntAct { "PtTqAtAxleFrntAct" };


}
}
