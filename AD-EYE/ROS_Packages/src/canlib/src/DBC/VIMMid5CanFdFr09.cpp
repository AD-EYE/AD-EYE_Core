#include "VIMMid5CanFdFr09.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr09_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimPSSGroupSafe6Chks, { AdPrimPSSGroupSafe6Chks, 0, 16, SignalType::E2E_CHKS, 0, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6Cntr, { AdPrimPSSGroupSafe6Cntr, 16, 8, SignalType::E2E_CNTR, 0, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DataID, { AdPrimPSSGroupSafe6DataID, 24, 16, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaTPos1, { AdPrimPSSGroupSafe6DeltaTPos1, 40, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaTPos2, { AdPrimPSSGroupSafe6DeltaTPos2, 64, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaTPos3, { AdPrimPSSGroupSafe6DeltaTPos3, 88, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaTPos4, { AdPrimPSSGroupSafe6DeltaTPos4, 112, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaTPos5, { AdPrimPSSGroupSafe6DeltaTPos5, 136, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaTPos6, { AdPrimPSSGroupSafe6DeltaTPos6, 160, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaXPos1, { AdPrimPSSGroupSafe6DeltaXPos1, 184, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaXPos2, { AdPrimPSSGroupSafe6DeltaXPos2, 202, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaXPos3, { AdPrimPSSGroupSafe6DeltaXPos3, 220, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaXPos4, { AdPrimPSSGroupSafe6DeltaXPos4, 238, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaXPos5, { AdPrimPSSGroupSafe6DeltaXPos5, 256, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaXPos6, { AdPrimPSSGroupSafe6DeltaXPos6, 274, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaYPos1, { AdPrimPSSGroupSafe6DeltaYPos1, 292, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaYPos2, { AdPrimPSSGroupSafe6DeltaYPos2, 310, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaYPos3, { AdPrimPSSGroupSafe6DeltaYPos3, 328, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaYPos4, { AdPrimPSSGroupSafe6DeltaYPos4, 346, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaYPos5, { AdPrimPSSGroupSafe6DeltaYPos5, 364, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6DeltaYPos6, { AdPrimPSSGroupSafe6DeltaYPos6, 382, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6HeadingPos1, { AdPrimPSSGroupSafe6HeadingPos1, 400, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6HeadingPos2, { AdPrimPSSGroupSafe6HeadingPos2, 416, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6HeadingPos3, { AdPrimPSSGroupSafe6HeadingPos3, 432, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6HeadingPos4, { AdPrimPSSGroupSafe6HeadingPos4, 448, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6HeadingPos5, { AdPrimPSSGroupSafe6HeadingPos5, 464, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6HeadingPos6, { AdPrimPSSGroupSafe6HeadingPos6, 480, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6TrajectID, { AdPrimPSSGroupSafe6TrajectID, 496, 4, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe6_UB, { AdPrimPSSGroupSafe6_UB, 511, 1, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr09, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimPSSGroupSafe6, { AdPrimPSSGroupSafe6, 0x2C7, { AdPrimPSSGroupSafe6Chks, AdPrimPSSGroupSafe6Cntr, AdPrimPSSGroupSafe6DataID, AdPrimPSSGroupSafe6DeltaTPos1, AdPrimPSSGroupSafe6DeltaTPos2, AdPrimPSSGroupSafe6DeltaTPos3, AdPrimPSSGroupSafe6DeltaTPos4, AdPrimPSSGroupSafe6DeltaTPos5, AdPrimPSSGroupSafe6DeltaTPos6, AdPrimPSSGroupSafe6DeltaXPos1, AdPrimPSSGroupSafe6DeltaXPos2, AdPrimPSSGroupSafe6DeltaXPos3, AdPrimPSSGroupSafe6DeltaXPos4, AdPrimPSSGroupSafe6DeltaXPos5, AdPrimPSSGroupSafe6DeltaXPos6, AdPrimPSSGroupSafe6DeltaYPos1, AdPrimPSSGroupSafe6DeltaYPos2, AdPrimPSSGroupSafe6DeltaYPos3, AdPrimPSSGroupSafe6DeltaYPos4, AdPrimPSSGroupSafe6DeltaYPos5, AdPrimPSSGroupSafe6DeltaYPos6, AdPrimPSSGroupSafe6HeadingPos1, AdPrimPSSGroupSafe6HeadingPos2, AdPrimPSSGroupSafe6HeadingPos3, AdPrimPSSGroupSafe6HeadingPos4, AdPrimPSSGroupSafe6HeadingPos5, AdPrimPSSGroupSafe6HeadingPos6, AdPrimPSSGroupSafe6TrajectID }, { E2EProfileType::P05, AdPrimPSSGroupSafe6Chks, AdPrimPSSGroupSafe6Cntr }, VIMMid5CanFdFr09 } } );

    frames_info.insert({ VIMMid5CanFdFr09, { VIMMid5CanFdFr09, 98, 64, 90, { AdPrimPSSGroupSafe6 }, { AdPrimPSSGroupSafe6_UB } } });

    frame_ids.insert({ 98, VIMMid5CanFdFr09 });
}


}
}
