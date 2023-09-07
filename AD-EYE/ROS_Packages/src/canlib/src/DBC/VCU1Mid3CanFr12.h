#include "../basic_types.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr12_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr12 { "VCU1Mid3CanFr12" };

// Groups
const std::string BrkPedlVal { "BrkPedlVal" };
const std::string ClstrSts2ForAutnmsDrv { "ClstrSts2ForAutnmsDrv" };

// Signals
const std::string BrkPedlVal_UB { "BrkPedlVal_UB" };
const std::string BrkPedlValBrkPedlVal { "BrkPedlValBrkPedlVal" };
const std::string BrkPedlValBrkPedlValQf { "BrkPedlValBrkPedlValQf" };
const std::string ClstrSts2ForAutnmsDrv_UB { "ClstrSts2ForAutnmsDrv_UB" };
const std::string ClstrSts2ForAutnmsDrvClstr2Chks { "ClstrSts2ForAutnmsDrvClstr2Chks" };
const std::string ClstrSts2ForAutnmsDrvClstr2Cnt { "ClstrSts2ForAutnmsDrvClstr2Cnt" };
const std::string ClstrSts2ForAutnmsDrvClstr2Sts { "ClstrSts2ForAutnmsDrvClstr2Sts" };
const std::string ExtDcDcActvnAllwd { "ExtDcDcActvnAllwd" };
const std::string ExtDcDcActvnAllwd_UB { "ExtDcDcActvnAllwd_UB" };
const std::string PtTqAtAxleAvlFrntMax { "PtTqAtAxleAvlFrntMax" };
const std::string PtTqAtAxleAvlFrntMax_UB { "PtTqAtAxleAvlFrntMax_UB" };
const std::string PtTqAtAxleAvlReMax { "PtTqAtAxleAvlReMax" };
const std::string PtTqAtAxleAvlReMax_UB { "PtTqAtAxleAvlReMax_UB" };


}
}
