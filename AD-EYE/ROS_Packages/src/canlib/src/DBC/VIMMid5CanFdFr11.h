#include "../basic_types.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr11_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const string VIMMid5CanFdFr11 { "VIMMid5CanFdFr11" };

// Groups
const string AdPrimPSSGroupSafe8 { "AdPrimPSSGroupSafe8" };

// Signals
const string AdPrimPSSGroupSafe8_UB { "AdPrimPSSGroupSafe8_UB" };
const string AdPrimPSSGroupSafe8Chks { "AdPrimPSSGroupSafe8Chks" };
const string AdPrimPSSGroupSafe8Cntr { "AdPrimPSSGroupSafe8Cntr" };
const string AdPrimPSSGroupSafe8DataID { "AdPrimPSSGroupSafe8DataID" };
const string AdPrimPSSGroupSafe8DeltaTPos1 { "AdPrimPSSGroupSafe8DeltaTPos1" };
const string AdPrimPSSGroupSafe8DeltaTPos2 { "AdPrimPSSGroupSafe8DeltaTPos2" };
const string AdPrimPSSGroupSafe8DeltaTPos3 { "AdPrimPSSGroupSafe8DeltaTPos3" };
const string AdPrimPSSGroupSafe8DeltaTPos4 { "AdPrimPSSGroupSafe8DeltaTPos4" };
const string AdPrimPSSGroupSafe8DeltaTPos5 { "AdPrimPSSGroupSafe8DeltaTPos5" };
const string AdPrimPSSGroupSafe8DeltaTPos6 { "AdPrimPSSGroupSafe8DeltaTPos6" };
const string AdPrimPSSGroupSafe8DeltaXPos1 { "AdPrimPSSGroupSafe8DeltaXPos1" };
const string AdPrimPSSGroupSafe8DeltaXPos2 { "AdPrimPSSGroupSafe8DeltaXPos2" };
const string AdPrimPSSGroupSafe8DeltaXPos3 { "AdPrimPSSGroupSafe8DeltaXPos3" };
const string AdPrimPSSGroupSafe8DeltaXPos4 { "AdPrimPSSGroupSafe8DeltaXPos4" };
const string AdPrimPSSGroupSafe8DeltaXPos5 { "AdPrimPSSGroupSafe8DeltaXPos5" };
const string AdPrimPSSGroupSafe8DeltaXPos6 { "AdPrimPSSGroupSafe8DeltaXPos6" };
const string AdPrimPSSGroupSafe8DeltaYPos1 { "AdPrimPSSGroupSafe8DeltaYPos1" };
const string AdPrimPSSGroupSafe8DeltaYPos2 { "AdPrimPSSGroupSafe8DeltaYPos2" };
const string AdPrimPSSGroupSafe8DeltaYPos3 { "AdPrimPSSGroupSafe8DeltaYPos3" };
const string AdPrimPSSGroupSafe8DeltaYPos4 { "AdPrimPSSGroupSafe8DeltaYPos4" };
const string AdPrimPSSGroupSafe8DeltaYPos5 { "AdPrimPSSGroupSafe8DeltaYPos5" };
const string AdPrimPSSGroupSafe8DeltaYPos6 { "AdPrimPSSGroupSafe8DeltaYPos6" };
const string AdPrimPSSGroupSafe8HeadingPos1 { "AdPrimPSSGroupSafe8HeadingPos1" };
const string AdPrimPSSGroupSafe8HeadingPos2 { "AdPrimPSSGroupSafe8HeadingPos2" };
const string AdPrimPSSGroupSafe8HeadingPos3 { "AdPrimPSSGroupSafe8HeadingPos3" };
const string AdPrimPSSGroupSafe8HeadingPos4 { "AdPrimPSSGroupSafe8HeadingPos4" };
const string AdPrimPSSGroupSafe8HeadingPos5 { "AdPrimPSSGroupSafe8HeadingPos5" };
const string AdPrimPSSGroupSafe8HeadingPos6 { "AdPrimPSSGroupSafe8HeadingPos6" };
const string AdPrimPSSGroupSafe8TrajectID { "AdPrimPSSGroupSafe8TrajectID" };


}
}