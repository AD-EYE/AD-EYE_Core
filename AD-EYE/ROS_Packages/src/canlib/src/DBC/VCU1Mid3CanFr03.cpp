#include "VCU1Mid3CanFr03.h"


namespace kcan {
namespace dbc {


void VCU1Mid3CanFr03_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecSteerActvnGroupSafe_UB, { AdSecSteerActvnGroupSafe_UB, 6, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr03 } });
    signals_info.insert({ AdSecSteerActvnGroupSafeAdSteerActvnReq, { AdSecSteerActvnGroupSafeAdSteerActvnReq, 5, 1, SignalType::APP_UNSIGNED, AdSecSteerActvnGroupSafe } });
    signals_info.insert({ AdSecSteerActvnGroupSafeAdSteerDeActvnReq, { AdSecSteerActvnGroupSafeAdSteerDeActvnReq, 4, 1, SignalType::APP_UNSIGNED, AdSecSteerActvnGroupSafe } });
    signals_info.insert({ AdSecSteerActvnGroupSafeChks, { AdSecSteerActvnGroupSafeChks, 8, 8, SignalType::E2E_CHKS, AdSecSteerActvnGroupSafe } });
    signals_info.insert({ AdSecSteerActvnGroupSafeCntr, { AdSecSteerActvnGroupSafeCntr, 0, 4, SignalType::E2E_CNTR, AdSecSteerActvnGroupSafe } });
    signals_info.insert({ PrpsnTqDir_UB, { PrpsnTqDir_UB, 54, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr03 } });
    signals_info.insert({ PrpsnTqDirAct, { PrpsnTqDirAct, 52, 2, SignalType::APP_UNSIGNED, PrpsnTqDir } });
    signals_info.insert({ PrpsnTqDirChks, { PrpsnTqDirChks, 56, 8, SignalType::E2E_CHKS, PrpsnTqDir } });
    signals_info.insert({ PrpsnTqDirCntr, { PrpsnTqDirCntr, 48, 4, SignalType::E2E_CNTR, PrpsnTqDir } });
    signals_info.insert({ SteerWhlTq, { SteerWhlTq, 8, 14, SignalType::APP_SIGNED, SteerWhlTqGroup } });
    signals_info.insert({ SteerWhlTqGroup_UB, { SteerWhlTqGroup_UB, 7, 1, SignalType::APP_UNSIGNED, VCU1Mid3CanFr03 } });
    signals_info.insert({ SteerWhlTqQf, { SteerWhlTqQf, 22, 2, SignalType::APP_UNSIGNED, SteerWhlTqGroup } });
    
    signalgroups_info.insert(
    {
        AdSecSteerActvnGroupSafe,
        {
            AdSecSteerActvnGroupSafe,
            0x1A7,
            {
                AdSecSteerActvnGroupSafeAdSteerActvnReq,
                AdSecSteerActvnGroupSafeAdSteerDeActvnReq,
                AdSecSteerActvnGroupSafeChks,
                AdSecSteerActvnGroupSafeCntr
            }, 
            { E2EProfileType::P01a, AdSecSteerActvnGroupSafeChks, AdSecSteerActvnGroupSafeCntr},
            VCU1Mid3CanFr03
        }
    });

    signalgroups_info.insert(
    {
        PrpsnTqDir,
        {
            PrpsnTqDir,
            0xA4,
            {
                PrpsnTqDirAct, 
                PrpsnTqDirChks,
                PrpsnTqDirCntr
            }, 
            { E2EProfileType::P01a, PrpsnTqDirChks, PrpsnTqDirCntr},
            VCU1Mid3CanFr03
        }
    });

    signalgroups_info.insert(
    {
        SteerWhlTqGroup,
        {
            SteerWhlTqGroup,
            0x0,
            {
                SteerWhlTq,
                SteerWhlTqQf
            }, 
            { E2EProfileType::P01a, "", "" },
            VCU1Mid3CanFr03
        }
    });

    frames_info.insert({ VCU1Mid3CanFr03, { VCU1Mid3CanFr03, 85, 8, 20, { AdSecSteerActvnGroupSafe, PrpsnTqDir, SteerWhlTqGroup }, { AdSecSteerActvnGroupSafe_UB, PrpsnTqDir_UB, SteerWhlTqGroup_UB } } });

    frame_ids.insert({ 85, VCU1Mid3CanFr03 });
}


}
}