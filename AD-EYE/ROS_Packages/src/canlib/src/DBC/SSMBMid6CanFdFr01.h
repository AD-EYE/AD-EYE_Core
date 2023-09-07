#include "../basic_types.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr01_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMBMid6CanFdFr01 { "SSMBMid6CanFdFr01" };

// Groups
const std::string AdSecSteerStsSafeGroup { "AdSecSteerStsSafeGroup" };

// Signals
const std::string AdSecSteerStsSafeGroup_UB {"AdSecSteerStsSafeGroup_UB"};
const std::string AdSecSteerStsSafeGroupAdSteerPerf {"AdSecSteerStsSafeGroupAdSteerPerf"};
const std::string AdSecSteerStsSafeGroupAdSteerSts {"AdSecSteerStsSafeGroupAdSteerSts"};
const std::string AdSecSteerStsSafeGroupChks {"AdSecSteerStsSafeGroupChks"};
const std::string AdSecSteerStsSafeGroupCntr {"AdSecSteerStsSafeGroupCntr"};

}
}
