#include "VIMBMid6CanFdFr19.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr19_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecPSSGroupSafe0Chks, { AdSecPSSGroupSafe0Chks, 0, 16, SignalType::E2E_CHKS, 0, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0Cntr, { AdSecPSSGroupSafe0Cntr, 16, 8, SignalType::E2E_CNTR, 0, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0DataID, { AdSecPSSGroupSafe0DataID, 24, 16, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0DeltaTPos1, { AdSecPSSGroupSafe0DeltaTPos1, 48, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0DeltaTPos2, { AdSecPSSGroupSafe0DeltaTPos2, 72, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0DeltaXPos1, { AdSecPSSGroupSafe0DeltaXPos1, 96, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0DeltaXPos2, { AdSecPSSGroupSafe0DeltaXPos2, 120, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0DeltaYPos1, { AdSecPSSGroupSafe0DeltaYPos1, 144, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0DeltaYPos2, { AdSecPSSGroupSafe0DeltaYPos2, 168, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0HeadingPos1, { AdSecPSSGroupSafe0HeadingPos1, 192, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0HeadingPos2, { AdSecPSSGroupSafe0HeadingPos2, 208, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0InitHeading, { AdSecPSSGroupSafe0InitHeading, 224, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0InitPosX, { AdSecPSSGroupSafe0InitPosX, 240, 32, SignalType::APP_SIGNED, 0, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0InitPosY, { AdSecPSSGroupSafe0InitPosY, 272, 32, SignalType::APP_SIGNED, 0, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0TiStampNanoSec, { AdSecPSSGroupSafe0TiStampNanoSec, 304, 32, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0TiStampSec, { AdSecPSSGroupSafe0TiStampSec, 336, 32, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0TrajectID, { AdSecPSSGroupSafe0TrajectID, 368, 4, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe0_UB, { AdSecPSSGroupSafe0_UB, 383, 1, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr19, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecPSSGroupSafe0, { AdSecPSSGroupSafe0, 0x2C1, { AdSecPSSGroupSafe0Chks, AdSecPSSGroupSafe0Cntr, AdSecPSSGroupSafe0DataID, AdSecPSSGroupSafe0DeltaTPos1, AdSecPSSGroupSafe0DeltaTPos2, AdSecPSSGroupSafe0DeltaXPos1, AdSecPSSGroupSafe0DeltaXPos2, AdSecPSSGroupSafe0DeltaYPos1, AdSecPSSGroupSafe0DeltaYPos2, AdSecPSSGroupSafe0HeadingPos1, AdSecPSSGroupSafe0HeadingPos2, AdSecPSSGroupSafe0InitHeading, AdSecPSSGroupSafe0InitPosX, AdSecPSSGroupSafe0InitPosY, AdSecPSSGroupSafe0TiStampNanoSec, AdSecPSSGroupSafe0TiStampSec, AdSecPSSGroupSafe0TrajectID }, { E2EProfileType::P05, AdSecPSSGroupSafe0Chks, AdSecPSSGroupSafe0Cntr }, VIMBMid6CanFdFr19 } } );

    frames_info.insert({ VIMBMid6CanFdFr19, { VIMBMid6CanFdFr19, 272, 48, 90, { AdSecPSSGroupSafe0 }, { AdSecPSSGroupSafe0_UB } } });

    frame_ids.insert({ 272, VIMBMid6CanFdFr19 });
}


}
}
