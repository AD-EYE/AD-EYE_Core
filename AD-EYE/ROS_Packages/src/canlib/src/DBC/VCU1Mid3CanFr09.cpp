#include "VCU1Mid3CanFr09.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr09_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSteerPaddlPsdGroupSafeChks, { AdSteerPaddlPsdGroupSafeChks, 56, 8, SignalType::E2E_CHKS, 0, AdSteerPaddlPsdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSteerPaddlPsdGroupSafeCntr, { AdSteerPaddlPsdGroupSafeCntr, 48, 4, SignalType::E2E_CNTR, 0, AdSteerPaddlPsdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSteerPaddlPsdGroupSafeLe, { AdSteerPaddlPsdGroupSafeLe, 55, 1, SignalType::APP_UNSIGNED, 0, AdSteerPaddlPsdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSteerPaddlPsdGroupSafeLeSts, { AdSteerPaddlPsdGroupSafeLeSts, 54, 1, SignalType::APP_UNSIGNED, 0, AdSteerPaddlPsdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSteerPaddlPsdGroupSafeRi, { AdSteerPaddlPsdGroupSafeRi, 53, 1, SignalType::APP_UNSIGNED, 0, AdSteerPaddlPsdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSteerPaddlPsdGroupSafeRiSts, { AdSteerPaddlPsdGroupSafeRiSts, 52, 1, SignalType::APP_UNSIGNED, 0, AdSteerPaddlPsdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SteerWhlAgSafe, { SteerWhlAgSafe, 8, 15, SignalType::APP_SIGNED, 0, SteerWhlSnsr, ParentType::GROUP } });
    signals_info.insert({ SteerWhlAgSpdSafe, { SteerWhlAgSpdSafe, 24, 14, SignalType::APP_SIGNED, 0, SteerWhlSnsr, ParentType::GROUP } });
    signals_info.insert({ SteerWhlSnsrQf, { SteerWhlSnsrQf, 22, 2, SignalType::APP_UNSIGNED, 1, SteerWhlSnsr, ParentType::GROUP } });
    signals_info.insert({ SteerWhlSnsrSafeChks, { SteerWhlSnsrSafeChks, 32, 8, SignalType::E2E_CHKS, 0, SteerWhlSnsr, ParentType::GROUP } });
    signals_info.insert({ SteerWhlSnsrSafeCntr, { SteerWhlSnsrSafeCntr, 44, 4, SignalType::E2E_CNTR, 0, SteerWhlSnsr, ParentType::GROUP } });
    signals_info.insert({ AdSteerPaddlPsdGroupSafe_UB, { AdSteerPaddlPsdGroupSafe_UB, 40, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr09, ParentType::FRAME } });
    signals_info.insert({ WhlMotSysCluSts, { WhlMotSysCluSts, 41, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr09, ParentType::FRAME } });
    signals_info.insert({ WhlMotSysCluSts_UB, { WhlMotSysCluSts_UB, 42, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr09, ParentType::FRAME } });
    signals_info.insert({ SteerWhlSnsr_UB, { SteerWhlSnsr_UB, 7, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr09, ParentType::FRAME } });

    signalgroups_info.insert({ AdSteerPaddlPsdGroupSafe, { AdSteerPaddlPsdGroupSafe, 0x404, { AdSteerPaddlPsdGroupSafeChks, AdSteerPaddlPsdGroupSafeCntr, AdSteerPaddlPsdGroupSafeLe, AdSteerPaddlPsdGroupSafeLeSts, AdSteerPaddlPsdGroupSafeRi, AdSteerPaddlPsdGroupSafeRiSts }, { E2EProfileType::P01a, AdSteerPaddlPsdGroupSafeChks, AdSteerPaddlPsdGroupSafeCntr }, VCU1Mid3CanFr09 } } );
    signalgroups_info.insert({ SteerWhlSnsr, { SteerWhlSnsr, 0x33, { SteerWhlAgSafe, SteerWhlAgSpdSafe, SteerWhlSnsrQf, SteerWhlSnsrSafeChks, SteerWhlSnsrSafeCntr }, { E2EProfileType::P01a, SteerWhlSnsrSafeChks, SteerWhlSnsrSafeCntr }, VCU1Mid3CanFr09 } } );

    frames_info.insert({ VCU1Mid3CanFr09, { VCU1Mid3CanFr09, 73, 8, 15, { AdSteerPaddlPsdGroupSafe, SteerWhlSnsr }, { AdSteerPaddlPsdGroupSafe_UB, WhlMotSysCluSts, WhlMotSysCluSts_UB, SteerWhlSnsr_UB } } });

    frame_ids.insert({ 73, VCU1Mid3CanFr09 });
}


}
}
