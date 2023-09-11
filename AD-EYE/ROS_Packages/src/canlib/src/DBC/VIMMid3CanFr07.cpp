#include "VIMMid3CanFr07.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr07_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AutnmsDrvStReq_UB, { AutnmsDrvStReq_UB, 31, 1, SignalType::APP_UNSIGNED, VIMMid3CanFr07 } });
    signals_info.insert({ AutnmsDrvStReqAutnmsDrvStReq, { AutnmsDrvStReqAutnmsDrvStReq, 15, 2, SignalType::APP_UNSIGNED, AutnmsDrvStReq } });
    signals_info.insert({ AutnmsDrvStReqChecksum, { AutnmsDrvStReqChecksum, 7, 8, SignalType::E2E_CHKS, AutnmsDrvStReq } });
    signals_info.insert({ AutnmsDrvStReqCounter, { AutnmsDrvStReqCounter, 5, 4, SignalType::E2E_CNTR, AutnmsDrvStReq } });

    signalgroups_info.insert(
    {
        AutnmsDrvStReq,
        {
            AutnmsDrvStReq,
            0x1F7,
            {
                AutnmsDrvStReqAutnmsDrvStReq,
                AutnmsDrvStReqChecksum,
                AutnmsDrvStReqCounter
            }, 
            { E2EProfileType::P01a, AutnmsDrvStReqChecksum, AutnmsDrvStReqCounter },
            VIMMid3CanFr07
        }
    });

    frames_info.insert({ VIMMid3CanFr07, { VIMMid3CanFr07, 46, 8, 10, { AutnmsDrvStReq }, { AutnmsDrvStReq_UB } } });

    frame_ids.insert({ 46, VIMMid3CanFr07 });
}


}
}
