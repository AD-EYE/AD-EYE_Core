#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr05_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMBMid6CanFdFr05 { "SSMBMid6CanFdFr05" };


// Groups
const std::string AdSecWhlAgEstimdGroupSafe { "AdSecWhlAgEstimdGroupSafe" };
const std::string SecWhlRotToothCntr { "SecWhlRotToothCntr" };


// Signals
const std::string AdSecWhlAgEstimdGroupSafe_UB { "AdSecWhlAgEstimdGroupSafe_UB" };
const std::string AdSecWhlAgEstimdGroupSafeCntr { "AdSecWhlAgEstimdGroupSafeCntr" };
const std::string AdSecWhlAgEstimdGroupSafeChks { "AdSecWhlAgEstimdGroupSafeChks" };
const std::string AdSecWhlAgEstimdGroupSafeWhlAg { "AdSecWhlAgEstimdGroupSafeWhlAg" };
const std::string AdSecWhlAgEstimdGroupSafeWhlAgRate { "AdSecWhlAgEstimdGroupSafeWhlAgRate" };
const std::string AdSecWhlAgEstimdGroupSafeQf1 { "AdSecWhlAgEstimdGroupSafeQf1" };
const std::string SecWhlRotToothCntr_UB { "SecWhlRotToothCntr_UB" };
const std::string SecWhlRotToothCntrCntr { "SecWhlRotToothCntrCntr" };
const std::string SecWhlRotToothCntrChks { "SecWhlRotToothCntrChks" };
const std::string SecWhlRotToothCntrWhlRotToothCntrFrntLe { "SecWhlRotToothCntrWhlRotToothCntrFrntLe" };
const std::string SecWhlRotToothCntrWhlRotToothCntrFrntLeQf { "SecWhlRotToothCntrWhlRotToothCntrFrntLeQf" };
const std::string SecWhlRotToothCntrWhlRotToothCntrFrntRiQf { "SecWhlRotToothCntrWhlRotToothCntrFrntRiQf" };
const std::string SecWhlRotToothCntrWhlRotToothCntrReLeQf { "SecWhlRotToothCntrWhlRotToothCntrReLeQf" };
const std::string SecWhlRotToothCntrWhlRotToothCntrReRiQf { "SecWhlRotToothCntrWhlRotToothCntrReRiQf" };
const std::string SecWhlRotToothCntrWhlRotToothCntrFrntRi { "SecWhlRotToothCntrWhlRotToothCntrFrntRi" };
const std::string SecWhlRotToothCntrWhlRotToothCntrReLe { "SecWhlRotToothCntrWhlRotToothCntrReLe" };
const std::string SecWhlRotToothCntrWhlRotToothCntrReRi { "SecWhlRotToothCntrWhlRotToothCntrReRi" };


}
}
