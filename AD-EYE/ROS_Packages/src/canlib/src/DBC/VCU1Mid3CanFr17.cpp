#include "VCU1Mid3CanFr17.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr17_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ ALnchTiDly3Qf, { ALnchTiDly3Qf, 38, 2, true, SignalType::APP_UNSIGNED, 0, ALnchTiDly3, ParentType::GROUP } });
    signals_info.insert({ ALnchTiDly3Sec2, { ALnchTiDly3Sec2, 32, 6, true, SignalType::APP_UNSIGNED, 0, ALnchTiDly3, ParentType::GROUP } });
    signals_info.insert({ AlrmSt, { AlrmSt, 8, 2, true, SignalType::APP_UNSIGNED, 0, AlrmSts1, ParentType::GROUP } });
    signals_info.insert({ AlrmTrgSrc, { AlrmTrgSrc, 10, 4, true, SignalType::APP_UNSIGNED, 0, AlrmSts1, ParentType::GROUP } });
    signals_info.insert({ SnsrInclnFailr, { SnsrInclnFailr, 14, 1, true, SignalType::APP_UNSIGNED, 0, AlrmSts1, ParentType::GROUP } });
    signals_info.insert({ SnsrIntrScanrFailr, { SnsrIntrScanrFailr, 15, 1, true, SignalType::APP_UNSIGNED, 0, AlrmSts1, ParentType::GROUP } });
    signals_info.insert({ SnsrSoundrBattBackedFailr, { SnsrSoundrBattBackedFailr, 0, 1, true, SignalType::APP_UNSIGNED, 0, AlrmSts1, ParentType::GROUP } });
    signals_info.insert({ ALnchTiDly3_UB, { ALnchTiDly3_UB, 47, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ AlrmSts1_UB, { AlrmSts1_UB, 1, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ DoorDrvrReSts, { DoorDrvrReSts, 16, 2, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ DoorDrvrReSts_UB, { DoorDrvrReSts_UB, 18, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ DoorDrvrSts, { DoorDrvrSts, 19, 2, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ DoorDrvrSts_UB, { DoorDrvrSts_UB, 21, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ DoorPassReSts, { DoorPassReSts, 30, 2, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ DoorPassReSts_UB, { DoorPassReSts_UB, 22, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ DoorPassSts, { DoorPassSts, 28, 2, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ DoorPassSts_UB, { DoorPassSts_UB, 23, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ EngOilLvlSts, { EngOilLvlSts, 5, 3, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ EngOilLvlSts_UB, { EngOilLvlSts_UB, 4, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ HoodSts, { HoodSts, 26, 2, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ HoodSts_UB, { HoodSts_UB, 2, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ TrSts, { TrSts, 24, 2, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });
    signals_info.insert({ TrSts_UB, { TrSts_UB, 3, 1, true, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr17, ParentType::FRAME } });

    signalgroups_info.insert({ ALnchTiDly3, { ALnchTiDly3, 0x0, { ALnchTiDly3Qf, ALnchTiDly3Sec2 }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr17 } } );
    signalgroups_info.insert({ AlrmSts1, { AlrmSts1, 0x0, { AlrmSt, AlrmTrgSrc, SnsrInclnFailr, SnsrIntrScanrFailr, SnsrSoundrBattBackedFailr }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr17 } } );

    frames_info.insert({ VCU1Mid3CanFr17, { VCU1Mid3CanFr17, 384, 8, 300, { ALnchTiDly3, AlrmSts1 }, { DoorPassSts, AlrmSts1_UB, DoorDrvrReSts, TrSts_UB, DoorPassReSts, DoorPassSts_UB, DoorDrvrSts_UB, EngOilLvlSts, DoorDrvrReSts_UB, HoodSts, EngOilLvlSts_UB, DoorDrvrSts, DoorPassReSts_UB, ALnchTiDly3_UB, TrSts, HoodSts_UB } } });

    frame_ids.insert({ 384, VCU1Mid3CanFr17 });
}


}
}
