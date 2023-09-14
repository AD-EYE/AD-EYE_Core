#include "SSMMid3CanFr01.h"


namespace kcan {
namespace dbc {


void SSMMid3CanFr01_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecSteerModStsSafeGroupByGatewyAdSteerMod, { AdSecSteerModStsSafeGroupByGatewyAdSteerMod, 8, 2, SignalType::APP_UNSIGNED, 2, AdSecSteerModStsSafeGroupByGatewy, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerModStsSafeGroupByGatewyChks, { AdSecSteerModStsSafeGroupByGatewyChks, 16, 8, SignalType::E2E_CHKS, 0, AdSecSteerModStsSafeGroupByGatewy, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerModStsSafeGroupByGatewyCntr, { AdSecSteerModStsSafeGroupByGatewyCntr, 10, 4, SignalType::E2E_CNTR, 0, AdSecSteerModStsSafeGroupByGatewy, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerModStsSafeGroupByGatewyVehOperIntv, { AdSecSteerModStsSafeGroupByGatewyVehOperIntv, 0, 1, SignalType::APP_UNSIGNED, 0, AdSecSteerModStsSafeGroupByGatewy, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerModStsSafeGroupByGatewyVehOperModSts1, { AdSecSteerModStsSafeGroupByGatewyVehOperModSts1, 14, 2, SignalType::APP_UNSIGNED, 0, AdSecSteerModStsSafeGroupByGatewy, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerStsSafeGroupByGatewyAdSteerPerf, { AdSecSteerStsSafeGroupByGatewyAdSteerPerf, 32, 5, SignalType::APP_UNSIGNED, 20, AdSecSteerStsSafeGroupByGatewy, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerStsSafeGroupByGatewyAdSteerSts, { AdSecSteerStsSafeGroupByGatewyAdSteerSts, 37, 3, SignalType::APP_UNSIGNED, 4, AdSecSteerStsSafeGroupByGatewy, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerStsSafeGroupByGatewyChks, { AdSecSteerStsSafeGroupByGatewyChks, 40, 8, SignalType::E2E_CHKS, 0, AdSecSteerStsSafeGroupByGatewy, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerStsSafeGroupByGatewyCntr, { AdSecSteerStsSafeGroupByGatewyCntr, 24, 4, SignalType::E2E_CNTR, 0, AdSecSteerStsSafeGroupByGatewy, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerStsSafeGroupByGatewy_UB, { AdSecSteerStsSafeGroupByGatewy_UB, 28, 1, SignalType::APP_UNSIGNED, 0, SSMMid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ AdSecSteerModStsSafeGroupByGatewy_UB, { AdSecSteerModStsSafeGroupByGatewy_UB, 1, 1, SignalType::APP_UNSIGNED, 0, SSMMid3CanFr01, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecSteerModStsSafeGroupByGatewy, { AdSecSteerModStsSafeGroupByGatewy, 0x407, { AdSecSteerModStsSafeGroupByGatewyAdSteerMod, AdSecSteerModStsSafeGroupByGatewyChks, AdSecSteerModStsSafeGroupByGatewyCntr, AdSecSteerModStsSafeGroupByGatewyVehOperIntv, AdSecSteerModStsSafeGroupByGatewyVehOperModSts1 }, { E2EProfileType::P01a, AdSecSteerModStsSafeGroupByGatewyChks, AdSecSteerModStsSafeGroupByGatewyCntr }, SSMMid3CanFr01 } } );
    signalgroups_info.insert({ AdSecSteerStsSafeGroupByGatewy, { AdSecSteerStsSafeGroupByGatewy, 0x408, { AdSecSteerStsSafeGroupByGatewyAdSteerPerf, AdSecSteerStsSafeGroupByGatewyAdSteerSts, AdSecSteerStsSafeGroupByGatewyChks, AdSecSteerStsSafeGroupByGatewyCntr }, { E2EProfileType::P01a, AdSecSteerStsSafeGroupByGatewyChks, AdSecSteerStsSafeGroupByGatewyCntr }, SSMMid3CanFr01 } } );

    frames_info.insert({ SSMMid3CanFr01, { SSMMid3CanFr01, 262, 8, 45, { AdSecSteerModStsSafeGroupByGatewy, AdSecSteerStsSafeGroupByGatewy }, { AdSecSteerStsSafeGroupByGatewy_UB, AdSecSteerModStsSafeGroupByGatewy_UB } } });

    frame_ids.insert({ 262, SSMMid3CanFr01 });
}


}
}
