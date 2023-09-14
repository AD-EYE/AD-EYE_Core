#include "VCU1Mid3CanFr34.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr34_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ StandStillMgrStsForHldSafeChks, { StandStillMgrStsForHldSafeChks, 32, 8, SignalType::E2E_CHKS, 0, StandStillMgrStsForHldSafe, ParentType::GROUP } });
    signals_info.insert({ StandStillMgrStsForHldSafeCntr, { StandStillMgrStsForHldSafeCntr, 24, 4, SignalType::E2E_CNTR, 0, StandStillMgrStsForHldSafe, ParentType::GROUP } });
    signals_info.insert({ StandStillMgrStsForHldSafeStandStillSts, { StandStillMgrStsForHldSafeStandStillSts, 28, 3, SignalType::APP_UNSIGNED, 0, StandStillMgrStsForHldSafe, ParentType::GROUP } });
    signals_info.insert({ SwtIndcrToAPIIndcrTypExtReq, { SwtIndcrToAPIIndcrTypExtReq, 4, 2, SignalType::APP_UNSIGNED, 0, SwtIndcrToAPI, ParentType::GROUP } });
    signals_info.insert({ SwtIndcrToAPIIndcrTypExtReqChks, { SwtIndcrToAPIIndcrTypExtReqChks, 8, 8, SignalType::APP_UNSIGNED, 0, SwtIndcrToAPI, ParentType::GROUP } });
    signals_info.insert({ SwtIndcrToAPIIndcrTypExtReqCntr, { SwtIndcrToAPIIndcrTypExtReqCntr, 2, 2, SignalType::APP_UNSIGNED, 0, SwtIndcrToAPI, ParentType::GROUP } });
    signals_info.insert({ SwtIndcrToAPIIndcrTypExtReqToUpdQf, { SwtIndcrToAPIIndcrTypExtReqToUpdQf, 0, 2, SignalType::APP_UNSIGNED, 0, SwtIndcrToAPI, ParentType::GROUP } });
    signals_info.insert({ SwtBeamHiToAPI_UB, { SwtBeamHiToAPI_UB, 22, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr34, ParentType::FRAME } });
    signals_info.insert({ SwtLiHzrdWarnToAPI_UB, { SwtLiHzrdWarnToAPI_UB, 7, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr34, ParentType::FRAME } });
    signals_info.insert({ SwtBeamHiToAPI, { SwtBeamHiToAPI, 20, 2, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr34, ParentType::FRAME } });
    signals_info.insert({ StandStillMgrStsForHldSafe_UB, { StandStillMgrStsForHldSafe_UB, 31, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr34, ParentType::FRAME } });
    signals_info.insert({ SwtIndcrToAPI_UB, { SwtIndcrToAPI_UB, 6, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr34, ParentType::FRAME } });
    signals_info.insert({ SwtLiHzrdWarnToAPI, { SwtLiHzrdWarnToAPI, 23, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr34, ParentType::FRAME } });

    signalgroups_info.insert({ StandStillMgrStsForHldSafe, { StandStillMgrStsForHldSafe, 0x1D0, { StandStillMgrStsForHldSafeChks, StandStillMgrStsForHldSafeCntr, StandStillMgrStsForHldSafeStandStillSts }, { E2EProfileType::P01a, StandStillMgrStsForHldSafeChks, StandStillMgrStsForHldSafeCntr }, VCU1Mid3CanFr34 } } );
    signalgroups_info.insert({ SwtIndcrToAPI, { SwtIndcrToAPI, 0x0, { SwtIndcrToAPIIndcrTypExtReq, SwtIndcrToAPIIndcrTypExtReqChks, SwtIndcrToAPIIndcrTypExtReqCntr, SwtIndcrToAPIIndcrTypExtReqToUpdQf }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr34 } } );

    frames_info.insert({ VCU1Mid3CanFr34, { VCU1Mid3CanFr34, 97, 8, 45, { StandStillMgrStsForHldSafe, SwtIndcrToAPI }, { SwtBeamHiToAPI_UB, SwtLiHzrdWarnToAPI_UB, SwtBeamHiToAPI, StandStillMgrStsForHldSafe_UB, SwtIndcrToAPI_UB, SwtLiHzrdWarnToAPI } } });

    frame_ids.insert({ 97, VCU1Mid3CanFr34 });
}


}
}
