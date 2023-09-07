#include "../basic_types.h"


namespace kcan {
namespace dbc {


void SSMMid3CanFr07_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMMid3CanFr07 { "SSMMid3CanFr07" };

// Groups
const std::string PrimVehSpdGroupSafe { "PrimVehSpdGroupSafe" };

// Signals
const std::string PrimVehSpdGroupSafe_UB {"PrimVehSpdGroupSafe_UB"};
const std::string PrimVehSpdGroupSafeChks {"PrimVehSpdGroupSafeChks"};
const std::string PrimVehSpdGroupSafeCntr {"PrimVehSpdGroupSafeCntr"};
const std::string PrimVehSpdGroupSafeMax {"PrimVehSpdGroupSafeMax"};
const std::string PrimVehSpdGroupSafeMin {"PrimVehSpdGroupSafeMin"};
const std::string PrimVehSpdGroupSafeMinMaxQf {"PrimVehSpdGroupSafeMinMaxQf"};
const std::string PrimVehSpdGroupSafeMovDir {"PrimVehSpdGroupSafeMovDir"};
const std::string PrimVehSpdGroupSafeMovDirQf {"PrimVehSpdGroupSafeMovDirQf"};
const std::string PrimVehSpdGroupSafeNom {"PrimVehSpdGroupSafeNom"};
const std::string PrimVehSpdGroupSafeNomQf {"PrimVehSpdGroupSafeNomQf"};

}
}
