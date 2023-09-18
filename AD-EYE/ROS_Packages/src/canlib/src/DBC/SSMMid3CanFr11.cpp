#include "SSMMid3CanFr11.h"


namespace kcan {
namespace dbc {


void SSMMid3CanFr11_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ PrimALgtDataRawSafeChks, { PrimALgtDataRawSafeChks, 8, 8, true, SignalType::E2E_CHKS, 0, PrimALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALgtDataRawSafeCntr, { PrimALgtDataRawSafeCntr, 0, 4, true, SignalType::E2E_CNTR, 0, PrimALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALgtDataRawSafeMax, { PrimALgtDataRawSafeMax, 25, 15, true, SignalType::APP_UNSIGNED, 16384, PrimALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALgtDataRawSafeMin, { PrimALgtDataRawSafeMin, 26, 15, true, SignalType::APP_UNSIGNED, 16384, PrimALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALgtDataRawSafeMinMaxQf, { PrimALgtDataRawSafeMinMaxQf, 5, 2, true, SignalType::APP_UNSIGNED, 0, PrimALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALgtDataRawSafeNom, { PrimALgtDataRawSafeNom, 56, 15, true, SignalType::APP_UNSIGNED, 16384, PrimALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALgtDataRawSafeNomQf, { PrimALgtDataRawSafeNomQf, 40, 2, true, SignalType::APP_UNSIGNED, 1, PrimALgtDataRawSafe, ParentType::GROUP } });
    signals_info.insert({ PrimALgtDataRawSafe_UB, { PrimALgtDataRawSafe_UB, 7, 1, true, SignalType::APP_UNSIGNED, 0, SSMMid3CanFr11, ParentType::FRAME } });

    signalgroups_info.insert({ PrimALgtDataRawSafe, { PrimALgtDataRawSafe, 0x20F, { PrimALgtDataRawSafeChks, PrimALgtDataRawSafeCntr, PrimALgtDataRawSafeMax, PrimALgtDataRawSafeMin, PrimALgtDataRawSafeMinMaxQf, PrimALgtDataRawSafeNom, PrimALgtDataRawSafeNomQf }, { E2EProfileType::P01a, PrimALgtDataRawSafeChks, PrimALgtDataRawSafeCntr }, SSMMid3CanFr11 } } );

    frames_info.insert({ SSMMid3CanFr11, { SSMMid3CanFr11, 52, 8, 10, { PrimALgtDataRawSafe }, { PrimALgtDataRawSafe_UB } } });

    frame_ids.insert({ 52, SSMMid3CanFr11 });
}


}
}
