#include "VIMMid3CanFr08.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr08_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ VehOperStReq_UB, { VehOperStReq_UB, 4, 1, SignalType::APP_UNSIGNED, VIMMid3CanFr08 } });
    signals_info.insert({ VehOperStReqChecksum, { VehOperStReqChecksum, 8, 12, SignalType::APP_UNSIGNED, VehOperStReq } });
    signals_info.insert({ VehOperStReqCounter, { VehOperStReqCounter, 8, 12, SignalType::APP_UNSIGNED, VehOperStReq } });
    signals_info.insert({ VehOperStReqVehOperStReq, { VehOperStReqVehOperStReq, 32, 8, SignalType::E2E_CHKS, VehOperStReq } });

    signalgroups_info.insert(
    {
        VehOperStReq,
        {
            VehOperStReq,
            0x1F6,
            {
                VehOperStReqChecksum,
                VehOperStReqCounter,
                VehOperStReqVehOperStReq
            }, 
            { E2EProfileType::P01a, VehOperStReqChecksum, VehOperStReqCounter },
            VIMMid3CanFr08
        }
    });

    frames_info.insert({ VIMMid3CanFr08, { VIMMid3CanFr08, 293, 8, 200, { VehOperStReq }, { VehOperStReq_UB } } });

    frame_ids.insert({ 293, VIMMid3CanFr08 });
}


}
}
