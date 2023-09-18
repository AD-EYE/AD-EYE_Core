#include "VIMMid5CanFdFr04.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr04_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimPSSGroupSafe1Chks, { AdPrimPSSGroupSafe1Chks, 0, 16, false, SignalType::E2E_CHKS, 0, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1Cntr, { AdPrimPSSGroupSafe1Cntr, 16, 8, false, SignalType::E2E_CNTR, 0, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DataID, { AdPrimPSSGroupSafe1DataID, 24, 16, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaTPos1, { AdPrimPSSGroupSafe1DeltaTPos1, 40, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaTPos2, { AdPrimPSSGroupSafe1DeltaTPos2, 64, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaTPos3, { AdPrimPSSGroupSafe1DeltaTPos3, 88, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaTPos4, { AdPrimPSSGroupSafe1DeltaTPos4, 112, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaTPos5, { AdPrimPSSGroupSafe1DeltaTPos5, 136, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaTPos6, { AdPrimPSSGroupSafe1DeltaTPos6, 160, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaXPos1, { AdPrimPSSGroupSafe1DeltaXPos1, 184, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaXPos2, { AdPrimPSSGroupSafe1DeltaXPos2, 202, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaXPos3, { AdPrimPSSGroupSafe1DeltaXPos3, 220, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaXPos4, { AdPrimPSSGroupSafe1DeltaXPos4, 238, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaXPos5, { AdPrimPSSGroupSafe1DeltaXPos5, 256, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaXPos6, { AdPrimPSSGroupSafe1DeltaXPos6, 274, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaYPos1, { AdPrimPSSGroupSafe1DeltaYPos1, 292, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaYPos2, { AdPrimPSSGroupSafe1DeltaYPos2, 310, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaYPos3, { AdPrimPSSGroupSafe1DeltaYPos3, 328, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaYPos4, { AdPrimPSSGroupSafe1DeltaYPos4, 346, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaYPos5, { AdPrimPSSGroupSafe1DeltaYPos5, 364, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1DeltaYPos6, { AdPrimPSSGroupSafe1DeltaYPos6, 382, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1HeadingPos1, { AdPrimPSSGroupSafe1HeadingPos1, 400, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1HeadingPos2, { AdPrimPSSGroupSafe1HeadingPos2, 416, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1HeadingPos3, { AdPrimPSSGroupSafe1HeadingPos3, 432, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1HeadingPos4, { AdPrimPSSGroupSafe1HeadingPos4, 448, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1HeadingPos5, { AdPrimPSSGroupSafe1HeadingPos5, 464, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1HeadingPos6, { AdPrimPSSGroupSafe1HeadingPos6, 480, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1TrajectID, { AdPrimPSSGroupSafe1TrajectID, 496, 4, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe1_UB, { AdPrimPSSGroupSafe1_UB, 511, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr04, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimPSSGroupSafe1, { AdPrimPSSGroupSafe1, 0x2BC, { AdPrimPSSGroupSafe1Chks, AdPrimPSSGroupSafe1Cntr, AdPrimPSSGroupSafe1DataID, AdPrimPSSGroupSafe1DeltaTPos1, AdPrimPSSGroupSafe1DeltaTPos2, AdPrimPSSGroupSafe1DeltaTPos3, AdPrimPSSGroupSafe1DeltaTPos4, AdPrimPSSGroupSafe1DeltaTPos5, AdPrimPSSGroupSafe1DeltaTPos6, AdPrimPSSGroupSafe1DeltaXPos1, AdPrimPSSGroupSafe1DeltaXPos2, AdPrimPSSGroupSafe1DeltaXPos3, AdPrimPSSGroupSafe1DeltaXPos4, AdPrimPSSGroupSafe1DeltaXPos5, AdPrimPSSGroupSafe1DeltaXPos6, AdPrimPSSGroupSafe1DeltaYPos1, AdPrimPSSGroupSafe1DeltaYPos2, AdPrimPSSGroupSafe1DeltaYPos3, AdPrimPSSGroupSafe1DeltaYPos4, AdPrimPSSGroupSafe1DeltaYPos5, AdPrimPSSGroupSafe1DeltaYPos6, AdPrimPSSGroupSafe1HeadingPos1, AdPrimPSSGroupSafe1HeadingPos2, AdPrimPSSGroupSafe1HeadingPos3, AdPrimPSSGroupSafe1HeadingPos4, AdPrimPSSGroupSafe1HeadingPos5, AdPrimPSSGroupSafe1HeadingPos6, AdPrimPSSGroupSafe1TrajectID }, { E2EProfileType::P05, AdPrimPSSGroupSafe1Chks, AdPrimPSSGroupSafe1Cntr }, VIMMid5CanFdFr04 } } );

    frames_info.insert({ VIMMid5CanFdFr04, { VIMMid5CanFdFr04, 68, 64, 90, { AdPrimPSSGroupSafe1 }, { AdPrimPSSGroupSafe1_UB } } });

    frame_ids.insert({ 68, VIMMid5CanFdFr04 });
}


}
}
