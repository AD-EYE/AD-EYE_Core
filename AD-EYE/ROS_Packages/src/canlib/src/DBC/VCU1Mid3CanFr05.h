#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr05_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr05 { "VCU1Mid3CanFr05" };


// Groups
const std::string AdSecBlindStopMonActvnGroupSafe { "AdSecBlindStopMonActvnGroupSafe" };
const std::string DrvrGearShiftManReq { "DrvrGearShiftManReq" };
const std::string SnsrClngErrIf { "SnsrClngErrIf" };
const std::string VehMGroup { "VehMGroup" };


// Signals
const std::string VehMGroup_UB { "VehMGroup_UB" };
const std::string SnsrClngErrIf_UB { "SnsrClngErrIf_UB" };
const std::string DrvrGearShiftManReq_UB { "DrvrGearShiftManReq_UB" };
const std::string DrvrGearShiftManReqUpTipReq { "DrvrGearShiftManReqUpTipReq" };
const std::string DrvrGearShiftManReqTipReq { "DrvrGearShiftManReqTipReq" };
const std::string DrvrGearShiftManReqSteerWhlUpReq { "DrvrGearShiftManReqSteerWhlUpReq" };
const std::string DrvrGearShiftManReqSteerWhlDwnReq { "DrvrGearShiftManReqSteerWhlDwnReq" };
const std::string DrvrGearShiftManReqDwnTipReq { "DrvrGearShiftManReqDwnTipReq" };
const std::string SnsrClngErrIfActr1 { "SnsrClngErrIfActr1" };
const std::string SnsrClngErrIfActr2 { "SnsrClngErrIfActr2" };
const std::string SnsrClngErrIfActr3 { "SnsrClngErrIfActr3" };
const std::string SnsrClngErrIfRsvd1 { "SnsrClngErrIfRsvd1" };
const std::string SnsrClngErrIfRsvd2 { "SnsrClngErrIfRsvd2" };
const std::string SnsrClngErrIfRsvd3 { "SnsrClngErrIfRsvd3" };
const std::string SnsrClngErrIfSysClngFailr { "SnsrClngErrIfSysClngFailr" };
const std::string SnsrClngErrIfWshrFldSnsrFailr { "SnsrClngErrIfWshrFldSnsrFailr" };
const std::string WiprActvIf_UB { "WiprActvIf_UB" };
const std::string WiprActvIf { "WiprActvIf" };
const std::string WinWipgAutCmdIf_UB { "WinWipgAutCmdIf_UB" };
const std::string WinWipgAutCmdIf { "WinWipgAutCmdIf" };
const std::string VehMQly { "VehMQly" };
const std::string VehMNomTrlrM { "VehMNomTrlrM" };
const std::string VehM { "VehM" };
const std::string WipgFrntAutModIf_UB { "WipgFrntAutModIf_UB" };
const std::string WipgFrntAutModIf { "WipgFrntAutModIf" };
const std::string WshngCycActvIf_UB { "WshngCycActvIf_UB" };
const std::string WshngCycActvIf { "WshngCycActvIf" };
const std::string PassSeatSts_UB { "PassSeatSts_UB" };
const std::string PassSeatSts { "PassSeatSts" };
const std::string AdSecBlindStopMonActvnGroupSafe_UB { "AdSecBlindStopMonActvnGroupSafe_UB" };
const std::string AdSecBlindStopMonActvnGroupSafeActvnReq { "AdSecBlindStopMonActvnGroupSafeActvnReq" };
const std::string AdSecBlindStopMonActvnGroupSafeDeactvnReq { "AdSecBlindStopMonActvnGroupSafeDeactvnReq" };
const std::string AdSecBlindStopMonActvnGroupSafeCntr { "AdSecBlindStopMonActvnGroupSafeCntr" };
const std::string AdSecBlindStopMonActvnGroupSafeChks { "AdSecBlindStopMonActvnGroupSafeChks" };


}
}
