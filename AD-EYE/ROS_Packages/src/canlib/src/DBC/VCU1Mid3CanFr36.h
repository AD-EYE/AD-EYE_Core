#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr36_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr36 { "VCU1Mid3CanFr36" };


// Groups
const std::string ALgtMaxAvl { "ALgtMaxAvl" };
const std::string WhlLockSts { "WhlLockSts" };


// Signals
const std::string WhlLockSts_UB { "WhlLockSts_UB" };
const std::string ALgtMaxAvl_UB { "ALgtMaxAvl_UB" };
const std::string ALgtMaxAvlCntr { "ALgtMaxAvlCntr" };
const std::string ALgtMaxAvlALgtMaxAvl { "ALgtMaxAvlALgtMaxAvl" };
const std::string ALgtMaxAvlDecelLgtMaxAvl { "ALgtMaxAvlDecelLgtMaxAvl" };
const std::string ALgtMaxAvlChks { "ALgtMaxAvlChks" };
const std::string ALgtMaxAvlALgtMaxAvlLong { "ALgtMaxAvlALgtMaxAvlLong" };
const std::string WhlLockStsDegradedSts { "WhlLockStsDegradedSts" };
const std::string WhlLockStsLockSts { "WhlLockStsLockSts" };
const std::string WhlLockStsCntr { "WhlLockStsCntr" };
const std::string WhlLockStsChks { "WhlLockStsChks" };


}
}
