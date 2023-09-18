#include "VIMBMid6CanFdFr04.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr04_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ SecRoadGradientlFromAdBanking, { SecRoadGradientlFromAdBanking, 24, 16, true, SignalType::APP_SIGNED, 0, SecRoadGradientlFromAd, ParentType::GROUP } });
    signals_info.insert({ SecRoadGradientlFromAdBankingConf, { SecRoadGradientlFromAdBankingConf, 12, 3, true, SignalType::APP_UNSIGNED, 0, SecRoadGradientlFromAd, ParentType::GROUP } });
    signals_info.insert({ SecRoadGradientlFromAdChks, { SecRoadGradientlFromAdChks, 32, 8, true, SignalType::E2E_CHKS, 0, SecRoadGradientlFromAd, ParentType::GROUP } });
    signals_info.insert({ SecRoadGradientlFromAdCntr, { SecRoadGradientlFromAdCntr, 8, 4, true, SignalType::E2E_CNTR, 0, SecRoadGradientlFromAd, ParentType::GROUP } });
    signals_info.insert({ SecRoadGradientlFromAdIncln, { SecRoadGradientlFromAdIncln, 48, 16, true, SignalType::APP_SIGNED, 0, SecRoadGradientlFromAd, ParentType::GROUP } });
    signals_info.insert({ SecRoadGradientlFromAdInclnConf, { SecRoadGradientlFromAdInclnConf, 0, 3, true, SignalType::APP_UNSIGNED, 0, SecRoadGradientlFromAd, ParentType::GROUP } });
    signals_info.insert({ SecRoadGradientlFromAd_UB, { SecRoadGradientlFromAd_UB, 3, 1, true, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr04, ParentType::FRAME } });

    signalgroups_info.insert({ SecRoadGradientlFromAd, { SecRoadGradientlFromAd, 0x1DD, { SecRoadGradientlFromAdBanking, SecRoadGradientlFromAdBankingConf, SecRoadGradientlFromAdChks, SecRoadGradientlFromAdCntr, SecRoadGradientlFromAdIncln, SecRoadGradientlFromAdInclnConf }, { E2EProfileType::P01a, SecRoadGradientlFromAdChks, SecRoadGradientlFromAdCntr }, VIMBMid6CanFdFr04 } } );

    frames_info.insert({ VIMBMid6CanFdFr04, { VIMBMid6CanFdFr04, 144, 8, 60, { SecRoadGradientlFromAd }, { SecRoadGradientlFromAd_UB } } });

    frame_ids.insert({ 144, VIMBMid6CanFdFr04 });
}


}
}
