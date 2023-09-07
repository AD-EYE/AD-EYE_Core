#include "../basic_types.h"


namespace kcan {
namespace dbc {


void SSMMid5CanFdFr06_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMMid5CanFdFr06 { "SSMMid5CanFdFr06" };

// Groups
const std::string AdPrimSafeStopActvGroupSafe { "AdPrimSafeStopActvGroupSafe" };
const std::string SSMDegraded { "SSMDegraded" };

// Signals
const std::string AdPrimSafeStopActvGroupSafe_UB {"AdPrimSafeStopActvGroupSafe_UB"};
const std::string AdPrimSafeStopActvGroupSafeChks {"AdPrimSafeStopActvGroupSafeChks"};
const std::string AdPrimSafeStopActvGroupSafeCntr {"AdPrimSafeStopActvGroupSafeCntr"};
const std::string AdPrimSafeStopActvGroupSafePlatf {"AdPrimSafeStopActvGroupSafePlatf"};
const std::string SSMDegraded_UB {"SSMDegraded_UB"};
const std::string SSMDegradedchks {"SSMDegradedchks"};
const std::string SSMDegradedcntr {"SSMDegradedcntr"};
const std::string SSMDegradedssmdegraded {"SSMDegradedssmdegraded"};

}
}
