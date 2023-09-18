#include "VIMBMid6CanFdFr22.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr22_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecPSSGroupSafe3Chks, { AdSecPSSGroupSafe3Chks, 0, 16, false, SignalType::E2E_CHKS, 0, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3Cntr, { AdSecPSSGroupSafe3Cntr, 16, 8, false, SignalType::E2E_CNTR, 0, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DataID, { AdSecPSSGroupSafe3DataID, 24, 16, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaTPos1, { AdSecPSSGroupSafe3DeltaTPos1, 40, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaTPos2, { AdSecPSSGroupSafe3DeltaTPos2, 64, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaTPos3, { AdSecPSSGroupSafe3DeltaTPos3, 88, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaTPos4, { AdSecPSSGroupSafe3DeltaTPos4, 112, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaTPos5, { AdSecPSSGroupSafe3DeltaTPos5, 136, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaTPos6, { AdSecPSSGroupSafe3DeltaTPos6, 160, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaXPos1, { AdSecPSSGroupSafe3DeltaXPos1, 184, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaXPos2, { AdSecPSSGroupSafe3DeltaXPos2, 202, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaXPos3, { AdSecPSSGroupSafe3DeltaXPos3, 220, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaXPos4, { AdSecPSSGroupSafe3DeltaXPos4, 238, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaXPos5, { AdSecPSSGroupSafe3DeltaXPos5, 256, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaXPos6, { AdSecPSSGroupSafe3DeltaXPos6, 274, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaYPos1, { AdSecPSSGroupSafe3DeltaYPos1, 292, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaYPos2, { AdSecPSSGroupSafe3DeltaYPos2, 310, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaYPos3, { AdSecPSSGroupSafe3DeltaYPos3, 328, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaYPos4, { AdSecPSSGroupSafe3DeltaYPos4, 346, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaYPos5, { AdSecPSSGroupSafe3DeltaYPos5, 364, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3DeltaYPos6, { AdSecPSSGroupSafe3DeltaYPos6, 382, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3HeadingPos1, { AdSecPSSGroupSafe3HeadingPos1, 400, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3HeadingPos2, { AdSecPSSGroupSafe3HeadingPos2, 416, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3HeadingPos3, { AdSecPSSGroupSafe3HeadingPos3, 432, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3HeadingPos4, { AdSecPSSGroupSafe3HeadingPos4, 448, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3HeadingPos5, { AdSecPSSGroupSafe3HeadingPos5, 464, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3HeadingPos6, { AdSecPSSGroupSafe3HeadingPos6, 480, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3TrajectID, { AdSecPSSGroupSafe3TrajectID, 496, 4, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe3, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe3_UB, { AdSecPSSGroupSafe3_UB, 511, 1, true, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr22, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecPSSGroupSafe3, { AdSecPSSGroupSafe3, 0x2C4, { AdSecPSSGroupSafe3Chks, AdSecPSSGroupSafe3Cntr, AdSecPSSGroupSafe3DataID, AdSecPSSGroupSafe3DeltaTPos1, AdSecPSSGroupSafe3DeltaTPos2, AdSecPSSGroupSafe3DeltaTPos3, AdSecPSSGroupSafe3DeltaTPos4, AdSecPSSGroupSafe3DeltaTPos5, AdSecPSSGroupSafe3DeltaTPos6, AdSecPSSGroupSafe3DeltaXPos1, AdSecPSSGroupSafe3DeltaXPos2, AdSecPSSGroupSafe3DeltaXPos3, AdSecPSSGroupSafe3DeltaXPos4, AdSecPSSGroupSafe3DeltaXPos5, AdSecPSSGroupSafe3DeltaXPos6, AdSecPSSGroupSafe3DeltaYPos1, AdSecPSSGroupSafe3DeltaYPos2, AdSecPSSGroupSafe3DeltaYPos3, AdSecPSSGroupSafe3DeltaYPos4, AdSecPSSGroupSafe3DeltaYPos5, AdSecPSSGroupSafe3DeltaYPos6, AdSecPSSGroupSafe3HeadingPos1, AdSecPSSGroupSafe3HeadingPos2, AdSecPSSGroupSafe3HeadingPos3, AdSecPSSGroupSafe3HeadingPos4, AdSecPSSGroupSafe3HeadingPos5, AdSecPSSGroupSafe3HeadingPos6, AdSecPSSGroupSafe3TrajectID }, { E2EProfileType::P05, AdSecPSSGroupSafe3Chks, AdSecPSSGroupSafe3Cntr }, VIMBMid6CanFdFr22 } } );

    frames_info.insert({ VIMBMid6CanFdFr22, { VIMBMid6CanFdFr22, 283, 64, 90, { AdSecPSSGroupSafe3 }, { AdSecPSSGroupSafe3_UB } } });

    frame_ids.insert({ 283, VIMBMid6CanFdFr22 });
}


}
}
