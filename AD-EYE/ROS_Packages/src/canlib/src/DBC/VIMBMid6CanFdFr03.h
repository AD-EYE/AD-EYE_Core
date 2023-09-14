#include "../basic_types.h"

namespace kcan {
namespace dbc {


void VIMBMid6CanFdFr03_Init(
    map<uint, string>& frame_ids,
    map<std::string, FrameInfo>& frames_info,
    map<std::string, SignalGroupInfo>& signalgroups_info,
    map<std::string, SignalInfo>& signals_info
);


// Frame
const std::string VIMBMid6CanFdFr03 { "VIMBMid6CanFdFr03" };


// Groups
const std::string AdSecPose { "AdSecPose" };


// Signals
const std::string AdSecPoseChks { "AdSecPoseChks" };
const std::string AdSecPoseCntr { "AdSecPoseCntr" };
const std::string AdSecPoseAX { "AdSecPoseAX" };
const std::string AdSecPoseAY { "AdSecPoseAY" };
const std::string AdSecPoseAZ { "AdSecPoseAZ" };
const std::string AdSecPoseDataID { "AdSecPoseDataID" };
const std::string AdSecPosePitch { "AdSecPosePitch" };
const std::string AdSecPosePitchRate { "AdSecPosePitchRate" };
const std::string AdSecPosePosX { "AdSecPosePosX" };
const std::string AdSecPosePosY { "AdSecPosePosY" };
const std::string AdSecPoseRoll { "AdSecPoseRoll" };
const std::string AdSecPoseRollRate { "AdSecPoseRollRate" };
const std::string AdSecPoseTiStampNanoSec { "AdSecPoseTiStampNanoSec" };
const std::string AdSecPoseTiStampSec { "AdSecPoseTiStampSec" };
const std::string AdSecPoseVX { "AdSecPoseVX" };
const std::string AdSecPoseVY { "AdSecPoseVY" };
const std::string AdSecPoseYaw { "AdSecPoseYaw" };
const std::string AdSecPoseYawRate { "AdSecPoseYawRate" };
const std::string AdSecPoseAXConf { "AdSecPoseAXConf" };
const std::string AdSecPoseAYConf { "AdSecPoseAYConf" };
const std::string AdSecPoseAZConf { "AdSecPoseAZConf" };
const std::string AdSecPosePitchConf { "AdSecPosePitchConf" };
const std::string AdSecPosePitchRateConf { "AdSecPosePitchRateConf" };
const std::string AdSecPosePosXConf { "AdSecPosePosXConf" };
const std::string AdSecPosePosYConf { "AdSecPosePosYConf" };
const std::string AdSecPoseRollConf { "AdSecPoseRollConf" };
const std::string AdSecPoseRollRateConf { "AdSecPoseRollRateConf" };
const std::string AdSecPoseVXConf { "AdSecPoseVXConf" };
const std::string AdSecPoseVYConf { "AdSecPoseVYConf" };
const std::string AdSecPoseYawConf { "AdSecPoseYawConf" };
const std::string AdSecPoseYawRateConf { "AdSecPoseYawRateConf" };
const std::string AdSecPose_UB { "AdSecPose_UB" };


}
}
