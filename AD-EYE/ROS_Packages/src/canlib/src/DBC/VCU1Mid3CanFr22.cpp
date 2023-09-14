#include "VCU1Mid3CanFr22.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr22_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecBrkActvnGroupSafeActvnReq, { AdSecBrkActvnGroupSafeActvnReq, 53, 1, SignalType::APP_UNSIGNED, 0, AdSecBrkActvnGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecBrkActvnGroupSafeChks, { AdSecBrkActvnGroupSafeChks, 56, 8, SignalType::E2E_CHKS, 0, AdSecBrkActvnGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecBrkActvnGroupSafeCntr, { AdSecBrkActvnGroupSafeCntr, 48, 4, SignalType::E2E_CNTR, 0, AdSecBrkActvnGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecBrkActvnGroupSafeDeactvnReq, { AdSecBrkActvnGroupSafeDeactvnReq, 52, 1, SignalType::APP_UNSIGNED, 0, AdSecBrkActvnGroupSafe, ParentType::GROUP } });
    signals_info.insert({ BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsAct, { BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsAct, 9, 15, SignalType::APP_UNSIGNED, 0, BrkFricTqTotAtWhlsAct, ParentType::GROUP } });
    signals_info.insert({ BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsActChks, { BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsActChks, 8, 8, SignalType::E2E_CHKS, 0, BrkFricTqTotAtWhlsAct, ParentType::GROUP } });
    signals_info.insert({ BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsActCntr, { BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsActCntr, 0, 4, SignalType::E2E_CNTR, 0, BrkFricTqTotAtWhlsAct, ParentType::GROUP } });
    signals_info.insert({ PtTqAtAxleAvlFrntMaxLong_UB, { PtTqAtAxleAvlFrntMaxLong_UB, 5, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr22, ParentType::FRAME } });
    signals_info.insert({ AdSecBrkActvnGroupSafe_UB, { AdSecBrkActvnGroupSafe_UB, 54, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr22, ParentType::FRAME } });
    signals_info.insert({ PtTqAtAxleAvlFrntMaxLong, { PtTqAtAxleAvlFrntMaxLong, 40, 13, SignalType::APP_SIGNED, 0, VCU1Mid3CanFr22, ParentType::FRAME } });
    signals_info.insert({ BrkFricTqTotAtWhlsAct_UB, { BrkFricTqTotAtWhlsAct_UB, 4, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr22, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecBrkActvnGroupSafe, { AdSecBrkActvnGroupSafe, 0x221, { AdSecBrkActvnGroupSafeActvnReq, AdSecBrkActvnGroupSafeChks, AdSecBrkActvnGroupSafeCntr, AdSecBrkActvnGroupSafeDeactvnReq }, { E2EProfileType::P01a, AdSecBrkActvnGroupSafeChks, AdSecBrkActvnGroupSafeCntr }, VCU1Mid3CanFr22 } } );
    signalgroups_info.insert({ BrkFricTqTotAtWhlsAct, { BrkFricTqTotAtWhlsAct, 0x7B, { BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsAct, BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsActChks, BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsActCntr }, { E2EProfileType::P01a, BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsActChks, BrkFricTqTotAtWhlsActBrkFricTqTotAtWhlsActCntr }, VCU1Mid3CanFr22 } } );

    frames_info.insert({ VCU1Mid3CanFr22, { VCU1Mid3CanFr22, 133, 8, 20, { AdSecBrkActvnGroupSafe, BrkFricTqTotAtWhlsAct }, { PtTqAtAxleAvlFrntMaxLong_UB, AdSecBrkActvnGroupSafe_UB, PtTqAtAxleAvlFrntMaxLong, BrkFricTqTotAtWhlsAct_UB } } });

    frame_ids.insert({ 133, VCU1Mid3CanFr22 });
}


}
}
