#include "VCU1Mid3CanFr03.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr03_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecSteerActvnGroupSafeAdSteerActvnReq, { AdSecSteerActvnGroupSafeAdSteerActvnReq, 5, 1, SignalType::APP_UNSIGNED, 0, AdSecSteerActvnGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerActvnGroupSafeAdSteerDeActvnReq, { AdSecSteerActvnGroupSafeAdSteerDeActvnReq, 4, 1, SignalType::APP_UNSIGNED, 0, AdSecSteerActvnGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerActvnGroupSafeChks, { AdSecSteerActvnGroupSafeChks, 8, 8, SignalType::E2E_CHKS, 0, AdSecSteerActvnGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerActvnGroupSafeCntr, { AdSecSteerActvnGroupSafeCntr, 0, 4, SignalType::E2E_CNTR, 0, AdSecSteerActvnGroupSafe, ParentType::GROUP } });
    signals_info.insert({ PrpsnTqDirAct, { PrpsnTqDirAct, 52, 2, SignalType::APP_UNSIGNED, 0, PrpsnTqDir, ParentType::GROUP } });
    signals_info.insert({ PrpsnTqDirChks, { PrpsnTqDirChks, 56, 8, SignalType::E2E_CHKS, 0, PrpsnTqDir, ParentType::GROUP } });
    signals_info.insert({ PrpsnTqDirCntr, { PrpsnTqDirCntr, 48, 4, SignalType::E2E_CNTR, 0, PrpsnTqDir, ParentType::GROUP } });
    signals_info.insert({ SteerWhlTq, { SteerWhlTq, 24, 14, SignalType::APP_SIGNED, 0, SteerWhlTqGroup, ParentType::GROUP } });
    signals_info.insert({ SteerWhlTqQf, { SteerWhlTqQf, 22, 2, SignalType::APP_UNSIGNED, 1, SteerWhlTqGroup, ParentType::GROUP } });
    signals_info.insert({ AdSecSteerActvnGroupSafe_UB, { AdSecSteerActvnGroupSafe_UB, 6, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr03, ParentType::FRAME } });
    signals_info.insert({ PrpsnTqDir_UB, { PrpsnTqDir_UB, 54, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr03, ParentType::FRAME } });
    signals_info.insert({ SteerWhlTqGroup_UB, { SteerWhlTqGroup_UB, 7, 1, SignalType::APP_UNSIGNED, 0, VCU1Mid3CanFr03, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecSteerActvnGroupSafe, { AdSecSteerActvnGroupSafe, 0x1A7, { AdSecSteerActvnGroupSafeAdSteerActvnReq, AdSecSteerActvnGroupSafeAdSteerDeActvnReq, AdSecSteerActvnGroupSafeChks, AdSecSteerActvnGroupSafeCntr }, { E2EProfileType::P01a, AdSecSteerActvnGroupSafeChks, AdSecSteerActvnGroupSafeCntr }, VCU1Mid3CanFr03 } } );
    signalgroups_info.insert({ PrpsnTqDir, { PrpsnTqDir, 0xA4, { PrpsnTqDirAct, PrpsnTqDirChks, PrpsnTqDirCntr }, { E2EProfileType::P01a, PrpsnTqDirChks, PrpsnTqDirCntr }, VCU1Mid3CanFr03 } } );
    signalgroups_info.insert({ SteerWhlTqGroup, { SteerWhlTqGroup, 0x0, { SteerWhlTq, SteerWhlTqQf }, { E2EProfileType::None, "", "" }, VCU1Mid3CanFr03 } } );

    frames_info.insert({ VCU1Mid3CanFr03, { VCU1Mid3CanFr03, 85, 8, 20, { AdSecSteerActvnGroupSafe, PrpsnTqDir, SteerWhlTqGroup }, { AdSecSteerActvnGroupSafe_UB, PrpsnTqDir_UB, SteerWhlTqGroup_UB } } });

    frame_ids.insert({ 85, VCU1Mid3CanFr03 });
}


}
}
