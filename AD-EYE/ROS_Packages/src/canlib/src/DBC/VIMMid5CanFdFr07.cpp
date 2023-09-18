#include "VIMMid5CanFdFr07.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr07_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimPSSGroupSafe4Chks, { AdPrimPSSGroupSafe4Chks, 0, 16, false, SignalType::E2E_CHKS, 0, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4Cntr, { AdPrimPSSGroupSafe4Cntr, 16, 8, false, SignalType::E2E_CNTR, 0, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DataID, { AdPrimPSSGroupSafe4DataID, 24, 16, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaTPos1, { AdPrimPSSGroupSafe4DeltaTPos1, 40, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaTPos2, { AdPrimPSSGroupSafe4DeltaTPos2, 64, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaTPos3, { AdPrimPSSGroupSafe4DeltaTPos3, 88, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaTPos4, { AdPrimPSSGroupSafe4DeltaTPos4, 112, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaTPos5, { AdPrimPSSGroupSafe4DeltaTPos5, 136, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaTPos6, { AdPrimPSSGroupSafe4DeltaTPos6, 160, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaXPos1, { AdPrimPSSGroupSafe4DeltaXPos1, 184, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaXPos2, { AdPrimPSSGroupSafe4DeltaXPos2, 202, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaXPos3, { AdPrimPSSGroupSafe4DeltaXPos3, 220, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaXPos4, { AdPrimPSSGroupSafe4DeltaXPos4, 238, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaXPos5, { AdPrimPSSGroupSafe4DeltaXPos5, 256, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaXPos6, { AdPrimPSSGroupSafe4DeltaXPos6, 274, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaYPos1, { AdPrimPSSGroupSafe4DeltaYPos1, 292, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaYPos2, { AdPrimPSSGroupSafe4DeltaYPos2, 310, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaYPos3, { AdPrimPSSGroupSafe4DeltaYPos3, 328, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaYPos4, { AdPrimPSSGroupSafe4DeltaYPos4, 346, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaYPos5, { AdPrimPSSGroupSafe4DeltaYPos5, 364, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4DeltaYPos6, { AdPrimPSSGroupSafe4DeltaYPos6, 382, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4HeadingPos1, { AdPrimPSSGroupSafe4HeadingPos1, 400, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4HeadingPos2, { AdPrimPSSGroupSafe4HeadingPos2, 416, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4HeadingPos3, { AdPrimPSSGroupSafe4HeadingPos3, 432, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4HeadingPos4, { AdPrimPSSGroupSafe4HeadingPos4, 448, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4HeadingPos5, { AdPrimPSSGroupSafe4HeadingPos5, 464, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4HeadingPos6, { AdPrimPSSGroupSafe4HeadingPos6, 480, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4TrajectID, { AdPrimPSSGroupSafe4TrajectID, 496, 4, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe4_UB, { AdPrimPSSGroupSafe4_UB, 511, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr07, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimPSSGroupSafe4, { AdPrimPSSGroupSafe4, 0x2BF, { AdPrimPSSGroupSafe4Chks, AdPrimPSSGroupSafe4Cntr, AdPrimPSSGroupSafe4DataID, AdPrimPSSGroupSafe4DeltaTPos1, AdPrimPSSGroupSafe4DeltaTPos2, AdPrimPSSGroupSafe4DeltaTPos3, AdPrimPSSGroupSafe4DeltaTPos4, AdPrimPSSGroupSafe4DeltaTPos5, AdPrimPSSGroupSafe4DeltaTPos6, AdPrimPSSGroupSafe4DeltaXPos1, AdPrimPSSGroupSafe4DeltaXPos2, AdPrimPSSGroupSafe4DeltaXPos3, AdPrimPSSGroupSafe4DeltaXPos4, AdPrimPSSGroupSafe4DeltaXPos5, AdPrimPSSGroupSafe4DeltaXPos6, AdPrimPSSGroupSafe4DeltaYPos1, AdPrimPSSGroupSafe4DeltaYPos2, AdPrimPSSGroupSafe4DeltaYPos3, AdPrimPSSGroupSafe4DeltaYPos4, AdPrimPSSGroupSafe4DeltaYPos5, AdPrimPSSGroupSafe4DeltaYPos6, AdPrimPSSGroupSafe4HeadingPos1, AdPrimPSSGroupSafe4HeadingPos2, AdPrimPSSGroupSafe4HeadingPos3, AdPrimPSSGroupSafe4HeadingPos4, AdPrimPSSGroupSafe4HeadingPos5, AdPrimPSSGroupSafe4HeadingPos6, AdPrimPSSGroupSafe4TrajectID }, { E2EProfileType::P05, AdPrimPSSGroupSafe4Chks, AdPrimPSSGroupSafe4Cntr }, VIMMid5CanFdFr07 } } );

    frames_info.insert({ VIMMid5CanFdFr07, { VIMMid5CanFdFr07, 84, 64, 90, { AdPrimPSSGroupSafe4 }, { AdPrimPSSGroupSafe4_UB } } });

    frame_ids.insert({ 84, VIMMid5CanFdFr07 });
}


}
}
