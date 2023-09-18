#include "VIMMid3CanFr12.h"


namespace kcan {
namespace dbc {


void VIMMid3CanFr12_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ ActvnOfHndlDoorLiFromAPIHndlDoorLiDrvr, { ActvnOfHndlDoorLiFromAPIHndlDoorLiDrvr, 6, 1, true, SignalType::APP_UNSIGNED, 0, ActvnOfHndlDoorLiFromAPI, ParentType::GROUP } });
    signals_info.insert({ ActvnOfHndlDoorLiFromAPIHndlDoorLiDrvrRe, { ActvnOfHndlDoorLiFromAPIHndlDoorLiDrvrRe, 5, 1, true, SignalType::APP_UNSIGNED, 0, ActvnOfHndlDoorLiFromAPI, ParentType::GROUP } });
    signals_info.insert({ ActvnOfHndlDoorLiFromAPIHndlDoorLiPass, { ActvnOfHndlDoorLiFromAPIHndlDoorLiPass, 4, 1, true, SignalType::APP_UNSIGNED, 0, ActvnOfHndlDoorLiFromAPI, ParentType::GROUP } });
    signals_info.insert({ ActvnOfHndlDoorLiFromAPIHndlDoorLiPassRe, { ActvnOfHndlDoorLiFromAPIHndlDoorLiPassRe, 3, 1, true, SignalType::APP_UNSIGNED, 0, ActvnOfHndlDoorLiFromAPI, ParentType::GROUP } });
    signals_info.insert({ ActvnOfHndlDoorLiFromAPI_UB, { ActvnOfHndlDoorLiFromAPI_UB, 7, 1, true, SignalType::APP_UNSIGNED, 0, VIMMid3CanFr12, ParentType::FRAME } });

    signalgroups_info.insert({ ActvnOfHndlDoorLiFromAPI, { ActvnOfHndlDoorLiFromAPI, 0x0, { ActvnOfHndlDoorLiFromAPIHndlDoorLiDrvr, ActvnOfHndlDoorLiFromAPIHndlDoorLiDrvrRe, ActvnOfHndlDoorLiFromAPIHndlDoorLiPass, ActvnOfHndlDoorLiFromAPIHndlDoorLiPassRe }, { E2EProfileType::None, "", "" }, VIMMid3CanFr12 } } );

    frames_info.insert({ VIMMid3CanFr12, { VIMMid3CanFr12, 1091, 8, 840, { ActvnOfHndlDoorLiFromAPI }, { ActvnOfHndlDoorLiFromAPI_UB } } });

    frame_ids.insert({ 1091, VIMMid3CanFr12 });
}


}
}
