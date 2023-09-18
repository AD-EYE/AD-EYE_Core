#include "VIMMid5CanFdFr08.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr08_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimPSSGroupSafe5Chks, { AdPrimPSSGroupSafe5Chks, 0, 16, false, SignalType::E2E_CHKS, 0, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5Cntr, { AdPrimPSSGroupSafe5Cntr, 16, 8, false, SignalType::E2E_CNTR, 0, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DataID, { AdPrimPSSGroupSafe5DataID, 24, 16, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaTPos1, { AdPrimPSSGroupSafe5DeltaTPos1, 40, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaTPos2, { AdPrimPSSGroupSafe5DeltaTPos2, 64, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaTPos3, { AdPrimPSSGroupSafe5DeltaTPos3, 88, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaTPos4, { AdPrimPSSGroupSafe5DeltaTPos4, 112, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaTPos5, { AdPrimPSSGroupSafe5DeltaTPos5, 136, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaTPos6, { AdPrimPSSGroupSafe5DeltaTPos6, 160, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaXPos1, { AdPrimPSSGroupSafe5DeltaXPos1, 184, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaXPos2, { AdPrimPSSGroupSafe5DeltaXPos2, 202, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaXPos3, { AdPrimPSSGroupSafe5DeltaXPos3, 220, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaXPos4, { AdPrimPSSGroupSafe5DeltaXPos4, 238, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaXPos5, { AdPrimPSSGroupSafe5DeltaXPos5, 256, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaXPos6, { AdPrimPSSGroupSafe5DeltaXPos6, 274, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaYPos1, { AdPrimPSSGroupSafe5DeltaYPos1, 292, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaYPos2, { AdPrimPSSGroupSafe5DeltaYPos2, 310, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaYPos3, { AdPrimPSSGroupSafe5DeltaYPos3, 328, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaYPos4, { AdPrimPSSGroupSafe5DeltaYPos4, 346, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaYPos5, { AdPrimPSSGroupSafe5DeltaYPos5, 364, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5DeltaYPos6, { AdPrimPSSGroupSafe5DeltaYPos6, 382, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5HeadingPos1, { AdPrimPSSGroupSafe5HeadingPos1, 400, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5HeadingPos2, { AdPrimPSSGroupSafe5HeadingPos2, 416, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5HeadingPos3, { AdPrimPSSGroupSafe5HeadingPos3, 432, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5HeadingPos4, { AdPrimPSSGroupSafe5HeadingPos4, 448, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5HeadingPos5, { AdPrimPSSGroupSafe5HeadingPos5, 464, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5HeadingPos6, { AdPrimPSSGroupSafe5HeadingPos6, 480, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5TrajectID, { AdPrimPSSGroupSafe5TrajectID, 496, 4, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe5_UB, { AdPrimPSSGroupSafe5_UB, 511, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr08, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimPSSGroupSafe5, { AdPrimPSSGroupSafe5, 0x2C0, { AdPrimPSSGroupSafe5Chks, AdPrimPSSGroupSafe5Cntr, AdPrimPSSGroupSafe5DataID, AdPrimPSSGroupSafe5DeltaTPos1, AdPrimPSSGroupSafe5DeltaTPos2, AdPrimPSSGroupSafe5DeltaTPos3, AdPrimPSSGroupSafe5DeltaTPos4, AdPrimPSSGroupSafe5DeltaTPos5, AdPrimPSSGroupSafe5DeltaTPos6, AdPrimPSSGroupSafe5DeltaXPos1, AdPrimPSSGroupSafe5DeltaXPos2, AdPrimPSSGroupSafe5DeltaXPos3, AdPrimPSSGroupSafe5DeltaXPos4, AdPrimPSSGroupSafe5DeltaXPos5, AdPrimPSSGroupSafe5DeltaXPos6, AdPrimPSSGroupSafe5DeltaYPos1, AdPrimPSSGroupSafe5DeltaYPos2, AdPrimPSSGroupSafe5DeltaYPos3, AdPrimPSSGroupSafe5DeltaYPos4, AdPrimPSSGroupSafe5DeltaYPos5, AdPrimPSSGroupSafe5DeltaYPos6, AdPrimPSSGroupSafe5HeadingPos1, AdPrimPSSGroupSafe5HeadingPos2, AdPrimPSSGroupSafe5HeadingPos3, AdPrimPSSGroupSafe5HeadingPos4, AdPrimPSSGroupSafe5HeadingPos5, AdPrimPSSGroupSafe5HeadingPos6, AdPrimPSSGroupSafe5TrajectID }, { E2EProfileType::P05, AdPrimPSSGroupSafe5Chks, AdPrimPSSGroupSafe5Cntr }, VIMMid5CanFdFr08 } } );

    frames_info.insert({ VIMMid5CanFdFr08, { VIMMid5CanFdFr08, 88, 64, 90, { AdPrimPSSGroupSafe5 }, { AdPrimPSSGroupSafe5_UB } } });

    frame_ids.insert({ 88, VIMMid5CanFdFr08 });
}


}
}
