#include "VIMBMid6CanFdFr27.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr27_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecPSSGroupSafe8Chks, { AdSecPSSGroupSafe8Chks, 0, 16, false, SignalType::E2E_CHKS, 0, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8Cntr, { AdSecPSSGroupSafe8Cntr, 16, 8, false, SignalType::E2E_CNTR, 0, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DataID, { AdSecPSSGroupSafe8DataID, 24, 16, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaTPos1, { AdSecPSSGroupSafe8DeltaTPos1, 40, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaTPos2, { AdSecPSSGroupSafe8DeltaTPos2, 64, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaTPos3, { AdSecPSSGroupSafe8DeltaTPos3, 88, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaTPos4, { AdSecPSSGroupSafe8DeltaTPos4, 112, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaTPos5, { AdSecPSSGroupSafe8DeltaTPos5, 136, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaTPos6, { AdSecPSSGroupSafe8DeltaTPos6, 160, 18, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaXPos1, { AdSecPSSGroupSafe8DeltaXPos1, 184, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaXPos2, { AdSecPSSGroupSafe8DeltaXPos2, 202, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaXPos3, { AdSecPSSGroupSafe8DeltaXPos3, 220, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaXPos4, { AdSecPSSGroupSafe8DeltaXPos4, 238, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaXPos5, { AdSecPSSGroupSafe8DeltaXPos5, 256, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaXPos6, { AdSecPSSGroupSafe8DeltaXPos6, 274, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaYPos1, { AdSecPSSGroupSafe8DeltaYPos1, 292, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaYPos2, { AdSecPSSGroupSafe8DeltaYPos2, 310, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaYPos3, { AdSecPSSGroupSafe8DeltaYPos3, 328, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaYPos4, { AdSecPSSGroupSafe8DeltaYPos4, 346, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaYPos5, { AdSecPSSGroupSafe8DeltaYPos5, 364, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8DeltaYPos6, { AdSecPSSGroupSafe8DeltaYPos6, 382, 18, false, SignalType::APP_UNSIGNED, 131070, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8HeadingPos1, { AdSecPSSGroupSafe8HeadingPos1, 400, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8HeadingPos2, { AdSecPSSGroupSafe8HeadingPos2, 416, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8HeadingPos3, { AdSecPSSGroupSafe8HeadingPos3, 432, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8HeadingPos4, { AdSecPSSGroupSafe8HeadingPos4, 448, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8HeadingPos5, { AdSecPSSGroupSafe8HeadingPos5, 464, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8HeadingPos6, { AdSecPSSGroupSafe8HeadingPos6, 480, 16, false, SignalType::APP_UNSIGNED, 32767, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8TrajectID, { AdSecPSSGroupSafe8TrajectID, 496, 4, false, SignalType::APP_UNSIGNED, 0, AdSecPSSGroupSafe8, ParentType::GROUP } });
    signals_info.insert({ AdSecPSSGroupSafe8_UB, { AdSecPSSGroupSafe8_UB, 511, 1, true, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr27, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecPSSGroupSafe8, { AdSecPSSGroupSafe8, 0x423, { AdSecPSSGroupSafe8Chks, AdSecPSSGroupSafe8Cntr, AdSecPSSGroupSafe8DataID, AdSecPSSGroupSafe8DeltaTPos1, AdSecPSSGroupSafe8DeltaTPos2, AdSecPSSGroupSafe8DeltaTPos3, AdSecPSSGroupSafe8DeltaTPos4, AdSecPSSGroupSafe8DeltaTPos5, AdSecPSSGroupSafe8DeltaTPos6, AdSecPSSGroupSafe8DeltaXPos1, AdSecPSSGroupSafe8DeltaXPos2, AdSecPSSGroupSafe8DeltaXPos3, AdSecPSSGroupSafe8DeltaXPos4, AdSecPSSGroupSafe8DeltaXPos5, AdSecPSSGroupSafe8DeltaXPos6, AdSecPSSGroupSafe8DeltaYPos1, AdSecPSSGroupSafe8DeltaYPos2, AdSecPSSGroupSafe8DeltaYPos3, AdSecPSSGroupSafe8DeltaYPos4, AdSecPSSGroupSafe8DeltaYPos5, AdSecPSSGroupSafe8DeltaYPos6, AdSecPSSGroupSafe8HeadingPos1, AdSecPSSGroupSafe8HeadingPos2, AdSecPSSGroupSafe8HeadingPos3, AdSecPSSGroupSafe8HeadingPos4, AdSecPSSGroupSafe8HeadingPos5, AdSecPSSGroupSafe8HeadingPos6, AdSecPSSGroupSafe8TrajectID }, { E2EProfileType::P05, AdSecPSSGroupSafe8Chks, AdSecPSSGroupSafe8Cntr }, VIMBMid6CanFdFr27 } } );

    frames_info.insert({ VIMBMid6CanFdFr27, { VIMBMid6CanFdFr27, 296, 64, 90, { AdSecPSSGroupSafe8 }, { AdSecPSSGroupSafe8_UB } } });

    frame_ids.insert({ 296, VIMBMid6CanFdFr27 });
}


}
}
