#include "VCU1Mid3CanFr20.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr20_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ PtTqAtAxleFrntAct, { PtTqAtAxleFrntAct, 48, 16, true, SignalType::APP_SIGNED, 0, PtTqAtWhlFrntActGroup, ParentType::GROUP } });
    signals_info.insert({ PtTqAtWhlFrntLeAct, { PtTqAtWhlFrntLeAct, 32, 16, true, SignalType::APP_SIGNED, 0, PtTqAtWhlFrntActGroup, ParentType::GROUP } });
    signals_info.insert({ PtTqAtWhlFrntRiAct, { PtTqAtWhlFrntRiAct, 16, 16, true, SignalType::APP_SIGNED, 0, PtTqAtWhlFrntActGroup, ParentType::GROUP } });
    signals_info.insert({ PtTqAtWhlsFrntQly, { PtTqAtWhlsFrntQly, 0, 3, true, SignalType::APP_UNSIGNED, 0, PtTqAtWhlFrntActGroup, ParentType::GROUP } });
    signals_info.insert({ PtTqAtWhlFrntActGroup_UB, { PtTqAtWhlFrntActGroup_UB, 3, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr20, ParentType::FRAME } });

    signalgroups_info.insert({ PtTqAtWhlFrntActGroup, { PtTqAtWhlFrntActGroup, 0x0, { PtTqAtAxleFrntAct, PtTqAtWhlFrntLeAct, PtTqAtWhlFrntRiAct, PtTqAtWhlsFrntQly }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr20 } } );

    frames_info.insert({ VCU1Mid3CanFr20, { VCU1Mid3CanFr20, 88, 8, 20, { PtTqAtWhlFrntActGroup }, { PtTqAtWhlFrntActGroup_UB } } });

    frame_ids.insert({ 88, VCU1Mid3CanFr20 });
}


}
}
