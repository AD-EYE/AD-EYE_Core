#include <map>

#include "basic_types.h"
#include "dbc.h"

namespace kcan {
namespace dbc {


map<string, SignalInfo> g_signals_info;
map<string, SignalGroupInfo> g_signalgroups_info;
map<string, FrameInfo> g_frames_info;


void DBCInit() {
    VIMMid3CanFr11_Init(g_frames_info, g_signalgroups_info, g_signals_info);
}

/*
void init_dbc() {
    g_signalgroups_info.insert(
    {
        AdPrimSteerStsSafeGroup,
        {
            AdPrimSteerStsSafeGroup,
            24,
            0x1A0,
            0,
            {
                //AdPrimSteerStsSafeGroup_UB,
                AdPrimSteerStsSafeGroupAdSteerPerf,
                AdPrimSteerStsSafeGroupAdSteerSts,
                AdPrimSteerStsSafeGroupChks,
                AdPrimSteerStsSafeGroupCntr,
            }, 
            E2EProfile::P01a,
            VCU1Mid3CanFr01
        }
    });
    g_signalgroups_info.insert(
    {
        CarModInCrashStsSafe,
        {
            CarModInCrashStsSafe,
            24,
            0x261,
            24,
            {
                //CarModInCrashStsSafe_UB,
                CarModInCrashStsSafeChks,
                CarModInCrashStsSafeCntr,
                CarModInCrashStsSafeSts,     
            }, 
            E2EProfile::P01a,
            VCU1Mid3CanFr01
        }
    });

    g_frames_info.insert({ VCU1Mid3CanFr01, { VCU1Mid3CanFr01, 48, 64, 300, { AdPrimSteerStsSafeGroup, CarModInCrashStsSafe }, {} } });

    g_signals_info.insert({ AdPrimSteerStsSafeGroup_UB, { AdPrimSteerStsSafeGroup_UB, 5, 1, "None", VCU1Mid3CanFr01 } });
    g_signals_info.insert({ AdPrimSteerStsSafeGroupAdSteerPerf, { AdPrimSteerStsSafeGroupAdSteerPerf, 0, 5, AdPrimSteerStsSafeGroup, VCU1Mid3CanFr01 } });
    g_signals_info.insert({ AdPrimSteerStsSafeGroupAdSteerSts, { AdPrimSteerStsSafeGroupAdSteerSts, 13, 3, AdPrimSteerStsSafeGroup, VCU1Mid3CanFr01 } });
    g_signals_info.insert({ AdPrimSteerStsSafeGroupChks, { AdPrimSteerStsSafeGroupChks, 16, 8, AdPrimSteerStsSafeGroup, VCU1Mid3CanFr01 } });
    g_signals_info.insert({ AdPrimSteerStsSafeGroupCntr, { AdPrimSteerStsSafeGroupCntr, 8, 4, AdPrimSteerStsSafeGroup, VCU1Mid3CanFr01 } });
    g_signals_info.insert({ CarModInCrashStsSafe_UB, { CarModInCrashStsSafe_UB, 6, 1, "None", VCU1Mid3CanFr01 } });
    g_signals_info.insert({ CarModInCrashStsSafeChks, { CarModInCrashStsSafeChks, 24, 8, CarModInCrashStsSafe, VCU1Mid3CanFr01 } });
    g_signals_info.insert({ CarModInCrashStsSafeCntr, { CarModInCrashStsSafeCntr, 32, 4, CarModInCrashStsSafe, VCU1Mid3CanFr01 } });
    g_signals_info.insert({ CarModInCrashStsSafeSts, { CarModInCrashStsSafeSts, 40, 1, CarModInCrashStsSafe, VCU1Mid3CanFr01 } });

    g_signalgroups_info.insert(
    {
        AdPrimPose,
        {
            AdPrimPose,
            512,
            0x111,
            0,
            {
                //AdPrimPose_UB,
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
                AdPrimPoseYawRateConf,
            }, 
            E2EProfile::P05,
            VIMMid5CanFdFr02
        }
    });

    g_frames_info.insert({ VIMMid5CanFdFr02, { VIMMid5CanFdFr02, 33, 512, 100, { AdPrimPose }, {} } });

    g_signals_info.insert({ AdPrimPose_UB, { AdPrimPose_UB, 511, 1, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseAX, { AdPrimPoseAX, 24, 20, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseAXConf, { AdPrimPoseAXConf, 400, 3, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseAY, { AdPrimPoseAY, 48, 20, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseAYConf, { AdPrimPoseAYConf, 408, 3, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseAZ, { AdPrimPoseAZ, 72, 20, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseAZConf, { AdPrimPoseAZConf, 416, 3, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseChks, { AdPrimPoseChks, 0, 16, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseCntr, { AdPrimPoseCntr, 16, 8, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseDataID, { AdPrimPoseDataID, 96, 16, "group", "frame" } });
    g_signals_info.insert({ AdPrimPosePitch, { AdPrimPosePitch, 112, 16, "group", "frame" } });
    g_signals_info.insert({ AdPrimPosePitchConf, { AdPrimPosePitchConf, 424, 3, "group", "frame" } });
    g_signals_info.insert({ AdPrimPosePitchRate, { AdPrimPosePitchRate, 128, 20, "group", "frame" } });
    g_signals_info.insert({ AdPrimPosePitchRateConf, { AdPrimPosePitchRateConf, 432, 3, "group", "frame" } });
    g_signals_info.insert({ AdPrimPosePosX, { AdPrimPosePosX, 152, 32, "group", "frame" } });
    g_signals_info.insert({ AdPrimPosePosXConf, { AdPrimPosePosXConf, 440, 3, "group", "frame" } });
    g_signals_info.insert({ AdPrimPosePosY, { AdPrimPosePosY, 184, 32, "group", "frame" } });
    g_signals_info.insert({ AdPrimPosePosYConf, { AdPrimPosePosYConf, 448, 3, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseRoll, { AdPrimPoseRoll, 216, 16, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseRollConf, { AdPrimPoseRollConf, 456, 3, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseRollRate, { AdPrimPoseRollRate, 232, 20, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseRollRateConf, { AdPrimPoseRollRateConf, 464, 3, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseTiStampNanoSec, { AdPrimPoseTiStampNanoSec, 256, 32, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseTiStampSec, { AdPrimPoseTiStampSec, 288, 32, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseVX, { AdPrimPoseVX, 320, 16, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseVXConf, { AdPrimPoseVXConf, 472, 3, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseVY, { AdPrimPoseVY, 336, 14, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseVYConf, { AdPrimPoseVYConf, 480, 3, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseYaw, { AdPrimPoseYaw, 352, 24, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseYawConf, { AdPrimPoseYawConf, 488, 3, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseYawRate, { AdPrimPoseYawRate, 376, 22, "group", "frame" } });
    g_signals_info.insert({ AdPrimPoseYawRateConf, { AdPrimPoseYawRateConf, 496, 3, "group", "frame" } });
}
*/

}
}
