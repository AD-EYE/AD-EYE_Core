#include "VIMMid3CanFr11.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr11_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdFusedFricEstimn_UB, { AdFusedFricEstimn_UB, 3, 1, SignalType::APP_UNSIGNED, VIMMid3CanFr11 } });
    signals_info.insert({ AdFusedFricEstimnFricEstimn, { AdFusedFricEstimnFricEstimn, 8, 8, SignalType::APP_UNSIGNED, AdFusedFricEstimn } });
    signals_info.insert({ AdFusedFricEstimnFricEstimnConf, { AdFusedFricEstimnFricEstimnConf, 0, 3, SignalType::APP_UNSIGNED, AdFusedFricEstimn } });
    signals_info.insert({ AdpLiReqFromAPI_UB, { AdpLiReqFromAPI_UB, 4, 1, SignalType::APP_UNSIGNED, VIMMid3CanFr11 } });
    signals_info.insert({ AdpLiReqFromAPIAhbcActvn, { AdpLiReqFromAPIAhbcActvn, 16, 1, SignalType::APP_UNSIGNED, AdpLiReqFromAPI } });
    signals_info.insert({ AdpLiReqFromAPIChks, { AdpLiReqFromAPIChks, 24, 8, SignalType::E2E_CHKS, AdpLiReqFromAPI } });
    signals_info.insert({ AdpLiReqFromAPICntr, { AdpLiReqFromAPICntr, 36, 4, SignalType::E2E_CNTR, AdpLiReqFromAPI } });
    signals_info.insert({ AdpLiReqFromAPIHzrdLiActvnReq, { AdpLiReqFromAPIHzrdLiActvnReq, 35, 1, SignalType::APP_UNSIGNED, AdpLiReqFromAPI } });
    signals_info.insert({ AdpLiReqFromAPIHzrdLiDeactnReq, { AdpLiReqFromAPIHzrdLiDeactnReq, 34, 1, SignalType::APP_UNSIGNED, AdpLiReqFromAPI } });
    signals_info.insert({ AdpLiReqFromAPIIncrLiRiReq, { AdpLiReqFromAPIIncrLiRiReq, 33, 1, SignalType::APP_UNSIGNED, AdpLiReqFromAPI } });
    signals_info.insert({ AdpLiReqFromAPIIndcrLeReq, { AdpLiReqFromAPIIndcrLeReq, 32, 1, SignalType::APP_UNSIGNED, AdpLiReqFromAPI } });
    signals_info.insert({ SwtExtrLiFromAPI_UB, { SwtExtrLiFromAPI_UB, 46, 1, SignalType::APP_UNSIGNED, VIMMid3CanFr11 } });
    signals_info.insert({ SwtExtrLiFromAPILiExtFctCntr, { SwtExtrLiFromAPILiExtFctCntr, 44, 2, SignalType::E2E_CNTR, SwtExtrLiFromAPI } });
    signals_info.insert({ SwtExtrLiFromAPILiExtFctCrc, { SwtExtrLiFromAPILiExtFctCrc, 48, 8, SignalType::E2E_CHKS, SwtExtrLiFromAPI } });
    signals_info.insert({ SwtExtrLiFromAPILiExtFctQf, { SwtExtrLiFromAPILiExtFctQf, 42, 2, SignalType::APP_UNSIGNED, SwtExtrLiFromAPI } });
    signals_info.insert({ SwtExtrLiFromAPILiExtFctReq1, { SwtExtrLiFromAPILiExtFctReq1, 40, 2, SignalType::APP_UNSIGNED, SwtExtrLiFromAPI } });
    
    signalgroups_info.insert(
    {
        AdFusedFricEstimn,
        {
            AdFusedFricEstimn,
            0x0,
            {
                AdFusedFricEstimnFricEstimn,
                AdFusedFricEstimnFricEstimnConf
            }, 
            { E2EProfileType::None, "", "" },
            VIMMid3CanFr11
        }
    });

    signalgroups_info.insert(
    {
        AdpLiReqFromAPI,
        {
            AdpLiReqFromAPI,
            0x72E,
            {
                AdpLiReqFromAPIAhbcActvn,
                AdpLiReqFromAPIChks,
                AdpLiReqFromAPICntr,
                AdpLiReqFromAPIHzrdLiActvnReq,
                AdpLiReqFromAPIHzrdLiDeactnReq,
                AdpLiReqFromAPIIncrLiRiReq,
                AdpLiReqFromAPIIndcrLeReq
            }, 
            { E2EProfileType::P01a, AdpLiReqFromAPIChks, AdpLiReqFromAPICntr },
            VIMMid3CanFr11
        }
    });

    signalgroups_info.insert(
    {
        SwtExtrLiFromAPI,
        {
            SwtExtrLiFromAPI,
            0x0,
            {
                SwtExtrLiFromAPILiExtFctCntr,
                SwtExtrLiFromAPILiExtFctCrc,
                SwtExtrLiFromAPILiExtFctQf,
                SwtExtrLiFromAPILiExtFctReq1
            }, 
            E2EProfileType::None,
            VIMMid3CanFr11
        }
    });

    frames_info.insert({ VIMMid3CanFr11, { VIMMid3CanFr11, 288, 8, 300, { AdFusedFricEstimn, AdpLiReqFromAPI, SwtExtrLiFromAPI }, { AdFusedFricEstimn_UB, AdpLiReqFromAPI_UB, SwtExtrLiFromAPI_UB } } });

    frame_ids.insert({ 288, VIMMid3CanFr11 });
}


}
}