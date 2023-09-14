#include "VIMMid5CanFdFr13.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr13_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimSafeStopReqSafeChks, { AdPrimSafeStopReqSafeChks, 8, 8, SignalType::E2E_CHKS, 0, AdPrimSafeStopReqSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimSafeStopReqSafeCntr, { AdPrimSafeStopReqSafeCntr, 0, 4, SignalType::E2E_CNTR, 0, AdPrimSafeStopReqSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimSafeStopReqSafeSafeStopReq, { AdPrimSafeStopReqSafeSafeStopReq, 4, 1, SignalType::APP_UNSIGNED, 0, AdPrimSafeStopReqSafe, ParentType::GROUP } });
    signals_info.insert({ SDSFltMgrStsSafeChks, { SDSFltMgrStsSafeChks, 24, 8, SignalType::E2E_CHKS, 0, SDSFltMgrStsSafe, ParentType::GROUP } });
    signals_info.insert({ SDSFltMgrStsSafeCntr, { SDSFltMgrStsSafeCntr, 16, 4, SignalType::E2E_CNTR, 0, SDSFltMgrStsSafe, ParentType::GROUP } });
    signals_info.insert({ SDSFltMgrStsSafeSDSFltMgrSts, { SDSFltMgrStsSafeSDSFltMgrSts, 20, 4, SignalType::APP_UNSIGNED, 0, SDSFltMgrStsSafe, ParentType::GROUP } });
    signals_info.insert({ SDSFltMgrStsSafe_UB, { SDSFltMgrStsSafe_UB, 6, 1, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr13, ParentType::FRAME } });
    signals_info.insert({ AdPrimSafeStopReqSafe_UB, { AdPrimSafeStopReqSafe_UB, 5, 1, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr13, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimSafeStopReqSafe, { AdPrimSafeStopReqSafe, 0x202, { AdPrimSafeStopReqSafeChks, AdPrimSafeStopReqSafeCntr, AdPrimSafeStopReqSafeSafeStopReq }, { E2EProfileType::P01a, AdPrimSafeStopReqSafeChks, AdPrimSafeStopReqSafeCntr }, VIMMid5CanFdFr13 } } );
    signalgroups_info.insert({ SDSFltMgrStsSafe, { SDSFltMgrStsSafe, 0x746, { SDSFltMgrStsSafeChks, SDSFltMgrStsSafeCntr, SDSFltMgrStsSafeSDSFltMgrSts }, { E2EProfileType::P01a, SDSFltMgrStsSafeChks, SDSFltMgrStsSafeCntr }, VIMMid5CanFdFr13 } } );

    frames_info.insert({ VIMMid5CanFdFr13, { VIMMid5CanFdFr13, 60, 8, 60, { AdPrimSafeStopReqSafe, SDSFltMgrStsSafe }, { SDSFltMgrStsSafe_UB, AdPrimSafeStopReqSafe_UB } } });

    frame_ids.insert({ 60, VIMMid5CanFdFr13 });
}


}
}
