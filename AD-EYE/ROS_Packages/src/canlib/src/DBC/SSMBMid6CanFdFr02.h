#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr02_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMBMid6CanFdFr02 { "SSMBMid6CanFdFr02" };


// Groups
const std::string AdSecMotTqASILThrshldExcd { "AdSecMotTqASILThrshldExcd" };


// Signals
const std::string AdSecMotTqASILThrshldExcd_UB { "AdSecMotTqASILThrshldExcd_UB" };
const std::string AdSecMotTqASILThrshldExcdThrshldExceeded { "AdSecMotTqASILThrshldExcdThrshldExceeded" };
const std::string AdSecMotTqASILThrshldExcdCntr { "AdSecMotTqASILThrshldExcdCntr" };
const std::string AdSecMotTqASILThrshldExcdChks { "AdSecMotTqASILThrshldExcdChks" };


}
}
