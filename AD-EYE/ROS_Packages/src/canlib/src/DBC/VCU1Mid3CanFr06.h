#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr06_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr06 { "VCU1Mid3CanFr06" };


// Groups


// Signals
const std::string CarTiGlb { "CarTiGlb" };
const std::string CarTiGlb_UB { "CarTiGlb_UB" };


}
}
