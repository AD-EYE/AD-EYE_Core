#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid3CanFr05_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr05 { "VIMMid3CanFr05" };


// Groups


// Signals
const std::string ExtDcDcActvnSts2_UB { "ExtDcDcActvnSts2_UB" };
const std::string ExtDcDcActvnSts2 { "ExtDcDcActvnSts2" };


}
}
