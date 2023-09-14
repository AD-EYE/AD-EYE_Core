#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr22_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr22 { "VCU1Mid3CanFr22" };


// Groups
const std::string AdSecBrkActvnGroupSafe { "AdSecBrkActvnGroupSafe" };
const std::string BrkFricTqTotAtWhlsAct { "BrkFricTqTotAtWhlsAct" };


// Signals
const std::string PtTqAtAxleAvlFrntMaxLong_UB { "PtTqAtAxleAvlFrntMaxLong_UB" };
const std::string BrkFricTqTotAtWhlsAct_UB { "BrkFricTqTotAtWhlsAct_UB" };
const std::string BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsActCntr { "BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsActCntr" };
const std::string BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsActChks { "BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsActChks" };
const std::string BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsAct { "BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsAct" };
const std::string PtTqAtAxleAvlFrntMaxLong { "PtTqAtAxleAvlFrntMaxLong" };
const std::string AdSecBrkActvnGroupSafe_UB { "AdSecBrkActvnGroupSafe_UB" };
const std::string AdSecBrkActvnGroupSafeActvnReq { "AdSecBrkActvnGroupSafeActvnReq" };
const std::string AdSecBrkActvnGroupSafeDeactvnReq { "AdSecBrkActvnGroupSafeDeactvnReq" };
const std::string AdSecBrkActvnGroupSafeCntr { "AdSecBrkActvnGroupSafeCntr" };
const std::string AdSecBrkActvnGroupSafeChks { "AdSecBrkActvnGroupSafeChks" };


}
}
