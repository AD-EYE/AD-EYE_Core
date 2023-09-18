#include "VCU1Mid3CanFr30.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr30_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AutnmsDrvModMngtExtSafeAutnmsDrvModSts1, { AutnmsDrvModMngtExtSafeAutnmsDrvModSts1, 56, 2, false, SignalType::APP_UNSIGNED, 0, AutnmsDrvModMngtExtSafe, ParentType::GROUP } });
    signals_info.insert({ AutnmsDrvModMngtExtSafeChecksum, { AutnmsDrvModMngtExtSafeChecksum, 40, 8, false, SignalType::E2E_CHKS, 0, AutnmsDrvModMngtExtSafe, ParentType::GROUP } });
    signals_info.insert({ AutnmsDrvModMngtExtSafeCounter, { AutnmsDrvModMngtExtSafeCounter, 48, 4, false, SignalType::E2E_CNTR, 0, AutnmsDrvModMngtExtSafe, ParentType::GROUP } });
    signals_info.insert({ AutnmsDrvModMngtExtSafeVehOperModSts1, { AutnmsDrvModMngtExtSafeVehOperModSts1, 58, 2, false, SignalType::APP_UNSIGNED, 0, AutnmsDrvModMngtExtSafe, ParentType::GROUP } });
    signals_info.insert({ BrkDegradedChks, { BrkDegradedChks, 8, 8, true, SignalType::E2E_CHKS, 0, BrkDegraded, ParentType::GROUP } });
    signals_info.insert({ BrkDegradedCntr, { BrkDegradedCntr, 0, 4, true, SignalType::E2E_CNTR, 0, BrkDegraded, ParentType::GROUP } });
    signals_info.insert({ BrkDegradedSts, { BrkDegradedSts, 8, 16, true, SignalType::APP_UNSIGNED, 0, BrkDegraded, ParentType::GROUP } });
    signals_info.insert({ AutnmsDrvModMngtExtSafe_UB, { AutnmsDrvModMngtExtSafe_UB, 6, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr30, ParentType::FRAME } });
    signals_info.insert({ BrkDegraded_UB, { BrkDegraded_UB, 4, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr30, ParentType::FRAME } });
    signals_info.insert({ VehManDeactvnReqInProgs1, { VehManDeactvnReqInProgs1, 32, 2, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr30, ParentType::FRAME } });
    signals_info.insert({ VehManDeactvnReqInProgs1_UB, { VehManDeactvnReqInProgs1_UB, 34, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr30, ParentType::FRAME } });
    signals_info.insert({ VehUsgSt, { VehUsgSt, 36, 4, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr30, ParentType::FRAME } });
    signals_info.insert({ VehUsgSt_UB, { VehUsgSt_UB, 5, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr30, ParentType::FRAME } });

    signalgroups_info.insert({ AutnmsDrvModMngtExtSafe, { AutnmsDrvModMngtExtSafe, 0x2AD, { AutnmsDrvModMngtExtSafeAutnmsDrvModSts1, AutnmsDrvModMngtExtSafeChecksum, AutnmsDrvModMngtExtSafeCounter, AutnmsDrvModMngtExtSafeVehOperModSts1 }, { E2EProfileType::P01a, AutnmsDrvModMngtExtSafeChecksum, AutnmsDrvModMngtExtSafeCounter }, VCU1Mid3CanFr30 } } );
    signalgroups_info.insert({ BrkDegraded, { BrkDegraded, 0x1CB, { BrkDegradedChks, BrkDegradedCntr, BrkDegradedSts }, { E2EProfileType::P01a, BrkDegradedChks, BrkDegradedCntr }, VCU1Mid3CanFr30 } } );

    frames_info.insert({ VCU1Mid3CanFr30, { VCU1Mid3CanFr30, 83, 8, 15, { AutnmsDrvModMngtExtSafe, BrkDegraded }, { VehManDeactvnReqInProgs1_UB, VehUsgSt_UB, VehUsgSt, VehManDeactvnReqInProgs1, AutnmsDrvModMngtExtSafe_UB, BrkDegraded_UB } } });

    frame_ids.insert({ 83, VCU1Mid3CanFr30 });
}


}
}
