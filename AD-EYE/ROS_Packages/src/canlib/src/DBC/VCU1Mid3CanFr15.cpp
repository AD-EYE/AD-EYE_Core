#include "VCU1Mid3CanFr15.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr15_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ BltLockStAtRowSecMidForBltLockEquid, { BltLockStAtRowSecMidForBltLockEquid, 2, 1, true, SignalType::APP_UNSIGNED, 1, BltLockStAtRowSecMid, ParentType::GROUP } });
    signals_info.insert({ BltLockStAtRowSecMidForBltLockSt1, { BltLockStAtRowSecMidForBltLockSt1, 1, 1, true, SignalType::APP_UNSIGNED, 0, BltLockStAtRowSecMid, ParentType::GROUP } });
    signals_info.insert({ BltLockStAtRowSecMidForBltLockSts, { BltLockStAtRowSecMidForBltLockSts, 0, 1, true, SignalType::APP_UNSIGNED, 1, BltLockStAtRowSecMid, ParentType::GROUP } });
    signals_info.insert({ BeamHiIndcnDisp, { BeamHiIndcnDisp, 10, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ BeamHiIndcnDisp_UB, { BeamHiIndcnDisp_UB, 11, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ BltLockStAtRowSecMid_UB, { BltLockStAtRowSecMid_UB, 3, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltIndcrTurnLeFrnt, { FltIndcrTurnLeFrnt, 24, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltIndcrTurnLeFrnt_UB, { FltIndcrTurnLeFrnt_UB, 25, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltIndcrTurnLeRe, { FltIndcrTurnLeRe, 38, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltIndcrTurnLeRe_UB, { FltIndcrTurnLeRe_UB, 39, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltIndcrTurnRiFrnt, { FltIndcrTurnRiFrnt, 36, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltIndcrTurnRiFrnt_UB, { FltIndcrTurnRiFrnt_UB, 37, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltIndcrTurnRiRe, { FltIndcrTurnRiRe, 34, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltIndcrTurnRiRe_UB, { FltIndcrTurnRiRe_UB, 35, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltLiRvsg, { FltLiRvsg, 60, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltLiRvsg_UB, { FltLiRvsg_UB, 61, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBeamHiLe, { FltOfBeamHiLe, 42, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBeamHiLe_UB, { FltOfBeamHiLe_UB, 43, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBeamHiRi, { FltOfBeamHiRi, 40, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBeamHiRi_UB, { FltOfBeamHiRi_UB, 41, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBeamLoLe, { FltOfBeamLoLe, 54, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBeamLoLe_UB, { FltOfBeamLoLe_UB, 55, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBeamLoRi, { FltOfBeamLoRi, 52, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBeamLoRi_UB, { FltOfBeamLoRi_UB, 53, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBrkLiHiMntd, { FltOfBrkLiHiMntd, 30, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBrkLiHiMntd_UB, { FltOfBrkLiHiMntd_UB, 31, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBrkLiLe, { FltOfBrkLiLe, 28, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBrkLiLe_UB, { FltOfBrkLiLe_UB, 29, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBrkLiRi, { FltOfBrkLiRi, 26, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfBrkLiRi_UB, { FltOfBrkLiRi_UB, 27, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfFogLiFrnt, { FltOfFogLiFrnt, 44, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfFogLiFrnt_UB, { FltOfFogLiFrnt_UB, 45, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfLiPosnFrntLe, { FltOfLiPosnFrntLe, 32, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfLiPosnFrntLe_UB, { FltOfLiPosnFrntLe_UB, 33, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfLiPosnFrntRi, { FltOfLiPosnFrntRi, 46, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfLiPosnFrntRi_UB, { FltOfLiPosnFrntRi_UB, 47, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfPlateNr, { FltOfPlateNr, 62, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfPlateNr_UB, { FltOfPlateNr_UB, 63, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfPosnReLe, { FltOfPosnReLe, 50, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfPosnReLe_UB, { FltOfPosnReLe_UB, 51, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfPosnReRi, { FltOfPosnReRi, 48, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ FltOfPosnReRi_UB, { FltOfPosnReRi_UB, 49, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ HdlampSysFailr, { HdlampSysFailr, 58, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ HdlampSysFailr_UB, { HdlampSysFailr_UB, 59, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ SysBrkLiFailr, { SysBrkLiFailr, 12, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ SysBrkLiFailr_UB, { SysBrkLiFailr_UB, 13, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ SysDirIndcnFailr, { SysDirIndcnFailr, 14, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ SysDirIndcnFailr_UB, { SysDirIndcnFailr_UB, 15, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ TireRdEstimd, { TireRdEstimd, 0, 10, true, SignalType::APP_UNSIGNED, 204, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ TireRdEstimdQly, { TireRdEstimdQly, 5, 2, true, SignalType::APP_UNSIGNED, 1, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ TireRdEstimdQly_UB, { TireRdEstimdQly_UB, 7, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });
    signals_info.insert({ TireRdEstimd_UB, { TireRdEstimd_UB, 4, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr15, ParentType::FRAME } });

    signalgroups_info.insert({ BltLockStAtRowSecMid, { BltLockStAtRowSecMid, 0x0, { BltLockStAtRowSecMidForBltLockEquid, BltLockStAtRowSecMidForBltLockSt1, BltLockStAtRowSecMidForBltLockSts }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr15 } } );

    frames_info.insert({ VCU1Mid3CanFr15, { VCU1Mid3CanFr15, 1084, 8, 800, { BltLockStAtRowSecMid }, { FltOfBeamLoRi_UB, FltOfPosnReRi, FltIndcrTurnLeFrnt_UB, SysDirIndcnFailr, FltOfBrkLiHiMntd_UB, FltOfLiPosnFrntRi_UB, FltOfFogLiFrnt, FltOfBeamLoLe, FltOfBrkLiLe_UB, FltOfBrkLiRi_UB, FltOfBeamLoLe_UB, FltLiRvsg_UB, BeamHiIndcnDisp_UB, FltOfBeamHiRi, FltOfBeamHiLe_UB, FltOfLiPosnFrntLe_UB, FltOfBrkLiHiMntd, FltOfFogLiFrnt_UB, TireRdEstimd, FltOfBrkLiRi, SysBrkLiFailr_UB, FltIndcrTurnRiRe, FltOfBeamLoRi, BeamHiIndcnDisp, FltOfPlateNr, FltOfPosnReRi_UB, HdlampSysFailr, SysBrkLiFailr, FltIndcrTurnLeRe_UB, FltOfLiPosnFrntLe, FltLiRvsg, FltOfBeamHiLe, HdlampSysFailr_UB, FltOfBrkLiLe, FltOfPosnReLe_UB, FltOfBeamHiRi_UB, TireRdEstimdQly, SysDirIndcnFailr_UB, FltOfPlateNr_UB, FltIndcrTurnLeRe, FltIndcrTurnLeFrnt, FltIndcrTurnRiFrnt_UB, BltLockStAtRowSecMid_UB, TireRdEstimd_UB, FltOfLiPosnFrntRi, TireRdEstimdQly_UB, FltIndcrTurnRiRe_UB, FltIndcrTurnRiFrnt, FltOfPosnReLe } } });

    frame_ids.insert({ 1084, VCU1Mid3CanFr15 });
}


}
}
