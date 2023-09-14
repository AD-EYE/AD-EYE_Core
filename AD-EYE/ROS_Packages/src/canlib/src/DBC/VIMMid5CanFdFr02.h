#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMMid5CanFdFr02_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMMid5CanFdFr02 { "VIMMid5CanFdFr02" };


// Groups
const std::string AdPrimPose { "AdPrimPose" };


// Signals
const std::string AdPrimPoseChks { "AdPrimPoseChks" };
const std::string AdPrimPoseCntr { "AdPrimPoseCntr" };
const std::string AdPrimPoseAX { "AdPrimPoseAX" };
const std::string AdPrimPoseAY { "AdPrimPoseAY" };
const std::string AdPrimPoseAZ { "AdPrimPoseAZ" };
const std::string AdPrimPoseDataID { "AdPrimPoseDataID" };
const std::string AdPrimPosePitch { "AdPrimPosePitch" };
const std::string AdPrimPosePitchRate { "AdPrimPosePitchRate" };
const std::string AdPrimPosePosX { "AdPrimPosePosX" };
const std::string AdPrimPosePosY { "AdPrimPosePosY" };
const std::string AdPrimPoseRoll { "AdPrimPoseRoll" };
const std::string AdPrimPoseRollRate { "AdPrimPoseRollRate" };
const std::string AdPrimPoseTiStampNanoSec { "AdPrimPoseTiStampNanoSec" };
const std::string AdPrimPoseTiStampSec { "AdPrimPoseTiStampSec" };
const std::string AdPrimPoseVX { "AdPrimPoseVX" };
const std::string AdPrimPoseVY { "AdPrimPoseVY" };
const std::string AdPrimPoseYaw { "AdPrimPoseYaw" };
const std::string AdPrimPoseYawRate { "AdPrimPoseYawRate" };
const std::string AdPrimPoseAXConf { "AdPrimPoseAXConf" };
const std::string AdPrimPoseAYConf { "AdPrimPoseAYConf" };
const std::string AdPrimPoseAZConf { "AdPrimPoseAZConf" };
const std::string AdPrimPosePitchConf { "AdPrimPosePitchConf" };
const std::string AdPrimPosePitchRateConf { "AdPrimPosePitchRateConf" };
const std::string AdPrimPosePosXConf { "AdPrimPosePosXConf" };
const std::string AdPrimPosePosYConf { "AdPrimPosePosYConf" };
const std::string AdPrimPoseRollConf { "AdPrimPoseRollConf" };
const std::string AdPrimPoseRollRateConf { "AdPrimPoseRollRateConf" };
const std::string AdPrimPoseVXConf { "AdPrimPoseVXConf" };
const std::string AdPrimPoseVYConf { "AdPrimPoseVYConf" };
const std::string AdPrimPoseYawConf { "AdPrimPoseYawConf" };
const std::string AdPrimPoseYawRateConf { "AdPrimPoseYawRateConf" };
const std::string AdPrimPose_UB { "AdPrimPose_UB" };


}
}
