#include "../basic_types.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr25_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr25 { "VCU1Mid3CanFr25" };

// Groups
const std::string DrvrIntvSts { "DrvrIntvSts" };
const std::string DrvrPrsntGroup { "DrvrPrsntGroup" };

// Signals
const std::string DrvrIntvSts_UB {"DrvrIntvSts_UB"};
const std::string DrvrIntvStsDrvrIntvByAccrPedl {"DrvrIntvStsDrvrIntvByAccrPedl"};
const std::string DrvrIntvStsDrvrIntvByBrkPedl {"DrvrIntvStsDrvrIntvByBrkPedl"};
const std::string DrvrIntvStsDrvrIntvBySteering {"DrvrIntvStsDrvrIntvBySteering"};
const std::string DrvrPrsnt {"DrvrPrsnt"};
const std::string DrvrPrsntGroup_UB {"DrvrPrsntGroup_UB"};
const std::string DrvrPrsntQf {"DrvrPrsntQf"};
const std::string DrvrPrsntStsDrvrPrsntChks {"DrvrPrsntStsDrvrPrsntChks"};
const std::string DrvrPrsntStsDrvrPrsntCntr {"DrvrPrsntStsDrvrPrsntCntr"};
const std::string EgyAvlChrgTot {"EgyAvlChrgTot"};
const std::string EgyAvlChrgTot_UB {"EgyAvlChrgTot_UB"};
const std::string EgyAvlDchaTot {"EgyAvlDchaTot"};
const std::string EgyAvlDchaTot_UB {"EgyAvlDchaTot_UB"};

}
}
