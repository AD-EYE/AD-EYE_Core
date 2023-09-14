#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid5CanFdFr03_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid5CanFdFr03 { "VIMMid5CanFdFr03" };


// Groups
const std::string AdPrimPSSGroupSafe0 { "AdPrimPSSGroupSafe0" };


// Signals
const std::string AdPrimPSSGroupSafe0Chks { "AdPrimPSSGroupSafe0Chks" };
const std::string AdPrimPSSGroupSafe0Cntr { "AdPrimPSSGroupSafe0Cntr" };
const std::string AdPrimPSSGroupSafe0DataID { "AdPrimPSSGroupSafe0DataID" };
const std::string AdPrimPSSGroupSafe0TrajectID { "AdPrimPSSGroupSafe0TrajectID" };
const std::string AdPrimPSSGroupSafe0DeltaTPos1 { "AdPrimPSSGroupSafe0DeltaTPos1" };
const std::string AdPrimPSSGroupSafe0DeltaTPos2 { "AdPrimPSSGroupSafe0DeltaTPos2" };
const std::string AdPrimPSSGroupSafe0DeltaXPos1 { "AdPrimPSSGroupSafe0DeltaXPos1" };
const std::string AdPrimPSSGroupSafe0DeltaXPos2 { "AdPrimPSSGroupSafe0DeltaXPos2" };
const std::string AdPrimPSSGroupSafe0DeltaYPos1 { "AdPrimPSSGroupSafe0DeltaYPos1" };
const std::string AdPrimPSSGroupSafe0DeltaYPos2 { "AdPrimPSSGroupSafe0DeltaYPos2" };
const std::string AdPrimPSSGroupSafe0HeadingPos1 { "AdPrimPSSGroupSafe0HeadingPos1" };
const std::string AdPrimPSSGroupSafe0HeadingPos2 { "AdPrimPSSGroupSafe0HeadingPos2" };
const std::string AdPrimPSSGroupSafe0InitHeading { "AdPrimPSSGroupSafe0InitHeading" };
const std::string AdPrimPSSGroupSafe0InitPosX { "AdPrimPSSGroupSafe0InitPosX" };
const std::string AdPrimPSSGroupSafe0InitPosY { "AdPrimPSSGroupSafe0InitPosY" };
const std::string AdPrimPSSGroupSafe0TiStampNanoSec { "AdPrimPSSGroupSafe0TiStampNanoSec" };
const std::string AdPrimPSSGroupSafe0TiStampSec { "AdPrimPSSGroupSafe0TiStampSec" };
const std::string AdPrimPSSGroupSafe0_UB { "AdPrimPSSGroupSafe0_UB" };


}
}
