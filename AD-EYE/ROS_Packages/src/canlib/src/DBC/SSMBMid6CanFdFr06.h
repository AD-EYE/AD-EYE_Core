#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr06_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMBMid6CanFdFr06 { "SSMBMid6CanFdFr06" };


// Groups
const std::string SecALatDataRawSafe { "SecALatDataRawSafe" };
const std::string SecALgtDataRawSafe { "SecALgtDataRawSafe" };
const std::string SecAxleSlipStsAndRelAg { "SecAxleSlipStsAndRelAg" };
const std::string SecVLatSafe { "SecVLatSafe" };
const std::string SecWhlRotDirReSafe { "SecWhlRotDirReSafe" };
const std::string SecYawRateSafe { "SecYawRateSafe" };


// Signals
const std::string SecALatDataRawSafe_UB { "SecALatDataRawSafe_UB" };
const std::string SecALatDataRawSafeMinMaxQf { "SecALatDataRawSafeMinMaxQf" };
const std::string SecALatDataRawSafeCntr { "SecALatDataRawSafeCntr" };
const std::string SecALatDataRawSafeChks { "SecALatDataRawSafeChks" };
const std::string SecALatDataRawSafeMax { "SecALatDataRawSafeMax" };
const std::string SecALatDataRawSafeMin { "SecALatDataRawSafeMin" };
const std::string SecALatDataRawSafeNom { "SecALatDataRawSafeNom" };
const std::string SecALatDataRawSafeNomQf { "SecALatDataRawSafeNomQf" };
const std::string SecALgtDataRawSafeNomQf { "SecALgtDataRawSafeNomQf" };
const std::string SecALgtDataRawSafeCntr { "SecALgtDataRawSafeCntr" };
const std::string SecALgtDataRawSafeChks { "SecALgtDataRawSafeChks" };
const std::string SecALgtDataRawSafeMax { "SecALgtDataRawSafeMax" };
const std::string SecALgtDataRawSafeMin { "SecALgtDataRawSafeMin" };
const std::string SecALgtDataRawSafeNom { "SecALgtDataRawSafeNom" };
const std::string SecALgtDataRawSafeMinMaxQf { "SecALgtDataRawSafeMinMaxQf" };
const std::string SecAxleSlipStsAndRelAg_UB { "SecAxleSlipStsAndRelAg_UB" };
const std::string SecWhlRotDirReSafe_UB { "SecWhlRotDirReSafe_UB" };
const std::string SecALgtDataRawSafe_UB { "SecALgtDataRawSafe_UB" };
const std::string SecWhlRotDirReSafeCntr { "SecWhlRotDirReSafeCntr" };
const std::string SecWhlRotDirReSafeLe { "SecWhlRotDirReSafeLe" };
const std::string SecWhlRotDirReSafeLeQf { "SecWhlRotDirReSafeLeQf" };
const std::string SecWhlRotDirReSafeRi { "SecWhlRotDirReSafeRi" };
const std::string SecWhlRotDirReSafeRiQf { "SecWhlRotDirReSafeRiQf" };
const std::string SecWhlRotDirReSafeChks { "SecWhlRotDirReSafeChks" };
const std::string SecAxleSlipStsAndRelAgFrntAxle { "SecAxleSlipStsAndRelAgFrntAxle" };
const std::string SecAxleSlipStsAndRelAgReAxle { "SecAxleSlipStsAndRelAgReAxle" };
const std::string SecAxleSlipStsAndRelAgRelPitchQf { "SecAxleSlipStsAndRelAgRelPitchQf" };
const std::string SecAxleSlipStsAndRelAgRelRolQf { "SecAxleSlipStsAndRelAgRelRolQf" };
const std::string SecAxleSlipStsAndRelAgRelPitch { "SecAxleSlipStsAndRelAgRelPitch" };
const std::string SecAxleSlipStsAndRelAgRelRoll { "SecAxleSlipStsAndRelAgRelRoll" };
const std::string SecAxleSlipStsAndRelAgIntvSts { "SecAxleSlipStsAndRelAgIntvSts" };
const std::string SecVLatSafe_UB { "SecVLatSafe_UB" };
const std::string SecVLatSafeCntr { "SecVLatSafeCntr" };
const std::string SecVLatSafeNomQf { "SecVLatSafeNomQf" };
const std::string SecVLatSafeMinMaxQf { "SecVLatSafeMinMaxQf" };
const std::string SecVLatSafeChks { "SecVLatSafeChks" };
const std::string SecVLatSafeMax { "SecVLatSafeMax" };
const std::string SecVLatSafeMin { "SecVLatSafeMin" };
const std::string SecVLatSafeNom { "SecVLatSafeNom" };
const std::string SecYawRateSafe_UB { "SecYawRateSafe_UB" };
const std::string SecYawRateSafeNomQf { "SecYawRateSafeNomQf" };
const std::string SecYawRateSafeMinMaxQf { "SecYawRateSafeMinMaxQf" };
const std::string SecYawRateSafeCntr { "SecYawRateSafeCntr" };
const std::string SecYawRateSafeChks { "SecYawRateSafeChks" };
const std::string SecYawRateSafeMax { "SecYawRateSafeMax" };
const std::string SecYawRateSafeMin { "SecYawRateSafeMin" };
const std::string SecYawRateSafeNom { "SecYawRateSafeNom" };


}
}
