#include "VIMPrototypeMid5CanFdFr13.h"


namespace kcan {
namespace dbc {


void VIMPrototypeMid5CanFdFr13_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ PrimMonTiSyncMsgChks, { PrimMonTiSyncMsgChks, 64, 8, true, SignalType::E2E_CHKS, 0, PrimMonTiSyncMsg, ParentType::GROUP } });
    signals_info.insert({ PrimMonTiSyncMsgCntr, { PrimMonTiSyncMsgCntr, 76, 4, true, SignalType::E2E_CNTR, 0, PrimMonTiSyncMsg, ParentType::GROUP } });
    signals_info.insert({ PrimMonTiSyncMsgTiStampNanoSec, { PrimMonTiSyncMsgTiStampNanoSec, 24, 32, true, SignalType::APP_UNSIGNED, 0, PrimMonTiSyncMsg, ParentType::GROUP } });
    signals_info.insert({ PrimMonTiSyncMsgTiStampSec, { PrimMonTiSyncMsgTiStampSec, 8, 32, true, SignalType::APP_UNSIGNED, 0, PrimMonTiSyncMsg, ParentType::GROUP } });
    signals_info.insert({ PrimMonTiSyncMsg_UB, { PrimMonTiSyncMsg_UB, 75, 1, true, SignalType::APP_UNSIGNED, 0, VIMPrototypeMid5CanFdFr13, ParentType::FRAME } });

    signalgroups_info.insert({ PrimMonTiSyncMsg, { PrimMonTiSyncMsg, 0x71C, { PrimMonTiSyncMsgChks, PrimMonTiSyncMsgCntr, PrimMonTiSyncMsgTiStampNanoSec, PrimMonTiSyncMsgTiStampSec }, { E2EProfileType::P01a, PrimMonTiSyncMsgChks, PrimMonTiSyncMsgCntr }, VIMPrototypeMid5CanFdFr13 } } );

    frames_info.insert({ VIMPrototypeMid5CanFdFr13, { VIMPrototypeMid5CanFdFr13, 40, 12, 0xFFFFFFFF, { PrimMonTiSyncMsg }, { PrimMonTiSyncMsg_UB } } });

    frame_ids.insert({ 40, VIMPrototypeMid5CanFdFr13 });
}


}
}
