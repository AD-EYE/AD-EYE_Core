#include <iostream>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <ros/ros.h>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <std_msgs/Float64.h>

#include "can_controller.h"
#include "can_sender.h"
#include "can_receiver.h"
#include "e2e_protector.h"
#include "can_frame.h"
#include "dbc.h"

#include <stdlib.h> 

using namespace kcan;
using namespace kcan::dbc;

class Can
{
  private:
    ros::NodeHandle& nh_;
    ros::Subscriber sub_signals_;
    ros::Publisher pub_signals_;

    ros::Rate rate_;

    CANController ctrl_A {  CANBus::A };
    CANController ctrl_B {  CANBus::B };
    CANController ctrl_C {  CANBus::C };
    CANSender can_sender_A { ctrl_A };
    CANSender can_sender_B { ctrl_B };
    CANSender can_sender_C { ctrl_C };
    CANReceiver can_receiver_A { ctrl_A };
    CANReceiver can_receiver_B { ctrl_B };
    CANReceiver can_receiver_C { ctrl_C };

    float test;

    void steering(const std_msgs::Float64::ConstPtr& msg) {
        float steer_val = msg->data;
        float speed;
        float a_lat_req;
        float steer_ag_req;
        SignalValues sv_prim(SVMode::ZERO);
        SignalValues sv_sec(SVMode::ZERO);

        speed = (can_receiver_A.getSignal(PrimVehSpdGroupSafeMax).getValue(PrimVehSpdGroupSafeMax) + \
            can_receiver_A.getSignal(PrimVehSpdGroupSafeMin).getValue(PrimVehSpdGroupSafeMin)) / 2;
        a_lat_req = steer_val;
        test = a_lat_req;

        std::cout << a_lat_req << " rad " << a_lat_req * 180 / 3.14 << " deg" << std::endl;

        sv_prim.addSignal(AdPrimWhlAgReqGroupSafeWhlAgReq, a_lat_req);
        sv_sec.addSignal(AdSecWhlAgReqGroupSafeWhlAgReq, a_lat_req);
        can_sender_B.sendSignalGroup(AdPrimWhlAgReqGroupSafe, sv_prim, true);
        can_sender_C.sendSignalGroup(AdSecWhlAgReqGroupSafe, sv_sec, true);
        can_sender_B.sendSignal(AdPrimWhlAgReqGroupSafe_UB, 1);
        can_sender_C.sendSignal(AdSecWhlAgReqGroupSafe_UB, 1);
    }

    void wheelReceiving () {
        SignalValues signal;
        std_msgs::Float64 wheel_angle_;

        wheel_angle_.data = can_receiver_B.getSignal(AdPrimWhlAgEstimdGroupSafeWhlAg).getValue(AdPrimWhlAgEstimdGroupSafeWhlAg);
        wheel_angle_.data = test;
        pub_signals_.publish(wheel_angle_);
    }

  public:
    Can(ros::NodeHandle& nh) : nh_(nh), rate_(1)
    {
        pub_signals_ = nh_.advertise<std_msgs::Float64>("/sending_angle", 1, true);
        sub_signals_ = nh_.subscribe<std_msgs::Float64>("/receiving_angle", 1, &Can::steering, this);
    }
    
    void run() {      
        can_receiver_A.monitorSignal(PrimVehSpdGroupSafeMax);
        can_receiver_A.monitorSignal(PrimVehSpdGroupSafeMin);
        can_receiver_B.monitorSignal(AdPrimWhlAgEstimdGroupSafeWhlAg);

        while (nh_.ok()) {
            ros::spinOnce();
            wheelReceiving();
            rate_.sleep();
        }

    }
};

int main(int argc, char* argv[]) {
    DBCReader::init();
    ros::init(argc, argv, "CanSteering");
    ros::NodeHandle nh;
    Can VM(nh);
    VM.run();
    return 0;
}