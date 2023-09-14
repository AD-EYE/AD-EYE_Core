#include "VIMMid3CanFr11.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr11_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdFusedFricEstimnFricEstimn, { AdFusedFricEstimnFricEstimn, 8, 8, SignalType::APP_UNSIGNED, 0, AdFusedFricEstimn, ParentType::GROUP } });
    signals_info.insert({ AdFusedFricEstimnFricEstimnConf, { AdFusedFricEstimnFricEstimnConf, 0, 3, SignalType::APP_UNSIGNED, 0, AdFusedFricEstimn, ParentType::GROUP } });
    signals_info.insert({ AdpLiReqFromAPIAhbcActvn, { AdpLiReqFromAPIAhbcActvn, 16, 1, SignalType::APP_UNSIGNED, 0, AdpLiReqFromAPI, ParentType::GROUP } });
    signals_info.insert({ AdpLiReqFromAPIChks, { AdpLiReqFromAPIChks, 24, 8, SignalType::E2E_CHKS, 0, AdpLiReqFromAPI, ParentType::GROUP } });
    signals_info.insert({ AdpLiReqFromAPICntr, { AdpLiReqFromAPICntr, 36, 4, SignalType::E2E_CNTR, 0, AdpLiReqFromAPI, ParentType::GROUP } });
    signals_info.insert({ AdpLiReqFromAPIHzrdLiActvnReq, { AdpLiReqFromAPIHzrdLiActvnReq, 35, 1, SignalType::APP_UNSIGNED, 0, AdpLiReqFromAPI, ParentType::GROUP } });
    signals_info.insert({ AdpLiReqFromAPIHzrdLiDeactnReq, { AdpLiReqFromAPIHzrdLiDeactnReq, 34, 1, SignalType::APP_UNSIGNED, 0, AdpLiReqFromAPI, ParentType::GROUP } });
    signals_info.insert({ AdpLiReqFromAPIIncrLiRiReq, { AdpLiReqFromAPIIncrLiRiReq, 33, 1, SignalType::APP_UNSIGNED, 0, AdpLiReqFromAPI, ParentType::GROUP } });
    signals_info.insert({ AdpLiReqFromAPIIndcrLeReq, { AdpLiReqFromAPIIndcrLeReq, 32, 1, SignalType::APP_UNSIGNED, 0, AdpLiReqFromAPI, ParentType::GROUP } });
    signals_info.insert({ SwtExtrLiFromAPILiExtFctCntr, { SwtExtrLiFromAPILiExtFctCntr, 44, 2, SignalType::APP_UNSIGNED, 0, SwtExtrLiFromAPI, ParentType::GROUP } });
    signals_info.insert({ SwtExtrLiFromAPILiExtFctCrc, { SwtExtrLiFromAPILiExtFctCrc, 48, 8, SignalType::APP_UNSIGNED, 0, SwtExtrLiFromAPI, ParentType::GROUP } });
    signals_info.insert({ SwtExtrLiFromAPILiExtFctQf, { SwtExtrLiFromAPILiExtFctQf, 42, 2, SignalType::APP_UNSIGNED, 0, SwtExtrLiFromAPI, ParentType::GROUP } });
    signals_info.insert({ SwtExtrLiFromAPILiExtFctReq1, { SwtExtrLiFromAPILiExtFctReq1, 40, 2, SignalType::APP_UNSIGNED, 0, SwtExtrLiFromAPI, ParentType::GROUP } });
    signals_info.insert({ SwtExtrLiFromAPI_UB, { SwtExtrLiFromAPI_UB, 46, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ AdpLiReqFromAPI_UB, { AdpLiReqFromAPI_UB, 4, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr11, ParentType::FRAME } });
    signals_info.insert({ AdFusedFricEstimn_UB, { AdFusedFricEstimn_UB, 3, 1, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr11, ParentType::FRAME } });

    signalgroups_info.insert({ AdFusedFricEstimn, { AdFusedFricEstimn, 0x0, { AdFusedFricEstimnFricEstimn, AdFusedFricEstimnFricEstimnConf }, { E2EProfileType::None, "", "" }, VIMMid3CanFr11 } } );
    signalgroups_info.insert({ AdpLiReqFromAPI, { AdpLiReqFromAPI, 0x72E, { AdpLiReqFromAPIAhbcActvn, AdpLiReqFromAPIChks, AdpLiReqFromAPICntr, AdpLiReqFromAPIHzrdLiActvnReq, AdpLiReqFromAPIHzrdLiDeactnReq, AdpLiReqFromAPIIncrLiRiReq, AdpLiReqFromAPIIndcrLeReq }, { E2EProfileType::P01a, AdpLiReqFromAPIChks, AdpLiReqFromAPICntr }, VIMMid3CanFr11 } } );
    signalgroups_info.insert({ SwtExtrLiFromAPI, { SwtExtrLiFromAPI, 0x0, { SwtExtrLiFromAPILiExtFctCntr, SwtExtrLiFromAPILiExtFctCrc, SwtExtrLiFromAPILiExtFctQf, SwtExtrLiFromAPILiExtFctReq1 }, { E2EProfileType::None, "", "" }, VIMMid3CanFr11 } } );

    frames_info.insert({ VIMMid3CanFr11, { VIMMid3CanFr11, 288, 8, 80, { AdFusedFricEstimn, AdpLiReqFromAPI, SwtExtrLiFromAPI }, { SwtExtrLiFromAPI_UB, AdpLiReqFromAPI_UB, AdFusedFricEstimn_UB } } });

    frame_ids.insert({ 288, VIMMid3CanFr11 });
}


}
}
