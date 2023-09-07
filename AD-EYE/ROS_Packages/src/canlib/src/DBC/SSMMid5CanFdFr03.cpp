#include "SSMMid5CanFdFr03.h"


namespace kcan {
namespace dbc {


void SSMMid5CanFdFr03_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimWhlAgEstimdGroupSafe_UB, { AdPrimWhlAgEstimdGroupSafe_UB, 4, 1, SignalType::APP_UNSIGNED, SSMMid5CanFdFr03 } });
    signals_info.insert({ AdPrimWhlAgEstimdGroupSafeChks, { AdPrimWhlAgEstimdGroupSafeChks, 8, 8, SignalType::E2E_CHKS, AdPrimWhlAgEstimdGroupSafe } });
    signals_info.insert({ AdPrimWhlAgEstimdGroupSafeCntr, { AdPrimWhlAgEstimdGroupSafeCntr, 0, 4, SignalType::E2E_CNTR, AdPrimWhlAgEstimdGroupSafe } });
    signals_info.insert({ AdPrimWhlAgEstimdGroupSafeQf1, { AdPrimWhlAgEstimdGroupSafeQf1, 54, 2, SignalType::APP_UNSIGNED, AdPrimWhlAgEstimdGroupSafe } });
    signals_info.insert({ AdPrimWhlAgEstimdGroupSafeWhlAg, { AdPrimWhlAgEstimdGroupSafeWhlAg, 8, 15, SignalType::APP_UNSIGNED, AdPrimWhlAgEstimdGroupSafe } });
    signals_info.insert({ AdPrimWhlAgEstimdGroupSafeWhlAgR, { AdPrimWhlAgEstimdGroupSafeWhlAgR, 24, 15, SignalType::APP_UNSIGNED, AdPrimWhlAgEstimdGroupSafe } });
    signals_info.insert({ PrimALatDataRawSafe_UB, { PrimALatDataRawSafe_UB, 5, 1, SignalType::APP_UNSIGNED, SSMMid5CanFdFr03 } });
    signals_info.insert({ PrimALatDataRawSafeChks, { PrimALatDataRawSafeChks, 56, 8, SignalType::E2E_CHKS, PrimALatDataRawSafe } });
    signals_info.insert({ PrimALatDataRawSafeCntr, { PrimALatDataRawSafeCntr, 48, 4, SignalType::E2E_CNTR, PrimALatDataRawSafe } });
    signals_info.insert({ PrimALatDataRawSafeMax, { PrimALatDataRawSafeMax, 57, 15, SignalType::APP_UNSIGNED, PrimALatDataRawSafe } });
    signals_info.insert({ PrimALatDataRawSafeMin, { PrimALatDataRawSafeMin, 73, 15, SignalType::APP_UNSIGNED, PrimALatDataRawSafe } });
    signals_info.insert({ PrimALatDataRawSafeMinMaxQf, { PrimALatDataRawSafeMinMaxQf, 118, 2, SignalType::APP_UNSIGNED, PrimALatDataRawSafe } });
    signals_info.insert({ PrimALatDataRawSafeNom, { PrimALatDataRawSafeNom, 89, 15, SignalType::APP_UNSIGNED, PrimALatDataRawSafe } });
    signals_info.insert({ PrimALatDataRawSafeNomQf, { PrimALatDataRawSafeNomQf, 52, 2, SignalType::APP_UNSIGNED, PrimALatDataRawSafe } });
    signals_info.insert({ PrimAxleSlipStsAndRelAg_UB, { PrimAxleSlipStsAndRelAg_UB, 116, 1, SignalType::APP_UNSIGNED, SSMMid5CanFdFr03 } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgFrntAxle, { PrimAxleSlipStsAndRelAgFrntAxle, 182, 2, SignalType::E2E_CHKS, PrimAxleSlipStsAndRelAg } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgIntvSts, { PrimAxleSlipStsAndRelAgIntvSts, 222, 12, SignalType::APP_UNSIGNED, PrimAxleSlipStsAndRelAg } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgReAxle, { PrimAxleSlipStsAndRelAgReAxle, 180, 2, SignalType::APP_UNSIGNED, PrimAxleSlipStsAndRelAg } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgRelPitch, { PrimAxleSlipStsAndRelAgRelPitch, 176, 16, SignalType::APP_SIGNED, PrimAxleSlipStsAndRelAg } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgRelPitchQ, { PrimAxleSlipStsAndRelAgRelPitchQ, 178, 2, SignalType::APP_UNSIGNED, PrimAxleSlipStsAndRelAg } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgRelRoll, { PrimAxleSlipStsAndRelAgRelRoll, 191, 16, SignalType::APP_SIGNED, PrimAxleSlipStsAndRelAg } });
    signals_info.insert({ PrimAxleSlipStsAndRelAgRelRolQf, { PrimAxleSlipStsAndRelAgRelRolQf, 176, 2, SignalType::APP_UNSIGNED, PrimAxleSlipStsAndRelAg } });
    signals_info.insert({ PrimVLatSafe_UB, { PrimVLatSafe_UB, 396, 1, SignalType::APP_UNSIGNED, SSMMid5CanFdFr03 } });
    signals_info.insert({ PrimVLatSafeChks, { PrimVLatSafeChks, 408, 8, SignalType::E2E_CHKS, PrimVLatSafe } });
    signals_info.insert({ PrimVLatSafeCntr, { PrimVLatSafeCntr, 392, 4, SignalType::E2E_CNTR, PrimVLatSafe } });
    signals_info.insert({ PrimVLatSafeMax, { PrimVLatSafeMax, 408, 15, SignalType::APP_SIGNED, PrimVLatSafe } });
    signals_info.insert({ PrimVLatSafeMin, { PrimVLatSafeMin, 424, 15, SignalType::APP_SIGNED, PrimVLatSafe } });
    signals_info.insert({ PrimVLatSafeMinMaxQf, { PrimVLatSafeMinMaxQf, 401, 2, SignalType::APP_UNSIGNED, PrimVLatSafe } });
    signals_info.insert({ PrimVLatSafeNom, { PrimVLatSafeNom, 440, 15, SignalType::APP_SIGNED, PrimVLatSafe } });
    signals_info.insert({ PrimVLatSafeNomQf, { PrimVLatSafeNomQf, 403, 2, SignalType::APP_UNSIGNED, PrimVLatSafe } });
    signals_info.insert({ PrimWhlRotDirReSafe1_UB, { PrimWhlRotDirReSafe1_UB, 300, 1, SignalType::APP_UNSIGNED, SSMMid5CanFdFr03 } });
    signals_info.insert({ PrimWhlRotDirReSafe1Chks, { PrimWhlRotDirReSafe1Chks, 312, 8, SignalType::E2E_CHKS, PrimWhlRotDirReSafe1 } });
    signals_info.insert({ PrimWhlRotDirReSafe1Cntr, { PrimWhlRotDirReSafe1Cntr, 296, 4, SignalType::E2E_CNTR, PrimWhlRotDirReSafe1 } });
    signals_info.insert({ PrimWhlRotDirReSafe1Le, { PrimWhlRotDirReSafe1Le, 310, 2, SignalType::APP_UNSIGNED, PrimWhlRotDirReSafe1 } });
    signals_info.insert({ PrimWhlRotDirReSafe1LeQf, { PrimWhlRotDirReSafe1LeQf, 308, 2, SignalType::APP_UNSIGNED, PrimWhlRotDirReSafe1 } });
    signals_info.insert({ PrimWhlRotDirReSafe1Ri, { PrimWhlRotDirReSafe1Ri, 306, 2, SignalType::APP_UNSIGNED, PrimWhlRotDirReSafe1 } });
    signals_info.insert({ PrimWhlRotDirReSafe1RiQf, { PrimWhlRotDirReSafe1RiQf, 304, 2, SignalType::APP_UNSIGNED, PrimWhlRotDirReSafe1 } });
    signals_info.insert({ PrimWhlRotToothCntr_UB, { PrimWhlRotToothCntr_UB, 301, 1, SignalType::APP_UNSIGNED, SSMMid5CanFdFr03 } });
    signals_info.insert({ PrimWhlRotToothCntrChks, { PrimWhlRotToothCntrChks, 328, 8, SignalType::E2E_CHKS, PrimWhlRotToothCntr } });
    signals_info.insert({ PrimWhlRotToothCntrCntr, { PrimWhlRotToothCntrCntr, 320, 4, SignalType::E2E_CNTR, PrimWhlRotToothCntr } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotToothCn, { PrimWhlRotToothCntrWhlRotToothCn, 336, 8, SignalType::APP_UNSIGNED, PrimWhlRotToothCntr } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotTo_0000, { PrimWhlRotToothCntrWhlRotTo_0000, 350, 2, SignalType::APP_UNSIGNED, PrimWhlRotToothCntr } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotTo_0001, { PrimWhlRotToothCntrWhlRotTo_0001, 352, 8, SignalType::APP_UNSIGNED, PrimWhlRotToothCntr } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotTo_0002, { PrimWhlRotToothCntrWhlRotTo_0002, 348, 2, SignalType::APP_UNSIGNED, PrimWhlRotToothCntr } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotTo_0003, { PrimWhlRotToothCntrWhlRotTo_0003, 360, 8, SignalType::APP_UNSIGNED, PrimWhlRotToothCntr } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotTo_0004, { PrimWhlRotToothCntrWhlRotTo_0004, 346, 2, SignalType::APP_UNSIGNED, PrimWhlRotToothCntr } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotTo_0005, { PrimWhlRotToothCntrWhlRotTo_0005, 368, 8, SignalType::APP_UNSIGNED, PrimWhlRotToothCntr } });
    signals_info.insert({ PrimWhlRotToothCntrWhlRotTo_0006, { PrimWhlRotToothCntrWhlRotTo_0006, 344, 2, SignalType::APP_UNSIGNED, PrimWhlRotToothCntr } });
    signals_info.insert({ PrimYawRateSafe_UB, { PrimYawRateSafe_UB, 302, 1, SignalType::APP_UNSIGNED, SSMMid5CanFdFr03 } });
    signals_info.insert({ PrimYawRateSafeChks, { PrimYawRateSafeChks, 232, 8, SignalType::E2E_CHKS, PrimYawRateSafe } });
    signals_info.insert({ PrimYawRateSafeCntr, { PrimYawRateSafeCntr, 216, 4, SignalType::E2E_CNTR, PrimYawRateSafe } });
    signals_info.insert({ PrimYawRateSafeMax, { PrimYawRateSafeMax, 232, 15, SignalType::APP_UNSIGNED, PrimYawRateSafe } });
    signals_info.insert({ PrimYawRateSafeMin, { PrimYawRateSafeMin, 248, 15, SignalType::APP_UNSIGNED, PrimYawRateSafe } });
    signals_info.insert({ PrimYawRateSafeMinMaxQf, { PrimYawRateSafeMinMaxQf, 227, 2, SignalType::APP_UNSIGNED, PrimYawRateSafe } });
    signals_info.insert({ PrimYawRateSafeNom, { PrimYawRateSafeNom, 264, 15, SignalType::APP_UNSIGNED, PrimYawRateSafe } });
    signals_info.insert({ PrimYawRateSafeNomQf, { PrimYawRateSafeNomQf, 224, 2, SignalType::APP_UNSIGNED, PrimYawRateSafe } });

    signalgroups_info.insert(
    {
        AdPrimWhlAgEstimdGroupSafe,
        {
            AdPrimWhlAgEstimdGroupSafe,
            0x1AF,
            {
                AdPrimWhlAgEstimdGroupSafeChks,
                AdPrimWhlAgEstimdGroupSafeCntr,
                AdPrimWhlAgEstimdGroupSafeQf1,
                AdPrimWhlAgEstimdGroupSafeWhlAg,
                AdPrimWhlAgEstimdGroupSafeWhlAgR
            }, 
            { E2EProfileType::P01a, AdPrimWhlAgEstimdGroupSafeChks, AdPrimWhlAgEstimdGroupSafeCntr},
            SSMMid5CanFdFr03
        }
    });

    signalgroups_info.insert(
    {
        PrimALatDataRawSafe,
        {
            PrimALatDataRawSafe,
            0x20E,
            {
                PrimALatDataRawSafeChks,
                PrimALatDataRawSafeCntr,
                PrimALatDataRawSafeMax,
                PrimALatDataRawSafeMin,
                PrimALatDataRawSafeMinMaxQf,
                PrimALatDataRawSafeNom,
                PrimALatDataRawSafeNomQf
            }, 
            { E2EProfileType::P01a, PrimALatDataRawSafeChks, PrimALatDataRawSafeCntr},
            SSMMid5CanFdFr03
        }
    });

    signalgroups_info.insert(
    {
        PrimAxleSlipStsAndRelAg,
        {
            PrimAxleSlipStsAndRelAg,
            0x0,
            {
                PrimAxleSlipStsAndRelAgFrntAxle,
                PrimAxleSlipStsAndRelAgIntvSts,
                PrimAxleSlipStsAndRelAgReAxle,
                PrimAxleSlipStsAndRelAgRelPitch,
                PrimAxleSlipStsAndRelAgRelPitchQ,
                PrimAxleSlipStsAndRelAgRelRoll,
                PrimAxleSlipStsAndRelAgRelRolQf
            }, 
            { E2EProfileType::P05, "", ""},
            SSMMid5CanFdFr03
        }
    });

    signalgroups_info.insert(
    {
        PrimVLatSafe,
        {
            PrimVLatSafe,
            0x505,
            {
                PrimVLatSafeChks,
                PrimVLatSafeCntr,
                PrimVLatSafeMax,
                PrimVLatSafeMin,
                PrimVLatSafeMinMaxQf,
                PrimVLatSafeNom,
                PrimVLatSafeNomQf
            }, 
            { E2EProfileType::P01a, PrimVLatSafeChks, PrimVLatSafeCntr},
            SSMMid5CanFdFr03
        }
    });

    signalgroups_info.insert(
    {
        PrimWhlRotDirReSafe1,
        {
            PrimWhlRotDirReSafe1,
            0x714,
            {
                PrimWhlRotDirReSafe1Chks,
                PrimWhlRotDirReSafe1Cntr,
                PrimWhlRotDirReSafe1Le,
                PrimWhlRotDirReSafe1LeQf,
                PrimWhlRotDirReSafe1Ri,
                PrimWhlRotDirReSafe1RiQf
            }, 
            { E2EProfileType::P01a, PrimWhlRotDirReSafe1Chks, PrimWhlRotDirReSafe1Cntr},
            SSMMid5CanFdFr03
        }
    });

    signalgroups_info.insert(
    {
        PrimWhlRotToothCntr,
        {
            PrimWhlRotToothCntr,
            0x578,
            {
                PrimWhlRotToothCntrChks,
                PrimWhlRotToothCntrCntr,
                PrimWhlRotToothCntrWhlRotToothCn,
                PrimWhlRotToothCntrWhlRotTo_0000,
                PrimWhlRotToothCntrWhlRotTo_0001,
                PrimWhlRotToothCntrWhlRotTo_0002,
                PrimWhlRotToothCntrWhlRotTo_0003,
                PrimWhlRotToothCntrWhlRotTo_0004,
                PrimWhlRotToothCntrWhlRotTo_0005,
                PrimWhlRotToothCntrWhlRotTo_0006
            }, 
            { E2EProfileType::P05, PrimWhlRotToothCntrChks, PrimWhlRotToothCntrCntr},
            SSMMid5CanFdFr03
        }
    });

    signalgroups_info.insert(
    {
        PrimYawRateSafe,
        {
            PrimYawRateSafe,
            0x212,
            {
                PrimYawRateSafeChks,
                PrimYawRateSafeCntr,
                PrimYawRateSafeMax,
                PrimYawRateSafeMin,
                PrimYawRateSafeMinMaxQf,
                PrimYawRateSafeNom,
                PrimYawRateSafeNomQf
            }, 
            { E2EProfileType::P01a, PrimYawRateSafeChks, PrimYawRateSafeCntr},
            SSMMid5CanFdFr03
        }
    });

    frames_info.insert({ SSMMid5CanFdFr03, { SSMMid5CanFdFr03, 32, 64, 0, { AdPrimWhlAgEstimdGroupSafe, PrimALatDataRawSafe, PrimAxleSlipStsAndRelAg, PrimVLatSafe, PrimWhlRotDirReSafe1, PrimWhlRotToothCntr, PrimYawRateSafe }, { AdPrimWhlAgEstimdGroupSafe_UB, PrimALatDataRawSafe_UB, PrimAxleSlipStsAndRelAg_UB, PrimVLatSafe_UB, PrimWhlRotDirReSafe1_UB, PrimWhlRotToothCntr_UB, PrimYawRateSafe_UB } } });

    frame_ids.insert({ 32, SSMMid5CanFdFr03 });
}


}
}