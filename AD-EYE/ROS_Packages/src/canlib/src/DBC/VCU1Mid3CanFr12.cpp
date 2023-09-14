#include "VCU1Mid3CanFr12.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr12_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ BrkPedlValBrkPedlVal, { BrkPedlValBrkPedlVal, 8, 15, SignalType::APP_UNSIGNED, 0, BrkPedlVal, ParentType::GROUP } });
    signals_info.insert({ BrkPedlValBrkPedlValQf, { BrkPedlValBrkPedlValQf, 38, 2, SignalType::APP_UNSIGNED, 1, BrkPedlVal, ParentType::GROUP } });
    signals_info.insert({ ClstrSts2ForAutnmsDrvClstr2Chks, { ClstrSts2ForAutnmsDrvClstr2Chks, 8, 8, SignalType::E2E_CHKS, 0, ClstrSts2ForAutnmsDrv, ParentType::GROUP } });
    signals_info.insert({ ClstrSts2ForAutnmsDrvClstr2Cnt, { ClstrSts2ForAutnmsDrvClstr2Cnt, 0, 4, SignalType::E2E_CNTR, 0, ClstrSts2ForAutnmsDrv, ParentType::GROUP } });
    signals_info.insert({ ClstrSts2ForAutnmsDrvClstr2Sts, { ClstrSts2ForAutnmsDrvClstr2Sts, 4, 2, SignalType::APP_UNSIGNED, 0, ClstrSts2ForAutnmsDrv, ParentType::GROUP } });
    signals_info.insert({ PtTqAtAxleAvlFrntMax, { PtTqAtAxleAvlFrntMax, 40, 13, SignalType::APP_SIGNED, 0, VCU1Mid3CanFr12, ParentType::FRAME } });
    signals_info.insert({ ExtDcDcActvnAllwd_UB, { ExtDcDcActvnAllwd_UB, 54, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr12, ParentType::FRAME } });
    signals_info.insert({ PtTqAtAxleAvlFrntMax_UB, { PtTqAtAxleAvlFrntMax_UB, 37, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr12, ParentType::FRAME } });
    signals_info.insert({ PtTqAtAxleAvlReMax, { PtTqAtAxleAvlReMax, 56, 13, SignalType::APP_SIGNED, 0, VCU1Mid3CanFr12, ParentType::FRAME } });
    signals_info.insert({ ExtDcDcActvnAllwd, { ExtDcDcActvnAllwd, 53, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr12, ParentType::FRAME } });
    signals_info.insert({ PtTqAtAxleAvlReMax_UB, { PtTqAtAxleAvlReMax_UB, 7, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr12, ParentType::FRAME } });
    signals_info.insert({ ClstrSts2ForAutnmsDrv_UB, { ClstrSts2ForAutnmsDrv_UB, 6, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr12, ParentType::FRAME } });
    signals_info.insert({ BrkPedlVal_UB, { BrkPedlVal_UB, 23, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr12, ParentType::FRAME } });

    signalgroups_info.insert({ BrkPedlVal, { BrkPedlVal, 0x0, { BrkPedlValBrkPedlVal, BrkPedlValBrkPedlValQf }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr12 } } );
    signalgroups_info.insert({ ClstrSts2ForAutnmsDrv, { ClstrSts2ForAutnmsDrv, 0x259, { ClstrSts2ForAutnmsDrvClstr2Chks, ClstrSts2ForAutnmsDrvClstr2Cnt, ClstrSts2ForAutnmsDrvClstr2Sts }, { E2EProfileType::P01a, ClstrSts2ForAutnmsDrvClstr2Chks, ClstrSts2ForAutnmsDrvClstr2Cnt }, VCU1Mid3CanFr12 } } );

    frames_info.insert({ VCU1Mid3CanFr12, { VCU1Mid3CanFr12, 53, 8, 10, { BrkPedlVal, ClstrSts2ForAutnmsDrv }, { PtTqAtAxleAvlFrntMax, ExtDcDcActvnAllwd_UB, PtTqAtAxleAvlFrntMax_UB, PtTqAtAxleAvlReMax, ExtDcDcActvnAllwd, PtTqAtAxleAvlReMax_UB, ClstrSts2ForAutnmsDrv_UB, BrkPedlVal_UB } } });

    frame_ids.insert({ 53, VCU1Mid3CanFr12 });
}


}
}
