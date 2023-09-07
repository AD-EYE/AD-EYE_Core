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
const string VIMMid5CanFdFr02 { "VIMMid5CanFdFr02" };

// Groups
const string AdPrimPose { "AdPrimPose" };

// Signals
const string AdPrimPose_UB { "AdPrimPose_UB" };
const string AdPrimPoseAX { "AdPrimPoseAX" };
const string AdPrimPoseAXConf { "AdPrimPoseAXConf" };
const string AdPrimPoseAY { "AdPrimPoseAY" };
const string AdPrimPoseAYConf { "AdPrimPoseAYConf" };
const string AdPrimPoseAZ { "AdPrimPoseAZ" };
const string AdPrimPoseAZConf { "AdPrimPoseAZConf" };
const string AdPrimPoseChks { "AdPrimPoseChks" };
const string AdPrimPoseCntr { "AdPrimPoseCntr" };
const string AdPrimPoseDataID { "AdPrimPoseDataID" };
const string AdPrimPosePitch { "AdPrimPosePitch" };
const string AdPrimPosePitchConf { "AdPrimPosePitchConf" };
const string AdPrimPosePitchRate { "AdPrimPosePitchRate" };
const string AdPrimPosePitchRateConf { "AdPrimPosePitchRateConf" };
const string AdPrimPosePosX { "AdPrimPosePosX" };
const string AdPrimPosePosXConf { "AdPrimPosePosXConf" };
const string AdPrimPosePosY { "AdPrimPosePosY" };
const string AdPrimPosePosYConf { "AdPrimPosePosYConf" };
const string AdPrimPoseRoll { "AdPrimPoseRoll" };
const string AdPrimPoseRollConf { "AdPrimPoseRollConf" };
const string AdPrimPoseRollRate { "AdPrimPoseRollRate" };
const string AdPrimPoseRollRateConf { "AdPrimPoseRollRateConf" };
const string AdPrimPoseTiStampNanoSec { "AdPrimPoseTiStampNanoSec" };
const string AdPrimPoseTiStampSec { "AdPrimPoseTiStampSec" };
const string AdPrimPoseVX { "AdPrimPoseVX" };
const string AdPrimPoseVXConf { "AdPrimPoseVXConf" };
const string AdPrimPoseVY { "AdPrimPoseVY" };
const string AdPrimPoseVYConf { "AdPrimPoseVYConf" };
const string AdPrimPoseYaw { "AdPrimPoseYaw" };
const string AdPrimPoseYawConf { "AdPrimPoseYawConf" };
const string AdPrimPoseYawRate { "AdPrimPoseYawRate" };
const string AdPrimPoseYawRateConf { "AdPrimPoseYawRateConf" };


}
}
