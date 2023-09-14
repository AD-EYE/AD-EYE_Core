#include "SSMBMid6CanFdFr07.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr07_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ SecVehSpdGroupSafeChks, { SecVehSpdGroupSafeChks, 8, 8, SignalType::E2E_CHKS, 0, SecVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehSpdGroupSafeCntr, { SecVehSpdGroupSafeCntr, 0, 4, SignalType::E2E_CNTR, 0, SecVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehSpdGroupSafeMax, { SecVehSpdGroupSafeMax, 8, 13, SignalType::APP_UNSIGNED, 0, SecVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehSpdGroupSafeMin, { SecVehSpdGroupSafeMin, 24, 13, SignalType::APP_UNSIGNED, 0, SecVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehSpdGroupSafeMinMaxQf, { SecVehSpdGroupSafeMinMaxQf, 22, 2, SignalType::APP_UNSIGNED, 0, SecVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehSpdGroupSafeMovDir, { SecVehSpdGroupSafeMovDir, 4, 3, SignalType::APP_UNSIGNED, 0, SecVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehSpdGroupSafeMovDirQf, { SecVehSpdGroupSafeMovDirQf, 38, 2, SignalType::APP_UNSIGNED, 0, SecVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehSpdGroupSafeNom, { SecVehSpdGroupSafeNom, 40, 13, SignalType::APP_UNSIGNED, 0, SecVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehSpdGroupSafeNomQf, { SecVehSpdGroupSafeNomQf, 53, 2, SignalType::APP_UNSIGNED, 1, SecVehSpdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehSpdGroupSafe_UB, { SecVehSpdGroupSafe_UB, 7, 1, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr07, ParentType::FRAME } });

    signalgroups_info.insert({ SecVehSpdGroupSafe, { SecVehSpdGroupSafe, 0x218, { SecVehSpdGroupSafeChks, SecVehSpdGroupSafeCntr, SecVehSpdGroupSafeMax, SecVehSpdGroupSafeMin, SecVehSpdGroupSafeMinMaxQf, SecVehSpdGroupSafeMovDir, SecVehSpdGroupSafeMovDirQf, SecVehSpdGroupSafeNom, SecVehSpdGroupSafeNomQf }, { E2EProfileType::P01a, SecVehSpdGroupSafeChks, SecVehSpdGroupSafeCntr }, SSMBMid6CanFdFr07 } } );

    frames_info.insert({ SSMBMid6CanFdFr07, { SSMBMid6CanFdFr07, 122, 8, 40, { SecVehSpdGroupSafe }, { SecVehSpdGroupSafe_UB } } });

    frame_ids.insert({ 122, SSMBMid6CanFdFr07 });
}


}
}
