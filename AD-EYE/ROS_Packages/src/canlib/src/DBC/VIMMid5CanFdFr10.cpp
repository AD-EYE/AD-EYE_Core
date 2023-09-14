#include "VIMMid5CanFdFr10.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr10_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimPSSGroupSafe7Chks, { AdPrimPSSGroupSafe7Chks, 0, 16, SignalType::E2E_CHKS, 0, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7Cntr, { AdPrimPSSGroupSafe7Cntr, 16, 8, SignalType::E2E_CNTR, 0, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DataID, { AdPrimPSSGroupSafe7DataID, 24, 16, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaTPos1, { AdPrimPSSGroupSafe7DeltaTPos1, 40, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaTPos2, { AdPrimPSSGroupSafe7DeltaTPos2, 64, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaTPos3, { AdPrimPSSGroupSafe7DeltaTPos3, 88, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaTPos4, { AdPrimPSSGroupSafe7DeltaTPos4, 112, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaTPos5, { AdPrimPSSGroupSafe7DeltaTPos5, 136, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaTPos6, { AdPrimPSSGroupSafe7DeltaTPos6, 160, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaXPos1, { AdPrimPSSGroupSafe7DeltaXPos1, 184, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaXPos2, { AdPrimPSSGroupSafe7DeltaXPos2, 202, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaXPos3, { AdPrimPSSGroupSafe7DeltaXPos3, 220, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaXPos4, { AdPrimPSSGroupSafe7DeltaXPos4, 238, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaXPos5, { AdPrimPSSGroupSafe7DeltaXPos5, 256, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaXPos6, { AdPrimPSSGroupSafe7DeltaXPos6, 274, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaYPos1, { AdPrimPSSGroupSafe7DeltaYPos1, 292, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaYPos2, { AdPrimPSSGroupSafe7DeltaYPos2, 310, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaYPos3, { AdPrimPSSGroupSafe7DeltaYPos3, 328, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaYPos4, { AdPrimPSSGroupSafe7DeltaYPos4, 346, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaYPos5, { AdPrimPSSGroupSafe7DeltaYPos5, 364, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7DeltaYPos6, { AdPrimPSSGroupSafe7DeltaYPos6, 382, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7HeadingPos1, { AdPrimPSSGroupSafe7HeadingPos1, 400, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7HeadingPos2, { AdPrimPSSGroupSafe7HeadingPos2, 416, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7HeadingPos3, { AdPrimPSSGroupSafe7HeadingPos3, 432, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7HeadingPos4, { AdPrimPSSGroupSafe7HeadingPos4, 448, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7HeadingPos5, { AdPrimPSSGroupSafe7HeadingPos5, 464, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7HeadingPos6, { AdPrimPSSGroupSafe7HeadingPos6, 480, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7TrajectID, { AdPrimPSSGroupSafe7TrajectID, 496, 4, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe7_UB, { AdPrimPSSGroupSafe7_UB, 511, 1, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr10, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimPSSGroupSafe7, { AdPrimPSSGroupSafe7, 0x2C8, { AdPrimPSSGroupSafe7Chks, AdPrimPSSGroupSafe7Cntr, AdPrimPSSGroupSafe7DataID, AdPrimPSSGroupSafe7DeltaTPos1, AdPrimPSSGroupSafe7DeltaTPos2, AdPrimPSSGroupSafe7DeltaTPos3, AdPrimPSSGroupSafe7DeltaTPos4, AdPrimPSSGroupSafe7DeltaTPos5, AdPrimPSSGroupSafe7DeltaTPos6, AdPrimPSSGroupSafe7DeltaXPos1, AdPrimPSSGroupSafe7DeltaXPos2, AdPrimPSSGroupSafe7DeltaXPos3, AdPrimPSSGroupSafe7DeltaXPos4, AdPrimPSSGroupSafe7DeltaXPos5, AdPrimPSSGroupSafe7DeltaXPos6, AdPrimPSSGroupSafe7DeltaYPos1, AdPrimPSSGroupSafe7DeltaYPos2, AdPrimPSSGroupSafe7DeltaYPos3, AdPrimPSSGroupSafe7DeltaYPos4, AdPrimPSSGroupSafe7DeltaYPos5, AdPrimPSSGroupSafe7DeltaYPos6, AdPrimPSSGroupSafe7HeadingPos1, AdPrimPSSGroupSafe7HeadingPos2, AdPrimPSSGroupSafe7HeadingPos3, AdPrimPSSGroupSafe7HeadingPos4, AdPrimPSSGroupSafe7HeadingPos5, AdPrimPSSGroupSafe7HeadingPos6, AdPrimPSSGroupSafe7TrajectID }, { E2EProfileType::P05, AdPrimPSSGroupSafe7Chks, AdPrimPSSGroupSafe7Cntr }, VIMMid5CanFdFr10 } } );

    frames_info.insert({ VIMMid5CanFdFr10, { VIMMid5CanFdFr10, 100, 64, 90, { AdPrimPSSGroupSafe7 }, { AdPrimPSSGroupSafe7_UB } } });

    frame_ids.insert({ 100, VIMMid5CanFdFr10 });
}


}
}
