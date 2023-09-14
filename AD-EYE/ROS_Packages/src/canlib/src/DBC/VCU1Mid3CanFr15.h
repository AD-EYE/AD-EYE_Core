#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VCU1Mid3CanFr15_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VCU1Mid3CanFr15 { "VCU1Mid3CanFr15" };


// Groups
const std::string BltLockStAtRowSecMid { "BltLockStAtRowSecMid" };


// Signals
const std::string TireRdEstimdQly_UB { "TireRdEstimdQly_UB" };
const std::string TireRdEstimdQly { "TireRdEstimdQly" };
const std::string TireRdEstimd_UB { "TireRdEstimd_UB" };
const std::string BltLockStAtRowSecMid_UB { "BltLockStAtRowSecMid_UB" };
const std::string BltLockStAtRowSecMidForBltLockEquid { "BltLockStAtRowSecMidForBltLockEquid" };
const std::string BltLockStAtRowSecMidForBltLockSt1 { "BltLockStAtRowSecMidForBltLockSt1" };
const std::string BltLockStAtRowSecMidForBltLockSts { "BltLockStAtRowSecMidForBltLockSts" };
const std::string SysDirIndcnFailr_UB { "SysDirIndcnFailr_UB" };
const std::string SysDirIndcnFailr { "SysDirIndcnFailr" };
const std::string SysBrkLiFailr_UB { "SysBrkLiFailr_UB" };
const std::string SysBrkLiFailr { "SysBrkLiFailr" };
const std::string BeamHiIndcnDisp_UB { "BeamHiIndcnDisp_UB" };
const std::string BeamHiIndcnDisp { "BeamHiIndcnDisp" };
const std::string TireRdEstimd { "TireRdEstimd" };
const std::string FltOfBrkLiHiMntd_UB { "FltOfBrkLiHiMntd_UB" };
const std::string FltOfBrkLiHiMntd { "FltOfBrkLiHiMntd" };
const std::string FltOfBrkLiLe_UB { "FltOfBrkLiLe_UB" };
const std::string FltOfBrkLiLe { "FltOfBrkLiLe" };
const std::string FltOfBrkLiRi_UB { "FltOfBrkLiRi_UB" };
const std::string FltOfBrkLiRi { "FltOfBrkLiRi" };
const std::string FltIndcrTurnLeFrnt_UB { "FltIndcrTurnLeFrnt_UB" };
const std::string FltIndcrTurnLeFrnt { "FltIndcrTurnLeFrnt" };
const std::string FltIndcrTurnLeRe_UB { "FltIndcrTurnLeRe_UB" };
const std::string FltIndcrTurnLeRe { "FltIndcrTurnLeRe" };
const std::string FltIndcrTurnRiFrnt_UB { "FltIndcrTurnRiFrnt_UB" };
const std::string FltIndcrTurnRiFrnt { "FltIndcrTurnRiFrnt" };
const std::string FltIndcrTurnRiRe_UB { "FltIndcrTurnRiRe_UB" };
const std::string FltIndcrTurnRiRe { "FltIndcrTurnRiRe" };
const std::string FltOfLiPosnFrntLe_UB { "FltOfLiPosnFrntLe_UB" };
const std::string FltOfLiPosnFrntLe { "FltOfLiPosnFrntLe" };
const std::string FltOfLiPosnFrntRi_UB { "FltOfLiPosnFrntRi_UB" };
const std::string FltOfLiPosnFrntRi { "FltOfLiPosnFrntRi" };
const std::string FltOfFogLiFrnt_UB { "FltOfFogLiFrnt_UB" };
const std::string FltOfFogLiFrnt { "FltOfFogLiFrnt" };
const std::string FltOfBeamHiLe_UB { "FltOfBeamHiLe_UB" };
const std::string FltOfBeamHiLe { "FltOfBeamHiLe" };
const std::string FltOfBeamHiRi_UB { "FltOfBeamHiRi_UB" };
const std::string FltOfBeamHiRi { "FltOfBeamHiRi" };
const std::string FltOfBeamLoLe_UB { "FltOfBeamLoLe_UB" };
const std::string FltOfBeamLoLe { "FltOfBeamLoLe" };
const std::string FltOfBeamLoRi_UB { "FltOfBeamLoRi_UB" };
const std::string FltOfBeamLoRi { "FltOfBeamLoRi" };
const std::string FltOfPosnReLe_UB { "FltOfPosnReLe_UB" };
const std::string FltOfPosnReLe { "FltOfPosnReLe" };
const std::string FltOfPosnReRi_UB { "FltOfPosnReRi_UB" };
const std::string FltOfPosnReRi { "FltOfPosnReRi" };
const std::string FltOfPlateNr_UB { "FltOfPlateNr_UB" };
const std::string FltOfPlateNr { "FltOfPlateNr" };
const std::string FltLiRvsg_UB { "FltLiRvsg_UB" };
const std::string FltLiRvsg { "FltLiRvsg" };
const std::string HdlampSysFailr_UB { "HdlampSysFailr_UB" };
const std::string HdlampSysFailr { "HdlampSysFailr" };


}
}
