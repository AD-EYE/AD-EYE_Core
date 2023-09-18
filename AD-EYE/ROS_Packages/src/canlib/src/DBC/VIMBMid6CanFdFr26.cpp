#include "VIMBMid6CanFdFr26.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr26_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecPSSGroupSafe7Chks, { AdSecPSSGroupSafe7Chks, 0, 16, false, SignalType::E2E_CHKS, 0, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7Cntr, { AdSecPSSGroupSafe7Cntr, 16, 8, false, SignalType::E2E_CNTR, 0, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DataID, { AdSecPSSGroupSafe7DataID, 24, 16, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaTPos1, { AdSecPSSGroupSafe7DeltaTPos1, 40, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaTPos2, { AdSecPSSGroupSafe7DeltaTPos2, 64, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaTPos3, { AdSecPSSGroupSafe7DeltaTPos3, 88, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaTPos4, { AdSecPSSGroupSafe7DeltaTPos4, 112, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaTPos5, { AdSecPSSGroupSafe7DeltaTPos5, 136, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaTPos6, { AdSecPSSGroupSafe7DeltaTPos6, 160, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaXPos1, { AdSecPSSGroupSafe7DeltaXPos1, 184, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaXPos2, { AdSecPSSGroupSafe7DeltaXPos2, 202, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaXPos3, { AdSecPSSGroupSafe7DeltaXPos3, 220, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaXPos4, { AdSecPSSGroupSafe7DeltaXPos4, 238, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaXPos5, { AdSecPSSGroupSafe7DeltaXPos5, 256, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaXPos6, { AdSecPSSGroupSafe7DeltaXPos6, 274, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaYPos1, { AdSecPSSGroupSafe7DeltaYPos1, 292, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaYPos2, { AdSecPSSGroupSafe7DeltaYPos2, 310, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaYPos3, { AdSecPSSGroupSafe7DeltaYPos3, 328, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaYPos4, { AdSecPSSGroupSafe7DeltaYPos4, 346, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaYPos5, { AdSecPSSGroupSafe7DeltaYPos5, 364, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7DeltaYPos6, { AdSecPSSGroupSafe7DeltaYPos6, 382, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7HeadingPos1, { AdSecPSSGroupSafe7HeadingPos1, 400, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7HeadingPos2, { AdSecPSSGroupSafe7HeadingPos2, 416, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7HeadingPos3, { AdSecPSSGroupSafe7HeadingPos3, 432, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7HeadingPos4, { AdSecPSSGroupSafe7HeadingPos4, 448, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7HeadingPos5, { AdSecPSSGroupSafe7HeadingPos5, 464, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7HeadingPos6, { AdSecPSSGroupSafe7HeadingPos6, 480, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7TrajectID, { AdSecPSSGroupSafe7TrajectID, 496, 4, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe7, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe7_UB, { AdSecPSSGroupSafe7_UB, 511, 1, true, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr26, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecPSSGroupSafe7, { AdSecPSSGroupSafe7, 0x2CB, { AdSecPSSGroupSafe7Chks, AdSecPSSGroupSafe7Cntr, AdSecPSSGroupSafe7DataID, AdSecPSSGroupSafe7DeltaTPos1, AdSecPSSGroupSafe7DeltaTPos2, AdSecPSSGroupSafe7DeltaTPos3, AdSecPSSGroupSafe7DeltaTPos4, AdSecPSSGroupSafe7DeltaTPos5, AdSecPSSGroupSafe7DeltaTPos6, AdSecPSSGroupSafe7DeltaXPos1, AdSecPSSGroupSafe7DeltaXPos2, AdSecPSSGroupSafe7DeltaXPos3, AdSecPSSGroupSafe7DeltaXPos4, AdSecPSSGroupSafe7DeltaXPos5, AdSecPSSGroupSafe7DeltaXPos6, AdSecPSSGroupSafe7DeltaYPos1, AdSecPSSGroupSafe7DeltaYPos2, AdSecPSSGroupSafe7DeltaYPos3, AdSecPSSGroupSafe7DeltaYPos4, AdSecPSSGroupSafe7DeltaYPos5, AdSecPSSGroupSafe7DeltaYPos6, AdSecPSSGroupSafe7HeadingPos1, AdSecPSSGroupSafe7HeadingPos2, AdSecPSSGroupSafe7HeadingPos3, AdSecPSSGroupSafe7HeadingPos4, AdSecPSSGroupSafe7HeadingPos5, AdSecPSSGroupSafe7HeadingPos6, AdSecPSSGroupSafe7TrajectID }, { E2EProfileType::P05, AdSecPSSGroupSafe7Chks, AdSecPSSGroupSafe7Cntr }, VIMBMid6CanFdFr26 } } );

    frames_info.insert({ VIMBMid6CanFdFr26, { VIMBMid6CanFdFr26, 295, 64, 90, { AdSecPSSGroupSafe7 }, { AdSecPSSGroupSafe7_UB } } });

    frame_ids.insert({ 295, VIMBMid6CanFdFr26 });
}


}
}
