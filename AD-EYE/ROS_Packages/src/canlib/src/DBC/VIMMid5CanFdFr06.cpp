#include "VIMMid5CanFdFr06.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr06_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimPSSGroupSafe3Chks, { AdPrimPSSGroupSafe3Chks, 0, 16, false, SignalType::E2E_CHKS, 0, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3Cntr, { AdPrimPSSGroupSafe3Cntr, 16, 8, false, SignalType::E2E_CNTR, 0, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DataID, { AdPrimPSSGroupSafe3DataID, 24, 16, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaTPos1, { AdPrimPSSGroupSafe3DeltaTPos1, 40, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaTPos2, { AdPrimPSSGroupSafe3DeltaTPos2, 64, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaTPos3, { AdPrimPSSGroupSafe3DeltaTPos3, 88, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaTPos4, { AdPrimPSSGroupSafe3DeltaTPos4, 112, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaTPos5, { AdPrimPSSGroupSafe3DeltaTPos5, 136, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaTPos6, { AdPrimPSSGroupSafe3DeltaTPos6, 160, 18, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaXPos1, { AdPrimPSSGroupSafe3DeltaXPos1, 184, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaXPos2, { AdPrimPSSGroupSafe3DeltaXPos2, 202, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaXPos3, { AdPrimPSSGroupSafe3DeltaXPos3, 220, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaXPos4, { AdPrimPSSGroupSafe3DeltaXPos4, 238, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaXPos5, { AdPrimPSSGroupSafe3DeltaXPos5, 256, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaXPos6, { AdPrimPSSGroupSafe3DeltaXPos6, 274, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaYPos1, { AdPrimPSSGroupSafe3DeltaYPos1, 292, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaYPos2, { AdPrimPSSGroupSafe3DeltaYPos2, 310, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaYPos3, { AdPrimPSSGroupSafe3DeltaYPos3, 328, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaYPos4, { AdPrimPSSGroupSafe3DeltaYPos4, 346, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaYPos5, { AdPrimPSSGroupSafe3DeltaYPos5, 364, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3DeltaYPos6, { AdPrimPSSGroupSafe3DeltaYPos6, 382, 18, false, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3HeadingPos1, { AdPrimPSSGroupSafe3HeadingPos1, 400, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3HeadingPos2, { AdPrimPSSGroupSafe3HeadingPos2, 416, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3HeadingPos3, { AdPrimPSSGroupSafe3HeadingPos3, 432, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3HeadingPos4, { AdPrimPSSGroupSafe3HeadingPos4, 448, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3HeadingPos5, { AdPrimPSSGroupSafe3HeadingPos5, 464, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3HeadingPos6, { AdPrimPSSGroupSafe3HeadingPos6, 480, 16, false, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3TrajectID, { AdPrimPSSGroupSafe3TrajectID, 496, 4, false, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe3_UB, { AdPrimPSSGroupSafe3_UB, 511, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr06, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimPSSGroupSafe3, { AdPrimPSSGroupSafe3, 0x2BE, { AdPrimPSSGroupSafe3Chks, AdPrimPSSGroupSafe3Cntr, AdPrimPSSGroupSafe3DataID, AdPrimPSSGroupSafe3DeltaTPos1, AdPrimPSSGroupSafe3DeltaTPos2, AdPrimPSSGroupSafe3DeltaTPos3, AdPrimPSSGroupSafe3DeltaTPos4, AdPrimPSSGroupSafe3DeltaTPos5, AdPrimPSSGroupSafe3DeltaTPos6, AdPrimPSSGroupSafe3DeltaXPos1, AdPrimPSSGroupSafe3DeltaXPos2, AdPrimPSSGroupSafe3DeltaXPos3, AdPrimPSSGroupSafe3DeltaXPos4, AdPrimPSSGroupSafe3DeltaXPos5, AdPrimPSSGroupSafe3DeltaXPos6, AdPrimPSSGroupSafe3DeltaYPos1, AdPrimPSSGroupSafe3DeltaYPos2, AdPrimPSSGroupSafe3DeltaYPos3, AdPrimPSSGroupSafe3DeltaYPos4, AdPrimPSSGroupSafe3DeltaYPos5, AdPrimPSSGroupSafe3DeltaYPos6, AdPrimPSSGroupSafe3HeadingPos1, AdPrimPSSGroupSafe3HeadingPos2, AdPrimPSSGroupSafe3HeadingPos3, AdPrimPSSGroupSafe3HeadingPos4, AdPrimPSSGroupSafe3HeadingPos5, AdPrimPSSGroupSafe3HeadingPos6, AdPrimPSSGroupSafe3TrajectID }, { E2EProfileType::P05, AdPrimPSSGroupSafe3Chks, AdPrimPSSGroupSafe3Cntr }, VIMMid5CanFdFr06 } } );

    frames_info.insert({ VIMMid5CanFdFr06, { VIMMid5CanFdFr06, 82, 64, 90, { AdPrimPSSGroupSafe3 }, { AdPrimPSSGroupSafe3_UB } } });

    frame_ids.insert({ 82, VIMMid5CanFdFr06 });
}


}
}
