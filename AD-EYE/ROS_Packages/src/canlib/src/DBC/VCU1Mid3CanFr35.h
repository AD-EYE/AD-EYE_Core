#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr35_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr35 { "VCU1Mid3CanFr35" };


// Groups
const std::string AplidSwtExtrLiToAPI { "AplidSwtExtrLiToAPI" };


// Signals
const std::string AplidSwtExtrLiToAPI_UB { "AplidSwtExtrLiToAPI_UB" };
const std::string AplidSwtExtrLiToAPILiExtFctCntr { "AplidSwtExtrLiToAPILiExtFctCntr" };
const std::string AplidSwtExtrLiToAPILiExtFctQf { "AplidSwtExtrLiToAPILiExtFctQf" };
const std::string AplidSwtExtrLiToAPILiExtFctReq1 { "AplidSwtExtrLiToAPILiExtFctReq1" };
const std::string AplidSwtExtrLiToAPILiExtFctCrc { "AplidSwtExtrLiToAPILiExtFctCrc" };


}
}
