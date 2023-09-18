#include "VCU1Mid3CanFr34.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr34_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ StandStillMgrStsForHldSafeChks, { StandStillMgrStsForHldSafeChks, 32, 8, true, SignalType::E2E_CHKS, 0, StandStillMgrStsForHldSafe, ParentType::GROUP } });
    signals_info.insert({ StandStillMgrStsForHldSafeCntr, { StandStillMgrStsForHldSafeCntr, 24, 4, true, SignalType::E2E_CNTR, 0, StandStillMgrStsForHldSafe, ParentType::GROUP } });
    signals_info.insert({ StandStillMgrStsForHldSafeStandStillSts, { StandStillMgrStsForHldSafeStandStillSts, 28, 3, true, SignalType::APP_UNSIGNED, 0, StandStillMgrStsForHldSafe, ParentType::GROUP } });
    signals_info.insert({ SwtIndcrToAPIIndcrTypExtReq, { SwtIndcrToAPIIndcrTypExtReq, 4, 2, true, SignalType::APP_UNSIGNED, 0, SwtIndcrToAPI, ParentType::GROUP } });
    signals_info.insert({ SwtIndcrToAPIIndcrTypExtReqChks, { SwtIndcrToAPIIndcrTypExtReqChks, 8, 8, true, SignalType::E2E_CHKS, 0, SwtIndcrToAPI, ParentType::GROUP } });
    signals_info.insert({ SwtIndcrToAPIIndcrTypExtReqCntr, { SwtIndcrToAPIIndcrTypExtReqCntr, 2, 2, true, SignalType::E2E_CNTR, 0, SwtIndcrToAPI, ParentType::GROUP } });
    signals_info.insert({ SwtIndcrToAPIIndcrTypExtReqToUpdQf, { SwtIndcrToAPIIndcrTypExtReqToUpdQf, 0, 2, true, SignalType::APP_UNSIGNED, 0, SwtIndcrToAPI, ParentType::GROUP } });
    signals_info.insert({ StandStillMgrStsForHldSafe_UB, { StandStillMgrStsForHldSafe_UB, 31, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr34, ParentType::FRAME } });
    signals_info.insert({ SwtBeamHiToAPI, { SwtBeamHiToAPI, 20, 2, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr34, ParentType::FRAME } });
    signals_info.insert({ SwtBeamHiToAPI_UB, { SwtBeamHiToAPI_UB, 22, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr34, ParentType::FRAME } });
    signals_info.insert({ SwtIndcrToAPI_UB, { SwtIndcrToAPI_UB, 6, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr34, ParentType::FRAME } });
    signals_info.insert({ SwtLiHzrdWarnToAPI, { SwtLiHzrdWarnToAPI, 23, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr34, ParentType::FRAME } });
    signals_info.insert({ SwtLiHzrdWarnToAPI_UB, { SwtLiHzrdWarnToAPI_UB, 7, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr34, ParentType::FRAME } });

    signalgroups_info.insert({ StandStillMgrStsForHldSafe, { StandStillMgrStsForHldSafe, 0x1D0, { StandStillMgrStsForHldSafeChks, StandStillMgrStsForHldSafeCntr, StandStillMgrStsForHldSafeStandStillSts }, { E2EProfileType::P01a, StandStillMgrStsForHldSafeChks, StandStillMgrStsForHldSafeCntr }, VCU1Mid3CanFr34 } } );
    signalgroups_info.insert({ SwtIndcrToAPI, { SwtIndcrToAPI, 0x0, { SwtIndcrToAPIIndcrTypExtReq, SwtIndcrToAPIIndcrTypExtReqChks, SwtIndcrToAPIIndcrTypExtReqCntr, SwtIndcrToAPIIndcrTypExtReqToUpdQf }, { E2EProfileType::P05, SwtIndcrToAPIIndcrTypExtReqChks, SwtIndcrToAPIIndcrTypExtReqCntr }, VCU1Mid3CanFr34 } } );

    frames_info.insert({ VCU1Mid3CanFr34, { VCU1Mid3CanFr34, 97, 8, 45, { StandStillMgrStsForHldSafe, SwtIndcrToAPI }, { SwtLiHzrdWarnToAPI_UB, SwtBeamHiToAPI_UB, StandStillMgrStsForHldSafe_UB, SwtBeamHiToAPI, SwtLiHzrdWarnToAPI, SwtIndcrToAPI_UB } } });

    frame_ids.insert({ 97, VCU1Mid3CanFr34 });
}


}
}
