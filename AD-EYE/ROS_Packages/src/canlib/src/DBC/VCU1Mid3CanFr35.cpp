#include "VCU1Mid3CanFr35.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr35_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AplidSwtExtrLiToAPILiExtFctCntr, { AplidSwtExtrLiToAPILiExtFctCntr, 4, 2, true, SignalType::E2E_CNTR, 0, AplidSwtExtrLiToAPI, ParentType::GROUP } });
    signals_info.insert({ AplidSwtExtrLiToAPILiExtFctCrc, { AplidSwtExtrLiToAPILiExtFctCrc, 8, 8, true, SignalType::E2E_CHKS, 0, AplidSwtExtrLiToAPI, ParentType::GROUP } });
    signals_info.insert({ AplidSwtExtrLiToAPILiExtFctQf, { AplidSwtExtrLiToAPILiExtFctQf, 2, 2, true, SignalType::APP_UNSIGNED, 1, AplidSwtExtrLiToAPI, ParentType::GROUP } });
    signals_info.insert({ AplidSwtExtrLiToAPILiExtFctReq1, { AplidSwtExtrLiToAPILiExtFctReq1, 0, 2, true, SignalType::APP_UNSIGNED, 0, AplidSwtExtrLiToAPI, ParentType::GROUP } });
    signals_info.insert({ AplidSwtExtrLiToAPI_UB, { AplidSwtExtrLiToAPI_UB, 6, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr35, ParentType::FRAME } });

    signalgroups_info.insert({ AplidSwtExtrLiToAPI, { AplidSwtExtrLiToAPI, 0x0, { AplidSwtExtrLiToAPILiExtFctCntr, AplidSwtExtrLiToAPILiExtFctCrc, AplidSwtExtrLiToAPILiExtFctQf, AplidSwtExtrLiToAPILiExtFctReq1 }, { E2EProfileType::P05, AplidSwtExtrLiToAPILiExtFctCrc, AplidSwtExtrLiToAPILiExtFctCntr }, VCU1Mid3CanFr35 } } );

    frames_info.insert({ VCU1Mid3CanFr35, { VCU1Mid3CanFr35, 1092, 8, 840, { AplidSwtExtrLiToAPI }, { AplidSwtExtrLiToAPI_UB } } });

    frame_ids.insert({ 1092, VCU1Mid3CanFr35 });
}


}
}
