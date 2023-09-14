#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMMid5CanFdFr02_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMMid5CanFdFr02 { "SSMMid5CanFdFr02" };


// Groups
const std::string AdPrimMotTqASILThrshldExcd { "AdPrimMotTqASILThrshldExcd" };
const std::string PrimPoseMonSafe { "PrimPoseMonSafe" };


// Signals
const std::string PrimPoseMonSafe_UB { "PrimPoseMonSafe_UB" };
const std::string AdPrimMotTqASILThrshldExcd_UB { "AdPrimMotTqASILThrshldExcd_UB" };
const std::string AdPrimMotTqASILThrshldExcdThrshldExceeded { "AdPrimMotTqASILThrshldExcdThrshldExceeded" };
const std::string AdPrimMotTqASILThrshldExcdCntr { "AdPrimMotTqASILThrshldExcdCntr" };
const std::string AdPrimMotTqASILThrshldExcdChks { "AdPrimMotTqASILThrshldExcdChks" };
const std::string PrimPoseMonSafeChks { "PrimPoseMonSafeChks" };
const std::string PrimPoseMonSafeYawErr { "PrimPoseMonSafeYawErr" };
const std::string PrimPoseMonSafeSafeQf { "PrimPoseMonSafeSafeQf" };
const std::string PrimPoseMonSafeCntr { "PrimPoseMonSafeCntr" };
const std::string PrimPoseMonSafeLatErr { "PrimPoseMonSafeLatErr" };
const std::string PrimPoseMonSafeLgtErr { "PrimPoseMonSafeLgtErr" };


}
}
