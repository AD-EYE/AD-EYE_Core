#include "SSMMid5CanFdFr03.h"


namespace kcan {
namespace dbc {


void SSMMid5CanFdFr03_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimWhlAgEstimdGroupSafeChks, { AdPrimWhlAgEstimdGroupSafeChks, 8, 8, SignalType::E2E_CHKS, 0, AdPrimWhlAgEstimdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimWhlAgEstimdGroupSafeCntr, { AdPrimWhlAgEstimdGroupSafeCntr, 0, 4, SignalType::E2E_CNTR, 0, AdPrimWhlAgEstimdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimWhlAgEstimdGroupSafeQf1, { AdPrimWhlAgEstimdGroupSafeQf1, 54, 2, SignalType::APP_UNSIGNED, 0, AdPrimWhlAgEstimdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimWhlAgEstimdGroupSafeWhlAg, { AdPrimWhlAgEstimdGroupSafeWhlAg, 8, 15, SignalType::APP_UNSIGNED, 16193, AdPrimWhlAgEstimdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALatDataRawSafeChks, { PrimALatDataRawSafeChks, 56, 8, SignalType::E2E_CHKS, 0, PrimALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALatDataRawSafeCntr, { PrimALatDataRawSafeCntr, 48, 4, SignalType::E2E_CNTR, 0, PrimALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALatDataRawSafeMax, { PrimALatDataRawSafeMax, 57, 15, SignalType::APP_UNSIGNED, 16384, PrimALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALatDataRawSafeMin, { PrimALatDataRawSafeMin, 73, 15, SignalType::APP_UNSIGNED, 16384, PrimALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALatDataRawSafeMinMaxQf, { PrimALatDataRawSafeMinMaxQf, 118, 2, SignalType::APP_UNSIGNED, 0, PrimALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALatDataRawSafeNom, { PrimALatDataRawSafeNom, 89, 15, SignalType::APP_UNSIGNED, 16384, PrimALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALatDataRawSafeNomQf, { PrimALatDataRawSafeNomQf, 52, 2, SignalType::APP_UNSIGNED, 1, PrimALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgFrntAxle, { PrimAxleSlipStsAndRelAgFrntAxle, 182, 2, SignalType::APP_UNSIGNED, 1, PrimAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgIntvSts, { PrimAxleSlipStsAndRelAgIntvSts, 222, 2, SignalType::APP_UNSIGNED, 1, PrimAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgReAxle, { PrimAxleSlipStsAndRelAgReAxle, 180, 2, SignalType::APP_UNSIGNED, 1, PrimAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgRelPitch, { PrimAxleSlipStsAndRelAgRelPitch, 192, 16, SignalType::APP_SIGNED, 0, PrimAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgRelRoll, { PrimAxleSlipStsAndRelAgRelRoll, 208, 16, SignalType::APP_SIGNED, 0, PrimAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgRelRolQf, { PrimAxleSlipStsAndRelAgRelRolQf, 176, 2, SignalType::APP_UNSIGNED, 1, PrimAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ PrimVLatSafeChks, { PrimVLatSafeChks, 408, 8, SignalType::E2E_CHKS, 0, PrimVLatSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVLatSafeCntr, { PrimVLatSafeCntr, 392, 4, SignalType::E2E_CNTR, 0, PrimVLatSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVLatSafeMax, { PrimVLatSafeMax, 424, 15, SignalType::APP_SIGNED, 0, PrimVLatSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVLatSafeMin, { PrimVLatSafeMin, 440, 15, SignalType::APP_SIGNED, 0, PrimVLatSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVLatSafeMinMaxQf, { PrimVLatSafeMinMaxQf, 401, 2, SignalType::APP_UNSIGNED, 0, PrimVLatSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVLatSafeNom, { PrimVLatSafeNom, 456, 15, SignalType::APP_SIGNED, 0, PrimVLatSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVLatSafeNomQf, { PrimVLatSafeNomQf, 403, 2, SignalType::APP_UNSIGNED, 1, PrimVLatSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotDirReSafe1Chks, { PrimWhlRotDirReSafe1Chks, 312, 8, SignalType::E2E_CHKS, 0, PrimWhlRotDirReSafe1, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotDirReSafe1Cntr, { PrimWhlRotDirReSafe1Cntr, 296, 4, SignalType::E2E_CNTR, 0, PrimWhlRotDirReSafe1, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotDirReSafe1Le, { PrimWhlRotDirReSafe1Le, 310, 2, SignalType::APP_UNSIGNED, 0, PrimWhlRotDirReSafe1, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotDirReSafe1LeQf, { PrimWhlRotDirReSafe1LeQf, 308, 2, SignalType::APP_UNSIGNED, 1, PrimWhlRotDirReSafe1, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotDirReSafe1Ri, { PrimWhlRotDirReSafe1Ri, 306, 2, SignalType::APP_UNSIGNED, 0, PrimWhlRotDirReSafe1, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotDirReSafe1RiQf, { PrimWhlRotDirReSafe1RiQf, 304, 2, SignalType::APP_UNSIGNED, 1, PrimWhlRotDirReSafe1, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotToothCntrChks, { PrimWhlRotToothCntrChks, 328, 8, SignalType::E2E_CHKS, 0, PrimWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotToothCntrCntr, { PrimWhlRotToothCntrCntr, 320, 4, SignalType::E2E_CNTR, 0, PrimWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ PrimYawRateSafeChks, { PrimYawRateSafeChks, 232, 8, SignalType::E2E_CHKS, 0, PrimYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ PrimYawRateSafeCntr, { PrimYawRateSafeCntr, 216, 4, SignalType::E2E_CNTR, 0, PrimYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ PrimYawRateSafeMax, { PrimYawRateSafeMax, 248, 15, SignalType::APP_SIGNED, 0, PrimYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ PrimYawRateSafeMin, { PrimYawRateSafeMin, 264, 15, SignalType::APP_SIGNED, 0, PrimYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ PrimYawRateSafeMinMaxQf, { PrimYawRateSafeMinMaxQf, 227, 2, SignalType::APP_UNSIGNED, 0, PrimYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ PrimYawRateSafeNom, { PrimYawRateSafeNom, 280, 15, SignalType::APP_SIGNED, 0, PrimYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ PrimYawRateSafeNomQf, { PrimYawRateSafeNomQf, 224, 2, SignalType::APP_UNSIGNED, 1, PrimYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ PrimYawRateSafe_UB, { PrimYawRateSafe_UB, 302, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr03, ParentType::FRAME } });
    signals_info.insert({ PrimALatDataRawSafe_UB, { PrimALatDataRawSafe_UB, 5, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr03, ParentType::FRAME } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotToothCntrReLe, { PrimWhlRotToothCntrWhlRotToothCntrReLe, 360, 8, SignalType::APP_UNSIGNED, 0, PrimWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotToothCntrReRi, { PrimWhlRotToothCntrWhlRotToothCntrReRi, 368, 8, SignalType::APP_UNSIGNED, 0, PrimWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotToothCntrReLeQf, { PrimWhlRotToothCntrWhlRotToothCntrReLeQf, 346, 2, SignalType::APP_UNSIGNED, 1, PrimWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ PrimAxleSlipStsAndRelAg_UB, { PrimAxleSlipStsAndRelAg_UB, 116, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr03, ParentType::FRAME } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgRelPitchQf, { PrimAxleSlipStsAndRelAgRelPitchQf, 178, 2, SignalType::APP_UNSIGNED, 1, PrimAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotToothCntrFrntRi, { PrimWhlRotToothCntrWhlRotToothCntrFrntRi, 352, 8, SignalType::APP_UNSIGNED, 0, PrimWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotToothCntrFrntLe, { PrimWhlRotToothCntrWhlRotToothCntrFrntLe, 336, 8, SignalType::APP_UNSIGNED, 0, PrimWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotToothCntrFrntRiQf, { PrimWhlRotToothCntrWhlRotToothCntrFrntRiQf, 348, 2, SignalType::APP_UNSIGNED, 1, PrimWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotToothCntr_UB, { PrimWhlRotToothCntr_UB, 301, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr03, ParentType::FRAME } });
    signals_info.insert({ PrimWhlRotDirReSafe1_UB, { PrimWhlRotDirReSafe1_UB, 300, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr03, ParentType::FRAME } });
    signals_info.insert({ AdPrimWhlAgEstimdGroupSafe_UB, { AdPrimWhlAgEstimdGroupSafe_UB, 4, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr03, ParentType::FRAME } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotToothCntrReRiQf, { PrimWhlRotToothCntrWhlRotToothCntrReRiQf, 344, 2, SignalType::APP_UNSIGNED, 1, PrimWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotToothCntrFrntLeQf, { PrimWhlRotToothCntrWhlRotToothCntrFrntLeQf, 350, 2, SignalType::APP_UNSIGNED, 1, PrimWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ AdPrimWhlAgEstimdGroupSafeWhlAgRate, { AdPrimWhlAgEstimdGroupSafeWhlAgRate, 40, 15, SignalType::APP_UNSIGNED, 14000, AdPrimWhlAgEstimdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVLatSafe_UB, { PrimVLatSafe_UB, 396, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr03, ParentType::FRAME } });





    signalgroups_info.insert({ AdPrimWhlAgEstimdGroupSafe, { AdPrimWhlAgEstimdGroupSafe, 0x1AF, { AdPrimWhlAgEstimdGroupSafeChks, AdPrimWhlAgEstimdGroupSafeCntr, AdPrimWhlAgEstimdGroupSafeQf1, AdPrimWhlAgEstimdGroupSafeWhlAg, AdPrimWhlAgEstimdGroupSafeWhlAgRate }, { E2EProfileType::P01a, AdPrimWhlAgEstimdGroupSafeChks, AdPrimWhlAgEstimdGroupSafeCntr }, SSMMid5CanFdFr03 } } );
    signalgroups_info.insert({ PrimALatDataRawSafe, { PrimALatDataRawSafe, 0x20E, { PrimALatDataRawSafeChks, PrimALatDataRawSafeCntr, PrimALatDataRawSafeMax, PrimALatDataRawSafeMin, PrimALatDataRawSafeMinMaxQf, PrimALatDataRawSafeNom, PrimALatDataRawSafeNomQf }, { E2EProfileType::P01a, PrimALatDataRawSafeChks, PrimALatDataRawSafeCntr }, SSMMid5CanFdFr03 } } );
    signalgroups_info.insert({ PrimAxleSlipStsAndRelAg, { PrimAxleSlipStsAndRelAg, 0x0, { PrimAxleSlipStsAndRelAgFrntAxle, PrimAxleSlipStsAndRelAgIntvSts, PrimAxleSlipStsAndRelAgReAxle, PrimAxleSlipStsAndRelAgRelPitch, PrimAxleSlipStsAndRelAgRelPitchQf, PrimAxleSlipStsAndRelAgRelRoll, PrimAxleSlipStsAndRelAgRelRolQf }, { E2EProfileType::None, "", "" }, SSMMid5CanFdFr03 } } );
    signalgroups_info.insert({ PrimVLatSafe, { PrimVLatSafe, 0x505, { PrimVLatSafeChks, PrimVLatSafeCntr, PrimVLatSafeMax, PrimVLatSafeMin, PrimVLatSafeMinMaxQf, PrimVLatSafeNom, PrimVLatSafeNomQf }, { E2EProfileType::P01a, PrimVLatSafeChks, PrimVLatSafeCntr }, SSMMid5CanFdFr03 } } );
    signalgroups_info.insert({ PrimWhlRotDirReSafe1, { PrimWhlRotDirReSafe1, 0x714, { PrimWhlRotDirReSafe1Chks, PrimWhlRotDirReSafe1Cntr, PrimWhlRotDirReSafe1Le, PrimWhlRotDirReSafe1LeQf, PrimWhlRotDirReSafe1Ri, PrimWhlRotDirReSafe1RiQf }, { E2EProfileType::P01a, PrimWhlRotDirReSafe1Chks, PrimWhlRotDirReSafe1Cntr }, SSMMid5CanFdFr03 } } );
    signalgroups_info.insert({ PrimWhlRotToothCntr, { PrimWhlRotToothCntr, 0x578, { PrimWhlRotToothCntrChks, PrimWhlRotToothCntrCntr, PrimWhlRotToothCntrWhlRotToothCntrFrntLe, PrimWhlRotToothCntrWhlRotToothCntrFrntLeQf, PrimWhlRotToothCntrWhlRotToothCntrFrntRi, PrimWhlRotToothCntrWhlRotToothCntrFrntRiQf, PrimWhlRotToothCntrWhlRotToothCntrReLe, PrimWhlRotToothCntrWhlRotToothCntrReLeQf, PrimWhlRotToothCntrWhlRotToothCntrReRi, PrimWhlRotToothCntrWhlRotToothCntrReRiQf }, { E2EProfileType::P01a, PrimWhlRotToothCntrChks, PrimWhlRotToothCntrCntr }, SSMMid5CanFdFr03 } } );
    signalgroups_info.insert({ PrimYawRateSafe, { PrimYawRateSafe, 0x212, { PrimYawRateSafeChks, PrimYawRateSafeCntr, PrimYawRateSafeMax, PrimYawRateSafeMin, PrimYawRateSafeMinMaxQf, PrimYawRateSafeNom, PrimYawRateSafeNomQf }, { E2EProfileType::P01a, PrimYawRateSafeChks, PrimYawRateSafeCntr }, SSMMid5CanFdFr03 } } );

    frames_info.insert({ SSMMid5CanFdFr03, { SSMMid5CanFdFr03, 32, 64, 10, { AdPrimWhlAgEstimdGroupSafe, PrimALatDataRawSafe, PrimAxleSlipStsAndRelAg, PrimVLatSafe, PrimWhlRotDirReSafe1, PrimWhlRotToothCntr, PrimYawRateSafe }, { PrimYawRateSafe_UB, PrimALatDataRawSafe_UB, PrimAxleSlipStsAndRelAg_UB, PrimWhlRotToothCntr_UB, PrimWhlRotDirReSafe1_UB, AdPrimWhlAgEstimdGroupSafe_UB, PrimVLatSafe_UB } } });

   frame_ids.insert({ 32, SSMMid5CanFdFr03 });
}


}
}
