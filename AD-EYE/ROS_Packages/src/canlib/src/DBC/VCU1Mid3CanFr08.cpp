#include "VCU1Mid3CanFr08.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr08_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AgDataRawSafe_UB, { AgDataRawSafe_UB, 55, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr08 } });
    signals_info.insert({ AgDataRawSafeChks, { AgDataRawSafeChks, 42, 8, SignalType::E2E_CHKS, AgDataRawSafe } });
    signals_info.insert({ AgDataRawSafeCntr, { AgDataRawSafeCntr, 44, 4, SignalType::E2E_CNTR, AgDataRawSafe } });
    signals_info.insert({ ClstrSts1ForAutnmsDrv_UB, { ClstrSts1ForAutnmsDrv_UB, 54, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr08 } });
    signals_info.insert({ ClstrSts1ForAutnmsDrvClstr1Chks, { ClstrSts1ForAutnmsDrvClstr1Chks, 56, 8, SignalType::E2E_CHKS, ClstrSts1ForAutnmsDrv } });
    signals_info.insert({ ClstrSts1ForAutnmsDrvClstr1Cnt, { ClstrSts1ForAutnmsDrvClstr1Cnt, 48, 4, SignalType::E2E_CNTR, ClstrSts1ForAutnmsDrv } });
    signals_info.insert({ ClstrSts1ForAutnmsDrvClstr1Sts, { ClstrSts1ForAutnmsDrvClstr1Sts, 52, 2, SignalType::APP_UNSIGNED, ClstrSts1ForAutnmsDrv } });
    signals_info.insert({ RollRate1, { RollRate1, 8, 16, SignalType::APP_SIGNED, AgDataRawSafe } });
    signals_info.insert({ RollRate1Qf1, { RollRate1Qf1, 42, 2, SignalType::APP_UNSIGNED, AgDataRawSafe } });
    signals_info.insert({ YawRate1, { YawRate1, 8, 16, SignalType::APP_SIGNED, AgDataRawSafe } });
    signals_info.insert({ YawRate1Qf1, { YawRate1Qf1, 40, 2, SignalType::APP_UNSIGNED, AgDataRawSafe } });
    
    signalgroups_info.insert(
    {
        AgDataRawSafe,
        {
            AgDataRawSafe,
            0x23,
            {
                AgDataRawSafeChks,
                AgDataRawSafeCntr,
                RollRate1,
                RollRate1Qf1,
                YawRate1,
                YawRate1Qf1
            }, 
            E2EProfileType::None,
            VCU1Mid3CanFr08
        }
    });

    signalgroups_info.insert(
    {
        ClstrSts1ForAutnmsDrv,
        {
            ClstrSts1ForAutnmsDrv,
            0x258,
            {
                ClstrSts1ForAutnmsDrvClstr1Chks,
                ClstrSts1ForAutnmsDrvClstr1Cnt,
                ClstrSts1ForAutnmsDrvClstr1Sts
            }, 
            { E2EProfileType::P01a, ClstrSts1ForAutnmsDrvClstr1Chks, ClstrSts1ForAutnmsDrvClstr1Cnt },
            VCU1Mid3CanFr08
        }
    });


    frames_info.insert({ VCU1Mid3CanFr08, { VCU1Mid3CanFr08, 57, 8, 10, { AgDataRawSafe, ClstrSts1ForAutnmsDrv }, { AgDataRawSafe_UB, ClstrSts1ForAutnmsDrv_UB } } });

    frame_ids.insert({ 57, VCU1Mid3CanFr08 });
}


}
}