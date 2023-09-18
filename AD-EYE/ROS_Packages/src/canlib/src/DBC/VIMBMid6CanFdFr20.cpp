#include "VIMBMid6CanFdFr20.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr20_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecPSSGroupSafe1Chks, { AdSecPSSGroupSafe1Chks, 0, 16, false, SignalType::E2E_CHKS, 0, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1Cntr, { AdSecPSSGroupSafe1Cntr, 16, 8, false, SignalType::E2E_CNTR, 0, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DataID, { AdSecPSSGroupSafe1DataID, 24, 16, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaTPos1, { AdSecPSSGroupSafe1DeltaTPos1, 40, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaTPos2, { AdSecPSSGroupSafe1DeltaTPos2, 64, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaTPos3, { AdSecPSSGroupSafe1DeltaTPos3, 88, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaTPos4, { AdSecPSSGroupSafe1DeltaTPos4, 112, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaTPos5, { AdSecPSSGroupSafe1DeltaTPos5, 136, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaTPos6, { AdSecPSSGroupSafe1DeltaTPos6, 160, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaXPos1, { AdSecPSSGroupSafe1DeltaXPos1, 184, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaXPos2, { AdSecPSSGroupSafe1DeltaXPos2, 202, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaXPos3, { AdSecPSSGroupSafe1DeltaXPos3, 220, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaXPos4, { AdSecPSSGroupSafe1DeltaXPos4, 238, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaXPos5, { AdSecPSSGroupSafe1DeltaXPos5, 256, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaXPos6, { AdSecPSSGroupSafe1DeltaXPos6, 274, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaYPos1, { AdSecPSSGroupSafe1DeltaYPos1, 292, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaYPos2, { AdSecPSSGroupSafe1DeltaYPos2, 310, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaYPos3, { AdSecPSSGroupSafe1DeltaYPos3, 328, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaYPos4, { AdSecPSSGroupSafe1DeltaYPos4, 346, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaYPos5, { AdSecPSSGroupSafe1DeltaYPos5, 364, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1DeltaYPos6, { AdSecPSSGroupSafe1DeltaYPos6, 382, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1HeadingPos1, { AdSecPSSGroupSafe1HeadingPos1, 400, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1HeadingPos2, { AdSecPSSGroupSafe1HeadingPos2, 416, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1HeadingPos3, { AdSecPSSGroupSafe1HeadingPos3, 432, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1HeadingPos4, { AdSecPSSGroupSafe1HeadingPos4, 448, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1HeadingPos5, { AdSecPSSGroupSafe1HeadingPos5, 464, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1HeadingPos6, { AdSecPSSGroupSafe1HeadingPos6, 480, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1TrajectID, { AdSecPSSGroupSafe1TrajectID, 496, 4, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe1, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe1_UB, { AdSecPSSGroupSafe1_UB, 511, 1, true, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr20, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecPSSGroupSafe1, { AdSecPSSGroupSafe1, 0x2C2, { AdSecPSSGroupSafe1Chks, AdSecPSSGroupSafe1Cntr, AdSecPSSGroupSafe1DataID, AdSecPSSGroupSafe1DeltaTPos1, AdSecPSSGroupSafe1DeltaTPos2, AdSecPSSGroupSafe1DeltaTPos3, AdSecPSSGroupSafe1DeltaTPos4, AdSecPSSGroupSafe1DeltaTPos5, AdSecPSSGroupSafe1DeltaTPos6, AdSecPSSGroupSafe1DeltaXPos1, AdSecPSSGroupSafe1DeltaXPos2, AdSecPSSGroupSafe1DeltaXPos3, AdSecPSSGroupSafe1DeltaXPos4, AdSecPSSGroupSafe1DeltaXPos5, AdSecPSSGroupSafe1DeltaXPos6, AdSecPSSGroupSafe1DeltaYPos1, AdSecPSSGroupSafe1DeltaYPos2, AdSecPSSGroupSafe1DeltaYPos3, AdSecPSSGroupSafe1DeltaYPos4, AdSecPSSGroupSafe1DeltaYPos5, AdSecPSSGroupSafe1DeltaYPos6, AdSecPSSGroupSafe1HeadingPos1, AdSecPSSGroupSafe1HeadingPos2, AdSecPSSGroupSafe1HeadingPos3, AdSecPSSGroupSafe1HeadingPos4, AdSecPSSGroupSafe1HeadingPos5, AdSecPSSGroupSafe1HeadingPos6, AdSecPSSGroupSafe1TrajectID }, { E2EProfileType::P05, AdSecPSSGroupSafe1Chks, AdSecPSSGroupSafe1Cntr }, VIMBMid6CanFdFr20 } } );

    frames_info.insert({ VIMBMid6CanFdFr20, { VIMBMid6CanFdFr20, 278, 64, 90, { AdSecPSSGroupSafe1 }, { AdSecPSSGroupSafe1_UB } } });

    frame_ids.insert({ 278, VIMBMid6CanFdFr20 });
}


}
}
