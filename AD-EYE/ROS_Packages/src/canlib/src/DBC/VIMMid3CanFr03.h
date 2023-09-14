#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid3CanFr03_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr03 { "VIMMid3CanFr03" };


// Groups


// Signals
const std::string PwrDoorPassClsReqAPI_UB { "PwrDoorPassClsReqAPI_UB" };
const std::string PwrDoorPassClsReqAPI { "PwrDoorPassClsReqAPI" };
const std::string PwrDoorDrvrClsReqAPI_UB { "PwrDoorDrvrClsReqAPI_UB" };
const std::string PwrDoorDrvrClsReqAPI { "PwrDoorDrvrClsReqAPI" };
const std::string PwrDoorPassReClsReqAPI_UB { "PwrDoorPassReClsReqAPI_UB" };
const std::string PwrDoorPassReClsReqAPI { "PwrDoorPassReClsReqAPI" };
const std::string PwrDoorDrvrReClsReqAPI_UB { "PwrDoorDrvrReClsReqAPI_UB" };
const std::string PwrDoorDrvrReClsReqAPI { "PwrDoorDrvrReClsReqAPI" };


}
}
