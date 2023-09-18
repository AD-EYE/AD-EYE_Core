#include "VIMBMid6CanFdFr03.h"


namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr03_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
) {
    signals_info.insert({ AdSecPoseAX, { AdSecPoseAX, 24, 20, false, SignalType::APP_UNSIGNED, 524290, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseAXConf, { AdSecPoseAXConf, 400, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseAY, { AdSecPoseAY, 48, 20, false, SignalType::APP_UNSIGNED, 524290, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseAYConf, { AdSecPoseAYConf, 408, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseAZ, { AdSecPoseAZ, 72, 20, false, SignalType::APP_UNSIGNED, 524290, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseAZConf, { AdSecPoseAZConf, 416, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseChks, { AdSecPoseChks, 0, 16, false, SignalType::E2E_CHKS, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseCntr, { AdSecPoseCntr, 16, 8, false, SignalType::E2E_CNTR, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseDataID, { AdSecPoseDataID, 96, 16, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPosePitch, { AdSecPosePitch, 112, 16, false, SignalType::APP_UNSIGNED, 32760, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPosePitchConf, { AdSecPosePitchConf, 424, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPosePitchRate, { AdSecPosePitchRate, 128, 20, false, SignalType::APP_UNSIGNED, 524300, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPosePitchRateConf, { AdSecPosePitchRateConf, 432, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPosePosX, { AdSecPosePosX, 152, 32, false, SignalType::APP_SIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPosePosXConf, { AdSecPosePosXConf, 440, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPosePosY, { AdSecPosePosY, 184, 32, false, SignalType::APP_SIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPosePosYConf, { AdSecPosePosYConf, 448, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseRoll, { AdSecPoseRoll, 216, 16, false, SignalType::APP_UNSIGNED, 32760, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseRollConf, { AdSecPoseRollConf, 456, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseRollRate, { AdSecPoseRollRate, 232, 20, false, SignalType::APP_UNSIGNED, 524300, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseRollRateConf, { AdSecPoseRollRateConf, 464, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseTiStampNanoSec, { AdSecPoseTiStampNanoSec, 256, 32, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseTiStampSec, { AdSecPoseTiStampSec, 288, 32, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseVX, { AdSecPoseVX, 320, 16, false, SignalType::APP_UNSIGNED, 12768, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseVXConf, { AdSecPoseVXConf, 472, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseVY, { AdSecPoseVY, 336, 14, false, SignalType::APP_UNSIGNED, 8192, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseVYConf, { AdSecPoseVYConf, 480, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseYaw, { AdSecPoseYaw, 352, 24, false, SignalType::APP_UNSIGNED, 8388000, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseYawConf, { AdSecPoseYawConf, 488, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseYawRate, { AdSecPoseYawRate, 376, 22, false, SignalType::APP_UNSIGNED, 2097000, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPoseYawRateConf, { AdSecPoseYawRateConf, 496, 3, false, SignalType::APP_UNSIGNED, 0, AdSecPose, ParentType::GROUP } });
    signals_info.insert({ AdSecPose_UB, { AdSecPose_UB, 511, 1, true, SignalType::APP_UNSIGNED, 0, VIMBMid6CanFdFr03, ParentType::FRAME } });

    signalgroups_info.insert({ AdSecPose, { AdSecPose, 0x507, { AdSecPoseAX, AdSecPoseAXConf, AdSecPoseAY, AdSecPoseAYConf, AdSecPoseAZ, AdSecPoseAZConf, AdSecPoseChks, AdSecPoseCntr, AdSecPoseDataID, AdSecPosePitch, AdSecPosePitchConf, AdSecPosePitchRate, AdSecPosePitchRateConf, AdSecPosePosX, AdSecPosePosXConf, AdSecPosePosY, AdSecPosePosYConf, AdSecPoseRoll, AdSecPoseRollConf, AdSecPoseRollRate, AdSecPoseRollRateConf, AdSecPoseTiStampNanoSec, AdSecPoseTiStampSec, AdSecPoseVX, AdSecPoseVXConf, AdSecPoseVY, AdSecPoseVYConf, AdSecPoseYaw, AdSecPoseYawConf, AdSecPoseYawRate, AdSecPoseYawRateConf }, { E2EProfileType::P05, AdSecPoseChks, AdSecPoseCntr }, VIMBMid6CanFdFr03 } } );

    frames_info.insert({ VIMBMid6CanFdFr03, { VIMBMid6CanFdFr03, 65, 64, 10, { AdSecPose }, { AdSecPose_UB } } });

    frame_ids.insert({ 65, VIMBMid6CanFdFr03 });
}


}
}
