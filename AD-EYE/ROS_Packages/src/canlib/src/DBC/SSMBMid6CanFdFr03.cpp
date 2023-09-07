#include "SSMBMid6CanFdFr03.h"


namespace kcan {
namespace dbc {


// Problem with 2 signals here! Mismatch with canoe

void SSMBMid6CanFdFr03_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ SecPoseMonSafe_UB, { SecPoseMonSafe_UB, 22, 1, SignalType::APP_UNSIGNED, SSMBMid6CanFdFr03 } });
    signals_info.insert({ SecPoseMonSafeChks, { SecPoseMonSafeChks, 24, 8, SignalType::E2E_CHKS, SecPoseMonSafe } });
    signals_info.insert({ SecPoseMonSafeCntr, { SecPoseMonSafeCntr, 16, 4, SignalType::E2E_CNTR, SecPoseMonSafe } });
    signals_info.insert({ SecPoseMonSafeLatErr, { SecPoseMonSafeLatErr, 38, 10, SignalType::APP_SIGNED, SecPoseMonSafe } });
    signals_info.insert({ SecPoseMonSafeLgtErr, { SecPoseMonSafeLgtErr, 43, 11, SignalType::APP_SIGNED, SecPoseMonSafe } });
    signals_info.insert({ SecPoseMonSafeSafeQf, { SecPoseMonSafeSafeQf, 20, 2, SignalType::APP_UNSIGNED, SecPoseMonSafe } });
    signals_info.insert({ SecPoseMonSafeYawErr, { SecPoseMonSafeYawErr, 32, 8, SignalType::APP_SIGNED, SecPoseMonSafe } });
    signals_info.insert({ SecSteerMotTq_UB, { SecSteerMotTq_UB, 23, 1, SignalType::APP_UNSIGNED, SSMBMid6CanFdFr03 } });
    signals_info.insert({ SecSteerMotTqSteerMotTq, { SecSteerMotTqSteerMotTq, 8, 14, SignalType::APP_SIGNED, SecSteerMotTqSteerMotTq } });
    signals_info.insert({ SecSteerMotTqSteerMotTqQf, { SecSteerMotTqSteerMotTqQf, 6, 2, SignalType::APP_UNSIGNED, SecSteerMotTqSteerMotTq } });
    signals_info.insert({ SecWhlLockSts_UB, { SecWhlLockSts_UB, 58, 1, SignalType::APP_UNSIGNED, SSMBMid6CanFdFr03 } });
    signals_info.insert({ SecWhlLockStsChks, { SecWhlLockStsChks, 72, 8, SignalType::E2E_CHKS, SecWhlLockSts } });
    signals_info.insert({ SecWhlLockStsCntr, { SecWhlLockStsCntr, 64, 4, SignalType::E2E_CNTR, SecWhlLockSts } });
    signals_info.insert({ SecWhlLockStsDegradedSts, { SecWhlLockStsDegradedSts, 56, 2, SignalType::APP_UNSIGNED, SecWhlLockSts } });
    signals_info.insert({ SecWhlLockStsLockSts, { SecWhlLockStsLockSts, 68, 3, SignalType::APP_UNSIGNED, SecWhlLockSts } });
    signals_info.insert({ SSMBDegraded_UB, { SSMBDegraded_UB, 103, 1, SignalType::APP_UNSIGNED, SSMBMid6CanFdFr03 } });
    signals_info.insert({ SSMBDegradedchks, { SSMBDegradedchks, 88, 8, SignalType::E2E_CHKS, SSMBDegraded } });
    signals_info.insert({ SSMBDegradedcntr, { SSMBDegradedcntr, 80, 4, SignalType::E2E_CNTR, SSMBDegraded } });
    signals_info.insert({ SSMBDegradedSSMBDegraded, { SSMBDegradedSSMBDegraded, 84, 4, SignalType::APP_UNSIGNED, SSMBDegraded } });
    
    signalgroups_info.insert(
    {
        SecPoseMonSafe,
        {
            SecPoseMonSafe,
            0x80C,
            {
                SecPoseMonSafeChks,
                SecPoseMonSafeCntr,
                SecPoseMonSafeLatErr,
                SecPoseMonSafeLgtErr,
                SecPoseMonSafeSafeQf,
                SecPoseMonSafeYawErr
            }, 
            E2EProfileType::None,
            SSMBMid6CanFdFr03
        }
    });

    signalgroups_info.insert(
    {
        SecSteerMotTq,
        {
            SecSteerMotTq,
            0x0,
            {
                SecSteerMotTqSteerMotTq,
                SecSteerMotTqSteerMotTqQf
            }, 
            E2EProfileType::P01a,
            SSMBMid6CanFdFr03
        }
    });

    signalgroups_info.insert(
    {
        SecWhlLockSts,
        {
            SecWhlLockSts,
            0x80F,
            {
                SecWhlLockStsChks,
                SecWhlLockStsCntr,
                SecWhlLockStsDegradedSts,
                SecWhlLockStsLockSts
            }, 
            { E2EProfileType::P01a,SecWhlLockStsChks,SecWhlLockStsCntr },
            SSMBMid6CanFdFr03
        }
    });

    signalgroups_info.insert(
    {
        SSMBDegraded,
        {
            SSMBDegraded,
            0xEF,
            {
                SSMBDegradedchks,
                SSMBDegradedcntr,
                SSMBDegradedSSMBDegraded
            }, 
            { E2EProfileType::P01a, SSMBDegradedchks, SSMBDegradedcntr },
            SSMBMid6CanFdFr03
        }
    });

    frames_info.insert({ SSMBMid6CanFdFr03, { SSMBMid6CanFdFr03, 259, 16, 80, { SecPoseMonSafe, SecSteerMotTq, SecWhlLockSts, SSMBDegraded }, { SecPoseMonSafe_UB, SecSteerMotTq_UB, SecWhlLockSts_UB, SSMBDegraded_UB } } });

    frame_ids.insert({ 259, SSMBMid6CanFdFr03 });
}


}
}