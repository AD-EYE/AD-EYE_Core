#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMMid5CanFdFr07_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMMid5CanFdFr07 { "SSMMid5CanFdFr07" };


// Groups


// Signals
const std::string SteerMechMonSts_UB { "SteerMechMonSts_UB" };
const std::string SteerMechMonSts { "SteerMechMonSts" };


}
}
