#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr08_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMBMid6CanFdFr08 { "SSMBMid6CanFdFr08" };


// Groups
const std::string SecVehMSafe { "SecVehMSafe" };
const std::string SecWhlAgSpdFrntSafe { "SecWhlAgSpdFrntSafe" };
const std::string SecWhlAgSpdReSafe { "SecWhlAgSpdReSafe" };


// Signals
const std::string SecWhlAgSpdFrntSafeRiQf { "SecWhlAgSpdFrntSafeRiQf" };
const std::string SecWhlAgSpdFrntSafeLeQf { "SecWhlAgSpdFrntSafeLeQf" };
const std::string SecWhlAgSpdFrntSafeCntr { "SecWhlAgSpdFrntSafeCntr" };
const std::string SecWhlAgSpdFrntSafeChks { "SecWhlAgSpdFrntSafeChks" };
const std::string SecWhlAgSpdFrntSafeLe { "SecWhlAgSpdFrntSafeLe" };
const std::string SecWhlAgSpdFrntSafeRi { "SecWhlAgSpdFrntSafeRi" };
const std::string SecWhlAgSpdReSafeRiQf { "SecWhlAgSpdReSafeRiQf" };
const std::string SecWhlAgSpdReSafeLeQf { "SecWhlAgSpdReSafeLeQf" };
const std::string SecWhlAgSpdReSafeCntr { "SecWhlAgSpdReSafeCntr" };
const std::string SecWhlAgSpdReSafeChks { "SecWhlAgSpdReSafeChks" };
const std::string SecWhlAgSpdReSafeLe { "SecWhlAgSpdReSafeLe" };
const std::string SecWhlAgSpdReSafeRi { "SecWhlAgSpdReSafeRi" };
const std::string SecWhlAgSpdFrntSafe_UB { "SecWhlAgSpdFrntSafe_UB" };
const std::string SecWhlAgSpdReSafe_UB { "SecWhlAgSpdReSafe_UB" };
const std::string SecVehMSafeNomQf { "SecVehMSafeNomQf" };
const std::string SecVehMSafeCntr { "SecVehMSafeCntr" };
const std::string SecVehMSafeVehMMax { "SecVehMSafeVehMMax" };
const std::string SecVehMSafeVehMMin { "SecVehMSafeVehMMin" };
const std::string SecVehMSafeVehMNom { "SecVehMSafeVehMNom" };
const std::string SecVehMSafeChks { "SecVehMSafeChks" };
const std::string SecVehMSafeSafeQf { "SecVehMSafeSafeQf" };
const std::string SecVehMSafe_UB { "SecVehMSafe_UB" };


}
}
