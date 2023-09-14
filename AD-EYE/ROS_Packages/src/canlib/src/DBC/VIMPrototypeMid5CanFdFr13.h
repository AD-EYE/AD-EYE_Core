#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMPrototypeMid5CanFdFr13_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMPrototypeMid5CanFdFr13 { "VIMPrototypeMid5CanFdFr13" };


// Groups
const std::string PrimMonTiSyncMsg { "PrimMonTiSyncMsg" };


// Signals
const std::string PrimMonTiSyncMsgTiStampNanoSec { "PrimMonTiSyncMsgTiStampNanoSec" };
const std::string PrimMonTiSyncMsgTiStampSec { "PrimMonTiSyncMsgTiStampSec" };
const std::string PrimMonTiSyncMsgChks { "PrimMonTiSyncMsgChks" };
const std::string PrimMonTiSyncMsgCntr { "PrimMonTiSyncMsgCntr" };
const std::string PrimMonTiSyncMsg_UB { "PrimMonTiSyncMsg_UB" };


}
}
