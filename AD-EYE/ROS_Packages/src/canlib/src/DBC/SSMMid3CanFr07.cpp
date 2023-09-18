#include "SSMMid3CanFr07.h"


namespace kcan {
namespace dbc {


void SSMMid3CanFr07_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ PrimVehSpdGroupSafeChks, { PrimVehSpdGroupSafeChks, 8, 8, true, SignalType::E2E_CHKS, 0, PrimVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehSpdGroupSafeCntr, { PrimVehSpdGroupSafeCntr, 0, 4, true, SignalType::E2E_CNTR, 0, PrimVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehSpdGroupSafeMax, { PrimVehSpdGroupSafeMax, 8, 13, true, SignalType::APP_UNSIGNED, 0, PrimVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehSpdGroupSafeMin, { PrimVehSpdGroupSafeMin, 24, 13, true, SignalType::APP_UNSIGNED, 0, PrimVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehSpdGroupSafeMinMaxQf, { PrimVehSpdGroupSafeMinMaxQf, 22, 2, true, SignalType::APP_UNSIGNED, 0, PrimVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehSpdGroupSafeMovDir, { PrimVehSpdGroupSafeMovDir, 4, 3, true, SignalType::APP_UNSIGNED, 0, PrimVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehSpdGroupSafeMovDirQf, { PrimVehSpdGroupSafeMovDirQf, 38, 2, true, SignalType::APP_UNSIGNED, 0, PrimVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehSpdGroupSafeNom, { PrimVehSpdGroupSafeNom, 40, 13, true, SignalType::APP_UNSIGNED, 0, PrimVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehSpdGroupSafeNomQf, { PrimVehSpdGroupSafeNomQf, 53, 2, true, SignalType::APP_UNSIGNED, 1, PrimVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehSpdGroupSafe_UB, { PrimVehSpdGroupSafe_UB, 7, 1, true, SignalType::APP_UNSIGNED, 0, SSMMid3CanFr07, ParentType::FRAME } });

    signalgroups_info.insert({ PrimVehSpdGroupSafe, { PrimVehSpdGroupSafe, 0x210, { PrimVehSpdGroupSafeChks, PrimVehSpdGroupSafeCntr, PrimVehSpdGroupSafeMax, PrimVehSpdGroupSafeMin, PrimVehSpdGroupSafeMinMaxQf, PrimVehSpdGroupSafeMovDir, PrimVehSpdGroupSafeMovDirQf, PrimVehSpdGroupSafeNom, PrimVehSpdGroupSafeNomQf }, { E2EProfileType::P01a, PrimVehSpdGroupSafeChks, PrimVehSpdGroupSafeCntr }, SSMMid3CanFr07 } } );

    frames_info.insert({ SSMMid3CanFr07, { SSMMid3CanFr07, 99, 8, 40, { PrimVehSpdGroupSafe }, { PrimVehSpdGroupSafe_UB } } });

    frame_ids.insert({ 99, SSMMid3CanFr07 });
}


}
}
