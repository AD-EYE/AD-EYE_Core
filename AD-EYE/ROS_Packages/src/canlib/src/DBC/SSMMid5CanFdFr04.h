#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMMid5CanFdFr04_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMMid5CanFdFr04 { "SSMMid5CanFdFr04" };


// Groups
const std::string PrimVehMSafe { "PrimVehMSafe" };
const std::string PrimWhlAgSpdFrntSafe { "PrimWhlAgSpdFrntSafe" };
const std::string PrimWhlAgSpdReSafe { "PrimWhlAgSpdReSafe" };


// Signals
const std::string PrimWhlAgSpdFrntSafeRiQf { "PrimWhlAgSpdFrntSafeRiQf" };
const std::string PrimWhlAgSpdFrntSafeLeQf { "PrimWhlAgSpdFrntSafeLeQf" };
const std::string PrimWhlAgSpdFrntSafeCntr { "PrimWhlAgSpdFrntSafeCntr" };
const std::string PrimWhlAgSpdFrntSafeChks { "PrimWhlAgSpdFrntSafeChks" };
const std::string PrimWhlAgSpdFrntSafeLe { "PrimWhlAgSpdFrntSafeLe" };
const std::string PrimWhlAgSpdFrntSafeRi { "PrimWhlAgSpdFrntSafeRi" };
const std::string PrimWhlAgSpdReSafeRiQf { "PrimWhlAgSpdReSafeRiQf" };
const std::string PrimWhlAgSpdReSafeLeQf { "PrimWhlAgSpdReSafeLeQf" };
const std::string PrimWhlAgSpdReSafeCntr { "PrimWhlAgSpdReSafeCntr" };
const std::string PrimWhlAgSpdReSafeChks { "PrimWhlAgSpdReSafeChks" };
const std::string PrimWhlAgSpdReSafeLe { "PrimWhlAgSpdReSafeLe" };
const std::string PrimWhlAgSpdReSafeRi { "PrimWhlAgSpdReSafeRi" };
const std::string PrimWhlAgSpdFrntSafe_UB { "PrimWhlAgSpdFrntSafe_UB" };
const std::string PrimWhlAgSpdReSafe_UB { "PrimWhlAgSpdReSafe_UB" };
const std::string PrimVehMSafeNomQf { "PrimVehMSafeNomQf" };
const std::string PrimVehMSafeCntr { "PrimVehMSafeCntr" };
const std::string PrimVehMSafeChks { "PrimVehMSafeChks" };
const std::string PrimVehMSafeVehMMax { "PrimVehMSafeVehMMax" };
const std::string PrimVehMSafeVehMMin { "PrimVehMSafeVehMMin" };
const std::string PrimVehMSafeVehMNom { "PrimVehMSafeVehMNom" };
const std::string PrimVehMSafeSafeQf { "PrimVehMSafeSafeQf" };
const std::string PrimVehMSafe_UB { "PrimVehMSafe_UB" };


}
}
