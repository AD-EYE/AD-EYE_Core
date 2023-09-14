#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr24_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr24 { "VCU1Mid3CanFr24" };


// Groups
const std::string PrimSteerMotTq { "PrimSteerMotTq" };


// Signals
const std::string PrimSteerMotTqSteerMotTqQf { "PrimSteerMotTqSteerMotTqQf" };
const std::string PrimSteerMotTqSteerMotTq { "PrimSteerMotTqSteerMotTq" };
const std::string PrimSteerMotTq_UB { "PrimSteerMotTq_UB" };


}
}
