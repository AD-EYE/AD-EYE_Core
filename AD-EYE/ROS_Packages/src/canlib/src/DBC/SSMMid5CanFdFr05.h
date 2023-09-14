#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMMid5CanFdFr05_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMMid5CanFdFr05 { "SSMMid5CanFdFr05" };


// Groups
const std::string AdPrimWhlAgRateLimEstimdSafe { "AdPrimWhlAgRateLimEstimdSafe" };
const std::string PrimMaxALatEstimdGroup { "PrimMaxALatEstimdGroup" };


// Signals
const std::string PrimMaxALatEstimdGroup_UB { "PrimMaxALatEstimdGroup_UB" };
const std::string PrimMaxALatEstimdGroupAcceleration { "PrimMaxALatEstimdGroupAcceleration" };
const std::string PrimMaxALatEstimdGroupJerk { "PrimMaxALatEstimdGroupJerk" };
const std::string AdPrimWhlAgRateLimEstimdSafe_UB { "AdPrimWhlAgRateLimEstimdSafe_UB" };
const std::string AdPrimWhlAgRateLimEstimdSafeCntr { "AdPrimWhlAgRateLimEstimdSafeCntr" };
const std::string AdPrimWhlAgRateLimEstimdSafeChks { "AdPrimWhlAgRateLimEstimdSafeChks" };
const std::string AdPrimWhlAgRateLimEstimdSafeAdWhlAgRate1 { "AdPrimWhlAgRateLimEstimdSafeAdWhlAgRate1" };


}
}
