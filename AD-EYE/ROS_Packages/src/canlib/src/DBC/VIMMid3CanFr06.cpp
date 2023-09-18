#include "VIMMid3CanFr06.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr06_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ ExtDcDcActvnSts, { ExtDcDcActvnSts, 29, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr06, ParentType::FRAME } });
    signals_info.insert({ ExtDcDcActvnSts_UB, { ExtDcDcActvnSts_UB, 30, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr06, ParentType::FRAME } });
    signals_info.insert({ HvIDcDcHiSideExt, { HvIDcDcHiSideExt, 48, 13, true, SignalType::APP_UNSIGNED, 4100, VIMMid3CanFr06, ParentType::FRAME } });
    signals_info.insert({ HvIDcDcHiSideExt_UB, { HvIDcDcHiSideExt_UB, 28, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr06, ParentType::FRAME } });
    signals_info.insert({ HvUDcDcHiSideExt, { HvUDcDcHiSideExt, 16, 11, true, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr06, ParentType::FRAME } });
    signals_info.insert({ HvUDcDcHiSideExt_UB, { HvUDcDcHiSideExt_UB, 27, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr06, ParentType::FRAME } });


    frames_info.insert({ VIMMid3CanFr06, { VIMMid3CanFr06, 40, 8, 10, {  }, { HvIDcDcHiSideExt_UB, ExtDcDcActvnSts, HvUDcDcHiSideExt_UB, ExtDcDcActvnSts_UB, HvIDcDcHiSideExt, HvUDcDcHiSideExt } } });

    frame_ids.insert({ 40, VIMMid3CanFr06 });
}


}
}
