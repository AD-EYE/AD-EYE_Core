#include "VIMBMid6CanFdFr21.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr21_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecPSSGroupSafe2Chks, { AdSecPSSGroupSafe2Chks, 0, 16, false, SignalType::E2E_CHKS, 0, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2Cntr, { AdSecPSSGroupSafe2Cntr, 16, 8, false, SignalType::E2E_CNTR, 0, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DataID, { AdSecPSSGroupSafe2DataID, 24, 16, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaTPos1, { AdSecPSSGroupSafe2DeltaTPos1, 40, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaTPos2, { AdSecPSSGroupSafe2DeltaTPos2, 64, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaTPos3, { AdSecPSSGroupSafe2DeltaTPos3, 88, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaTPos4, { AdSecPSSGroupSafe2DeltaTPos4, 112, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaTPos5, { AdSecPSSGroupSafe2DeltaTPos5, 136, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaTPos6, { AdSecPSSGroupSafe2DeltaTPos6, 160, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaXPos1, { AdSecPSSGroupSafe2DeltaXPos1, 184, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaXPos2, { AdSecPSSGroupSafe2DeltaXPos2, 202, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaXPos3, { AdSecPSSGroupSafe2DeltaXPos3, 220, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaXPos4, { AdSecPSSGroupSafe2DeltaXPos4, 238, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaXPos5, { AdSecPSSGroupSafe2DeltaXPos5, 256, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaXPos6, { AdSecPSSGroupSafe2DeltaXPos6, 274, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaYPos1, { AdSecPSSGroupSafe2DeltaYPos1, 292, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaYPos2, { AdSecPSSGroupSafe2DeltaYPos2, 310, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaYPos3, { AdSecPSSGroupSafe2DeltaYPos3, 328, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaYPos4, { AdSecPSSGroupSafe2DeltaYPos4, 346, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaYPos5, { AdSecPSSGroupSafe2DeltaYPos5, 364, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2DeltaYPos6, { AdSecPSSGroupSafe2DeltaYPos6, 382, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2HeadingPos1, { AdSecPSSGroupSafe2HeadingPos1, 400, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2HeadingPos2, { AdSecPSSGroupSafe2HeadingPos2, 416, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2HeadingPos3, { AdSecPSSGroupSafe2HeadingPos3, 432, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2HeadingPos4, { AdSecPSSGroupSafe2HeadingPos4, 448, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2HeadingPos5, { AdSecPSSGroupSafe2HeadingPos5, 464, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2HeadingPos6, { AdSecPSSGroupSafe2HeadingPos6, 480, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2TrajectID, { AdSecPSSGroupSafe2TrajectID, 496, 4, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe2, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe2_UB, { AdSecPSSGroupSafe2_UB, 511, 1, true, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr21, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecPSSGroupSafe2, { AdSecPSSGroupSafe2, 0x2C3, { AdSecPSSGroupSafe2Chks, AdSecPSSGroupSafe2Cntr, AdSecPSSGroupSafe2DataID, AdSecPSSGroupSafe2DeltaTPos1, AdSecPSSGroupSafe2DeltaTPos2, AdSecPSSGroupSafe2DeltaTPos3, AdSecPSSGroupSafe2DeltaTPos4, AdSecPSSGroupSafe2DeltaTPos5, AdSecPSSGroupSafe2DeltaTPos6, AdSecPSSGroupSafe2DeltaXPos1, AdSecPSSGroupSafe2DeltaXPos2, AdSecPSSGroupSafe2DeltaXPos3, AdSecPSSGroupSafe2DeltaXPos4, AdSecPSSGroupSafe2DeltaXPos5, AdSecPSSGroupSafe2DeltaXPos6, AdSecPSSGroupSafe2DeltaYPos1, AdSecPSSGroupSafe2DeltaYPos2, AdSecPSSGroupSafe2DeltaYPos3, AdSecPSSGroupSafe2DeltaYPos4, AdSecPSSGroupSafe2DeltaYPos5, AdSecPSSGroupSafe2DeltaYPos6, AdSecPSSGroupSafe2HeadingPos1, AdSecPSSGroupSafe2HeadingPos2, AdSecPSSGroupSafe2HeadingPos3, AdSecPSSGroupSafe2HeadingPos4, AdSecPSSGroupSafe2HeadingPos5, AdSecPSSGroupSafe2HeadingPos6, AdSecPSSGroupSafe2TrajectID }, { E2EProfileType::P05, AdSecPSSGroupSafe2Chks, AdSecPSSGroupSafe2Cntr }, VIMBMid6CanFdFr21 } } );

    frames_info.insert({ VIMBMid6CanFdFr21, { VIMBMid6CanFdFr21, 281, 64, 90, { AdSecPSSGroupSafe2 }, { AdSecPSSGroupSafe2_UB } } });

    frame_ids.insert({ 281, VIMBMid6CanFdFr21 });
}


}
}
