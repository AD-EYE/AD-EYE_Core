#include "VIMMid5CanFdFr03.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr03_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimPSSGroupSafe0Chks, { AdPrimPSSGroupSafe0Chks, 0, 16, SignalType::E2E_CHKS, 0, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0Cntr, { AdPrimPSSGroupSafe0Cntr, 16, 8, SignalType::E2E_CNTR, 0, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0DataID, { AdPrimPSSGroupSafe0DataID, 24, 16, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0DeltaTPos1, { AdPrimPSSGroupSafe0DeltaTPos1, 48, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0DeltaTPos2, { AdPrimPSSGroupSafe0DeltaTPos2, 72, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0DeltaXPos1, { AdPrimPSSGroupSafe0DeltaXPos1, 96, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0DeltaXPos2, { AdPrimPSSGroupSafe0DeltaXPos2, 120, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0DeltaYPos1, { AdPrimPSSGroupSafe0DeltaYPos1, 144, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0DeltaYPos2, { AdPrimPSSGroupSafe0DeltaYPos2, 168, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0HeadingPos1, { AdPrimPSSGroupSafe0HeadingPos1, 192, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0HeadingPos2, { AdPrimPSSGroupSafe0HeadingPos2, 208, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0InitHeading, { AdPrimPSSGroupSafe0InitHeading, 224, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0InitPosX, { AdPrimPSSGroupSafe0InitPosX, 240, 32, SignalType::APP_SIGNED, 0, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0InitPosY, { AdPrimPSSGroupSafe0InitPosY, 272, 32, SignalType::APP_SIGNED, 0, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0TiStampSec, { AdPrimPSSGroupSafe0TiStampSec, 336, 32, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0TrajectID, { AdPrimPSSGroupSafe0TrajectID, 40, 4, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe0, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe0TiStampNanoSec, { AdPrimPSSGroupSafe0TiStampNanoSec, 304, 32, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr03, ParentType::FRAME } });
    signals_info.insert({ AdPrimPSSGroupSafe0_UB, { AdPrimPSSGroupSafe0_UB, 375, 1, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr03, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimPSSGroupSafe0, { AdPrimPSSGroupSafe0, 0x2BB, { AdPrimPSSGroupSafe0Chks, AdPrimPSSGroupSafe0Cntr, AdPrimPSSGroupSafe0DataID, AdPrimPSSGroupSafe0DeltaTPos1, AdPrimPSSGroupSafe0DeltaTPos2, AdPrimPSSGroupSafe0DeltaXPos1, AdPrimPSSGroupSafe0DeltaXPos2, AdPrimPSSGroupSafe0DeltaYPos1, AdPrimPSSGroupSafe0DeltaYPos2, AdPrimPSSGroupSafe0HeadingPos1, AdPrimPSSGroupSafe0HeadingPos2, AdPrimPSSGroupSafe0InitHeading, AdPrimPSSGroupSafe0InitPosX, AdPrimPSSGroupSafe0InitPosY, AdPrimPSSGroupSafe0TiStampNanoSec, AdPrimPSSGroupSafe0TiStampSec, AdPrimPSSGroupSafe0TrajectID }, { E2EProfileType::P05, AdPrimPSSGroupSafe0Chks, AdPrimPSSGroupSafe0Cntr }, VIMMid5CanFdFr03 } } );

    frames_info.insert({ VIMMid5CanFdFr03, { VIMMid5CanFdFr03, 65, 48, 90, { AdPrimPSSGroupSafe0 }, { AdPrimPSSGroupSafe0TiStampNanoSec, AdPrimPSSGroupSafe0_UB } } });

    frame_ids.insert({ 65, VIMMid5CanFdFr03 });
}


}
}
