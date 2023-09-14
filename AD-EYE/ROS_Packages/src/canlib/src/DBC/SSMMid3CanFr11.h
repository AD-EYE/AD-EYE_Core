#include "../basic_types.h"

namespace kcan {
namespace dbc {


void SSMMid3CanFr11_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string SSMMid3CanFr11 { "SSMMid3CanFr11" };


// Groups
const std::string PrimALgtDataRawSafe { "PrimALgtDataRawSafe" };


// Signals
const std::string PrimALgtDataRawSafe_UB { "PrimALgtDataRawSafe_UB" };
const std::string PrimALgtDataRawSafeMinMaxQf { "PrimALgtDataRawSafeMinMaxQf" };
const std::string PrimALgtDataRawSafeCntr { "PrimALgtDataRawSafeCntr" };
const std::string PrimALgtDataRawSafeChks { "PrimALgtDataRawSafeChks" };
const std::string PrimALgtDataRawSafeMax { "PrimALgtDataRawSafeMax" };
const std::string PrimALgtDataRawSafeMin { "PrimALgtDataRawSafeMin" };
const std::string PrimALgtDataRawSafeNomQf { "PrimALgtDataRawSafeNomQf" };
const std::string PrimALgtDataRawSafeNom { "PrimALgtDataRawSafeNom" };


}
}
