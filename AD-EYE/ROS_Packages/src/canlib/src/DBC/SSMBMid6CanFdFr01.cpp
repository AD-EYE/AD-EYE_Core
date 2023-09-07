#include "SSMBMid6CanFdFr01.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr01_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecSteerStsSafeGroup_UB, { AdSecSteerStsSafeGroup_UB, 4, 1, SignalType::APP_UNSIGNED, SSMBMid6CanFdFr01 } });
    signals_info.insert({ AdSecSteerStsSafeGroupAdSteerPerf, { AdSecSteerStsSafeGroupAdSteerPerf, 16, 5, SignalType::APP_UNSIGNED, AdSecSteerStsSafeGroup } });
    signals_info.insert({ AdSecSteerStsSafeGroupAdSteerSts, { AdSecSteerStsSafeGroupAdSteerSts, 21, 3, SignalType::APP_UNSIGNED, AdSecSteerStsSafeGroup } });
    signals_info.insert({ AdSecSteerStsSafeGroupChks, { AdSecSteerStsSafeGroupChks, 8, 8, SignalType::E2E_CHKS, AdSecSteerStsSafeGroup } });
    signals_info.insert({ AdSecSteerStsSafeGroupCntr, { AdSecSteerStsSafeGroupCntr, 0, 4, SignalType::E2E_CNTR, AdSecSteerStsSafeGroup } });
    
    signalgroups_info.insert(
    {
        AdSecSteerStsSafeGroup,
        {
            AdSecSteerStsSafeGroup,
            0x1A1,
            {
                AdSecSteerStsSafeGroupAdSteerPerf,
                AdSecSteerStsSafeGroupAdSteerSts,
                AdSecSteerStsSafeGroupChks,
                AdSecSteerStsSafeGroupCntr
            }, 
            { E2EProfileType::P01a, AdSecSteerStsSafeGroupChks, AdSecSteerStsSafeGroupCntr },
            SSMBMid6CanFdFr01
        }
    });

    frames_info.insert({ SSMBMid6CanFdFr01, { SSMBMid6CanFdFr01, 23, 8, 10, { AdSecSteerStsSafeGroup }, { AdSecSteerStsSafeGroup_UB } } });

    frame_ids.insert({ 23, SSMBMid6CanFdFr01 });
}


}
}