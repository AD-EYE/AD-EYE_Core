#include "gtest/gtest.h"

#include "../dbc_reader.h"


namespace {


using namespace kcan;


TEST(DBCReaderTest, getSignalInfo) {
    DBCReader::init();
    auto& si = DBCReader::getSignalInfo("PrpsnTqDirAct");
    EXPECT_EQ("PrpsnTqDirAct", si.name);
    EXPECT_EQ(52, si.start_bit);
    EXPECT_EQ(2, si.length);
    EXPECT_EQ(SignalType::APP_UNSIGNED, si.type);
    EXPECT_EQ("PrpsnTqDir", si.parent_name);
}


TEST(DBCReaderTest, getSignalInfo_Exception) {
    bool exception_caught = false;
    try {
        DBCReader::getSignalInfo("--fs-");
    } catch(invalid_argument& e) {
        exception_caught = true;
        EXPECT_STREQ("Signal [--fs-] not found!", e.what());
    }
    EXPECT_TRUE(exception_caught);
}


TEST(DBCReaderTest, getSignalGroupInfo) {
    DBCReader::init();
    auto& sgi = DBCReader::getSignalGroupInfo("PrpsnTqDir");
    EXPECT_EQ("PrpsnTqDir", sgi.name);
    EXPECT_EQ(0xA4, sgi.dataId);
    E2EProfileSettings settings { E2EProfileType::P01a, "PrpsnTqDirChks", "PrpsnTqDirCntr" };
    EXPECT_EQ(settings.checksum_name, sgi.e2e_settings.checksum_name);
    EXPECT_EQ(settings.counter_name, sgi.e2e_settings.counter_name);
    EXPECT_EQ(settings.type, sgi.e2e_settings.type);
    vector<string> signals { "PrpsnTqDirAct", "PrpsnTqDirChks", "PrpsnTqDirCntr" };
    EXPECT_EQ(signals, sgi.signals);
    EXPECT_EQ("VCU1Mid3CanFr03", sgi.parent_name);
}


TEST(DBCReaderTest, getSignalGroupInfo_Exception) {
    bool exception_caught = false;
    try {
        DBCReader::getSignalGroupInfo("--fs-");
    } catch(invalid_argument& e) {
        exception_caught = true;
        EXPECT_STREQ("Signal group [--fs-] not found!", e.what());
    }
    EXPECT_TRUE(exception_caught);
}


TEST(DBCReaderTest, getFrameInfo) {
    auto& fi = DBCReader::getFrameInfo("VCU1Mid3CanFr03");
    EXPECT_EQ(85, fi.id);
    EXPECT_EQ(8, fi.length);
    EXPECT_EQ("VCU1Mid3CanFr03", fi.name);
    EXPECT_EQ(20, fi.period);
    vector<string> signal_groups { "AdSecSteerActvnGroupSafe", "PrpsnTqDir", "SteerWhlTqGroup" };
    vector<string> signals { "PrpsnTqDir_UB", "SteerWhlTqGroup_UB", "AdSecSteerActvnGroupSafe_UB" };
    EXPECT_EQ(signal_groups, fi.signal_groups);
    EXPECT_EQ(signals, fi.signals);
 }


TEST(DBCReaderTest, getFrameInfo_Exception) {
    bool exception_caught = false;
    try {
        DBCReader::getFrameInfo("--fs-");
    } catch(invalid_argument& e) {
        exception_caught = true;
        EXPECT_STREQ("Frame [--fs-] not found!", e.what());
    }
    EXPECT_TRUE(exception_caught);
}

}