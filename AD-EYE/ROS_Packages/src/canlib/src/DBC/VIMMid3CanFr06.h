#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid3CanFr06_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr06 { "VIMMid3CanFr06" };


// Groups


// Signals
const std::string ExtDcDcActvnSts_UB { "ExtDcDcActvnSts_UB" };
const std::string ExtDcDcActvnSts { "ExtDcDcActvnSts" };
const std::string HvIDcDcHiSideExt_UB { "HvIDcDcHiSideExt_UB" };
const std::string HvUDcDcHiSideExt_UB { "HvUDcDcHiSideExt_UB" };
const std::string HvUDcDcHiSideExt { "HvUDcDcHiSideExt" };
const std::string HvIDcDcHiSideExt { "HvIDcDcHiSideExt" };


}
}
