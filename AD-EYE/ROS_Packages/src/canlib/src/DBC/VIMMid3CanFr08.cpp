#include "VIMMid3CanFr08.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr08_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ VehOperStReq_UB, { VehOperStReq_UB, 31, 1, SignalType::APP_UNSIGNED, VIMMid3CanFr08 } });
    signals_info.insert({ VehOperStReqChecksum, { VehOperStReqChecksum, 0, 8, SignalType::E2E_CHKS, VehOperStReq } });
    signals_info.insert({ VehOperStReqCounter, { VehOperStReqCounter, 8, 4, SignalType::E2E_CNTR, VehOperStReq } });
    signals_info.insert({ VehOperStReqVehOperStReq, { VehOperStReqVehOperStReq, 16, 2, SignalType::APP_UNSIGNED, VehOperStReq } });

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
