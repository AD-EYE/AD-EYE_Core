#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid3CanFr10_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr10 { "VIMMid3CanFr10" };


// Groups
const std::string PrimRoadGradientFromAd { "PrimRoadGradientFromAd" };


// Signals
const std::string PrimRoadGradientFromAd_UB { "PrimRoadGradientFromAd_UB" };
const std::string PrimRoadGradientFromAdBankingConf { "PrimRoadGradientFromAdBankingConf" };
const std::string PrimRoadGradientFromAdInclnConf { "PrimRoadGradientFromAdInclnConf" };
const std::string PrimRoadGradientFromAdCntr { "PrimRoadGradientFromAdCntr" };
const std::string PrimRoadGradientFromAdChks { "PrimRoadGradientFromAdChks" };
const std::string PrimRoadGradientFromAdBanking { "PrimRoadGradientFromAdBanking" };
const std::string PrimRoadGradientFromAdIncln { "PrimRoadGradientFromAdIncln" };


}
}
