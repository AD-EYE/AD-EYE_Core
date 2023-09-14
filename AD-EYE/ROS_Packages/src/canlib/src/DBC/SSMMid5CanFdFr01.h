#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMMid5CanFdFr01_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMMid5CanFdFr01 { "SSMMid5CanFdFr01" };


// Groups
const std::string PinionSteerAg1Group { "PinionSteerAg1Group" };
const std::string PinionSteerAgSpd1Group { "PinionSteerAgSpd1Group" };


// Signals
const std::string PinionSteerAgSpd1Group_UB { "PinionSteerAgSpd1Group_UB" };
const std::string PinionSteerAg1Group_UB { "PinionSteerAg1Group_UB" };
const std::string PinionSteerAg1Qf { "PinionSteerAg1Qf" };
const std::string PinionSteerAg1 { "PinionSteerAg1" };
const std::string PinionSteerAgSpd1Qf { "PinionSteerAgSpd1Qf" };
const std::string PinionSteerAgSpd1 { "PinionSteerAgSpd1" };


}
}
