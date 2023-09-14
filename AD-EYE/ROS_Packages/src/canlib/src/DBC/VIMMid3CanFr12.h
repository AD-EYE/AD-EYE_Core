#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid3CanFr12_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid3CanFr12 { "VIMMid3CanFr12" };


// Groups
const std::string ActvnOfHndlDoorLiFromAPI { "ActvnOfHndlDoorLiFromAPI" };


// Signals
const std::string ActvnOfHndlDoorLiFromAPI_UB { "ActvnOfHndlDoorLiFromAPI_UB" };
const std::string ActvnOfHndlDoorLiFromAPIHndlDoorLiDrvr { "ActvnOfHndlDoorLiFromAPIHndlDoorLiDrvr" };
const std::string ActvnOfHndlDoorLiFromAPIHndlDoorLiDrvrRe { "ActvnOfHndlDoorLiFromAPIHndlDoorLiDrvrRe" };
const std::string ActvnOfHndlDoorLiFromAPIHndlDoorLiPass { "ActvnOfHndlDoorLiFromAPIHndlDoorLiPass" };
const std::string ActvnOfHndlDoorLiFromAPIHndlDoorLiPassRe { "ActvnOfHndlDoorLiFromAPIHndlDoorLiPassRe" };


}
}
