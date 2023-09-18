#include "VIMMid5CanFdFr11.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr11_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimPSSGroupSafe8Chks, { AdPrimPSSGroupSafe8Chks, 0, 16, false, SignalType::E2E_CHKS, 0, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8Cntr, { AdPrimPSSGroupSafe8Cntr, 16, 8, false, SignalType::E2E_CNTR, 0, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DataID, { AdPrimPSSGroupSafe8DataID, 24, 16, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaTPos1, { AdPrimPSSGroupSafe8DeltaTPos1, 40, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaTPos2, { AdPrimPSSGroupSafe8DeltaTPos2, 64, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaTPos3, { AdPrimPSSGroupSafe8DeltaTPos3, 88, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaTPos4, { AdPrimPSSGroupSafe8DeltaTPos4, 112, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaTPos5, { AdPrimPSSGroupSafe8DeltaTPos5, 136, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaTPos6, { AdPrimPSSGroupSafe8DeltaTPos6, 160, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaXPos1, { AdPrimPSSGroupSafe8DeltaXPos1, 184, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaXPos2, { AdPrimPSSGroupSafe8DeltaXPos2, 202, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaXPos3, { AdPrimPSSGroupSafe8DeltaXPos3, 220, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaXPos4, { AdPrimPSSGroupSafe8DeltaXPos4, 238, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaXPos5, { AdPrimPSSGroupSafe8DeltaXPos5, 256, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaXPos6, { AdPrimPSSGroupSafe8DeltaXPos6, 274, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaYPos1, { AdPrimPSSGroupSafe8DeltaYPos1, 292, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaYPos2, { AdPrimPSSGroupSafe8DeltaYPos2, 310, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaYPos3, { AdPrimPSSGroupSafe8DeltaYPos3, 328, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaYPos4, { AdPrimPSSGroupSafe8DeltaYPos4, 346, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaYPos5, { AdPrimPSSGroupSafe8DeltaYPos5, 364, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8DeltaYPos6, { AdPrimPSSGroupSafe8DeltaYPos6, 382, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8HeadingPos1, { AdPrimPSSGroupSafe8HeadingPos1, 400, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8HeadingPos2, { AdPrimPSSGroupSafe8HeadingPos2, 416, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8HeadingPos3, { AdPrimPSSGroupSafe8HeadingPos3, 432, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8HeadingPos4, { AdPrimPSSGroupSafe8HeadingPos4, 448, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8HeadingPos5, { AdPrimPSSGroupSafe8HeadingPos5, 464, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8HeadingPos6, { AdPrimPSSGroupSafe8HeadingPos6, 480, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8TrajectID, { AdPrimPSSGroupSafe8TrajectID, 496, 4, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe8_UB, { AdPrimPSSGroupSafe8_UB, 511, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr11, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimPSSGroupSafe8, { AdPrimPSSGroupSafe8, 0x2CD, { AdPrimPSSGroupSafe8Chks, AdPrimPSSGroupSafe8Cntr, AdPrimPSSGroupSafe8DataID, AdPrimPSSGroupSafe8DeltaTPos1, AdPrimPSSGroupSafe8DeltaTPos2, AdPrimPSSGroupSafe8DeltaTPos3, AdPrimPSSGroupSafe8DeltaTPos4, AdPrimPSSGroupSafe8DeltaTPos5, AdPrimPSSGroupSafe8DeltaTPos6, AdPrimPSSGroupSafe8DeltaXPos1, AdPrimPSSGroupSafe8DeltaXPos2, AdPrimPSSGroupSafe8DeltaXPos3, AdPrimPSSGroupSafe8DeltaXPos4, AdPrimPSSGroupSafe8DeltaXPos5, AdPrimPSSGroupSafe8DeltaXPos6, AdPrimPSSGroupSafe8DeltaYPos1, AdPrimPSSGroupSafe8DeltaYPos2, AdPrimPSSGroupSafe8DeltaYPos3, AdPrimPSSGroupSafe8DeltaYPos4, AdPrimPSSGroupSafe8DeltaYPos5, AdPrimPSSGroupSafe8DeltaYPos6, AdPrimPSSGroupSafe8HeadingPos1, AdPrimPSSGroupSafe8HeadingPos2, AdPrimPSSGroupSafe8HeadingPos3, AdPrimPSSGroupSafe8HeadingPos4, AdPrimPSSGroupSafe8HeadingPos5, AdPrimPSSGroupSafe8HeadingPos6, AdPrimPSSGroupSafe8TrajectID }, { E2EProfileType::P05, AdPrimPSSGroupSafe8Chks, AdPrimPSSGroupSafe8Cntr }, VIMMid5CanFdFr11 } } );

    frames_info.insert({ VIMMid5CanFdFr11, { VIMMid5CanFdFr11, 104, 64, 90, { AdPrimPSSGroupSafe8 }, { AdPrimPSSGroupSafe8_UB } } });

    frame_ids.insert({ 104, VIMMid5CanFdFr11 });
}


}
}
