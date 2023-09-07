#include "gtest/gtest.h"

#include "../e2e_protector.h"
#include "../dbc.h"


namespace {


using namespace kcan;
using namespace kcan::dbc;


TEST(E2EProtectorTest, AdpLiReqFromAPI) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdpLiReqFromAPIHzrdLiDeactnReq, 0);
    sv.addSignal(AdpLiReqFromAPIHzrdLiActvnReq, 0);
    sv.addSignal(AdpLiReqFromAPIAhbcActvn, 0);
    sv.addSignal(AdpLiReqFromAPIIncrLiRiReq, 0);
    sv.addSignal(AdpLiReqFromAPIIndcrLeReq, 0);

    E2EProtector e2e(AdpLiReqFromAPI);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xBC, res.checksum);
    EXPECT_EQ(0x0, res.counter);
}

TEST(E2EProtectorTest, AdSecSteerStsSafeGroup) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdSecSteerStsSafeGroupAdSteerPerf, 20);
    sv.addSignal(AdSecSteerStsSafeGroupAdSteerSts, 4);
    sv.addSignal(AdSecSteerStsSafeGroupCntr, 0x4);

    E2EProtector e2e(AdSecSteerStsSafeGroup);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xFE, res.checksum);
    EXPECT_EQ(0x4, res.counter);
}


TEST(E2EProtectorTest, SSMBDegraded) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(SSMBDegradedSSMBDegraded, 0x0);
    sv.addSignal(SSMBDegradedcntr, 0x2);

    E2EProtector e2e(SSMBDegraded);
    E2EResult res = e2e.applyProfile(sv);

    EXPECT_EQ(0x2, res.counter);
    EXPECT_EQ(0x1B, res.checksum);
}


TEST(E2EProtectorTest, BrkDegradedRdnt) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(BrkDegradedRdntSts, 0);
    sv.addSignal(BrkDegradedRdntCntr, 0xA);

    E2EProtector e2e(BrkDegradedRdnt);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x86, res.checksum);
    EXPECT_EQ(0xA, res.counter);
}


TEST(E2EProtectorTest, SSMDegraded) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(SSMDegradedssmdegraded, 0);
    sv.addSignal(SSMDegradedcntr, 0xE);

    E2EProtector e2e(SSMDegraded);
    E2EResult res = e2e.applyProfile(sv);

    EXPECT_EQ(0xE, res.counter);
    EXPECT_EQ(0xF1, res.checksum);
}


TEST(E2EProtectorTest, AdPrimSteerStsSafeGroup) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdPrimSteerStsSafeGroupAdSteerPerf, 20);
    sv.addSignal(AdPrimSteerStsSafeGroupAdSteerSts, 4);
    sv.addSignal(AdPrimSteerStsSafeGroupCntr, 2);

    E2EProtector e2e(AdPrimSteerStsSafeGroup);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x91, res.checksum);
    EXPECT_EQ(0x2, res.counter);
}

TEST(E2EProtectorTest, ClstrSts1ForAutnmsDrv) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(ClstrSts1ForAutnmsDrvClstr1Sts, 3);
    sv.addSignal(ClstrSts1ForAutnmsDrvClstr1Cnt, 0xA);

    E2EProtector e2e(ClstrSts1ForAutnmsDrv);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xCB, res.checksum);
    EXPECT_EQ(0xA, res.counter);
}

TEST(E2EProtectorTest, ClstrSts2ForAutnmsDrv) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(ClstrSts2ForAutnmsDrvClstr2Sts, 3);
    sv.addSignal(ClstrSts2ForAutnmsDrvClstr2Cnt, 0xA);

    E2EProtector e2e(ClstrSts2ForAutnmsDrv);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x56, res.checksum);
    EXPECT_EQ(0xA, res.counter);
}


TEST(E2EProtectorTest, AutnmsDrvModMngtGlbSafe1) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AutnmsDrvModMngtGlbSafe1AutnmsDrvModSts1, 2);
    sv.addSignal(AutnmsDrvModMngtGlbSafe1AutnmsLowSpdModSts1, 0);
    sv.addSignal(AutnmsDrvModMngtGlbSafe1Counter, 0xA);
    sv.addSignal(AutnmsDrvModMngtGlbSafe1VehOperModSts1, 2);

    E2EProtector e2e(AutnmsDrvModMngtGlbSafe1);
    E2EResult res = e2e.applyProfile(sv);

    EXPECT_EQ(0xA, res.counter);
    EXPECT_EQ(0x56, res.checksum);
}


