#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr17_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr17 { "VCU1Mid3CanFr17" };


// Groups
const std::string ALnchTiDly3 { "ALnchTiDly3" };
const std::string AlrmSts1 { "AlrmSts1" };


// Signals
const std::string EngOilLvlSts { "EngOilLvlSts" };
const std::string EngOilLvlSts_UB { "EngOilLvlSts_UB" };
const std::string TrSts_UB { "TrSts_UB" };
const std::string HoodSts_UB { "HoodSts_UB" };
const std::string AlrmSts1_UB { "AlrmSts1_UB" };
const std::string SnsrSoundrBattBackedFailr { "SnsrSoundrBattBackedFailr" };
const std::string SnsrIntrScanrFailr { "SnsrIntrScanrFailr" };
const std::string SnsrInclnFailr { "SnsrInclnFailr" };
const std::string AlrmTrgSrc { "AlrmTrgSrc" };
const std::string AlrmSt { "AlrmSt" };
const std::string DoorPassSts_UB { "DoorPassSts_UB" };
const std::string DoorPassReSts_UB { "DoorPassReSts_UB" };
const std::string DoorDrvrSts_UB { "DoorDrvrSts_UB" };
const std::string DoorDrvrSts { "DoorDrvrSts" };
const std::string DoorDrvrReSts_UB { "DoorDrvrReSts_UB" };
const std::string DoorDrvrReSts { "DoorDrvrReSts" };
const std::string DoorPassReSts { "DoorPassReSts" };
const std::string DoorPassSts { "DoorPassSts" };
const std::string HoodSts { "HoodSts" };
const std::string TrSts { "TrSts" };
const std::string ALnchTiDly3Qf { "ALnchTiDly3Qf" };
const std::string ALnchTiDly3Sec2 { "ALnchTiDly3Sec2" };
const std::string ALnchTiDly3_UB { "ALnchTiDly3_UB" };


}
}
