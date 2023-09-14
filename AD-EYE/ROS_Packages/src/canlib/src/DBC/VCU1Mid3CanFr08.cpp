#include "VCU1Mid3CanFr08.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr08_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AgDataRawSafeChks, { AgDataRawSafeChks, 32, 8, SignalType::E2E_CHKS, 255, AgDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ AgDataRawSafeCntr, { AgDataRawSafeCntr, 44, 4, SignalType::E2E_CNTR, 0, AgDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ RollRate1, { RollRate1, 8, 16, SignalType::APP_SIGNED, 0, AgDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ RollRate1Qf1, { RollRate1Qf1, 42, 2, SignalType::APP_UNSIGNED, 1, AgDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ YawRate1, { YawRate1, 24, 16, SignalType::APP_SIGNED, 0, AgDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ YawRate1Qf1, { YawRate1Qf1, 40, 2, SignalType::APP_UNSIGNED, 1, AgDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ ClstrSts1ForAutnmsDrvClstr1Chks, { ClstrSts1ForAutnmsDrvClstr1Chks, 56, 8, SignalType::E2E_CHKS, 0, ClstrSts1ForAutnmsDrv, ParentType::GROUP } });
    signals_info.insert({ ClstrSts1ForAutnmsDrvClstr1Cnt, { ClstrSts1ForAutnmsDrvClstr1Cnt, 48, 4, SignalType::E2E_CNTR, 0, ClstrSts1ForAutnmsDrv, ParentType::GROUP } });
    signals_info.insert({ ClstrSts1ForAutnmsDrvClstr1Sts, { ClstrSts1ForAutnmsDrvClstr1Sts, 52, 2, SignalType::APP_UNSIGNED, 0, ClstrSts1ForAutnmsDrv, ParentType::GROUP } });
    signals_info.insert({ ClstrSts1ForAutnmsDrv_UB, { ClstrSts1ForAutnmsDrv_UB, 54, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr08, ParentType::FRAME } });
    signals_info.insert({ AgDataRawSafe_UB, { AgDataRawSafe_UB, 55, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr08, ParentType::FRAME } });

    signalgroups_info.insert({ AgDataRawSafe, { AgDataRawSafe, 0x23, { AgDataRawSafeChks, AgDataRawSafeCntr, RollRate1, RollRate1Qf1, YawRate1, YawRate1Qf1 }, { E2EProfileType::P01a, AgDataRawSafeChks, AgDataRawSafeCntr }, VCU1Mid3CanFr08 } } );
    signalgroups_info.insert({ ClstrSts1ForAutnmsDrv, { ClstrSts1ForAutnmsDrv, 0x258, { ClstrSts1ForAutnmsDrvClstr1Chks, ClstrSts1ForAutnmsDrvClstr1Cnt, ClstrSts1ForAutnmsDrvClstr1Sts }, { E2EProfileType::P01a, ClstrSts1ForAutnmsDrvClstr1Chks, ClstrSts1ForAutnmsDrvClstr1Cnt }, VCU1Mid3CanFr08 } } );

    frames_info.insert({ VCU1Mid3CanFr08, { VCU1Mid3CanFr08, 57, 8, 10, { AgDataRawSafe, ClstrSts1ForAutnmsDrv }, { ClstrSts1ForAutnmsDrv_UB, AgDataRawSafe_UB } } });

   frame_ids.insert({ 57, VCU1Mid3CanFr08 });
}


}
}
