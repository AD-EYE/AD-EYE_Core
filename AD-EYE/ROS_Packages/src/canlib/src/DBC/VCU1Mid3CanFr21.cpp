#include "VCU1Mid3CanFr21.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr21_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ PtTqAtAxleReAct, { PtTqAtAxleReAct, 48, 16, SignalType::APP_SIGNED, 0, PtTqAtWhlReActGroup, ParentType::GROUP } });
    signals_info.insert({ PtTqAtWhlReLeAct, { PtTqAtWhlReLeAct, 32, 16, SignalType::APP_SIGNED, 0, PtTqAtWhlReActGroup, ParentType::GROUP } });
    signals_info.insert({ PtTqAtWhlReRiAct, { PtTqAtWhlReRiAct, 16, 16, SignalType::APP_SIGNED, 0, PtTqAtWhlReActGroup, ParentType::GROUP } });
    signals_info.insert({ PtTqAtWhlsReQly, { PtTqAtWhlsReQly, 0, 3, SignalType::APP_UNSIGNED, 0, PtTqAtWhlReActGroup, ParentType::GROUP } });
    signals_info.insert({ PtTqAtWhlReActGroup_UB, { PtTqAtWhlReActGroup_UB, 3, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr21, ParentType::FRAME } });

    signalgroups_info.insert({ PtTqAtWhlReActGroup, { PtTqAtWhlReActGroup, 0x0, { PtTqAtAxleReAct, PtTqAtWhlReLeAct, PtTqAtWhlReRiAct, PtTqAtWhlsReQly }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr21 } } );

    frames_info.insert({ VCU1Mid3CanFr21, { VCU1Mid3CanFr21, 89, 8, 20, { PtTqAtWhlReActGroup }, { PtTqAtWhlReActGroup_UB } } });

    frame_ids.insert({ 89, VCU1Mid3CanFr21 });
}


}
}
