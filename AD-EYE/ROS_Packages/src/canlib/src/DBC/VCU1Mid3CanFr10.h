#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr10_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr10 { "VCU1Mid3CanFr10" };


// Groups
const std::string DoorDrvrPosnStsToAPI { "DoorDrvrPosnStsToAPI" };
const std::string DoorDrvrRePosnStsToAPI { "DoorDrvrRePosnStsToAPI" };
const std::string DoorPassPosnStsToAPI { "DoorPassPosnStsToAPI" };
const std::string WiprLvrStsIf { "WiprLvrStsIf" };


// Signals
const std::string DoorDrvrPosnStsToAPIDrvrDoorPosnSts { "DoorDrvrPosnStsToAPIDrvrDoorPosnSts" };
const std::string DoorDrvrPosnStsToAPIDrvrDoorPosnStsCntr { "DoorDrvrPosnStsToAPIDrvrDoorPosnStsCntr" };
const std::string DoorDrvrPosnStsToAPIDrvrDoorPosnStsChks { "DoorDrvrPosnStsToAPIDrvrDoorPosnStsChks" };
const std::string DoorDrvrPosnStsToAPI_UB { "DoorDrvrPosnStsToAPI_UB" };
const std::string DoorDrvrRePosnStsToAPI_UB { "DoorDrvrRePosnStsToAPI_UB" };
const std::string DoorPassPosnStsToAPI_UB { "DoorPassPosnStsToAPI_UB" };
const std::string WiprLvrStsIfWiprFrntSts { "WiprLvrStsIfWiprFrntSts" };
const std::string WiprLvrStsIfWiprReSts { "WiprLvrStsIfWiprReSts" };
const std::string DoorDrvrRePosnStsToAPIDrvrReDoorPosnSts { "DoorDrvrRePosnStsToAPIDrvrReDoorPosnSts" };
const std::string DoorDrvrRePosnStsToAPIDrvrReDoorPosnStsCntr { "DoorDrvrRePosnStsToAPIDrvrReDoorPosnStsCntr" };
const std::string DoorDrvrRePosnStsToAPIDrvrReDoorPosnStsChks { "DoorDrvrRePosnStsToAPIDrvrReDoorPosnStsChks" };
const std::string DoorPassPosnStsToAPIPassDoorPosnSts { "DoorPassPosnStsToAPIPassDoorPosnSts" };
const std::string DoorPassPosnStsToAPIPassDoorPosnStsCntr { "DoorPassPosnStsToAPIPassDoorPosnStsCntr" };
const std::string DoorPassPosnStsToAPIPassDoorPosnStsChks { "DoorPassPosnStsToAPIPassDoorPosnStsChks" };
const std::string WiprLvrStsIf_UB { "WiprLvrStsIf_UB" };
const std::string EngCooltIndcnReqForExt_UB { "EngCooltIndcnReqForExt_UB" };
const std::string EngCooltIndcnReqForExt { "EngCooltIndcnReqForExt" };


}
}
