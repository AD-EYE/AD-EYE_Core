#include "SSMBMid6CanFdFr03.h"


namespace kcan {
namespace dbc {


void SSMBMid6CanFdFr03_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ SSMBDegradedchks, { SSMBDegradedchks, 88, 8, true, SignalType::E2E_CHKS, 0, SSMBDegraded, ParentType::GROUP } });
    signals_info.insert({ SSMBDegradedcntr, { SSMBDegradedcntr, 80, 4, true, SignalType::E2E_CNTR, 0, SSMBDegraded, ParentType::GROUP } });
    signals_info.insert({ SSMBDegradedSSMBDegraded, { SSMBDegradedSSMBDegraded, 84, 4, true, SignalType::APP_UNSIGNED, 0, SSMBDegraded, ParentType::GROUP } });
    signals_info.insert({ SecPoseMonSafeChks, { SecPoseMonSafeChks, 24, 8, true, SignalType::E2E_CHKS, 0, SecPoseMonSafe, ParentType::GROUP } });
    signals_info.insert({ SecPoseMonSafeCntr, { SecPoseMonSafeCntr, 16, 4, true, SignalType::E2E_CNTR, 0, SecPoseMonSafe, ParentType::GROUP } });
    signals_info.insert({ SecPoseMonSafeLatErr, { SecPoseMonSafeLatErr, 54, 10, true, SignalType::APP_SIGNED, 0, SecPoseMonSafe, ParentType::GROUP } });
    signals_info.insert({ SecPoseMonSafeLgtErr, { SecPoseMonSafeLgtErr, 59, 11, true, SignalType::APP_SIGNED, 0, SecPoseMonSafe, ParentType::GROUP } });
    signals_info.insert({ SecPoseMonSafeSafeQf, { SecPoseMonSafeSafeQf, 20, 2, true, SignalType::APP_UNSIGNED, 0, SecPoseMonSafe, ParentType::GROUP } });
    signals_info.insert({ SecPoseMonSafeYawErr, { SecPoseMonSafeYawErr, 48, 8, true, SignalType::APP_SIGNED, 0, SecPoseMonSafe, ParentType::GROUP } });
    signals_info.insert({ SecSteerMotTqSteerMotTq, { SecSteerMotTqSteerMotTq, 8, 14, true, SignalType::APP_SIGNED, 0, SecSteerMotTq, ParentType::GROUP } });
    signals_info.insert({ SecSteerMotTqSteerMotTqQf, { SecSteerMotTqSteerMotTqQf, 6, 2, true, SignalType::APP_UNSIGNED, 1, SecSteerMotTq, ParentType::GROUP } });
    signals_info.insert({ SecWhlLockStsChks, { SecWhlLockStsChks, 72, 8, true, SignalType::E2E_CHKS, 0, SecWhlLockSts, ParentType::GROUP } });
    signals_info.insert({ SecWhlLockStsCntr, { SecWhlLockStsCntr, 64, 4, true, SignalType::E2E_CNTR, 0, SecWhlLockSts, ParentType::GROUP } });
    signals_info.insert({ SecWhlLockStsDegradedSts, { SecWhlLockStsDegradedSts, 56, 2, true, SignalType::APP_UNSIGNED, 0, SecWhlLockSts, ParentType::GROUP } });
    signals_info.insert({ SecWhlLockStsLockSts, { SecWhlLockStsLockSts, 68, 3, true, SignalType::APP_UNSIGNED, 0, SecWhlLockSts, ParentType::GROUP } });
    signals_info.insert({ SSMBDegraded_UB, { SSMBDegraded_UB, 103, 1, true, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr03, ParentType::FRAME } });
    signals_info.insert({ SecPoseMonSafe_UB, { SecPoseMonSafe_UB, 22, 1, true, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr03, ParentType::FRAME } });
    signals_info.insert({ SecSteerMotTq_UB, { SecSteerMotTq_UB, 23, 1, true, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr03, ParentType::FRAME } });
    signals_info.insert({ SecWhlLockSts_UB, { SecWhlLockSts_UB, 58, 1, true, SignalType::APP_UNSIGNED, 0, SSMBMid6CanFdFr03, ParentType::FRAME } });

    signalgroups_info.insert({ SSMBDegraded, { SSMBDegraded, 0x0, { SSMBDegradedchks, SSMBDegradedcntr, SSMBDegradedSSMBDegraded }, { E2EProfileType::P01a, SSMBDegradedchks, SSMBDegradedcntr }, SSMBMid6CanFdFr03 } } );
    signalgroups_info.insert({ SecPoseMonSafe, { SecPoseMonSafe, 0x80C, { SecPoseMonSafeChks, SecPoseMonSafeCntr, SecPoseMonSafeLatErr, SecPoseMonSafeLgtErr, SecPoseMonSafeSafeQf, SecPoseMonSafeYawErr }, { E2EProfileType::P01a, SecPoseMonSafeChks, SecPoseMonSafeCntr }, SSMBMid6CanFdFr03 } } );
    signalgroups_info.insert({ SecSteerMotTq, { SecSteerMotTq, 0x0, { SecSteerMotTqSteerMotTq, SecSteerMotTqSteerMotTqQf }, { E2EProfileType::None, "", "" }, SSMBMid6CanFdFr03 } } );
    signalgroups_info.insert({ SecWhlLockSts, { SecWhlLockSts, 0x80F, { SecWhlLockStsChks, SecWhlLockStsCntr, SecWhlLockStsDegradedSts, SecWhlLockStsLockSts }, { E2EProfileType::P01a, SecWhlLockStsChks, SecWhlLockStsCntr }, SSMBMid6CanFdFr03 } } );

    frames_info.insert({ SSMBMid6CanFdFr03, { SSMBMid6CanFdFr03, 259, 16, 80, { SecPoseMonSafe, SecSteerMotTq, SecWhlLockSts, SSMBDegraded }, { SecSteerMotTq_UB, SSMBDegraded_UB, SecPoseMonSafe_UB, SecWhlLockSts_UB } } });

    frame_ids.insert({ 259, SSMBMid6CanFdFr03 });
}


}
}
