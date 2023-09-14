#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr30_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr30 { "VCU1Mid3CanFr30" };


// Groups
const std::string AutnmsDrvModMngtExtSafe { "AutnmsDrvModMngtExtSafe" };
const std::string BrkDegraded { "BrkDegraded" };


// Signals
const std::string AutnmsDrvModMngtExtSafe_UB { "AutnmsDrvModMngtExtSafe_UB" };
const std::string VehUsgSt_UB { "VehUsgSt_UB" };
const std::string BrkDegraded_UB { "BrkDegraded_UB" };
const std::string BrkDegradedCntr { "BrkDegradedCntr" };
const std::string BrkDegradedChks { "BrkDegradedChks" };
const std::string BrkDegradedSts { "BrkDegradedSts" };
const std::string VehUsgSt { "VehUsgSt" };
const std::string VehManDeactvnReqInProgs1_UB { "VehManDeactvnReqInProgs1_UB" };
const std::string VehManDeactvnReqInProgs1 { "VehManDeactvnReqInProgs1" };
const std::string AutnmsDrvModMngtExtSafeChecksum { "AutnmsDrvModMngtExtSafeChecksum" };
const std::string AutnmsDrvModMngtExtSafeCounter { "AutnmsDrvModMngtExtSafeCounter" };
const std::string AutnmsDrvModMngtExtSafeAutnmsDrvModSts1 { "AutnmsDrvModMngtExtSafeAutnmsDrvModSts1" };
const std::string AutnmsDrvModMngtExtSafeVehOperModSts1 { "AutnmsDrvModMngtExtSafeVehOperModSts1" };


}
}
