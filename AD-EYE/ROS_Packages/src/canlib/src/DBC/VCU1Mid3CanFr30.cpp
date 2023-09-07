#include "VCU1Mid3CanFr30.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr30_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AutnmsDrvModMngtExtSafe_UB, { AutnmsDrvModMngtExtSafe_UB, 6, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr30 } });
    signals_info.insert({ AutnmsDrvModMngtExtSafeAutnmsDrvModSts1, { AutnmsDrvModMngtExtSafeAutnmsDrvModSts1, 56, 2, SignalType::APP_UNSIGNED, AutnmsDrvModMngtExtSafe } });
    signals_info.insert({ AutnmsDrvModMngtExtSafeChecksum, { AutnmsDrvModMngtExtSafeChecksum, 40, 8, SignalType::E2E_CHKS, AutnmsDrvModMngtExtSafe } });
    signals_info.insert({ AutnmsDrvModMngtExtSafeCounter, { AutnmsDrvModMngtExtSafeCounter, 48, 4, SignalType::E2E_CNTR, AutnmsDrvModMngtExtSafe } });
    signals_info.insert({ AutnmsDrvModMngtExtSafeVehOperModSts1, { AutnmsDrvModMngtExtSafeVehOperModSts1, 58, 2, SignalType::APP_UNSIGNED, AutnmsDrvModMngtExtSafe } });
    signals_info.insert({ BrkDegraded_UB, { BrkDegraded_UB, 4, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr30 } });
    signals_info.insert({ BrkDegradedChks, { BrkDegradedChks, 8, 8, SignalType::E2E_CHKS, BrkDegraded } });
    signals_info.insert({ BrkDegradedCntr, { BrkDegradedCntr, 0, 4, SignalType::E2E_CNTR, BrkDegraded } });
    signals_info.insert({ BrkDegradedSts, { BrkDegradedSts, 8, 16, SignalType::APP_UNSIGNED, BrkDegraded } });
    signals_info.insert({ VehManDeactvnReqInProgs1, { VehManDeactvnReqInProgs1, 32, 2, SignalType::APP_UNSIGNED, VCU1Mid3CanFr30 } });
    signals_info.insert({ VehManDeactvnReqInProgs1_UB, { VehManDeactvnReqInProgs1_UB, 34, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr30 } });
    signals_info.insert({ VehUsgSt, { VehUsgSt, 36, 4, SignalType::APP_UNSIGNED, VCU1Mid3CanFr30 } });
    signals_info.insert({ VehUsgSt_UB, { VehUsgSt_UB, 5, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr30 } });
   

    signalgroups_info.insert(
    {
        AutnmsDrvModMngtExtSafe,
        {
            AutnmsDrvModMngtExtSafe,
            0x2AD,
            {
                AutnmsDrvModMngtExtSafeAutnmsDrvModSts1,
                AutnmsDrvModMngtExtSafeChecksum,
                AutnmsDrvModMngtExtSafeCounter,
                AutnmsDrvModMngtExtSafeVehOperModSts1
            }, 
            E2EProfileType::None,
            VCU1Mid3CanFr30
        }
    });

    signalgroups_info.insert(
    {
        BrkDegraded,
        {
            BrkDegraded,
            0x1CB,
            {
                BrkDegradedChks,
                BrkDegradedCntr,
                BrkDegradedSts
            }, 
            {E2EProfileType::P01a, BrkDegradedChks, BrkDegradedCntr },
            VCU1Mid3CanFr30
        }
    });

    frames_info.insert({ VCU1Mid3CanFr30, { VCU1Mid3CanFr30, 83, 8, 15, { AutnmsDrvModMngtExtSafe, BrkDegraded }, { AutnmsDrvModMngtExtSafe_UB, BrkDegraded_UB, VehManDeactvnReqInProgs1, VehManDeactvnReqInProgs1_UB, VehUsgSt, VehUsgSt_UB } } });

    frame_ids.insert({ 83, VCU1Mid3CanFr30 });
}


}
}