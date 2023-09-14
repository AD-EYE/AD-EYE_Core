#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr03_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMBMid6CanFdFr03 { "SSMBMid6CanFdFr03" };


// Groups
const std::string SecPoseMonSafe { "SecPoseMonSafe" };
const std::string SecSteerMotTq { "SecSteerMotTq" };
const std::string SecWhlLockSts { "SecWhlLockSts" };
const std::string SSMBDegraded { "SSMBDegraded" };


// Signals
const std::string SecSteerMotTqSteerMotTqQf { "SecSteerMotTqSteerMotTqQf" };
const std::string SecSteerMotTqSteerMotTq { "SecSteerMotTqSteerMotTq" };
const std::string SecSteerMotTq_UB { "SecSteerMotTq_UB" };
const std::string SecPoseMonSafe_UB { "SecPoseMonSafe_UB" };
const std::string SecPoseMonSafeSafeQf { "SecPoseMonSafeSafeQf" };
const std::string SecPoseMonSafeCntr { "SecPoseMonSafeCntr" };
const std::string SecPoseMonSafeChks { "SecPoseMonSafeChks" };
const std::string SecPoseMonSafeYawErr { "SecPoseMonSafeYawErr" };
const std::string SecPoseMonSafeLatErr { "SecPoseMonSafeLatErr" };
const std::string SecPoseMonSafeLgtErr { "SecPoseMonSafeLgtErr" };
const std::string SecWhlLockSts_UB { "SecWhlLockSts_UB" };
const std::string SecWhlLockStsDegradedSts { "SecWhlLockStsDegradedSts" };
const std::string SecWhlLockStsLockSts { "SecWhlLockStsLockSts" };
const std::string SecWhlLockStsCntr { "SecWhlLockStsCntr" };
const std::string SecWhlLockStsChks { "SecWhlLockStsChks" };
const std::string SSMBDegradedSSMBDegraded { "SSMBDegradedSSMBDegraded" };
const std::string SSMBDegradedcntr { "SSMBDegradedcntr" };
const std::string SSMBDegradedchks { "SSMBDegradedchks" };
const std::string SSMBDegraded_UB { "SSMBDegraded_UB" };


}
}
