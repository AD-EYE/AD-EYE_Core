#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMMid3CanFr02_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMMid3CanFr02 { "SSMMid3CanFr02" };


// Groups
const std::string PrimSafeStopActv1 { "PrimSafeStopActv1" };


// Signals
const std::string PrimSafeStopActv1_UB { "PrimSafeStopActv1_UB" };
const std::string PrimSafeStopActv1PlatformSafeStopActv { "PrimSafeStopActv1PlatformSafeStopActv" };
const std::string PrimSafeStopActv1Cntr { "PrimSafeStopActv1Cntr" };
const std::string PrimSafeStopActv1Chks { "PrimSafeStopActv1Chks" };


}
}
