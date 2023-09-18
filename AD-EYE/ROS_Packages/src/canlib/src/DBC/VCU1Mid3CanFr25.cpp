#include "VCU1Mid3CanFr25.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr25_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ DrvrIntvStsDrvrIntvByAccrPedl, { DrvrIntvStsDrvrIntvByAccrPedl, 36, 1, true, SignalType::APP_UNSIGNED, 0, DrvrIntvSts, ParentType::GROUP } });
    signals_info.insert({ DrvrIntvStsDrvrIntvByBrkPedl, { DrvrIntvStsDrvrIntvByBrkPedl, 37, 1, true, SignalType::APP_UNSIGNED, 0, DrvrIntvSts, ParentType::GROUP } });
    signals_info.insert({ DrvrIntvStsDrvrIntvBySteering, { DrvrIntvStsDrvrIntvBySteering, 38, 1, true, SignalType::APP_UNSIGNED, 0, DrvrIntvSts, ParentType::GROUP } });
    signals_info.insert({ DrvrPrsnt, { DrvrPrsnt, 10, 2, true, SignalType::APP_UNSIGNED, 1, DrvrPrsntGroup, ParentType::GROUP } });
    signals_info.insert({ DrvrPrsntQf, { DrvrPrsntQf, 8, 2, true, SignalType::APP_UNSIGNED, 1, DrvrPrsntGroup, ParentType::GROUP } });
    signals_info.insert({ DrvrPrsntStsDrvrPrsntChks, { DrvrPrsntStsDrvrPrsntChks, 0, 8, true, SignalType::E2E_CHKS, 0, DrvrPrsntGroup, ParentType::GROUP } });
    signals_info.insert({ DrvrPrsntStsDrvrPrsntCntr, { DrvrPrsntStsDrvrPrsntCntr, 12, 4, true, SignalType::E2E_CNTR, 0, DrvrPrsntGroup, ParentType::GROUP } });
    signals_info.insert({ DrvrIntvSts_UB, { DrvrIntvSts_UB, 39, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr25, ParentType::FRAME } });
    signals_info.insert({ DrvrPrsntGroup_UB, { DrvrPrsntGroup_UB, 23, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr25, ParentType::FRAME } });
    signals_info.insert({ EgyAvlChrgTot, { EgyAvlChrgTot, 24, 12, true, SignalType::APP_UNSIGNED, 10, VCU1Mid3CanFr25, ParentType::FRAME } });
    signals_info.insert({ EgyAvlChrgTot_UB, { EgyAvlChrgTot_UB, 20, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr25, ParentType::FRAME } });
    signals_info.insert({ EgyAvlDchaTot, { EgyAvlDchaTot, 40, 12, true, SignalType::APP_UNSIGNED, 10, VCU1Mid3CanFr25, ParentType::FRAME } });
    signals_info.insert({ EgyAvlDchaTot_UB, { EgyAvlDchaTot_UB, 21, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr25, ParentType::FRAME } });

    signalgroups_info.insert({ DrvrIntvSts, { DrvrIntvSts, 0x0, { DrvrIntvStsDrvrIntvByAccrPedl, DrvrIntvStsDrvrIntvByBrkPedl, DrvrIntvStsDrvrIntvBySteering }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr25 } } );
    signalgroups_info.insert({ DrvrPrsntGroup, { DrvrPrsntGroup, 0x79, { DrvrPrsnt, DrvrPrsntQf, DrvrPrsntStsDrvrPrsntChks, DrvrPrsntStsDrvrPrsntCntr }, { E2EProfileType::P01a, DrvrPrsntStsDrvrPrsntChks, DrvrPrsntStsDrvrPrsntCntr }, VCU1Mid3CanFr25 } } );

    frames_info.insert({ VCU1Mid3CanFr25, { VCU1Mid3CanFr25, 391, 8, 160, { DrvrIntvSts, DrvrPrsntGroup }, { EgyAvlDchaTot, DrvrPrsntGroup_UB, EgyAvlChrgTot, DrvrIntvSts_UB, EgyAvlChrgTot_UB, EgyAvlDchaTot_UB } } });

    frame_ids.insert({ 391, VCU1Mid3CanFr25 });
}


}
}
