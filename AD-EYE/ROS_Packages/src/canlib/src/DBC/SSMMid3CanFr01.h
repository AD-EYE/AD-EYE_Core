#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMMid3CanFr01_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMMid3CanFr01 { "SSMMid3CanFr01" };


// Groups
const std::string AdSecSteerModStsSafeGroupByGatewy { "AdSecSteerModStsSafeGroupByGatewy" };
const std::string AdSecSteerStsSafeGroupByGatewy { "AdSecSteerStsSafeGroupByGatewy" };


// Signals
const std::string AdSecSteerModStsSafeGroupByGatewy_UB { "AdSecSteerModStsSafeGroupByGatewy_UB" };
const std::string AdSecSteerModStsSafeGroupByGatewyVehOperIntv { "AdSecSteerModStsSafeGroupByGatewyVehOperIntv" };
const std::string AdSecSteerModStsSafeGroupByGatewyVehOperModSts1 { "AdSecSteerModStsSafeGroupByGatewyVehOperModSts1" };
const std::string AdSecSteerModStsSafeGroupByGatewyCntr { "AdSecSteerModStsSafeGroupByGatewyCntr" };
const std::string AdSecSteerModStsSafeGroupByGatewyAdSteerMod { "AdSecSteerModStsSafeGroupByGatewyAdSteerMod" };
const std::string AdSecSteerModStsSafeGroupByGatewyChks { "AdSecSteerModStsSafeGroupByGatewyChks" };
const std::string AdSecSteerStsSafeGroupByGatewy_UB { "AdSecSteerStsSafeGroupByGatewy_UB" };
const std::string AdSecSteerStsSafeGroupByGatewyCntr { "AdSecSteerStsSafeGroupByGatewyCntr" };
const std::string AdSecSteerStsSafeGroupByGatewyAdSteerSts { "AdSecSteerStsSafeGroupByGatewyAdSteerSts" };
const std::string AdSecSteerStsSafeGroupByGatewyAdSteerPerf { "AdSecSteerStsSafeGroupByGatewyAdSteerPerf" };
const std::string AdSecSteerStsSafeGroupByGatewyChks { "AdSecSteerStsSafeGroupByGatewyChks" };


}
}
