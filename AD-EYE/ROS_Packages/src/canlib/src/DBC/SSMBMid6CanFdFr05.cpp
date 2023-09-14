#include "SSMBMid6CanFdFr05.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr05_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecWhlAgEstimdGroupSafeChks, { AdSecWhlAgEstimdGroupSafeChks, 8, 8, SignalType::E2E_CHKS, 0, AdSecWhlAgEstimdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecWhlAgEstimdGroupSafeCntr, { AdSecWhlAgEstimdGroupSafeCntr, 0, 4, SignalType::E2E_CNTR, 0, AdSecWhlAgEstimdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecWhlAgEstimdGroupSafeQf1, { AdSecWhlAgEstimdGroupSafeQf1, 54, 2, SignalType::APP_UNSIGNED, 0, AdSecWhlAgEstimdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecWhlAgEstimdGroupSafeWhlAg, { AdSecWhlAgEstimdGroupSafeWhlAg, 8, 15, SignalType::APP_UNSIGNED, 16193, AdSecWhlAgEstimdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ AdSecWhlAgEstimdGroupSafeWhlAgRate, { AdSecWhlAgEstimdGroupSafeWhlAgRate, 24, 15, SignalType::APP_UNSIGNED, 14000, AdSecWhlAgEstimdGroupSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotToothCntrChks, { SecWhlRotToothCntrChks, 56, 8, SignalType::E2E_CHKS, 0, SecWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotToothCntrCntr, { SecWhlRotToothCntrCntr, 48, 4, SignalType::E2E_CNTR, 0, SecWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotToothCntrWhlRotToothCntrFrntLe, { SecWhlRotToothCntrWhlRotToothCntrFrntLe, 64, 8, SignalType::APP_UNSIGNED, 0, SecWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotToothCntrWhlRotToothCntrFrntLeQf, { SecWhlRotToothCntrWhlRotToothCntrFrntLeQf, 78, 2, SignalType::APP_UNSIGNED, 1, SecWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotToothCntrWhlRotToothCntrFrntRi, { SecWhlRotToothCntrWhlRotToothCntrFrntRi, 80, 8, SignalType::APP_UNSIGNED, 0, SecWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotToothCntrWhlRotToothCntrFrntRiQf, { SecWhlRotToothCntrWhlRotToothCntrFrntRiQf, 76, 2, SignalType::APP_UNSIGNED, 1, SecWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotToothCntrWhlRotToothCntrReLe, { SecWhlRotToothCntrWhlRotToothCntrReLe, 88, 8, SignalType::APP_UNSIGNED, 0, SecWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotToothCntrWhlRotToothCntrReLeQf, { SecWhlRotToothCntrWhlRotToothCntrReLeQf, 74, 2, SignalType::APP_UNSIGNED, 1, SecWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotToothCntrWhlRotToothCntrReRi, { SecWhlRotToothCntrWhlRotToothCntrReRi, 96, 8, SignalType::APP_UNSIGNED, 0, SecWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotToothCntrWhlRotToothCntrReRiQf, { SecWhlRotToothCntrWhlRotToothCntrReRiQf, 72, 2, SignalType::APP_UNSIGNED, 1, SecWhlRotToothCntr, ParentType::GROUP } });
    signals_info.insert({ SecWhlRotToothCntr_UB, { SecWhlRotToothCntr_UB, 52, 1, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr05, ParentType::FRAME } });
    signals_info.insert({ AdSecWhlAgEstimdGroupSafe_UB, { AdSecWhlAgEstimdGroupSafe_UB, 4, 1, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr05, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecWhlAgEstimdGroupSafe, { AdSecWhlAgEstimdGroupSafe, 0x1B0, { AdSecWhlAgEstimdGroupSafeChks, AdSecWhlAgEstimdGroupSafeCntr, AdSecWhlAgEstimdGroupSafeQf1, AdSecWhlAgEstimdGroupSafeWhlAg, AdSecWhlAgEstimdGroupSafeWhlAgRate }, { E2EProfileType::P01a, AdSecWhlAgEstimdGroupSafeChks, AdSecWhlAgEstimdGroupSafeCntr }, SSMBMid6CanFdFr05 } } );
    signalgroups_info.insert({ SecWhlRotToothCntr, { SecWhlRotToothCntr, 0x579, { SecWhlRotToothCntrChks, SecWhlRotToothCntrCntr, SecWhlRotToothCntrWhlRotToothCntrFrntLe, SecWhlRotToothCntrWhlRotToothCntrFrntLeQf, SecWhlRotToothCntrWhlRotToothCntrFrntRi, SecWhlRotToothCntrWhlRotToothCntrFrntRiQf, SecWhlRotToothCntrWhlRotToothCntrReLe, SecWhlRotToothCntrWhlRotToothCntrReLeQf, SecWhlRotToothCntrWhlRotToothCntrReRi, SecWhlRotToothCntrWhlRotToothCntrReRiQf }, { E2EProfileType::P01a, SecWhlRotToothCntrChks, SecWhlRotToothCntrCntr }, SSMBMid6CanFdFr05 } } );

    frames_info.insert({ SSMBMid6CanFdFr05, { SSMBMid6CanFdFr05, 32, 16, 10, { AdSecWhlAgEstimdGroupSafe, SecWhlRotToothCntr }, { SecWhlRotToothCntr_UB, AdSecWhlAgEstimdGroupSafe_UB } } });

    frame_ids.insert({ 32, SSMBMid6CanFdFr05 });
}


}
}
