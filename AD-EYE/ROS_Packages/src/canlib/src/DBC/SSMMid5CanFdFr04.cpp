#include "SSMMid5CanFdFr04.h"


namespace kcan {
namespace dbc {


void SSMMid5CanFdFr04_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ PrimVehMSafeChks, { PrimVehMSafeChks, 104, 8, SignalType::E2E_CHKS, 0, PrimVehMSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehMSafeCntr, { PrimVehMSafeCntr, 96, 4, SignalType::E2E_CNTR, 0, PrimVehMSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehMSafeNomQf, { PrimVehMSafeNomQf, 100, 2, SignalType::APP_UNSIGNED, 1, PrimVehMSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehMSafeSafeQf, { PrimVehMSafeSafeQf, 142, 2, SignalType::APP_UNSIGNED, 0, PrimVehMSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehMSafeVehMMax, { PrimVehMSafeVehMMax, 112, 8, SignalType::APP_UNSIGNED, 0, PrimVehMSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehMSafeVehMMin, { PrimVehMSafeVehMMin, 120, 8, SignalType::APP_UNSIGNED, 0, PrimVehMSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehMSafeVehMNom, { PrimVehMSafeVehMNom, 128, 8, SignalType::APP_UNSIGNED, 0, PrimVehMSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlAgSpdFrntSafeChks, { PrimWhlAgSpdFrntSafeChks, 8, 8, SignalType::E2E_CHKS, 0, PrimWhlAgSpdFrntSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlAgSpdFrntSafeCntr, { PrimWhlAgSpdFrntSafeCntr, 0, 4, SignalType::E2E_CNTR, 0, PrimWhlAgSpdFrntSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlAgSpdFrntSafeLe, { PrimWhlAgSpdFrntSafeLe, 24, 16, SignalType::APP_SIGNED, 0, PrimWhlAgSpdFrntSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlAgSpdFrntSafeLeQf, { PrimWhlAgSpdFrntSafeLeQf, 4, 2, SignalType::APP_UNSIGNED, 1, PrimWhlAgSpdFrntSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlAgSpdFrntSafeRi, { PrimWhlAgSpdFrntSafeRi, 40, 16, SignalType::APP_SIGNED, 0, PrimWhlAgSpdFrntSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlAgSpdFrntSafeRiQf, { PrimWhlAgSpdFrntSafeRiQf, 6, 2, SignalType::APP_UNSIGNED, 1, PrimWhlAgSpdFrntSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlAgSpdReSafeChks, { PrimWhlAgSpdReSafeChks, 56, 8, SignalType::E2E_CHKS, 0, PrimWhlAgSpdReSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlAgSpdReSafeCntr, { PrimWhlAgSpdReSafeCntr, 48, 4, SignalType::E2E_CNTR, 0, PrimWhlAgSpdReSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlAgSpdReSafeLe, { PrimWhlAgSpdReSafeLe, 72, 16, SignalType::APP_SIGNED, 0, PrimWhlAgSpdReSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlAgSpdReSafeLeQf, { PrimWhlAgSpdReSafeLeQf, 52, 2, SignalType::APP_UNSIGNED, 1, PrimWhlAgSpdReSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlAgSpdReSafeRi, { PrimWhlAgSpdReSafeRi, 88, 16, SignalType::APP_SIGNED, 0, PrimWhlAgSpdReSafe, ParentType::GROUP } });
    signals_info.insert({ PrimWhlAgSpdReSafeRiQf, { PrimWhlAgSpdReSafeRiQf, 54, 2, SignalType::APP_UNSIGNED, 1, PrimWhlAgSpdReSafe, ParentType::GROUP } });
    signals_info.insert({ PrimVehMSafe_UB, { PrimVehMSafe_UB, 141, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr04, ParentType::FRAME } });
    signals_info.insert({ PrimWhlAgSpdFrntSafe_UB, { PrimWhlAgSpdFrntSafe_UB, 103, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr04, ParentType::FRAME } });
    signals_info.insert({ PrimWhlAgSpdReSafe_UB, { PrimWhlAgSpdReSafe_UB, 102, 1, SignalType::APP_UNSIGNED, 0, SSMMid5CanFdFr04, ParentType::FRAME } });

    signalgroups_info.insert({ PrimVehMSafe, { PrimVehMSafe, 0x725, { PrimVehMSafeChks, PrimVehMSafeCntr, PrimVehMSafeNomQf, PrimVehMSafeSafeQf, PrimVehMSafeVehMMax, PrimVehMSafeVehMMin, PrimVehMSafeVehMNom }, { E2EProfileType::P01a, PrimVehMSafeChks, PrimVehMSafeCntr }, SSMMid5CanFdFr04 } } );
    signalgroups_info.insert({ PrimWhlAgSpdFrntSafe, { PrimWhlAgSpdFrntSafe, 0x1E3, { PrimWhlAgSpdFrntSafeChks, PrimWhlAgSpdFrntSafeCntr, PrimWhlAgSpdFrntSafeLe, PrimWhlAgSpdFrntSafeLeQf, PrimWhlAgSpdFrntSafeRi, PrimWhlAgSpdFrntSafeRiQf }, { E2EProfileType::P01a, PrimWhlAgSpdFrntSafeChks, PrimWhlAgSpdFrntSafeCntr }, SSMMid5CanFdFr04 } } );
    signalgroups_info.insert({ PrimWhlAgSpdReSafe, { PrimWhlAgSpdReSafe, 0x1E4, { PrimWhlAgSpdReSafeChks, PrimWhlAgSpdReSafeCntr, PrimWhlAgSpdReSafeLe, PrimWhlAgSpdReSafeLeQf, PrimWhlAgSpdReSafeRi, PrimWhlAgSpdReSafeRiQf }, { E2EProfileType::P01a, PrimWhlAgSpdReSafeChks, PrimWhlAgSpdReSafeCntr }, SSMMid5CanFdFr04 } } );

    frames_info.insert({ SSMMid5CanFdFr04, { SSMMid5CanFdFr04, 21, 20, 10, { PrimVehMSafe, PrimWhlAgSpdFrntSafe, PrimWhlAgSpdReSafe }, { PrimVehMSafe_UB, PrimWhlAgSpdFrntSafe_UB, PrimWhlAgSpdReSafe_UB } } });

    frame_ids.insert({ 21, SSMMid5CanFdFr04 });
}


}
}