TEST(E2EProtectorTest, BrkDegraded) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(BrkDegradedSts, 0);
    sv.addSignal(BrkDegradedCntr, 0xE);

    E2EProtector e2e(BrkDegraded);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xE1, res.checksum);
    EXPECT_EQ(0xE, res.counter);
}

TEST(E2EProtectorTest, WhlLockSts) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(WhlLockStsDegradedSts, 1);
    sv.addSignal(WhlLockStsLockSts, 4);
    sv.addSignal(WhlLockStsCntr, 0xC);

    E2EProtector e2e(WhlLockSts);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xE, res.checksum);
    EXPECT_EQ(0xC, res.counter);
}

TEST(E2EProtectorTest, AdPrimPose) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdPrimPoseAX, 0x80002);
    sv.addSignal(AdPrimPoseAXConf, 0);
    sv.addSignal(AdPrimPoseAY, 0x80002);
    sv.addSignal(AdPrimPoseAYConf, 0);
    sv.addSignal(AdPrimPoseAZ, 0x80002);
    sv.addSignal(AdPrimPoseAZConf, 0);
    sv.addSignal(AdPrimPoseCntr, 0xA);
    sv.addSignal(AdPrimPoseDataID, 0);
    sv.addSignal(AdPrimPosePitch, 0x7FF8);
    sv.addSignal(AdPrimPosePitchConf, 0);
    sv.addSignal(AdPrimPosePitchRate, 0x8000C);
    sv.addSignal(AdPrimPosePitchRateConf, 0);
    sv.addSignal(AdPrimPosePosX, 0);
    sv.addSignal(AdPrimPosePosXConf, 0);
    sv.addSignal(AdPrimPosePosY, 0);
    sv.addSignal(AdPrimPosePosYConf, 0);
    sv.addSignal(AdPrimPoseRoll, 0x7FF8);
    sv.addSignal(AdPrimPoseRollConf, 0);
    sv.addSignal(AdPrimPoseRollRate, 0x8000C);
    sv.addSignal(AdPrimPoseRollRateConf, 0);
    sv.addSignal(AdPrimPoseTiStampNanoSec, 0);
    sv.addSignal(AdPrimPoseTiStampSec, 0);
    sv.addSignal(AdPrimPoseVX, 0x31E0);
    sv.addSignal(AdPrimPoseVXConf, 0);
    sv.addSignal(AdPrimPoseVY, 0x2000);
    sv.addSignal(AdPrimPoseVYConf, 0);
    sv.addSignal(AdPrimPoseYaw, 0x7FFDA0);
    sv.addSignal(AdPrimPoseYawConf, 0);
    sv.addSignal(AdPrimPoseYawRate, 0x1FFF68);
    sv.addSignal(AdPrimPoseYawRateConf, 0);

    E2EProtector e2e(AdPrimPose);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xA, res.counter);
    EXPECT_EQ(0xE38D, res.checksum);
}


TEST(E2EProtectorTest, AdPrimPSSGroupSafe8) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdPrimPSSGroupSafe8Cntr, 0xb8);
    sv.addSignal(AdPrimPSSGroupSafe8DataID, 0);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaTPos1, 0);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaTPos2, 0);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaTPos3, 0);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaTPos4, 0);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaTPos5, 0);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaTPos6, 0);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaXPos1, 0x1fffe);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaXPos2, 0x1fffe);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaXPos3, 0x1fffe);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaXPos4, 0x1fffe);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaXPos5, 0x1fffe);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaXPos6, 0x1fffe);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaYPos1, 0x1fffe);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaYPos2, 0x1fffe);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaYPos3, 0x1fffe);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaYPos4, 0x1fffe);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaYPos5, 0x1fffe);
    sv.addSignal(AdPrimPSSGroupSafe8DeltaYPos6, 0x1fffe);
    sv.addSignal(AdPrimPSSGroupSafe8HeadingPos1, 0x7fff);
    sv.addSignal(AdPrimPSSGroupSafe8HeadingPos2, 0x7fff);
    sv.addSignal(AdPrimPSSGroupSafe8HeadingPos3, 0x7fff);
    sv.addSignal(AdPrimPSSGroupSafe8HeadingPos4, 0x7fff);
    sv.addSignal(AdPrimPSSGroupSafe8HeadingPos5, 0x7fff);
    sv.addSignal(AdPrimPSSGroupSafe8HeadingPos6, 0x7fff);
    sv.addSignal(AdPrimPSSGroupSafe8TrajectID, 0x0);

    E2EProtector e2e(AdPrimPSSGroupSafe8);
    E2EResult res = e2e.applyProfile(sv);

    EXPECT_EQ(0xB8, res.counter);
    EXPECT_EQ(0x97C4, res.checksum);
}

