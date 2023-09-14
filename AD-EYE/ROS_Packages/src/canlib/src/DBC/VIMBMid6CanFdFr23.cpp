#include "VIMBMid6CanFdFr23.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr23_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecPSSGroupSafe4Chks, { AdSecPSSGroupSafe4Chks, 0, 16, SignalType::E2E_CHKS, 0, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4Cntr, { AdSecPSSGroupSafe4Cntr, 16, 8, SignalType::E2E_CNTR, 0, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DataID, { AdSecPSSGroupSafe4DataID, 24, 16, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaTPos1, { AdSecPSSGroupSafe4DeltaTPos1, 40, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaTPos2, { AdSecPSSGroupSafe4DeltaTPos2, 64, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaTPos3, { AdSecPSSGroupSafe4DeltaTPos3, 88, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaTPos4, { AdSecPSSGroupSafe4DeltaTPos4, 112, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaTPos5, { AdSecPSSGroupSafe4DeltaTPos5, 136, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaTPos6, { AdSecPSSGroupSafe4DeltaTPos6, 160, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaXPos1, { AdSecPSSGroupSafe4DeltaXPos1, 184, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaXPos2, { AdSecPSSGroupSafe4DeltaXPos2, 202, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaXPos3, { AdSecPSSGroupSafe4DeltaXPos3, 220, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaXPos4, { AdSecPSSGroupSafe4DeltaXPos4, 238, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaXPos5, { AdSecPSSGroupSafe4DeltaXPos5, 256, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaXPos6, { AdSecPSSGroupSafe4DeltaXPos6, 274, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaYPos1, { AdSecPSSGroupSafe4DeltaYPos1, 292, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaYPos2, { AdSecPSSGroupSafe4DeltaYPos2, 310, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaYPos3, { AdSecPSSGroupSafe4DeltaYPos3, 328, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaYPos4, { AdSecPSSGroupSafe4DeltaYPos4, 346, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaYPos5, { AdSecPSSGroupSafe4DeltaYPos5, 364, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4DeltaYPos6, { AdSecPSSGroupSafe4DeltaYPos6, 382, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4HeadingPos1, { AdSecPSSGroupSafe4HeadingPos1, 400, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4HeadingPos2, { AdSecPSSGroupSafe4HeadingPos2, 416, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4HeadingPos3, { AdSecPSSGroupSafe4HeadingPos3, 432, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4HeadingPos4, { AdSecPSSGroupSafe4HeadingPos4, 448, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4HeadingPos5, { AdSecPSSGroupSafe4HeadingPos5, 464, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4HeadingPos6, { AdSecPSSGroupSafe4HeadingPos6, 480, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4TrajectID, { AdSecPSSGroupSafe4TrajectID, 496, 4, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe4, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe4_UB, { AdSecPSSGroupSafe4_UB, 511, 1, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr23, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecPSSGroupSafe4, { AdSecPSSGroupSafe4, 0x2C5, { AdSecPSSGroupSafe4Chks, AdSecPSSGroupSafe4Cntr, AdSecPSSGroupSafe4DataID, AdSecPSSGroupSafe4DeltaTPos1, AdSecPSSGroupSafe4DeltaTPos2, AdSecPSSGroupSafe4DeltaTPos3, AdSecPSSGroupSafe4DeltaTPos4, AdSecPSSGroupSafe4DeltaTPos5, AdSecPSSGroupSafe4DeltaTPos6, AdSecPSSGroupSafe4DeltaXPos1, AdSecPSSGroupSafe4DeltaXPos2, AdSecPSSGroupSafe4DeltaXPos3, AdSecPSSGroupSafe4DeltaXPos4, AdSecPSSGroupSafe4DeltaXPos5, AdSecPSSGroupSafe4DeltaXPos6, AdSecPSSGroupSafe4DeltaYPos1, AdSecPSSGroupSafe4DeltaYPos2, AdSecPSSGroupSafe4DeltaYPos3, AdSecPSSGroupSafe4DeltaYPos4, AdSecPSSGroupSafe4DeltaYPos5, AdSecPSSGroupSafe4DeltaYPos6, AdSecPSSGroupSafe4HeadingPos1, AdSecPSSGroupSafe4HeadingPos2, AdSecPSSGroupSafe4HeadingPos3, AdSecPSSGroupSafe4HeadingPos4, AdSecPSSGroupSafe4HeadingPos5, AdSecPSSGroupSafe4HeadingPos6, AdSecPSSGroupSafe4TrajectID }, { E2EProfileType::P05, AdSecPSSGroupSafe4Chks, AdSecPSSGroupSafe4Cntr }, VIMBMid6CanFdFr23 } } );

    frames_info.insert({ VIMBMid6CanFdFr23, { VIMBMid6CanFdFr23, 286, 64, 90, { AdSecPSSGroupSafe4 }, { AdSecPSSGroupSafe4_UB } } });

    frame_ids.insert({ 286, VIMBMid6CanFdFr23 });
}


}
}
