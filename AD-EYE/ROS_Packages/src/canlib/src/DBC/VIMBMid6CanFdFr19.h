#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr19_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMBMid6CanFdFr19 { "VIMBMid6CanFdFr19" };


// Groups
const std::string AdSecPSSGroupSafe0 { "AdSecPSSGroupSafe0" };


// Signals
const std::string AdSecPSSGroupSafe0Chks { "AdSecPSSGroupSafe0Chks" };
const std::string AdSecPSSGroupSafe0Cntr { "AdSecPSSGroupSafe0Cntr" };
const std::string AdSecPSSGroupSafe0DataID { "AdSecPSSGroupSafe0DataID" };
const std::string AdSecPSSGroupSafe0DeltaTPos1 { "AdSecPSSGroupSafe0DeltaTPos1" };
const std::string AdSecPSSGroupSafe0DeltaTPos2 { "AdSecPSSGroupSafe0DeltaTPos2" };
const std::string AdSecPSSGroupSafe0DeltaXPos1 { "AdSecPSSGroupSafe0DeltaXPos1" };
const std::string AdSecPSSGroupSafe0DeltaXPos2 { "AdSecPSSGroupSafe0DeltaXPos2" };
const std::string AdSecPSSGroupSafe0DeltaYPos1 { "AdSecPSSGroupSafe0DeltaYPos1" };
const std::string AdSecPSSGroupSafe0DeltaYPos2 { "AdSecPSSGroupSafe0DeltaYPos2" };
const std::string AdSecPSSGroupSafe0HeadingPos1 { "AdSecPSSGroupSafe0HeadingPos1" };
const std::string AdSecPSSGroupSafe0HeadingPos2 { "AdSecPSSGroupSafe0HeadingPos2" };
const std::string AdSecPSSGroupSafe0InitHeading { "AdSecPSSGroupSafe0InitHeading" };
const std::string AdSecPSSGroupSafe0InitPosX { "AdSecPSSGroupSafe0InitPosX" };
const std::string AdSecPSSGroupSafe0InitPosY { "AdSecPSSGroupSafe0InitPosY" };
const std::string AdSecPSSGroupSafe0TiStampNanoSec { "AdSecPSSGroupSafe0TiStampNanoSec" };
const std::string AdSecPSSGroupSafe0TiStampSec { "AdSecPSSGroupSafe0TiStampSec" };
const std::string AdSecPSSGroupSafe0TrajectID { "AdSecPSSGroupSafe0TrajectID" };
const std::string AdSecPSSGroupSafe0_UB { "AdSecPSSGroupSafe0_UB" };


}
}
