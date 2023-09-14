#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr24_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMBMid6CanFdFr24 { "VIMBMid6CanFdFr24" };


// Groups
const std::string AdSecPSSGroupSafe5 { "AdSecPSSGroupSafe5" };


// Signals
const std::string AdSecPSSGroupSafe5Chks { "AdSecPSSGroupSafe5Chks" };
const std::string AdSecPSSGroupSafe5Cntr { "AdSecPSSGroupSafe5Cntr" };
const std::string AdSecPSSGroupSafe5DataID { "AdSecPSSGroupSafe5DataID" };
const std::string AdSecPSSGroupSafe5DeltaTPos1 { "AdSecPSSGroupSafe5DeltaTPos1" };
const std::string AdSecPSSGroupSafe5DeltaTPos2 { "AdSecPSSGroupSafe5DeltaTPos2" };
const std::string AdSecPSSGroupSafe5DeltaTPos3 { "AdSecPSSGroupSafe5DeltaTPos3" };
const std::string AdSecPSSGroupSafe5DeltaTPos4 { "AdSecPSSGroupSafe5DeltaTPos4" };
const std::string AdSecPSSGroupSafe5DeltaTPos5 { "AdSecPSSGroupSafe5DeltaTPos5" };
const std::string AdSecPSSGroupSafe5DeltaTPos6 { "AdSecPSSGroupSafe5DeltaTPos6" };
const std::string AdSecPSSGroupSafe5DeltaXPos1 { "AdSecPSSGroupSafe5DeltaXPos1" };
const std::string AdSecPSSGroupSafe5DeltaXPos2 { "AdSecPSSGroupSafe5DeltaXPos2" };
const std::string AdSecPSSGroupSafe5DeltaXPos3 { "AdSecPSSGroupSafe5DeltaXPos3" };
const std::string AdSecPSSGroupSafe5DeltaXPos4 { "AdSecPSSGroupSafe5DeltaXPos4" };
const std::string AdSecPSSGroupSafe5DeltaXPos5 { "AdSecPSSGroupSafe5DeltaXPos5" };
const std::string AdSecPSSGroupSafe5DeltaXPos6 { "AdSecPSSGroupSafe5DeltaXPos6" };
const std::string AdSecPSSGroupSafe5DeltaYPos1 { "AdSecPSSGroupSafe5DeltaYPos1" };
const std::string AdSecPSSGroupSafe5DeltaYPos2 { "AdSecPSSGroupSafe5DeltaYPos2" };
const std::string AdSecPSSGroupSafe5DeltaYPos3 { "AdSecPSSGroupSafe5DeltaYPos3" };
const std::string AdSecPSSGroupSafe5DeltaYPos4 { "AdSecPSSGroupSafe5DeltaYPos4" };
const std::string AdSecPSSGroupSafe5DeltaYPos5 { "AdSecPSSGroupSafe5DeltaYPos5" };
const std::string AdSecPSSGroupSafe5DeltaYPos6 { "AdSecPSSGroupSafe5DeltaYPos6" };
const std::string AdSecPSSGroupSafe5HeadingPos1 { "AdSecPSSGroupSafe5HeadingPos1" };
const std::string AdSecPSSGroupSafe5HeadingPos2 { "AdSecPSSGroupSafe5HeadingPos2" };
const std::string AdSecPSSGroupSafe5HeadingPos3 { "AdSecPSSGroupSafe5HeadingPos3" };
const std::string AdSecPSSGroupSafe5HeadingPos4 { "AdSecPSSGroupSafe5HeadingPos4" };
const std::string AdSecPSSGroupSafe5HeadingPos5 { "AdSecPSSGroupSafe5HeadingPos5" };
const std::string AdSecPSSGroupSafe5HeadingPos6 { "AdSecPSSGroupSafe5HeadingPos6" };
const std::string AdSecPSSGroupSafe5TrajectID { "AdSecPSSGroupSafe5TrajectID" };
const std::string AdSecPSSGroupSafe5_UB { "AdSecPSSGroupSafe5_UB" };


}
}
