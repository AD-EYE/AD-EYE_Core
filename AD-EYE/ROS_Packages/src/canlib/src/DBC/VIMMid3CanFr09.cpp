#include "VIMMid3CanFr09.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr09_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdDirReqChks, { AdDirReqChks, 16, 8, SignalType::E2E_CHKS, 0, AdDirReq, ParentType::GROUP } });
    signals_info.insert({ AdDirReqCntr, { AdDirReqCntr, 8, 4, SignalType::E2E_CNTR, 0, AdDirReq, ParentType::GROUP } });
    signals_info.insert({ AdDirReqDirReq, { AdDirReqDirReq, 12, 2, SignalType::APP_UNSIGNED, 0, AdDirReq, ParentType::GROUP } });
    signals_info.insert({ AdStandStillReqChks, { AdStandStillReqChks, 32, 8, SignalType::E2E_CHKS, 0, AdStandStillReq, ParentType::GROUP } });
    signals_info.insert({ AdStandStillReqCntr, { AdStandStillReqCntr, 24, 4, SignalType::E2E_CNTR, 0, AdStandStillReq, ParentType::GROUP } });
    signals_info.insert({ AdStandStillReqReq, { AdStandStillReqReq, 28, 2, SignalType::APP_UNSIGNED, 0, AdStandStillReq, ParentType::GROUP } });
    signals_info.insert({ VehUsgStReq_UB, { VehUsgStReq_UB, 4, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr09, ParentType::FRAME } });
    signals_info.insert({ AdDirReq_UB, { AdDirReq_UB, 14, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr09, ParentType::FRAME } });
    signals_info.insert({ AdStandStillReq_UB, { AdStandStillReq_UB, 15, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr09, ParentType::FRAME } });
    signals_info.insert({ VehUsgStReq, { VehUsgStReq, 0, 4, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr09, ParentType::FRAME } });

    signalgroups_info.insert({ AdDirReq, { AdDirReq, 0x1C4, { AdDirReqChks, AdDirReqCntr, AdDirReqDirReq }, { E2EProfileType::P01a, AdDirReqChks, AdDirReqCntr }, VIMMid3CanFr09 } } );
    signalgroups_info.insert({ AdStandStillReq, { AdStandStillReq, 0x557, { AdStandStillReqChks, AdStandStillReqCntr, AdStandStillReqReq }, { E2EProfileType::P01a, AdStandStillReqChks, AdStandStillReqCntr }, VIMMid3CanFr09 } } );

    frames_info.insert({ VIMMid3CanFr09, { VIMMid3CanFr09, 135, 8, 30, { AdDirReq, AdStandStillReq }, { VehUsgStReq_UB, AdDirReq_UB, AdStandStillReq_UB, VehUsgStReq } } });

    frame_ids.insert({ 135, VIMMid3CanFr09 });
}


}
}
