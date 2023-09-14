#include "VIMBMid6CanFdFr01.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr01_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecSafeStopReqSafeChks, { AdSecSafeStopReqSafeChks, 8, 8, SignalType::E2E_CHKS, 0, AdSecSafeStopReqSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecSafeStopReqSafeCntr, { AdSecSafeStopReqSafeCntr, 0, 4, SignalType::E2E_CNTR, 0, AdSecSafeStopReqSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecSafeStopReqSafeSafeStopReq, { AdSecSafeStopReqSafeSafeStopReq, 4, 1, SignalType::APP_UNSIGNED, 0, AdSecSafeStopReqSafe, ParentType::GROUP } });
    signals_info.insert({ SDSFltMgrStsRdntChks, { SDSFltMgrStsRdntChks, 24, 8, SignalType::E2E_CHKS, 0, SDSFltMgrStsRdnt, ParentType::GROUP } });
    signals_info.insert({ SDSFltMgrStsRdntCntr, { SDSFltMgrStsRdntCntr, 16, 4, SignalType::E2E_CNTR, 0, SDSFltMgrStsRdnt, ParentType::GROUP } });
    signals_info.insert({ SDSFltMgrStsRdntSDSFltMgrStsRdnt, { SDSFltMgrStsRdntSDSFltMgrStsRdnt, 20, 4, SignalType::APP_UNSIGNED, 0, SDSFltMgrStsRdnt, ParentType::GROUP } });
    signals_info.insert({ SDSFltMgrStsRdnt_UB, { SDSFltMgrStsRdnt_UB, 6, 1, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr01, ParentType::FRAME } });
    signals_info.insert({ AdSecSafeStopReqSafe_UB, { AdSecSafeStopReqSafe_UB, 5, 1, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr01, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecSafeStopReqSafe, { AdSecSafeStopReqSafe, 0x203, { AdSecSafeStopReqSafeChks, AdSecSafeStopReqSafeCntr, AdSecSafeStopReqSafeSafeStopReq }, { E2EProfileType::P01a, AdSecSafeStopReqSafeChks, AdSecSafeStopReqSafeCntr }, VIMBMid6CanFdFr01 } } );
    signalgroups_info.insert({ SDSFltMgrStsRdnt, { SDSFltMgrStsRdnt, 0x735, { SDSFltMgrStsRdntChks, SDSFltMgrStsRdntCntr, SDSFltMgrStsRdntSDSFltMgrStsRdnt }, { E2EProfileType::P01a, SDSFltMgrStsRdntChks, SDSFltMgrStsRdntCntr }, VIMBMid6CanFdFr01 } } );

    frames_info.insert({ VIMBMid6CanFdFr01, { VIMBMid6CanFdFr01, 256, 8, 65, { AdSecSafeStopReqSafe, SDSFltMgrStsRdnt }, { SDSFltMgrStsRdnt_UB, AdSecSafeStopReqSafe_UB } } });

    frame_ids.insert({ 256, VIMBMid6CanFdFr01 });
}


}
}
