#include "SSMBMid6CanFdFr08.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr08_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ SecVehMSafeChks, { SecVehMSafeChks, 128, 8, true, SignalType::E2E_CHKS, 0, SecVehMSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehMSafeCntr, { SecVehMSafeCntr, 96, 4, true, SignalType::E2E_CNTR, 0, SecVehMSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehMSafeNomQf, { SecVehMSafeNomQf, 100, 2, true, SignalType::APP_UNSIGNED, 1, SecVehMSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehMSafeSafeQf, { SecVehMSafeSafeQf, 142, 2, true, SignalType::APP_UNSIGNED, 0, SecVehMSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehMSafeVehMMax, { SecVehMSafeVehMMax, 104, 8, true, SignalType::APP_UNSIGNED, 0, SecVehMSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehMSafeVehMMin, { SecVehMSafeVehMMin, 112, 8, true, SignalType::APP_UNSIGNED, 0, SecVehMSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehMSafeVehMNom, { SecVehMSafeVehMNom, 120, 8, true, SignalType::APP_UNSIGNED, 0, SecVehMSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlAgSpdFrntSafeChks, { SecWhlAgSpdFrntSafeChks, 8, 8, true, SignalType::E2E_CHKS, 0, SecWhlAgSpdFrntSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlAgSpdFrntSafeCntr, { SecWhlAgSpdFrntSafeCntr, 0, 4, true, SignalType::E2E_CNTR, 0, SecWhlAgSpdFrntSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlAgSpdFrntSafeLe, { SecWhlAgSpdFrntSafeLe, 24, 16, true, SignalType::APP_SIGNED, 0, SecWhlAgSpdFrntSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlAgSpdFrntSafeLeQf, { SecWhlAgSpdFrntSafeLeQf, 4, 2, true, SignalType::APP_UNSIGNED, 1, SecWhlAgSpdFrntSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlAgSpdFrntSafeRi, { SecWhlAgSpdFrntSafeRi, 40, 16, true, SignalType::APP_SIGNED, 0, SecWhlAgSpdFrntSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlAgSpdFrntSafeRiQf, { SecWhlAgSpdFrntSafeRiQf, 6, 2, true, SignalType::APP_UNSIGNED, 1, SecWhlAgSpdFrntSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlAgSpdReSafeChks, { SecWhlAgSpdReSafeChks, 56, 8, true, SignalType::E2E_CHKS, 0, SecWhlAgSpdReSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlAgSpdReSafeCntr, { SecWhlAgSpdReSafeCntr, 48, 4, true, SignalType::E2E_CNTR, 0, SecWhlAgSpdReSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlAgSpdReSafeLe, { SecWhlAgSpdReSafeLe, 72, 16, true, SignalType::APP_SIGNED, 0, SecWhlAgSpdReSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlAgSpdReSafeLeQf, { SecWhlAgSpdReSafeLeQf, 52, 2, true, SignalType::APP_UNSIGNED, 1, SecWhlAgSpdReSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlAgSpdReSafeRi, { SecWhlAgSpdReSafeRi, 88, 16, true, SignalType::APP_SIGNED, 0, SecWhlAgSpdReSafe, ParentType::GROUP } });
    signals_info.insert({ SecWhlAgSpdReSafeRiQf, { SecWhlAgSpdReSafeRiQf, 54, 2, true, SignalType::APP_UNSIGNED, 1, SecWhlAgSpdReSafe, ParentType::GROUP } });
    signals_info.insert({ SecVehMSafe_UB, { SecVehMSafe_UB, 141, 1, true, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr08, ParentType::FRAME } });
    signals_info.insert({ SecWhlAgSpdFrntSafe_UB, { SecWhlAgSpdFrntSafe_UB, 103, 1, true, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr08, ParentType::FRAME } });
    signals_info.insert({ SecWhlAgSpdReSafe_UB, { SecWhlAgSpdReSafe_UB, 102, 1, true, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr08, ParentType::FRAME } });

    signalgroups_info.insert({ SecVehMSafe, { SecVehMSafe, 0x726, { SecVehMSafeChks, SecVehMSafeCntr, SecVehMSafeNomQf, SecVehMSafeSafeQf, SecVehMSafeVehMMax, SecVehMSafeVehMMin, SecVehMSafeVehMNom }, { E2EProfileType::P01a, SecVehMSafeChks, SecVehMSafeCntr }, SSMBMid6CanFdFr08 } } );
    signalgroups_info.insert({ SecWhlAgSpdFrntSafe, { SecWhlAgSpdFrntSafe, 0x1E6, { SecWhlAgSpdFrntSafeChks, SecWhlAgSpdFrntSafeCntr, SecWhlAgSpdFrntSafeLe, SecWhlAgSpdFrntSafeLeQf, SecWhlAgSpdFrntSafeRi, SecWhlAgSpdFrntSafeRiQf }, { E2EProfileType::P01a, SecWhlAgSpdFrntSafeChks, SecWhlAgSpdFrntSafeCntr }, SSMBMid6CanFdFr08 } } );
    signalgroups_info.insert({ SecWhlAgSpdReSafe, { SecWhlAgSpdReSafe, 0x1E5, { SecWhlAgSpdReSafeChks, SecWhlAgSpdReSafeCntr, SecWhlAgSpdReSafeLe, SecWhlAgSpdReSafeLeQf, SecWhlAgSpdReSafeRi, SecWhlAgSpdReSafeRiQf }, { E2EProfileType::P01a, SecWhlAgSpdReSafeChks, SecWhlAgSpdReSafeCntr }, SSMBMid6CanFdFr08 } } );

    frames_info.insert({ SSMBMid6CanFdFr08, { SSMBMid6CanFdFr08, 52, 20, 10, { SecVehMSafe, SecWhlAgSpdFrntSafe, SecWhlAgSpdReSafe }, { SecWhlAgSpdReSafe_UB, SecVehMSafe_UB, SecWhlAgSpdFrntSafe_UB } } });

    frame_ids.insert({ 52, SSMBMid6CanFdFr08 });
}


}
}
