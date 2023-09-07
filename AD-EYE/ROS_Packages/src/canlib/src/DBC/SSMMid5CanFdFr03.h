#include "../basic_types.h"


namespace kcan {
namespace dbc {


void SSMMid5CanFdFr03_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMMid5CanFdFr03 { "SSMMid5CanFdFr03" };

// Groups
const std::string AdPrimWhlAgEstimdGroupSafe { "AdPrimWhlAgEstimdGroupSafe" };
const std::string PrimALatDataRawSafe { "PrimALatDataRawSafe" };
const std::string PrimAxleSlipStsAndRelAg { "PrimAxleSlipStsAndRelAg" };
const std::string PrimVLatSafe { "PrimVLatSafe" };
const std::string PrimWhlRotDirReSafe1 { "PrimWhlRotDirReSafe1" };
const std::string PrimWhlRotToothCntr { "PrimWhlRotToothCntr" };
const std::string PrimYawRateSafe { "PrimYawRateSafe" };

// Signals
const std::string AdPrimWhlAgEstimdGroupSafe_UB {"AdPrimWhlAgEstimdGroupSafe_UB"};
const std::string AdPrimWhlAgEstimdGroupSafeChks {"AdPrimWhlAgEstimdGroupSafeChks"};
const std::string AdPrimWhlAgEstimdGroupSafeCntr {"AdPrimWhlAgEstimdGroupSafeCntr"};
const std::string AdPrimWhlAgEstimdGroupSafeQf1 {"AdPrimWhlAgEstimdGroupSafeQf1"};
const std::string AdPrimWhlAgEstimdGroupSafeWhlAg {"AdPrimWhlAgEstimdGroupSafeWhlAg"};
const std::string AdPrimWhlAgEstimdGroupSafeWhlAgR {"AdPrimWhlAgEstimdGroupSafeWhlAgR"};
const std::string PrimALatDataRawSafe_UB {"PrimALatDataRawSafe_UB"};
const std::string PrimALatDataRawSafeChks {"PrimALatDataRawSafeChks"};
const std::string PrimALatDataRawSafeCntr {"PrimALatDataRawSafeCntr"};
const std::string PrimALatDataRawSafeMax {"PrimALatDataRawSafeMax"};
const std::string PrimALatDataRawSafeMin {"PrimALatDataRawSafeMin"};
const std::string PrimALatDataRawSafeMinMaxQf {"PrimALatDataRawSafeMinMaxQf"};
const std::string PrimALatDataRawSafeNom {"PrimALatDataRawSafeNom"};
const std::string PrimALatDataRawSafeNomQf {"PrimALatDataRawSafeNomQf"};
const std::string PrimAxleSlipStsAndRelAg_UB {"PrimAxleSlipStsAndRelAg_UB"};
const std::string PrimAxleSlipStsAndRelAgFrntAxle {"PrimAxleSlipStsAndRelAgFrntAxle"};
const std::string PrimAxleSlipStsAndRelAgIntvSts {"PrimAxleSlipStsAndRelAgIntvSts"};
const std::string PrimAxleSlipStsAndRelAgReAxle {"PrimAxleSlipStsAndRelAgReAxle"};
const std::string PrimAxleSlipStsAndRelAgRelPitch {"PrimAxleSlipStsAndRelAgRelPitch"};
const std::string PrimAxleSlipStsAndRelAgRelPitchQ {"PrimAxleSlipStsAndRelAgRelPitchQ"};
const std::string PrimAxleSlipStsAndRelAgRelRoll {"PrimAxleSlipStsAndRelAgRelRoll"};
const std::string PrimAxleSlipStsAndRelAgRelRolQf {"PrimAxleSlipStsAndRelAgRelRolQf"};
const std::string PrimVLatSafe_UB {"PrimVLatSafe_UB"};
const std::string PrimVLatSafeChks {"PrimVLatSafeChks"};
const std::string PrimVLatSafeCntr {"PrimVLatSafeCntr"};
const std::string PrimVLatSafeMax {"PrimVLatSafeMax"};
const std::string PrimVLatSafeMin {"PrimVLatSafeMin"};
const std::string PrimVLatSafeMinMaxQf {"PrimVLatSafeMinMaxQf"};
const std::string PrimVLatSafeNom {"PrimVLatSafeNom"};
const std::string PrimVLatSafeNomQf {"PrimVLatSafeNomQf"};
const std::string PrimWhlRotDirReSafe1_UB {"PrimWhlRotDirReSafe1_UB"};
const std::string PrimWhlRotDirReSafe1Chks {"PrimWhlRotDirReSafe1Chks"};
const std::string PrimWhlRotDirReSafe1Cntr {"PrimWhlRotDirReSafe1Cntr"};
const std::string PrimWhlRotDirReSafe1Le {"PrimWhlRotDirReSafe1Le"};
const std::string PrimWhlRotDirReSafe1LeQf {"PrimWhlRotDirReSafe1LeQf"};
const std::string PrimWhlRotDirReSafe1Ri {"PrimWhlRotDirReSafe1Ri"};
const std::string PrimWhlRotDirReSafe1RiQf {"PrimWhlRotDirReSafe1RiQf"};
const std::string PrimWhlRotToothCntr_UB {"PrimWhlRotToothCntr_UB"};
const std::string PrimWhlRotToothCntrChks {"PrimWhlRotToothCntrChks"};
const std::string PrimWhlRotToothCntrCntr {"PrimWhlRotToothCntrCntr"};
const std::string PrimWhlRotToothCntrWhlRotToothCn {"PrimWhlRotToothCntrWhlRotToothCn"};
const std::string PrimWhlRotToothCntrWhlRotTo_0000 {"PrimWhlRotToothCntrWhlRotTo_0000"};
const std::string PrimWhlRotToothCntrWhlRotTo_0001 {"PrimWhlRotToothCntrWhlRotTo_0001"};
const std::string PrimWhlRotToothCntrWhlRotTo_0002 {"PrimWhlRotToothCntrWhlRotTo_0002"};
const std::string PrimWhlRotToothCntrWhlRotTo_0003 {"PrimWhlRotToothCntrWhlRotTo_0003"};
const std::string PrimWhlRotToothCntrWhlRotTo_0004 {"PrimWhlRotToothCntrWhlRotTo_0004"};
const std::string PrimWhlRotToothCntrWhlRotTo_0005 {"PrimWhlRotToothCntrWhlRotTo_0005"};
const std::string PrimWhlRotToothCntrWhlRotTo_0006 {"PrimWhlRotToothCntrWhlRotTo_0006"};
const std::string PrimYawRateSafe_UB {"PrimYawRateSafe_UB"};
const std::string PrimYawRateSafeChks {"PrimYawRateSafeChks"};
const std::string PrimYawRateSafeCntr {"PrimYawRateSafeCntr"};
const std::string PrimYawRateSafeMax {"PrimYawRateSafeMax"};
const std::string PrimYawRateSafeMin {"PrimYawRateSafeMin"};
const std::string PrimYawRateSafeMinMaxQf {"PrimYawRateSafeMinMaxQf"};
const std::string PrimYawRateSafeNom {"PrimYawRateSafeNom"};
const std::string PrimYawRateSafeNomQf {"PrimYawRateSafeNomQf"};

}
}
