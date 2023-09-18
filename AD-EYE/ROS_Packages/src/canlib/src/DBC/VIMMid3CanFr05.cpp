#include "VIMMid3CanFr05.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr05_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ ExtDcDcActvnSts2, { ExtDcDcActvnSts2, 6, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ ExtDcDcActvnSts2_UB, { ExtDcDcActvnSts2_UB, 7, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr05, ParentType::FRAME } });


    frames_info.insert({ VIMMid3CanFr05, { VIMMid3CanFr05, 35, 8, 15, {  }, { ExtDcDcActvnSts2_UB, ExtDcDcActvnSts2 } } });

    frame_ids.insert({ 35, VIMMid3CanFr05 });
}


}
}