TEST(E2EProtectorTest, AdSecSteerActvnGroupSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdSecSteerActvnGroupSafeAdSteerActvnReq, 0);
    sv.addSignal(AdSecSteerActvnGroupSafeAdSteerDeActvnReq, 1);
    sv.addSignal(AdSecSteerActvnGroupSafeCntr, 6);

    E2EProtector e2e(AdSecSteerActvnGroupSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x6C, res.checksum);
    EXPECT_EQ(0x6, res.counter);
}

TEST(E2EProtectorTest, PrpsnTqDir) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(PrpsnTqDirAct, 0);
    sv.addSignal(PrpsnTqDirCntr, 1);

    E2EProtector e2e(PrpsnTqDir);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x7D, res.checksum);
    EXPECT_EQ(0x1, res.counter);
}

TEST(E2EProtectorTest, DrvrPrsntGroup) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(DrvrPrsntQf, 3);
    sv.addSignal(DrvrPrsnt, 2);
    sv.addSignal(DrvrPrsntStsDrvrPrsntCntr, 0xE);

    E2EProtector e2e(DrvrPrsntGroup);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x1B, res.checksum);
    EXPECT_EQ(0xE, res.counter);
}

TEST(E2EProtectorTest, PrimVehSpdGroupSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(PrimVehSpdGroupSafeCntr, 9);
    sv.addSignal(PrimVehSpdGroupSafeMax, 0xA);
    sv.addSignal(PrimVehSpdGroupSafeMin, 0);
    sv.addSignal(PrimVehSpdGroupSafeMinMaxQf, 3);
    sv.addSignal(PrimVehSpdGroupSafeMovDir, 1);
    sv.addSignal(PrimVehSpdGroupSafeMovDirQf, 3);
    sv.addSignal(PrimVehSpdGroupSafeNom, 0);
    sv.addSignal(PrimVehSpdGroupSafeNomQf, 3);

    E2EProtector e2e(PrimVehSpdGroupSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x43, res.checksum);
    EXPECT_EQ(0x9, res.counter);
}

TEST(E2EProtectorTest, PrimALgtDataRawSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(PrimALgtDataRawSafeCntr, 0xB);
    sv.addSignal(PrimALgtDataRawSafeMax, 0x40D0);
    sv.addSignal(PrimALgtDataRawSafeMin, 0x3F40);
    sv.addSignal(PrimALgtDataRawSafeMinMaxQf, 3);
    sv.addSignal(PrimALgtDataRawSafeNom, 0x400A);
    sv.addSignal(PrimALgtDataRawSafeNomQf, 3);

    E2EProtector e2e(PrimALgtDataRawSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xFA, res.checksum);
    EXPECT_EQ(0xB, res.counter);
}

TEST(E2EProtectorTest, AdPrimWhlAgEstimdGroupSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdPrimWhlAgEstimdGroupSafeCntr, 0xE);
    sv.addSignal(AdPrimWhlAgEstimdGroupSafeQf1, 3);
    sv.addSignal(AdPrimWhlAgEstimdGroupSafeWhlAg, 0x3F26);
    sv.addSignal(AdPrimWhlAgEstimdGroupSafeWhlAgR, 0x36AF);

    E2EProtector e2e(AdPrimWhlAgEstimdGroupSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x27, res.checksum);
    EXPECT_EQ(0xE, res.counter);
}

