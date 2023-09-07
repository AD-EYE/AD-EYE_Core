#include "../basic_types.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr01_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr01 { "VCU1Mid3CanFr01" };

// Groups
const std::string AdPrimSteerStsSafeGroup { "AdPrimSteerStsSafeGroup" };
const std::string CarModInCrashStsSafe { "CarModInCrashStsSafe" };

// Signals
const std::string AdPrimSteerStsSafeGroup_UB {"AdPrimSteerStsSafeGroup_UB"};
const std::string AdPrimSteerStsSafeGroupAdSteerPerf {"AdPrimSteerStsSafeGroupAdSteerPerf"};
const std::string AdPrimSteerStsSafeGroupAdSteerSts {"AdPrimSteerStsSafeGroupAdSteerSts"};
const std::string AdPrimSteerStsSafeGroupChks {"AdPrimSteerStsSafeGroupChks"};
const std::string AdPrimSteerStsSafeGroupCntr {"AdPrimSteerStsSafeGroupCntr"};
const std::string CarModInCrashStsSafe_UB {"CarModInCrashStsSafe_UB"};
const std::string CarModInCrashStsSafeChks {"CarModInCrashStsSafeChks"};
const std::string CarModInCrashStsSafeCntr {"CarModInCrashStsSafeCntr"};
const std::string CarModInCrashStsSafeSts {"CarModInCrashStsSafeSts"};

}
}
