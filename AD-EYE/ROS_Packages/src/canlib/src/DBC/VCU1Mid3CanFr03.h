#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr03_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr03 { "VCU1Mid3CanFr03" };


// Groups
const std::string AdSecSteerActvnGroupSafe { "AdSecSteerActvnGroupSafe" };
const std::string PrpsnTqDir { "PrpsnTqDir" };
const std::string SteerWhlTqGroup { "SteerWhlTqGroup" };


// Signals
const std::string SteerWhlTqGroup_UB { "SteerWhlTqGroup_UB" };
const std::string AdSecSteerActvnGroupSafe_UB { "AdSecSteerActvnGroupSafe_UB" };
const std::string AdSecSteerActvnGroupSafeAdSteerActvnReq { "AdSecSteerActvnGroupSafeAdSteerActvnReq" };
const std::string AdSecSteerActvnGroupSafeAdSteerDeActvnReq { "AdSecSteerActvnGroupSafeAdSteerDeActvnReq" };
const std::string AdSecSteerActvnGroupSafeCntr { "AdSecSteerActvnGroupSafeCntr" };
const std::string AdSecSteerActvnGroupSafeChks { "AdSecSteerActvnGroupSafeChks" };
const std::string SteerWhlTqQf { "SteerWhlTqQf" };
const std::string SteerWhlTq { "SteerWhlTq" };
const std::string PrpsnTqDir_UB { "PrpsnTqDir_UB" };
const std::string PrpsnTqDirAct { "PrpsnTqDirAct" };
const std::string PrpsnTqDirCntr { "PrpsnTqDirCntr" };
const std::string PrpsnTqDirChks { "PrpsnTqDirChks" };


}
}
