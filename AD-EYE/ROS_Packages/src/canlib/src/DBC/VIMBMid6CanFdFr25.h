#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr25_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMBMid6CanFdFr25 { "VIMBMid6CanFdFr25" };


// Groups
const std::string AdSecPSSGroupSafe6 { "AdSecPSSGroupSafe6" };


// Signals
const std::string AdSecPSSGroupSafe6Chks { "AdSecPSSGroupSafe6Chks" };
const std::string AdSecPSSGroupSafe6Cntr { "AdSecPSSGroupSafe6Cntr" };
const std::string AdSecPSSGroupSafe6DataID { "AdSecPSSGroupSafe6DataID" };
const std::string AdSecPSSGroupSafe6DeltaTPos1 { "AdSecPSSGroupSafe6DeltaTPos1" };
const std::string AdSecPSSGroupSafe6DeltaTPos2 { "AdSecPSSGroupSafe6DeltaTPos2" };
const std::string AdSecPSSGroupSafe6DeltaTPos3 { "AdSecPSSGroupSafe6DeltaTPos3" };
const std::string AdSecPSSGroupSafe6DeltaTPos4 { "AdSecPSSGroupSafe6DeltaTPos4" };
const std::string AdSecPSSGroupSafe6DeltaTPos5 { "AdSecPSSGroupSafe6DeltaTPos5" };
const std::string AdSecPSSGroupSafe6DeltaTPos6 { "AdSecPSSGroupSafe6DeltaTPos6" };
const std::string AdSecPSSGroupSafe6DeltaXPos1 { "AdSecPSSGroupSafe6DeltaXPos1" };
const std::string AdSecPSSGroupSafe6DeltaXPos2 { "AdSecPSSGroupSafe6DeltaXPos2" };
const std::string AdSecPSSGroupSafe6DeltaXPos3 { "AdSecPSSGroupSafe6DeltaXPos3" };
const std::string AdSecPSSGroupSafe6DeltaXPos4 { "AdSecPSSGroupSafe6DeltaXPos4" };
const std::string AdSecPSSGroupSafe6DeltaXPos5 { "AdSecPSSGroupSafe6DeltaXPos5" };
const std::string AdSecPSSGroupSafe6DeltaXPos6 { "AdSecPSSGroupSafe6DeltaXPos6" };
const std::string AdSecPSSGroupSafe6DeltaYPos1 { "AdSecPSSGroupSafe6DeltaYPos1" };
const std::string AdSecPSSGroupSafe6DeltaYPos2 { "AdSecPSSGroupSafe6DeltaYPos2" };
const std::string AdSecPSSGroupSafe6DeltaYPos3 { "AdSecPSSGroupSafe6DeltaYPos3" };
const std::string AdSecPSSGroupSafe6DeltaYPos4 { "AdSecPSSGroupSafe6DeltaYPos4" };
const std::string AdSecPSSGroupSafe6DeltaYPos5 { "AdSecPSSGroupSafe6DeltaYPos5" };
const std::string AdSecPSSGroupSafe6DeltaYPos6 { "AdSecPSSGroupSafe6DeltaYPos6" };
const std::string AdSecPSSGroupSafe6HeadingPos1 { "AdSecPSSGroupSafe6HeadingPos1" };
const std::string AdSecPSSGroupSafe6HeadingPos2 { "AdSecPSSGroupSafe6HeadingPos2" };
const std::string AdSecPSSGroupSafe6HeadingPos3 { "AdSecPSSGroupSafe6HeadingPos3" };
const std::string AdSecPSSGroupSafe6HeadingPos4 { "AdSecPSSGroupSafe6HeadingPos4" };
const std::string AdSecPSSGroupSafe6HeadingPos5 { "AdSecPSSGroupSafe6HeadingPos5" };
const std::string AdSecPSSGroupSafe6HeadingPos6 { "AdSecPSSGroupSafe6HeadingPos6" };
const std::string AdSecPSSGroupSafe6TrajectID { "AdSecPSSGroupSafe6TrajectID" };
const std::string AdSecPSSGroupSafe6_UB { "AdSecPSSGroupSafe6_UB" };


}
}
