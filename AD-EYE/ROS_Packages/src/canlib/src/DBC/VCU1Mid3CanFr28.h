#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr28_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr28 { "VCU1Mid3CanFr28" };


// Groups
const std::string SftyDecelGroupSafe { "SftyDecelGroupSafe" };


// Signals
const std::string AsySftyDecelReq { "AsySftyDecelReq" };
const std::string SftyDecelGroupSafeChks { "SftyDecelGroupSafeChks" };
const std::string AsySftyEnaDecel { "AsySftyEnaDecel" };
const std::string SftyDecelGroupSafeCntr { "SftyDecelGroupSafeCntr" };
const std::string SftyDecelGroupSafe_UB { "SftyDecelGroupSafe_UB" };


}
}
