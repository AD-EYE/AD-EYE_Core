#include "VIMMid5CanFdFr02.h"


namespace kcan {
namespace dbc {


void VIMMid5CanFdFr02_Init(
    map<uint, string>& frame_ids,
    map<string, FrameInfo>& frames_info,
    map<string, SignalGroupInfo>& signalgroups_info,
    map<string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdPrimPose_UB, { AdPrimPose_UB, 511, 1, SignalType::APP_UNSIGNED, VIMMid5CanFdFr02 } });
    signals_info.insert({ AdPrimPoseAX, { AdPrimPoseAX, 24, 20, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseAXConf, { AdPrimPoseAXConf, 400, 3, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseAY, { AdPrimPoseAY, 48, 20, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseAYConf, { AdPrimPoseAYConf, 408, 3, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseAZ, { AdPrimPoseAZ, 72, 20, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseAZConf, { AdPrimPoseAZConf, 416, 3, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseChks, { AdPrimPoseChks, 0, 16, SignalType::E2E_CHKS, AdPrimPose } });
    signals_info.insert({ AdPrimPoseCntr, { AdPrimPoseCntr, 16, 8, SignalType::E2E_CNTR, AdPrimPose } });
    signals_info.insert({ AdPrimPoseDataID, { AdPrimPoseDataID, 96, 16, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPosePitch, { AdPrimPosePitch, 112, 16, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPosePitchConf, { AdPrimPosePitchConf, 424, 3, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPosePitchRate, { AdPrimPosePitchRate, 128, 20, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPosePitchRateConf, { AdPrimPosePitchRateConf, 432, 3, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPosePosX, { AdPrimPosePosX, 152, 32, SignalType::APP_SIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPosePosXConf, { AdPrimPosePosXConf, 440, 3, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPosePosY, { AdPrimPosePosY, 184, 32, SignalType::APP_SIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPosePosYConf, { AdPrimPosePosYConf, 448, 3, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseRoll, { AdPrimPoseRoll, 216, 16, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseRollConf, { AdPrimPoseRollConf, 456, 3, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseRollRate, { AdPrimPoseRollRate, 232, 20, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseRollRateConf, { AdPrimPoseRollRateConf, 464, 3, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseTiStampNanoSec, { AdPrimPoseTiStampNanoSec, 256, 32, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseTiStampSec, { AdPrimPoseTiStampSec, 288, 32, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseVX, { AdPrimPoseVX, 320, 16, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseVXConf, { AdPrimPoseVXConf, 472, 3, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseVY, { AdPrimPoseVY, 336, 14, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseVYConf, { AdPrimPoseVYConf, 480, 3, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseYaw, { AdPrimPoseYaw, 352, 24, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseYawConf, { AdPrimPoseYawConf, 488, 3, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseYawRate, { AdPrimPoseYawRate, 376, 22, SignalType::APP_UNSIGNED, AdPrimPose } });
    signals_info.insert({ AdPrimPoseYawRateConf, { AdPrimPoseYawRateConf, 496, 3, SignalType::APP_UNSIGNED, AdPrimPose } });

    signalgroups_info.insert(
    {
        AdPrimPose,
        {
            AdPrimPose,
            0x437,
            {
                AdPrimPoseAX,
                AdPrimPoseAXConf,
                AdPrimPoseAY,
                AdPrimPoseAYConf,
                AdPrimPoseAZ,
                AdPrimPoseAZConf,
                AdPrimPoseChks,
                AdPrimPoseCntr,
                AdPrimPoseDataID,
                AdPrimPosePitch,
                AdPrimPosePitchConf,
                AdPrimPosePitchRate,
                AdPrimPosePitchRateConf,
                AdPrimPosePosX,
                AdPrimPosePosXConf,
                AdPrimPosePosY,
                AdPrimPosePosYConf,
                AdPrimPoseRoll,
                AdPrimPoseRollConf,
                AdPrimPoseRollRate,
                AdPrimPoseRollRateConf,
                AdPrimPoseTiStampNanoSec,
                AdPrimPoseTiStampSec,
                AdPrimPoseVX,
                AdPrimPoseVXConf,
                AdPrimPoseVY,
                AdPrimPoseVYConf,
                AdPrimPoseYaw,
                AdPrimPoseYawConf,
                AdPrimPoseYawRate,
                AdPrimPoseYawRateConf
            }, 
            E2EProfileType::P05,
            VIMMid5CanFdFr02
        }
    });

    frames_info.insert({ VIMMid5CanFdFr02, { VIMMid5CanFdFr02, 33, 64, 300, { AdPrimPose }, { AdPrimPose_UB } } });

    frame_ids.insert({ 33, VIMMid5CanFdFr02 });
}


}
}
