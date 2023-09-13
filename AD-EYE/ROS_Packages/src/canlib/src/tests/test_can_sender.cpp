#include "gtest/gtest.h"

#include "../HAL/can_dummy.h"
#include "../can_sender.h"
#include "../dbc.h"


class SetupEnvironment : public ::testing::Environment {
public:
    void SetUp() {
        kcan::DBCReader::init();
    }

    void TearDown() {

    }
};


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment(new SetupEnvironment);
    return RUN_ALL_TESTS();
}


namespace {


using namespace kcan;
using namespace kcan::dbc;


TEST(CANSenderTest, sendSignalGroup) {
    DUMMYCANController ctrl(CANBus::A);
    CANSender can_sender(ctrl);
    SignalValues sv;
    sv.addSignal(AdpLiReqFromAPIHzrdLiDeactnReq, 1);
    sv.addSignal(AdpLiReqFromAPIHzrdLiActvnReq, 0);
    can_sender.sendSignalGroup(AdpLiReqFromAPI, sv);

    CANFrame frame;
    while (ctrl.receive(&frame) == -1) { }
    EXPECT_EQ(288,  frame.getFrameInfo().id);
    sv = frame.getSignalGroup(AdpLiReqFromAPI);
    EXPECT_EQ(1, sv.getValue(AdpLiReqFromAPIHzrdLiDeactnReq));
    EXPECT_EQ(0, sv.getValue(AdpLiReqFromAPIHzrdLiActvnReq));

    sv.addSignal(AdpLiReqFromAPIHzrdLiDeactnReq, 0);
    sv.addSignal(AdpLiReqFromAPIHzrdLiActvnReq, 1);
    can_sender.sendSignalGroup(AdpLiReqFromAPI, sv);

    while (ctrl.receive(&frame) == -1) { }
    EXPECT_EQ(288, frame.getFrameInfo().id);
    sv = frame.getSignalGroup(AdpLiReqFromAPI);
    EXPECT_EQ(0, sv.getValue(AdpLiReqFromAPIHzrdLiDeactnReq));
    EXPECT_EQ(1, sv.getValue(AdpLiReqFromAPIHzrdLiActvnReq));
}


}