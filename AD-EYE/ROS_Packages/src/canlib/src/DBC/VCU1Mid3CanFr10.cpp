#include "VCU1Mid3CanFr10.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr10_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ DoorDrvrPosnStsToAPIDrvrDoorPosnSts, { DoorDrvrPosnStsToAPIDrvrDoorPosnSts, 4, 4, SignalType::APP_UNSIGNED, 0, DoorDrvrPosnStsToAPI, ParentType::GROUP } });
    signals_info.insert({ DoorDrvrPosnStsToAPIDrvrDoorPosnStsChks, { DoorDrvrPosnStsToAPIDrvrDoorPosnStsChks, 8, 8, SignalType::E2E_CHKS, 0, DoorDrvrPosnStsToAPI, ParentType::GROUP } });
    signals_info.insert({ DoorDrvrPosnStsToAPIDrvrDoorPosnStsCntr, { DoorDrvrPosnStsToAPIDrvrDoorPosnStsCntr, 0, 4, SignalType::E2E_CNTR, 0, DoorDrvrPosnStsToAPI, ParentType::GROUP } });
    signals_info.insert({ DoorDrvrRePosnStsToAPIDrvrReDoorPosnSts, { DoorDrvrRePosnStsToAPIDrvrReDoorPosnSts, 28, 4, SignalType::APP_UNSIGNED, 0, DoorDrvrRePosnStsToAPI, ParentType::GROUP } });
    signals_info.insert({ DoorDrvrRePosnStsToAPIDrvrReDoorPosnStsChks, { DoorDrvrRePosnStsToAPIDrvrReDoorPosnStsChks, 32, 8, SignalType::E2E_CHKS, 0, DoorDrvrRePosnStsToAPI, ParentType::GROUP } });
    signals_info.insert({ DoorDrvrRePosnStsToAPIDrvrReDoorPosnStsCntr, { DoorDrvrRePosnStsToAPIDrvrReDoorPosnStsCntr, 24, 4, SignalType::E2E_CNTR, 0, DoorDrvrRePosnStsToAPI, ParentType::GROUP } });
    signals_info.insert({ DoorPassPosnStsToAPIPassDoorPosnSts, { DoorPassPosnStsToAPIPassDoorPosnSts, 44, 4, SignalType::APP_UNSIGNED, 0, DoorPassPosnStsToAPI, ParentType::GROUP } });
    signals_info.insert({ DoorPassPosnStsToAPIPassDoorPosnStsChks, { DoorPassPosnStsToAPIPassDoorPosnStsChks, 48, 8, SignalType::E2E_CHKS, 0, DoorPassPosnStsToAPI, ParentType::GROUP } });
    signals_info.insert({ DoorPassPosnStsToAPIPassDoorPosnStsCntr, { DoorPassPosnStsToAPIPassDoorPosnStsCntr, 40, 4, SignalType::E2E_CNTR, 0, DoorPassPosnStsToAPI, ParentType::GROUP } });
    signals_info.insert({ WiprLvrStsIfWiprFrntSts, { WiprLvrStsIfWiprFrntSts, 18, 3, SignalType::APP_UNSIGNED, 1, WiprLvrStsIf, ParentType::GROUP } });
    signals_info.insert({ WiprLvrStsIfWiprReSts, { WiprLvrStsIfWiprReSts, 16, 2, SignalType::APP_UNSIGNED, 0, WiprLvrStsIf, ParentType::GROUP } });
    signals_info.insert({ WiprLvrStsIf_UB, { WiprLvrStsIf_UB, 63, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr10, ParentType::FRAME } });
    signals_info.insert({ EngCooltIndcnReqForExt_UB, { EngCooltIndcnReqForExt_UB, 62, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr10, ParentType::FRAME } });
    signals_info.insert({ DoorDrvrPosnStsToAPI_UB, { DoorDrvrPosnStsToAPI_UB, 23, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr10, ParentType::FRAME } });
    signals_info.insert({ EngCooltIndcnReqForExt, { EngCooltIndcnReqForExt, 58, 4, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr10, ParentType::FRAME } });
    signals_info.insert({ DoorPassPosnStsToAPI_UB, { DoorPassPosnStsToAPI_UB, 21, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr10, ParentType::FRAME } });
    signals_info.insert({ DoorDrvrRePosnStsToAPI_UB, { DoorDrvrRePosnStsToAPI_UB, 22, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr10, ParentType::FRAME } });

    signalgroups_info.insert({ DoorDrvrPosnStsToAPI, { DoorDrvrPosnStsToAPI, 0x41B, { DoorDrvrPosnStsToAPIDrvrDoorPosnSts, DoorDrvrPosnStsToAPIDrvrDoorPosnStsChks, DoorDrvrPosnStsToAPIDrvrDoorPosnStsCntr }, { E2EProfileType::P01a, DoorDrvrPosnStsToAPIDrvrDoorPosnStsChks, DoorDrvrPosnStsToAPIDrvrDoorPosnStsCntr }, VCU1Mid3CanFr10 } } );
    signalgroups_info.insert({ DoorDrvrRePosnStsToAPI, { DoorDrvrRePosnStsToAPI, 0x41C, { DoorDrvrRePosnStsToAPIDrvrReDoorPosnSts, DoorDrvrRePosnStsToAPIDrvrReDoorPosnStsChks, DoorDrvrRePosnStsToAPIDrvrReDoorPosnStsCntr }, { E2EProfileType::P01a, DoorDrvrRePosnStsToAPIDrvrReDoorPosnStsChks, DoorDrvrRePosnStsToAPIDrvrReDoorPosnStsCntr }, VCU1Mid3CanFr10 } } );
    signalgroups_info.insert({ DoorPassPosnStsToAPI, { DoorPassPosnStsToAPI, 0x41D, { DoorPassPosnStsToAPIPassDoorPosnSts, DoorPassPosnStsToAPIPassDoorPosnStsChks, DoorPassPosnStsToAPIPassDoorPosnStsCntr }, { E2EProfileType::P01a, DoorPassPosnStsToAPIPassDoorPosnStsChks, DoorPassPosnStsToAPIPassDoorPosnStsCntr }, VCU1Mid3CanFr10 } } );
    signalgroups_info.insert({ WiprLvrStsIf, { WiprLvrStsIf, 0x0, { WiprLvrStsIfWiprFrntSts, WiprLvrStsIfWiprReSts }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr10 } } );

    frames_info.insert({ VCU1Mid3CanFr10, { VCU1Mid3CanFr10, 304, 8, 260, { DoorDrvrPosnStsToAPI, DoorDrvrRePosnStsToAPI, DoorPassPosnStsToAPI, WiprLvrStsIf }, { WiprLvrStsIf_UB, EngCooltIndcnReqForExt_UB, DoorDrvrPosnStsToAPI_UB, EngCooltIndcnReqForExt, DoorPassPosnStsToAPI_UB, DoorDrvrRePosnStsToAPI_UB } } });

    frame_ids.insert({ 304, VCU1Mid3CanFr10 });
}


}
}
