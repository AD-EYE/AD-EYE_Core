#include "VCU1Mid3CanFr05.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr05_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecBlindStopMonActvnGroupSafeActvnReq, { AdSecBlindStopMonActvnGroupSafeActvnReq, 53, 1, SignalType::APP_UNSIGNED, 0, AdSecBlindStopMonActvnGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecBlindStopMonActvnGroupSafeChks, { AdSecBlindStopMonActvnGroupSafeChks, 56, 8, SignalType::E2E_CHKS, 0, AdSecBlindStopMonActvnGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecBlindStopMonActvnGroupSafeCntr, { AdSecBlindStopMonActvnGroupSafeCntr, 48, 4, SignalType::E2E_CNTR, 0, AdSecBlindStopMonActvnGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecBlindStopMonActvnGroupSafeDeactvnReq, { AdSecBlindStopMonActvnGroupSafeDeactvnReq, 52, 1, SignalType::APP_UNSIGNED, 0, AdSecBlindStopMonActvnGroupSafe, ParentType::GROUP } });
    signals_info.insert({ DrvrGearShiftManReqDwnTipReq, { DrvrGearShiftManReqDwnTipReq, 0, 1, SignalType::APP_UNSIGNED, 0, DrvrGearShiftManReq, ParentType::GROUP } });
    signals_info.insert({ DrvrGearShiftManReqSteerWhlDwnReq, { DrvrGearShiftManReqSteerWhlDwnReq, 1, 1, SignalType::APP_UNSIGNED, 0, DrvrGearShiftManReq, ParentType::GROUP } });
    signals_info.insert({ DrvrGearShiftManReqSteerWhlUpReq, { DrvrGearShiftManReqSteerWhlUpReq, 2, 1, SignalType::APP_UNSIGNED, 0, DrvrGearShiftManReq, ParentType::GROUP } });
    signals_info.insert({ DrvrGearShiftManReqTipReq, { DrvrGearShiftManReqTipReq, 3, 1, SignalType::APP_UNSIGNED, 0, DrvrGearShiftManReq, ParentType::GROUP } });
    signals_info.insert({ DrvrGearShiftManReqUpTipReq, { DrvrGearShiftManReqUpTipReq, 4, 1, SignalType::APP_UNSIGNED, 0, DrvrGearShiftManReq, ParentType::GROUP } });
    signals_info.insert({ SnsrClngErrIfActr1, { SnsrClngErrIfActr1, 15, 1, SignalType::APP_UNSIGNED, 0, SnsrClngErrIf, ParentType::GROUP } });
    signals_info.insert({ SnsrClngErrIfActr2, { SnsrClngErrIfActr2, 14, 1, SignalType::APP_UNSIGNED, 0, SnsrClngErrIf, ParentType::GROUP } });
    signals_info.insert({ SnsrClngErrIfActr3, { SnsrClngErrIfActr3, 13, 1, SignalType::APP_UNSIGNED, 0, SnsrClngErrIf, ParentType::GROUP } });
    signals_info.insert({ SnsrClngErrIfRsvd1, { SnsrClngErrIfRsvd1, 12, 1, SignalType::APP_UNSIGNED, 0, SnsrClngErrIf, ParentType::GROUP } });
    signals_info.insert({ SnsrClngErrIfRsvd2, { SnsrClngErrIfRsvd2, 11, 1, SignalType::APP_UNSIGNED, 0, SnsrClngErrIf, ParentType::GROUP } });
    signals_info.insert({ SnsrClngErrIfRsvd3, { SnsrClngErrIfRsvd3, 10, 1, SignalType::APP_UNSIGNED, 0, SnsrClngErrIf, ParentType::GROUP } });
    signals_info.insert({ SnsrClngErrIfSysClngFailr, { SnsrClngErrIfSysClngFailr, 9, 1, SignalType::APP_UNSIGNED, 0, SnsrClngErrIf, ParentType::GROUP } });
    signals_info.insert({ SnsrClngErrIfWshrFldSnsrFailr, { SnsrClngErrIfWshrFldSnsrFailr, 8, 1, SignalType::APP_UNSIGNED, 0, SnsrClngErrIf, ParentType::GROUP } });
    signals_info.insert({ VehM, { VehM, 16, 14, SignalType::APP_UNSIGNED, 0, VehMGroup, ParentType::GROUP } });
    signals_info.insert({ VehMNomTrlrM, { VehMNomTrlrM, 30, 2, SignalType::APP_UNSIGNED, 0, VehMGroup, ParentType::GROUP } });
    signals_info.insert({ VehMQly, { VehMQly, 16, 2, SignalType::APP_UNSIGNED, 1, VehMGroup, ParentType::GROUP } });
    signals_info.insert({ WipgFrntAutModIf, { WipgFrntAutModIf, 45, 2, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ WipgFrntAutModIf_UB, { WipgFrntAutModIf_UB, 47, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ WiprActvIf_UB, { WiprActvIf_UB, 23, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ PassSeatSts, { PassSeatSts, 40, 2, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ SnsrClngErrIf_UB, { SnsrClngErrIf_UB, 6, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ WinWipgAutCmdIf_UB, { WinWipgAutCmdIf_UB, 21, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ DrvrGearShiftManReq_UB, { DrvrGearShiftManReq_UB, 5, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ WshngCycActvIf_UB, { WshngCycActvIf_UB, 44, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ AdSecBlindStopMonActvnGroupSafe_UB, { AdSecBlindStopMonActvnGroupSafe_UB, 54, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ PassSeatSts_UB, { PassSeatSts_UB, 42, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ WiprActvIf, { WiprActvIf, 22, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ WinWipgAutCmdIf, { WinWipgAutCmdIf, 18, 3, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ WshngCycActvIf, { WshngCycActvIf, 43, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });
    signals_info.insert({ VehMGroup_UB, { VehMGroup_UB, 7, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr05, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecBlindStopMonActvnGroupSafe, { AdSecBlindStopMonActvnGroupSafe, 0x26E, { AdSecBlindStopMonActvnGroupSafeActvnReq, AdSecBlindStopMonActvnGroupSafeChks, AdSecBlindStopMonActvnGroupSafeCntr, AdSecBlindStopMonActvnGroupSafeDeactvnReq }, { E2EProfileType::P01a, AdSecBlindStopMonActvnGroupSafeChks, AdSecBlindStopMonActvnGroupSafeCntr }, VCU1Mid3CanFr05 } } );
    signalgroups_info.insert({ DrvrGearShiftManReq, { DrvrGearShiftManReq, 0x0, { DrvrGearShiftManReqDwnTipReq, DrvrGearShiftManReqSteerWhlDwnReq, DrvrGearShiftManReqSteerWhlUpReq, DrvrGearShiftManReqTipReq, DrvrGearShiftManReqUpTipReq }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr05 } } );
    signalgroups_info.insert({ SnsrClngErrIf, { SnsrClngErrIf, 0x0, { SnsrClngErrIfActr1, SnsrClngErrIfActr2, SnsrClngErrIfActr3, SnsrClngErrIfRsvd1, SnsrClngErrIfRsvd2, SnsrClngErrIfRsvd3, SnsrClngErrIfSysClngFailr, SnsrClngErrIfWshrFldSnsrFailr }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr05 } } );
    signalgroups_info.insert({ VehMGroup, { VehMGroup, 0x0, { VehM, VehMNomTrlrM, VehMQly }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr05 } } );

    frames_info.insert({ VCU1Mid3CanFr05, { VCU1Mid3CanFr05, 153, 8, 95, { AdSecBlindStopMonActvnGroupSafe, DrvrGearShiftManReq, SnsrClngErrIf, VehMGroup }, { WipgFrntAutModIf, WipgFrntAutModIf_UB, WiprActvIf_UB, PassSeatSts, SnsrClngErrIf_UB, WinWipgAutCmdIf_UB, DrvrGearShiftManReq_UB, WshngCycActvIf_UB, AdSecBlindStopMonActvnGroupSafe_UB, PassSeatSts_UB, WiprActvIf, WinWipgAutCmdIf, WshngCycActvIf, VehMGroup_UB } } });

    frame_ids.insert({ 153, VCU1Mid3CanFr05 });
}


}
}
