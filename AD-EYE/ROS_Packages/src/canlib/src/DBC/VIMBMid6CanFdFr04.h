#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr04_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMBMid6CanFdFr04 { "VIMBMid6CanFdFr04" };


// Groups
const std::string SecRoadGradientlFromAd { "SecRoadGradientlFromAd" };


// Signals
const std::string SecRoadGradientlFromAd_UB { "SecRoadGradientlFromAd_UB" };
const std::string SecRoadGradientlFromAdInclnConf { "SecRoadGradientlFromAdInclnConf" };
const std::string SecRoadGradientlFromAdBankingConf { "SecRoadGradientlFromAdBankingConf" };
const std::string SecRoadGradientlFromAdCntr { "SecRoadGradientlFromAdCntr" };
const std::string SecRoadGradientlFromAdBanking { "SecRoadGradientlFromAdBanking" };
const std::string SecRoadGradientlFromAdChks { "SecRoadGradientlFromAdChks" };
const std::string SecRoadGradientlFromAdIncln { "SecRoadGradientlFromAdIncln" };


}
}
