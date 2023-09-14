#include "VCU1Mid3CanFr06.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr06_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ CarTiGlb_UB, { CarTiGlb_UB, 39, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr06, ParentType::FRAME } });
    signals_info.insert({ CarTiGlb, { CarTiGlb, 24, 32, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr06, ParentType::FRAME } });


    frames_info.insert({ VCU1Mid3CanFr06, { VCU1Mid3CanFr06, 896, 8, 380, {  }, { CarTiGlb_UB, CarTiGlb } } });

    frame_ids.insert({ 896, VCU1Mid3CanFr06 });
}


}
}
