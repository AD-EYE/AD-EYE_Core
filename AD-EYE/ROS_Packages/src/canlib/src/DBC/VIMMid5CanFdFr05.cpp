#include "VIMMid5CanFdFr05.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr05_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimPSSGroupSafe2Chks, { AdPrimPSSGroupSafe2Chks, 0, 16, SignalType::E2E_CHKS, 0, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2Cntr, { AdPrimPSSGroupSafe2Cntr, 16, 8, SignalType::E2E_CNTR, 0, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DataID, { AdPrimPSSGroupSafe2DataID, 24, 16, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaTPos1, { AdPrimPSSGroupSafe2DeltaTPos1, 40, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaTPos2, { AdPrimPSSGroupSafe2DeltaTPos2, 64, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaTPos3, { AdPrimPSSGroupSafe2DeltaTPos3, 88, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaTPos4, { AdPrimPSSGroupSafe2DeltaTPos4, 112, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaTPos5, { AdPrimPSSGroupSafe2DeltaTPos5, 136, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaTPos6, { AdPrimPSSGroupSafe2DeltaTPos6, 160, 18, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaXPos1, { AdPrimPSSGroupSafe2DeltaXPos1, 184, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaXPos2, { AdPrimPSSGroupSafe2DeltaXPos2, 202, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaXPos3, { AdPrimPSSGroupSafe2DeltaXPos3, 220, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaXPos4, { AdPrimPSSGroupSafe2DeltaXPos4, 238, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaXPos5, { AdPrimPSSGroupSafe2DeltaXPos5, 256, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaXPos6, { AdPrimPSSGroupSafe2DeltaXPos6, 274, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaYPos1, { AdPrimPSSGroupSafe2DeltaYPos1, 292, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaYPos2, { AdPrimPSSGroupSafe2DeltaYPos2, 310, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaYPos3, { AdPrimPSSGroupSafe2DeltaYPos3, 328, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaYPos4, { AdPrimPSSGroupSafe2DeltaYPos4, 346, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaYPos5, { AdPrimPSSGroupSafe2DeltaYPos5, 364, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2DeltaYPos6, { AdPrimPSSGroupSafe2DeltaYPos6, 382, 18, SignalType::APP_UNSIGNED, 131070, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2HeadingPos1, { AdPrimPSSGroupSafe2HeadingPos1, 400, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2HeadingPos2, { AdPrimPSSGroupSafe2HeadingPos2, 416, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2HeadingPos3, { AdPrimPSSGroupSafe2HeadingPos3, 432, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2HeadingPos4, { AdPrimPSSGroupSafe2HeadingPos4, 448, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2HeadingPos5, { AdPrimPSSGroupSafe2HeadingPos5, 464, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2HeadingPos6, { AdPrimPSSGroupSafe2HeadingPos6, 480, 16, SignalType::APP_UNSIGNED, 32767, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2TrajectID, { AdPrimPSSGroupSafe2TrajectID, 496, 4, SignalType::APP_UNSIGNED, 0, AdPrimPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdPrimPSSGroupSafe2_UB, { AdPrimPSSGroupSafe2_UB, 511, 1, SignalType::APP_UNSIGNED, 0, VIMMid5CanFdFr05, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimPSSGroupSafe2, { AdPrimPSSGroupSafe2, 0x2BD, { AdPrimPSSGroupSafe2Chks, AdPrimPSSGroupSafe2Cntr, AdPrimPSSGroupSafe2DataID, AdPrimPSSGroupSafe2DeltaTPos1, AdPrimPSSGroupSafe2DeltaTPos2, AdPrimPSSGroupSafe2DeltaTPos3, AdPrimPSSGroupSafe2DeltaTPos4, AdPrimPSSGroupSafe2DeltaTPos5, AdPrimPSSGroupSafe2DeltaTPos6, AdPrimPSSGroupSafe2DeltaXPos1, AdPrimPSSGroupSafe2DeltaXPos2, AdPrimPSSGroupSafe2DeltaXPos3, AdPrimPSSGroupSafe2DeltaXPos4, AdPrimPSSGroupSafe2DeltaXPos5, AdPrimPSSGroupSafe2DeltaXPos6, AdPrimPSSGroupSafe2DeltaYPos1, AdPrimPSSGroupSafe2DeltaYPos2, AdPrimPSSGroupSafe2DeltaYPos3, AdPrimPSSGroupSafe2DeltaYPos4, AdPrimPSSGroupSafe2DeltaYPos5, AdPrimPSSGroupSafe2DeltaYPos6, AdPrimPSSGroupSafe2HeadingPos1, AdPrimPSSGroupSafe2HeadingPos2, AdPrimPSSGroupSafe2HeadingPos3, AdPrimPSSGroupSafe2HeadingPos4, AdPrimPSSGroupSafe2HeadingPos5, AdPrimPSSGroupSafe2HeadingPos6, AdPrimPSSGroupSafe2TrajectID }, { E2EProfileType::P05, AdPrimPSSGroupSafe2Chks, AdPrimPSSGroupSafe2Cntr }, VIMMid5CanFdFr05 } } );

    frames_info.insert({ VIMMid5CanFdFr05, { VIMMid5CanFdFr05, 72, 64, 90, { AdPrimPSSGroupSafe2 }, { AdPrimPSSGroupSafe2_UB } } });

    frame_ids.insert({ 72, VIMMid5CanFdFr05 });
}


}
}