TEST(E2EProtectorTest, PrimALatDataRawSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(PrimALatDataRawSafeCntr, 0xE);
    sv.addSignal(PrimALatDataRawSafeMax, 0x40E8);
    sv.addSignal(PrimALatDataRawSafeMin, 0x3F58);
    sv.addSignal(PrimALatDataRawSafeMinMaxQf, 3);
    sv.addSignal(PrimALatDataRawSafeNom, 0x4020);
    sv.addSignal(PrimALatDataRawSafeNomQf, 3);

    E2EProtector e2e(PrimALatDataRawSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xBD, res.checksum);
    EXPECT_EQ(0xE, res.counter);
}

TEST(E2EProtectorTest, PrimVLatSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(PrimVLatSafeCntr, 0xE);
    sv.addSignal(PrimVLatSafeMax, 0);
    sv.addSignal(PrimVLatSafeMin, 0);
    sv.addSignal(PrimVLatSafeMinMaxQf, 3);
    sv.addSignal(PrimVLatSafeNom, 0);
    sv.addSignal(PrimVLatSafeNomQf, 3);

    E2EProtector e2e(PrimVLatSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xDE, res.checksum);
    EXPECT_EQ(0xE, res.counter);
}

TEST(E2EProtectorTest, PrimWhlRotDirReSafe1) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(PrimWhlRotDirReSafe1Cntr, 0xC);
    sv.addSignal(PrimWhlRotDirReSafe1Le, 1);
    sv.addSignal(PrimWhlRotDirReSafe1LeQf, 3);
    sv.addSignal(PrimWhlRotDirReSafe1Ri, 1);
    sv.addSignal(PrimWhlRotDirReSafe1RiQf, 3);

    E2EProtector e2e(PrimWhlRotDirReSafe1);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xA7, res.checksum);
    EXPECT_EQ(0xC, res.counter);
}

// This one is really weird

// TEST(E2EProtectorTest, PrimWhlRotToothCntr) {
//     DBCReader::init();

//     SignalValues sv;
//     sv.addSignal(PrimWhlRotToothCntrCntr, 0xE);
//     sv.addSignal(PrimWhlRotToothCntrWhlRotToothCn, 0);
//     sv.addSignal(PrimWhlRotToothCntrWhlRotTo_0000, 0);
//     sv.addSignal(PrimWhlRotToothCntrWhlRotTo_0001, 3);
//     sv.addSignal(PrimWhlRotToothCntrWhlRotTo_0002, 0);
//     sv.addSignal(PrimWhlRotToothCntrWhlRotTo_0003, 3);
//     sv.addSignal(PrimWhlRotToothCntrWhlRotTo_0004, 3);
//     sv.addSignal(PrimWhlRotToothCntrWhlRotTo_0005, 0);
//     sv.addSignal(PrimWhlRotToothCntrWhlRotTo_0006, 3);

//     E2EProtector e2e(PrimWhlRotToothCntr);
//     E2EResult res = e2e.applyProfile(sv);
//     EXPECT_EQ(0xDE, res.checksum);
//     EXPECT_EQ(0xE, res.counter);
// }

TEST(E2EProtectorTest, PrimYawRateSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(PrimYawRateSafeCntr, 0xE);
    sv.addSignal(PrimYawRateSafeMax, 0x106);
    sv.addSignal(PrimYawRateSafeMin, 0x7EFA);
    sv.addSignal(PrimYawRateSafeMinMaxQf, 3);
    sv.addSignal(PrimYawRateSafeNom, 0);
    sv.addSignal(PrimYawRateSafeNomQf, 3);

    E2EProtector e2e(PrimYawRateSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xE2, res.checksum);
    EXPECT_EQ(0xE, res.counter);
}

TEST(E2EProtectorTest, AdFreeDst) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdFreeDstCntr, 0x1);
    sv.addSignal(AdFreeDstFreeDstFwd, 0);
    sv.addSignal(AdFreeDstFreeDstRvs, 0);

    E2EProtector e2e(AdFreeDst);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xA5, res.checksum);
    EXPECT_EQ(0x1, res.counter);
}

TEST(E2EProtectorTest, AdWhlLockReq) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdWhlLockReqCntr, 1);
    sv.addSignal(AdWhlLockReqNoReqApplyRel, 0);

    E2EProtector e2e(AdWhlLockReq);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x29, res.checksum);
    EXPECT_EQ(1, res.counter);
}

