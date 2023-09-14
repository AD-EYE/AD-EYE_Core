#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr04_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMBMid6CanFdFr04 { "SSMBMid6CanFdFr04" };


// Groups
const std::string BrkDegradedRdnt { "BrkDegradedRdnt" };


// Signals
const std::string BrkDegradedRdnt_UB { "BrkDegradedRdnt_UB" };
const std::string BrkDegradedRdntCntr { "BrkDegradedRdntCntr" };
const std::string BrkDegradedRdntChks { "BrkDegradedRdntChks" };
const std::string BrkDegradedRdntSts { "BrkDegradedRdntSts" };


}
}
