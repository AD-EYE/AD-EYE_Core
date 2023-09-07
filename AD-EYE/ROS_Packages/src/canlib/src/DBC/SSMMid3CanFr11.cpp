#include "SSMMid3CanFr11.h"


namespace kcan {
namespace dbc {


void SSMMid3CanFr11_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ PrimALgtDataRawSafe_UB, { PrimALgtDataRawSafe_UB, 7, 1, SignalType::APP_UNSIGNED, SSMMid3CanFr11 } });
    signals_info.insert({ PrimALgtDataRawSafeChks, { PrimALgtDataRawSafeChks, 8, 8, SignalType::E2E_CHKS, PrimALgtDataRawSafe } });
    signals_info.insert({ PrimALgtDataRawSafeCntr, { PrimALgtDataRawSafeCntr, 0, 4, SignalType::E2E_CNTR, PrimALgtDataRawSafe } });
    signals_info.insert({ PrimALgtDataRawSafeMax, { PrimALgtDataRawSafeMax, 9, 15, SignalType::APP_UNSIGNED, PrimALgtDataRawSafe } });
    signals_info.insert({ PrimALgtDataRawSafeMin, { PrimALgtDataRawSafeMin, 10, 15, SignalType::APP_UNSIGNED, PrimALgtDataRawSafe } });
    signals_info.insert({ PrimALgtDataRawSafeMinMaxQf, { PrimALgtDataRawSafeMinMaxQf, 5, 2, SignalType::APP_UNSIGNED, PrimALgtDataRawSafe } });
    signals_info.insert({ PrimALgtDataRawSafeNom, { PrimALgtDataRawSafeNom, 40, 15, SignalType::APP_UNSIGNED, PrimALgtDataRawSafe } });
    signals_info.insert({ PrimALgtDataRawSafeNomQf, { PrimALgtDataRawSafeNomQf, 40, 2, SignalType::APP_UNSIGNED, PrimALgtDataRawSafe } });
    
    signalgroups_info.insert(
    {
        PrimALgtDataRawSafe,
        {
            PrimALgtDataRawSafe,
            0x20F,
            {
                PrimALgtDataRawSafeChks,
                PrimALgtDataRawSafeCntr,
                PrimALgtDataRawSafeMax,
                PrimALgtDataRawSafeMin,
                PrimALgtDataRawSafeMinMaxQf,
                PrimALgtDataRawSafeNom,
                PrimALgtDataRawSafeNomQf,
            }, 
            { E2EProfileType::P01a, PrimALgtDataRawSafeChks, PrimALgtDataRawSafeCntr},
            SSMMid3CanFr11
        }
    });

    frames_info.insert({ SSMMid3CanFr11, { SSMMid3CanFr11, 52, 8, 10, { PrimALgtDataRawSafe }, { PrimALgtDataRawSafe_UB } } });

    frame_ids.insert({ 52, SSMMid3CanFr11 });
}


}
}