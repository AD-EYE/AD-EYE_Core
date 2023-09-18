#include "VIMMid3CanFr10.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr10_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ PrimRoadGradientFromAdBanking, { PrimRoadGradientFromAdBanking, 32, 16, true, SignalType::APP_SIGNED, 0, PrimRoadGradientFromAd, ParentType::GROUP } });
    signals_info.insert({ PrimRoadGradientFromAdBankingConf, { PrimRoadGradientFromAdBankingConf, 0, 3, true, SignalType::APP_UNSIGNED, 0, PrimRoadGradientFromAd, ParentType::GROUP } });
    signals_info.insert({ PrimRoadGradientFromAdChks, { PrimRoadGradientFromAdChks, 16, 8, true, SignalType::E2E_CHKS, 0, PrimRoadGradientFromAd, ParentType::GROUP } });
    signals_info.insert({ PrimRoadGradientFromAdCntr, { PrimRoadGradientFromAdCntr, 8, 4, true, SignalType::E2E_CNTR, 0, PrimRoadGradientFromAd, ParentType::GROUP } });
    signals_info.insert({ PrimRoadGradientFromAdIncln, { PrimRoadGradientFromAdIncln, 48, 16, true, SignalType::APP_SIGNED, 0, PrimRoadGradientFromAd, ParentType::GROUP } });
    signals_info.insert({ PrimRoadGradientFromAdInclnConf, { PrimRoadGradientFromAdInclnConf, 12, 3, true, SignalType::APP_UNSIGNED, 0, PrimRoadGradientFromAd, ParentType::GROUP } });
    signals_info.insert({ PrimRoadGradientFromAd_UB, { PrimRoadGradientFromAd_UB, 3, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr10, ParentType::FRAME } });

    signalgroups_info.insert({ PrimRoadGradientFromAd, { PrimRoadGradientFromAd, 0x1DC, { PrimRoadGradientFromAdBanking, PrimRoadGradientFromAdBankingConf, PrimRoadGradientFromAdChks, PrimRoadGradientFromAdCntr, PrimRoadGradientFromAdIncln, PrimRoadGradientFromAdInclnConf }, { E2EProfileType::P01a, PrimRoadGradientFromAdChks, PrimRoadGradientFromAdCntr }, VIMMid3CanFr10 } } );

    frames_info.insert({ VIMMid3CanFr10, { VIMMid3CanFr10, 280, 8, 60, { PrimRoadGradientFromAd }, { PrimRoadGradientFromAd_UB } } });

    frame_ids.insert({ 280, VIMMid3CanFr10 });
}


}
}
