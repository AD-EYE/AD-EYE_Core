#include "../basic_types.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr06_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMBMid6CanFdFr06 { "SSMBMid6CanFdFr06" };

// Groups
const std::string SecYawRateSafe { "SecYawRateSafe" };

// Signals
const std::string SecYawRateSafe_UB {"SecYawRateSafe_UB" };
const std::string SecYawRateSafeChks {"SecYawRateSafeChks" };
const std::string SecYawRateSafeCntr {"SecYawRateSafeCntr" };
const std::string SecYawRateSafeMax {"SecYawRateSafeMax" };
const std::string SecYawRateSafeMin {"SecYawRateSafeMin" };
const std::string SecYawRateSafeMinMaxQf {"SecYawRateSafeMinMaxQf" };
const std::string SecYawRateSafeNom {"SecYawRateSafeNom" };
const std::string SecYawRateSafeNomQf {"SecYawRateSafeNomQf" };

}
}
