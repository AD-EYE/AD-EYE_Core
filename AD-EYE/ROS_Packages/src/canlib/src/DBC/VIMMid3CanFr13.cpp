#include "VIMMid3CanFr13.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr13_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdFreeDstChks, { AdFreeDstChks, 24, 8, SignalType::E2E_CHKS, 0, AdFreeDst, ParentType::GROUP } });
    signals_info.insert({ AdFreeDstCntr, { AdFreeDstCntr, 16, 4, SignalType::E2E_CNTR, 0, AdFreeDst, ParentType::GROUP } });
    signals_info.insert({ AdFreeDstFreeDstFwd, { AdFreeDstFreeDstFwd, 32, 8, SignalType::APP_UNSIGNED, 0, AdFreeDst, ParentType::GROUP } });
    signals_info.insert({ AdFreeDstFreeDstRvs, { AdFreeDstFreeDstRvs, 40, 8, SignalType::APP_UNSIGNED, 0, AdFreeDst, ParentType::GROUP } });
    signals_info.insert({ AdWhlLockReqChks, { AdWhlLockReqChks, 56, 8, SignalType::E2E_CHKS, 0, AdWhlLockReq, ParentType::GROUP } });
    signals_info.insert({ AdWhlLockReqCntr, { AdWhlLockReqCntr, 48, 4, SignalType::E2E_CNTR, 0, AdWhlLockReq, ParentType::GROUP } });
    signals_info.insert({ AdWhlLockReqNoReqApplyRel, { AdWhlLockReqNoReqApplyRel, 52, 2, SignalType::APP_UNSIGNED, 0, AdWhlLockReq, ParentType::GROUP } });
    signals_info.insert({ AdWhlLockReq_UB, { AdWhlLockReq_UB, 54, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr13, ParentType::FRAME } });
    signals_info.insert({ AdFreeDst_UB, { AdFreeDst_UB, 3, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr13, ParentType::FRAME } });
    signals_info.insert({ AdSetSpd_UB, { AdSetSpd_UB, 2, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr13, ParentType::FRAME } });
    signals_info.insert({ AdSetSpd, { AdSetSpd, 8, 10, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr13, ParentType::FRAME } });

    signalgroups_info.insert({ AdFreeDst, { AdFreeDst, 0x1C7, { AdFreeDstChks, AdFreeDstCntr, AdFreeDstFreeDstFwd, AdFreeDstFreeDstRvs }, { E2EProfileType::P01a, AdFreeDstChks, AdFreeDstCntr }, VIMMid3CanFr13 } } );
    signalgroups_info.insert({ AdWhlLockReq, { AdWhlLockReq, 0x647, { AdWhlLockReqChks, AdWhlLockReqCntr, AdWhlLockReqNoReqApplyRel }, { E2EProfileType::P01a, AdWhlLockReqChks, AdWhlLockReqCntr }, VIMMid3CanFr13 } } );

    frames_info.insert({ VIMMid3CanFr13, { VIMMid3CanFr13, 150, 8, 80, { AdFreeDst, AdWhlLockReq }, { AdWhlLockReq_UB, AdFreeDst_UB, AdSetSpd_UB, AdSetSpd } } });

    frame_ids.insert({ 150, VIMMid3CanFr13 });
}


}
}
