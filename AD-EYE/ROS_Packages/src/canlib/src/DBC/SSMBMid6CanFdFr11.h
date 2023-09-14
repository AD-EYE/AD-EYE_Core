#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr11_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMBMid6CanFdFr11 { "SSMBMid6CanFdFr11" };


// Groups
const std::string AdSecSafeStopActvGroupSafe { "AdSecSafeStopActvGroupSafe" };
const std::string AdSecWhlAgRateLimEstimdSafe { "AdSecWhlAgRateLimEstimdSafe" };
const std::string SecMaxALatEstimdGroup { "SecMaxALatEstimdGroup" };


// Signals
const std::string AdSecWhlAgRateLimEstimdSafe_UB { "AdSecWhlAgRateLimEstimdSafe_UB" };
const std::string AdSecSafeStopActvGroupSafe_UB { "AdSecSafeStopActvGroupSafe_UB" };
const std::string AdSecSafeStopActvGroupSafePlatformSafeStopActv { "AdSecSafeStopActvGroupSafePlatformSafeStopActv" };
const std::string AdSecSafeStopActvGroupSafeCntr { "AdSecSafeStopActvGroupSafeCntr" };
const std::string AdSecSafeStopActvGroupSafeChks { "AdSecSafeStopActvGroupSafeChks" };
const std::string SecMaxALatEstimdGroup_UB { "SecMaxALatEstimdGroup_UB" };
const std::string SecMaxALatEstimdGroupAcceleration { "SecMaxALatEstimdGroupAcceleration" };
const std::string SecMaxALatEstimdGroupJerk { "SecMaxALatEstimdGroupJerk" };
const std::string AdSecWhlAgRateLimEstimdSafeCntr { "AdSecWhlAgRateLimEstimdSafeCntr" };
const std::string AdSecWhlAgRateLimEstimdSafeChks { "AdSecWhlAgRateLimEstimdSafeChks" };
const std::string AdSecWhlAgRateLimEstimdSafeAdWhlAgRate1 { "AdSecWhlAgRateLimEstimdSafeAdWhlAgRate1" };


}
}
