#include "VCU1Mid3CanFr24.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr24_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ PrimSteerMotTqSteerMotTq, { PrimSteerMotTqSteerMotTq, 8, 14, SignalType::APP_SIGNED, 0, PrimSteerMotTq, ParentType::GROUP } });
    signals_info.insert({ PrimSteerMotTqSteerMotTqQf, { PrimSteerMotTqSteerMotTqQf, 6, 2, SignalType::APP_UNSIGNED, 1, PrimSteerMotTq, ParentType::GROUP } });
    signals_info.insert({ PrimSteerMotTq_UB, { PrimSteerMotTq_UB, 23, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr24, ParentType::FRAME } });

    signalgroups_info.insert({ PrimSteerMotTq, { PrimSteerMotTq, 0x0, { PrimSteerMotTqSteerMotTq, PrimSteerMotTqSteerMotTqQf }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr24 } } );

    frames_info.insert({ VCU1Mid3CanFr24, { VCU1Mid3CanFr24, 120, 8, 15, { PrimSteerMotTq }, { PrimSteerMotTq_UB } } });

    frame_ids.insert({ 120, VCU1Mid3CanFr24 });
}


}
}
