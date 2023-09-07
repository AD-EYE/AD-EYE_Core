#include "../basic_types.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr08_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr08 { "VCU1Mid3CanFr08" };

// Groups
const std::string AgDataRawSafe { "AgDataRawSafe" };
const std::string ClstrSts1ForAutnmsDrv { "ClstrSts1ForAutnmsDrv" };

// Signals
const std::string AgDataRawSafe_UB { "AgDataRawSafe_UB" };
const std::string AgDataRawSafeChks { "AgDataRawSafeChks" };
const std::string AgDataRawSafeCntr { "AgDataRawSafeCntr" };
const std::string ClstrSts1ForAutnmsDrv_UB { "ClstrSts1ForAutnmsDrv_UB" };
const std::string ClstrSts1ForAutnmsDrvClstr1Chks { "ClstrSts1ForAutnmsDrvClstr1Chks" };
const std::string ClstrSts1ForAutnmsDrvClstr1Cnt { "ClstrSts1ForAutnmsDrvClstr1Cnt" };
const std::string ClstrSts1ForAutnmsDrvClstr1Sts { "ClstrSts1ForAutnmsDrvClstr1Sts" };
const std::string RollRate1 { "RollRate1" };
const std::string RollRate1Qf1 { "RollRate1Qf1" };
const std::string YawRate1 { "YawRate1" };
const std::string YawRate1Qf1 { "YawRate1Qf1" };


}
}
