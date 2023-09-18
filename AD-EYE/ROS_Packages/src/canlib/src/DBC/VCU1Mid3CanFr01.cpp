#include "VCU1Mid3CanFr01.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr01_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimSteerStsSafeGroupAdSteerPerf, { AdPrimSteerStsSafeGroupAdSteerPerf, 0, 5, true, SignalType::APP_UNSIGNED, 20, AdPrimSteerStsSafeGroup, ParentType::GROUP } });
    signals_info.insert({ AdPrimSteerStsSafeGroupAdSteerSts, { AdPrimSteerStsSafeGroupAdSteerSts, 13, 3, true, SignalType::APP_UNSIGNED, 0, AdPrimSteerStsSafeGroup, ParentType::GROUP } });
    signals_info.insert({ AdPrimSteerStsSafeGroupChks, { AdPrimSteerStsSafeGroupChks, 16, 8, true, SignalType::E2E_CHKS, 0, AdPrimSteerStsSafeGroup, ParentType::GROUP } });
    signals_info.insert({ AdPrimSteerStsSafeGroupCntr, { AdPrimSteerStsSafeGroupCntr, 8, 4, true, SignalType::E2E_CNTR, 0, AdPrimSteerStsSafeGroup, ParentType::GROUP } });
    signals_info.insert({ CarModInCrashStsSafeChks, { CarModInCrashStsSafeChks, 24, 8, false, SignalType::E2E_CHKS, 0, CarModInCrashStsSafe, ParentType::GROUP } });
    signals_info.insert({ CarModInCrashStsSafeCntr, { CarModInCrashStsSafeCntr, 32, 4, false, SignalType::E2E_CNTR, 0, CarModInCrashStsSafe, ParentType::GROUP } });
    signals_info.insert({ CarModInCrashStsSafeSts, { CarModInCrashStsSafeSts, 40, 1, false, SignalType::APP_UNSIGNED, 0, CarModInCrashStsSafe, ParentType::GROUP } });
    signals_info.insert({ AdPrimSteerStsSafeGroup_UB, { AdPrimSteerStsSafeGroup_UB, 5, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr01, ParentType::FRAME } });
    signals_info.insert({ CarModInCrashStsSafe_UB, { CarModInCrashStsSafe_UB, 6, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr01, ParentType::FRAME } });

    signalgroups_info.insert({ AdPrimSteerStsSafeGroup, { AdPrimSteerStsSafeGroup, 0x1A0, { AdPrimSteerStsSafeGroupAdSteerPerf, AdPrimSteerStsSafeGroupAdSteerSts, AdPrimSteerStsSafeGroupChks, AdPrimSteerStsSafeGroupCntr }, { E2EProfileType::P01a, AdPrimSteerStsSafeGroupChks, AdPrimSteerStsSafeGroupCntr }, VCU1Mid3CanFr01 } } );
    signalgroups_info.insert({ CarModInCrashStsSafe, { CarModInCrashStsSafe, 0x261, { CarModInCrashStsSafeChks, CarModInCrashStsSafeCntr, CarModInCrashStsSafeSts }, { E2EProfileType::P01a, CarModInCrashStsSafeChks, CarModInCrashStsSafeCntr }, VCU1Mid3CanFr01 } } );

    frames_info.insert({ VCU1Mid3CanFr01, { VCU1Mid3CanFr01, 48, 8, 10, { AdPrimSteerStsSafeGroup, CarModInCrashStsSafe }, { CarModInCrashStsSafe_UB, AdPrimSteerStsSafeGroup_UB } } });

    frame_ids.insert({ 48, VCU1Mid3CanFr01 });
}


}
}
