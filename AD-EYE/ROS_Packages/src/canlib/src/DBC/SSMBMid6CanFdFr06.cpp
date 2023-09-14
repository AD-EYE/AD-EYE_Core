#include "SSMBMid6CanFdFr06.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr06_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ SecALatDataRawSafeChks, { SecALatDataRawSafeChks, 8, 8, SignalType::E2E_CHKS, 0, SecALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALatDataRawSafeCntr, { SecALatDataRawSafeCntr, 0, 4, SignalType::E2E_CNTR, 0, SecALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALatDataRawSafeMax, { SecALatDataRawSafeMax, 9, 15, SignalType::APP_UNSIGNED, 16384, SecALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALatDataRawSafeMin, { SecALatDataRawSafeMin, 25, 15, SignalType::APP_UNSIGNED, 16384, SecALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALatDataRawSafeMinMaxQf, { SecALatDataRawSafeMinMaxQf, 5, 2, SignalType::APP_UNSIGNED, 0, SecALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALatDataRawSafeNom, { SecALatDataRawSafeNom, 41, 15, SignalType::APP_UNSIGNED, 16384, SecALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALatDataRawSafeNomQf, { SecALatDataRawSafeNomQf, 70, 2, SignalType::APP_UNSIGNED, 1, SecALatDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALgtDataRawSafeChks, { SecALgtDataRawSafeChks, 72, 8, SignalType::E2E_CHKS, 0, SecALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALgtDataRawSafeCntr, { SecALgtDataRawSafeCntr, 64, 4, SignalType::E2E_CNTR, 0, SecALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALgtDataRawSafeMax, { SecALgtDataRawSafeMax, 72, 15, SignalType::APP_UNSIGNED, 16384, SecALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALgtDataRawSafeMin, { SecALgtDataRawSafeMin, 88, 15, SignalType::APP_UNSIGNED, 16384, SecALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALgtDataRawSafeMinMaxQf, { SecALgtDataRawSafeMinMaxQf, 134, 2, SignalType::APP_UNSIGNED, 0, SecALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALgtDataRawSafeNom, { SecALgtDataRawSafeNom, 104, 15, SignalType::APP_UNSIGNED, 16384, SecALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecALgtDataRawSafeNomQf, { SecALgtDataRawSafeNomQf, 68, 2, SignalType::APP_UNSIGNED, 1, SecALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ SecAxleSlipStsAndRelAgFrntAxle, { SecAxleSlipStsAndRelAgFrntAxle, 222, 2, SignalType::APP_UNSIGNED, 1, SecAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ SecAxleSlipStsAndRelAgIntvSts, { SecAxleSlipStsAndRelAgIntvSts, 262, 2, SignalType::APP_UNSIGNED, 1, SecAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ SecAxleSlipStsAndRelAgReAxle, { SecAxleSlipStsAndRelAgReAxle, 220, 2, SignalType::APP_UNSIGNED, 1, SecAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ SecAxleSlipStsAndRelAgRelPitch, { SecAxleSlipStsAndRelAgRelPitch, 232, 16, SignalType::APP_SIGNED, 0, SecAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ SecAxleSlipStsAndRelAgRelPitchQf, { SecAxleSlipStsAndRelAgRelPitchQf, 218, 2, SignalType::APP_UNSIGNED, 1, SecAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ SecAxleSlipStsAndRelAgRelRoll, { SecAxleSlipStsAndRelAgRelRoll, 248, 16, SignalType::APP_SIGNED, 0, SecAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ SecAxleSlipStsAndRelAgRelRolQf, { SecAxleSlipStsAndRelAgRelRolQf, 216, 2, SignalType::APP_UNSIGNED, 1, SecAxleSlipStsAndRelAg, ParentType::GROUP } });
    signals_info.insert({ SecVLatSafeChks, { SecVLatSafeChks, 272, 8, SignalType::E2E_CHKS, 0, SecVLatSafe, ParentType::GROUP } });
    signals_info.insert({ SecVLatSafeCntr, { SecVLatSafeCntr, 256, 4, SignalType::E2E_CNTR, 0, SecVLatSafe, ParentType::GROUP } });
    signals_info.insert({ SecVLatSafeMax, { SecVLatSafeMax, 288, 15, SignalType::APP_SIGNED, 0, SecVLatSafe, ParentType::GROUP } });
    signals_info.insert({ SecVLatSafeMin, { SecVLatSafeMin, 304, 15, SignalType::APP_SIGNED, 0, SecVLatSafe, ParentType::GROUP } });
    signals_info.insert({ SecVLatSafeMinMaxQf, { SecVLatSafeMinMaxQf, 265, 2, SignalType::APP_UNSIGNED, 0, SecVLatSafe, ParentType::GROUP } });
    signals_info.insert({ SecVLatSafeNom, { SecVLatSafeNom, 320, 15, SignalType::APP_SIGNED, 0, SecVLatSafe, ParentType::GROUP } });
    signals_info.insert({ SecVLatSafeNomQf, { SecVLatSafeNomQf, 267, 2, SignalType::APP_UNSIGNED, 1, SecVLatSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotDirReSafeChks, { SecWhlRotDirReSafeChks, 208, 8, SignalType::E2E_CHKS, 0, SecWhlRotDirReSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotDirReSafeCntr, { SecWhlRotDirReSafeCntr, 192, 4, SignalType::E2E_CNTR, 0, SecWhlRotDirReSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotDirReSafeLe, { SecWhlRotDirReSafeLe, 206, 2, SignalType::APP_UNSIGNED, 0, SecWhlRotDirReSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotDirReSafeLeQf, { SecWhlRotDirReSafeLeQf, 204, 2, SignalType::APP_UNSIGNED, 1, SecWhlRotDirReSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotDirReSafeRi, { SecWhlRotDirReSafeRi, 202, 2, SignalType::APP_UNSIGNED, 0, SecWhlRotDirReSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotDirReSafeRiQf, { SecWhlRotDirReSafeRiQf, 200, 2, SignalType::APP_UNSIGNED, 1, SecWhlRotDirReSafe, ParentType::GROUP } });
    signals_info.insert({ SecYawRateSafeChks, { SecYawRateSafeChks, 344, 8, SignalType::E2E_CHKS, 0, SecYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ SecYawRateSafeCntr, { SecYawRateSafeCntr, 336, 4, SignalType::E2E_CNTR, 0, SecYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ SecYawRateSafeMax, { SecYawRateSafeMax, 360, 15, SignalType::APP_SIGNED, 0, SecYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ SecYawRateSafeMin, { SecYawRateSafeMin, 376, 15, SignalType::APP_SIGNED, 0, SecYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ SecYawRateSafeMinMaxQf, { SecYawRateSafeMinMaxQf, 341, 2, SignalType::APP_UNSIGNED, 0, SecYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ SecYawRateSafeNom, { SecYawRateSafeNom, 392, 15, SignalType::APP_SIGNED, 0, SecYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ SecYawRateSafeNomQf, { SecYawRateSafeNomQf, 328, 2, SignalType::APP_UNSIGNED, 1, SecYawRateSafe, ParentType::GROUP } });
    signals_info.insert({ SecAxleSlipStsAndRelAg_UB, { SecAxleSlipStsAndRelAg_UB, 199, 1, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr06, ParentType::FRAME } });
    signals_info.insert({ SecWhlRotDirReSafe_UB, { SecWhlRotDirReSafe_UB, 198, 1, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr06, ParentType::FRAME } });
    signals_info.insert({ SecYawRateSafe_UB, { SecYawRateSafe_UB, 330, 1, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr06, ParentType::FRAME } });
    signals_info.insert({ SecALgtDataRawSafe_UB, { SecALgtDataRawSafe_UB, 196, 1, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr06, ParentType::FRAME } });
    signals_info.insert({ SecVLatSafe_UB, { SecVLatSafe_UB, 260, 1, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr06, ParentType::FRAME } });
    signals_info.insert({ SecALatDataRawSafe_UB, { SecALatDataRawSafe_UB, 7, 1, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr06, ParentType::FRAME } });

    signalgroups_info.insert({ SecALatDataRawSafe, { SecALatDataRawSafe, 0x214, { SecALatDataRawSafeChks, SecALatDataRawSafeCntr, SecALatDataRawSafeMax, SecALatDataRawSafeMin, SecALatDataRawSafeMinMaxQf, SecALatDataRawSafeNom, SecALatDataRawSafeNomQf }, { E2EProfileType::P01a, SecALatDataRawSafeChks, SecALatDataRawSafeCntr }, SSMBMid6CanFdFr06 } } );
    signalgroups_info.insert({ SecALgtDataRawSafe, { SecALgtDataRawSafe, 0x217, { SecALgtDataRawSafeChks, SecALgtDataRawSafeCntr, SecALgtDataRawSafeMax, SecALgtDataRawSafeMin, SecALgtDataRawSafeMinMaxQf, SecALgtDataRawSafeNom, SecALgtDataRawSafeNomQf }, { E2EProfileType::P01a, SecALgtDataRawSafeChks, SecALgtDataRawSafeCntr }, SSMBMid6CanFdFr06 } } );
    signalgroups_info.insert({ SecAxleSlipStsAndRelAg, { SecAxleSlipStsAndRelAg, 0x0, { SecAxleSlipStsAndRelAgFrntAxle, SecAxleSlipStsAndRelAgIntvSts, SecAxleSlipStsAndRelAgReAxle, SecAxleSlipStsAndRelAgRelPitch, SecAxleSlipStsAndRelAgRelPitchQf, SecAxleSlipStsAndRelAgRelRoll, SecAxleSlipStsAndRelAgRelRolQf }, { E2EProfileType::None, "", "" }, SSMBMid6CanFdFr06 } } );
    signalgroups_info.insert({ SecVLatSafe, { SecVLatSafe, 0x506, { SecVLatSafeChks, SecVLatSafeCntr, SecVLatSafeMax, SecVLatSafeMin, SecVLatSafeMinMaxQf, SecVLatSafeNom, SecVLatSafeNomQf }, { E2EProfileType::P01a, SecVLatSafeChks, SecVLatSafeCntr }, SSMBMid6CanFdFr06 } } );
    signalgroups_info.insert({ SecWhlRotDirReSafe, { SecWhlRotDirReSafe, 0x646, { SecWhlRotDirReSafeChks, SecWhlRotDirReSafeCntr, SecWhlRotDirReSafeLe, SecWhlRotDirReSafeLeQf, SecWhlRotDirReSafeRi, SecWhlRotDirReSafeRiQf }, { E2EProfileType::P01a, SecWhlRotDirReSafeChks, SecWhlRotDirReSafeCntr }, SSMBMid6CanFdFr06 } } );
    signalgroups_info.insert({ SecYawRateSafe, { SecYawRateSafe, 0x215, { SecYawRateSafeChks, SecYawRateSafeCntr, SecYawRateSafeMax, SecYawRateSafeMin, SecYawRateSafeMinMaxQf, SecYawRateSafeNom, SecYawRateSafeNomQf }, { E2EProfileType::P01a, SecYawRateSafeChks, SecYawRateSafeCntr }, SSMBMid6CanFdFr06 } } );

    frames_info.insert({ SSMBMid6CanFdFr06, { SSMBMid6CanFdFr06, 49, 64, 10, { SecALatDataRawSafe, SecALgtDataRawSafe, SecAxleSlipStsAndRelAg, SecVLatSafe, SecWhlRotDirReSafe, SecYawRateSafe }, { SecYawRateSafe_UB, SecALatDataRawSafe_UB, SecVLatSafe_UB, SecAxleSlipStsAndRelAg_UB, SecWhlRotDirReSafe_UB, SecALgtDataRawSafe_UB } } });

    frame_ids.insert({ 49, SSMBMid6CanFdFr06 });
}


}
}
