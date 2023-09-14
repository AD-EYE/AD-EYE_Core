#include "VIMBMid6CanFdFr24.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr24_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecPSSGroupSafe5Chks, { AdSecPSSGroupSafe5Chks, 0, 16, SignalType::E2E_CHKS, 0, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5Cntr, { AdSecPSSGroupSafe5Cntr, 16, 8, SignalType::E2E_CNTR, 0, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DataID, { AdSecPSSGroupSafe5DataID, 24, 16, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaTPos1, { AdSecPSSGroupSafe5DeltaTPos1, 40, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaTPos2, { AdSecPSSGroupSafe5DeltaTPos2, 64, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaTPos3, { AdSecPSSGroupSafe5DeltaTPos3, 88, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaTPos4, { AdSecPSSGroupSafe5DeltaTPos4, 112, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaTPos5, { AdSecPSSGroupSafe5DeltaTPos5, 136, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaTPos6, { AdSecPSSGroupSafe5DeltaTPos6, 160, 18, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaXPos1, { AdSecPSSGroupSafe5DeltaXPos1, 184, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaXPos2, { AdSecPSSGroupSafe5DeltaXPos2, 202, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaXPos3, { AdSecPSSGroupSafe5DeltaXPos3, 220, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaXPos4, { AdSecPSSGroupSafe5DeltaXPos4, 238, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaXPos5, { AdSecPSSGroupSafe5DeltaXPos5, 256, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaXPos6, { AdSecPSSGroupSafe5DeltaXPos6, 274, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaYPos1, { AdSecPSSGroupSafe5DeltaYPos1, 292, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaYPos2, { AdSecPSSGroupSafe5DeltaYPos2, 310, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaYPos3, { AdSecPSSGroupSafe5DeltaYPos3, 328, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaYPos4, { AdSecPSSGroupSafe5DeltaYPos4, 346, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaYPos5, { AdSecPSSGroupSafe5DeltaYPos5, 364, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5DeltaYPos6, { AdSecPSSGroupSafe5DeltaYPos6, 382, 18, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5HeadingPos1, { AdSecPSSGroupSafe5HeadingPos1, 400, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5HeadingPos2, { AdSecPSSGroupSafe5HeadingPos2, 416, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5HeadingPos3, { AdSecPSSGroupSafe5HeadingPos3, 432, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5HeadingPos4, { AdSecPSSGroupSafe5HeadingPos4, 448, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5HeadingPos5, { AdSecPSSGroupSafe5HeadingPos5, 464, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5HeadingPos6, { AdSecPSSGroupSafe5HeadingPos6, 480, 16, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5TrajectID, { AdSecPSSGroupSafe5TrajectID, 496, 4, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe5, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe5_UB, { AdSecPSSGroupSafe5_UB, 511, 1, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr24, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecPSSGroupSafe5, { AdSecPSSGroupSafe5, 0x2C6, { AdSecPSSGroupSafe5Chks, AdSecPSSGroupSafe5Cntr, AdSecPSSGroupSafe5DataID, AdSecPSSGroupSafe5DeltaTPos1, AdSecPSSGroupSafe5DeltaTPos2, AdSecPSSGroupSafe5DeltaTPos3, AdSecPSSGroupSafe5DeltaTPos4, AdSecPSSGroupSafe5DeltaTPos5, AdSecPSSGroupSafe5DeltaTPos6, AdSecPSSGroupSafe5DeltaXPos1, AdSecPSSGroupSafe5DeltaXPos2, AdSecPSSGroupSafe5DeltaXPos3, AdSecPSSGroupSafe5DeltaXPos4, AdSecPSSGroupSafe5DeltaXPos5, AdSecPSSGroupSafe5DeltaXPos6, AdSecPSSGroupSafe5DeltaYPos1, AdSecPSSGroupSafe5DeltaYPos2, AdSecPSSGroupSafe5DeltaYPos3, AdSecPSSGroupSafe5DeltaYPos4, AdSecPSSGroupSafe5DeltaYPos5, AdSecPSSGroupSafe5DeltaYPos6, AdSecPSSGroupSafe5HeadingPos1, AdSecPSSGroupSafe5HeadingPos2, AdSecPSSGroupSafe5HeadingPos3, AdSecPSSGroupSafe5HeadingPos4, AdSecPSSGroupSafe5HeadingPos5, AdSecPSSGroupSafe5HeadingPos6, AdSecPSSGroupSafe5TrajectID }, { E2EProfileType::P05, AdSecPSSGroupSafe5Chks, AdSecPSSGroupSafe5Cntr }, VIMBMid6CanFdFr24 } } );

    frames_info.insert({ VIMBMid6CanFdFr24, { VIMBMid6CanFdFr24, 289, 64, 90, { AdSecPSSGroupSafe5 }, { AdSecPSSGroupSafe5_UB } } });

    frame_ids.insert({ 289, VIMBMid6CanFdFr24 });
}


}
}