TEST(E2EProtectorTest, AdPrimWhlAgReqGroupSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdPrimWhlAgReqGroupSafeCntr, 0xD);
    sv.addSignal(AdPrimWhlAgReqGroupSafeWhlAgReq, 0x3F42);

    E2EProtector e2e(AdPrimWhlAgReqGroupSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x43, res.checksum);
    EXPECT_EQ(0xD, res.counter);
}

TEST(E2EProtectorTest, AdSecWhlAgReqGroupSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdSecWhlAgReqGroupSafeCntr, 0xE);
    sv.addSignal(AdSecWhlAgReqGroupSafeWhlAgReq, 0x3F42);

    E2EProtector e2e(AdSecWhlAgReqGroupSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x71, res.checksum);
    EXPECT_EQ(0xE, res.counter);
}

TEST(E2EProtectorTest, AdNomALgtReqGroupSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdNomALgtReqGroupSafeALgtNomReqMax, 0xF00);
    sv.addSignal(AdNomALgtReqGroupSafeALgtNomReqMin, 0);
    sv.addSignal(AdNomALgtReqGroupSafeCntr, 0xD);
    sv.addSignal(AdNomALgtReqGroupSafeNegLimForJerk, 0);
    sv.addSignal(AdNomALgtReqGroupSafePosLimForJerk, 0xFA0);

    E2EProtector e2e(AdNomALgtReqGroupSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x28, res.checksum);
    EXPECT_EQ(0xD, res.counter);
}

TEST(E2EProtectorTest, AdPrimALgtLimReqGroupSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdPrimALgtLimReqGroupSafeALgtMaxReq, 0xF00);
    sv.addSignal(AdPrimALgtLimReqGroupSafeALgtMinReq, 0);
    sv.addSignal(AdPrimALgtLimReqGroupSafeCntr, 0xE);

    E2EProtector e2e(AdPrimALgtLimReqGroupSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x13, res.checksum);
    EXPECT_EQ(0xE, res.counter);
}

TEST(E2EProtectorTest, AdSecALgtLimReqGroupSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(AdSecALgtLimReqGroupSafeALgtMaxReq, 0xF00);
    sv.addSignal(AdSecALgtLimReqGroupSafeALgtMinReq, 0);
    sv.addSignal(AdSecALgtLimReqGroupSafeCntr, 0xE);

    E2EProtector e2e(AdSecALgtLimReqGroupSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0x9D, res.checksum);
    EXPECT_EQ(0xE, res.counter);
}

TEST(E2EProtectorTest, SecAdNomALgtReqGroupSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(SecAdNomALgtReqGroupSafeALgtNomReqMax, 0x780);
    sv.addSignal(SecAdNomALgtReqGroupSafeALgtNomReqMin, 0x780);
    sv.addSignal(SecAdNomALgtReqGroupSafeCntr, 0xE);
    sv.addSignal(SecAdNomALgtReqGroupSafeNegLimForJerk, 0x7D0);
    sv.addSignal(SecAdNomALgtReqGroupSafePosLimForJerk, 0x7D0);

    E2EProtector e2e(SecAdNomALgtReqGroupSafe);
    E2EResult res = e2e.applyProfile(sv);
    EXPECT_EQ(0xEE, res.checksum);
    EXPECT_EQ(0xE, res.counter);
}


TEST(E2EProtectorTest, SecYawRateSafe) {
    DBCReader::init();

    SignalValues sv;
    sv.addSignal(SecYawRateSafeCntr, 0x7);
    sv.addSignal(SecYawRateSafeMax, 0x105);
    sv.addSignal(SecYawRateSafeMin, 0x7EFA);
    sv.addSignal(SecYawRateSafeMinMaxQf, 0x3);
    sv.addSignal(SecYawRateSafeNom, 0x0);
    sv.addSignal(SecYawRateSafeNomQf, 0x3);

    E2EProtector e2e(SecYawRateSafe);
    E2EResult res = e2e.applyProfile(sv);

    EXPECT_EQ(0x7, res.counter);
    EXPECT_EQ(0xA9, res.checksum);    
}


}