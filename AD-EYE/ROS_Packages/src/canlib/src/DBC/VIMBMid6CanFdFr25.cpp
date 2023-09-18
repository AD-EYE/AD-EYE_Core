#include "VIMBMid6CanFdFr25.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr25_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecPSSGroupSafe6Chks, { AdSecPSSGroupSafe6Chks, 0, 16, false, SignalType::E2E_CHKS, 0, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6Cntr, { AdSecPSSGroupSafe6Cntr, 16, 8, false, SignalType::E2E_CNTR, 0, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DataID, { AdSecPSSGroupSafe6DataID, 24, 16, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaTPos1, { AdSecPSSGroupSafe6DeltaTPos1, 40, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaTPos2, { AdSecPSSGroupSafe6DeltaTPos2, 64, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaTPos3, { AdSecPSSGroupSafe6DeltaTPos3, 88, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaTPos4, { AdSecPSSGroupSafe6DeltaTPos4, 112, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaTPos5, { AdSecPSSGroupSafe6DeltaTPos5, 136, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaTPos6, { AdSecPSSGroupSafe6DeltaTPos6, 160, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaXPos1, { AdSecPSSGroupSafe6DeltaXPos1, 184, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaXPos2, { AdSecPSSGroupSafe6DeltaXPos2, 202, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaXPos3, { AdSecPSSGroupSafe6DeltaXPos3, 220, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaXPos4, { AdSecPSSGroupSafe6DeltaXPos4, 238, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaXPos5, { AdSecPSSGroupSafe6DeltaXPos5, 256, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaXPos6, { AdSecPSSGroupSafe6DeltaXPos6, 274, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaYPos1, { AdSecPSSGroupSafe6DeltaYPos1, 292, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaYPos2, { AdSecPSSGroupSafe6DeltaYPos2, 310, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaYPos3, { AdSecPSSGroupSafe6DeltaYPos3, 328, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaYPos4, { AdSecPSSGroupSafe6DeltaYPos4, 346, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaYPos5, { AdSecPSSGroupSafe6DeltaYPos5, 364, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6DeltaYPos6, { AdSecPSSGroupSafe6DeltaYPos6, 382, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6HeadingPos1, { AdSecPSSGroupSafe6HeadingPos1, 400, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6HeadingPos2, { AdSecPSSGroupSafe6HeadingPos2, 416, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6HeadingPos3, { AdSecPSSGroupSafe6HeadingPos3, 432, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6HeadingPos4, { AdSecPSSGroupSafe6HeadingPos4, 448, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6HeadingPos5, { AdSecPSSGroupSafe6HeadingPos5, 464, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6HeadingPos6, { AdSecPSSGroupSafe6HeadingPos6, 480, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6TrajectID, { AdSecPSSGroupSafe6TrajectID, 496, 4, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe6, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe6_UB, { AdSecPSSGroupSafe6_UB, 511, 1, true, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr25, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecPSSGroupSafe6, { AdSecPSSGroupSafe6, 0x2CA, { AdSecPSSGroupSafe6Chks, AdSecPSSGroupSafe6Cntr, AdSecPSSGroupSafe6DataID, AdSecPSSGroupSafe6DeltaTPos1, AdSecPSSGroupSafe6DeltaTPos2, AdSecPSSGroupSafe6DeltaTPos3, AdSecPSSGroupSafe6DeltaTPos4, AdSecPSSGroupSafe6DeltaTPos5, AdSecPSSGroupSafe6DeltaTPos6, AdSecPSSGroupSafe6DeltaXPos1, AdSecPSSGroupSafe6DeltaXPos2, AdSecPSSGroupSafe6DeltaXPos3, AdSecPSSGroupSafe6DeltaXPos4, AdSecPSSGroupSafe6DeltaXPos5, AdSecPSSGroupSafe6DeltaXPos6, AdSecPSSGroupSafe6DeltaYPos1, AdSecPSSGroupSafe6DeltaYPos2, AdSecPSSGroupSafe6DeltaYPos3, AdSecPSSGroupSafe6DeltaYPos4, AdSecPSSGroupSafe6DeltaYPos5, AdSecPSSGroupSafe6DeltaYPos6, AdSecPSSGroupSafe6HeadingPos1, AdSecPSSGroupSafe6HeadingPos2, AdSecPSSGroupSafe6HeadingPos3, AdSecPSSGroupSafe6HeadingPos4, AdSecPSSGroupSafe6HeadingPos5, AdSecPSSGroupSafe6HeadingPos6, AdSecPSSGroupSafe6TrajectID }, { E2EProfileType::P05, AdSecPSSGroupSafe6Chks, AdSecPSSGroupSafe6Cntr }, VIMBMid6CanFdFr25 } } );

    frames_info.insert({ VIMBMid6CanFdFr25, { VIMBMid6CanFdFr25, 292, 64, 90, { AdSecPSSGroupSafe6 }, { AdSecPSSGroupSafe6_UB } } });

    frame_ids.insert({ 292, VIMBMid6CanFdFr25 });
}


}
}
