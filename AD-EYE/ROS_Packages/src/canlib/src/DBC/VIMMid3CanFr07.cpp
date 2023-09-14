#include "VIMMid3CanFr07.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr07_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AutnmsDrvStReqAutnmsDrvStReq, { AutnmsDrvStReqAutnmsDrvStReq, 16, 2, SignalType::APP_UNSIGNED, 0, AutnmsDrvStReq, ParentType::GROUP } });
    signals_info.insert({ AutnmsDrvStReqChecksum, { AutnmsDrvStReqChecksum, 0, 8, SignalType::E2E_CHKS, 0, AutnmsDrvStReq, ParentType::GROUP } });
    signals_info.insert({ AutnmsDrvStReqCounter, { AutnmsDrvStReqCounter, 8, 4, SignalType::E2E_CNTR, 0, AutnmsDrvStReq, ParentType::GROUP } });
    signals_info.insert({ AutnmsDrvStReq_UB, { AutnmsDrvStReq_UB, 31, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr07, ParentType::FRAME } });

    signalgroups_info.insert({ AutnmsDrvStReq, { AutnmsDrvStReq, 0x1F7, { AutnmsDrvStReqAutnmsDrvStReq, AutnmsDrvStReqChecksum, AutnmsDrvStReqCounter }, { E2EProfileType::P01a, AutnmsDrvStReqChecksum, AutnmsDrvStReqCounter }, VIMMid3CanFr07 } } );

    frames_info.insert({ VIMMid3CanFr07, { VIMMid3CanFr07, 46, 8, 10, { AutnmsDrvStReq }, { AutnmsDrvStReq_UB } } });

    frame_ids.insert({ 46, VIMMid3CanFr07 });
}


}
}
