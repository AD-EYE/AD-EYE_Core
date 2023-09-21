#include <iostream>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <ros/ros.h>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>

#include "can_controller.h"
#include "can_sender.h"
#include "can_receiver.h"
#include "e2e_protector.h"
#include "can_frame.h"
#include "dbc.h"


using namespace kcan;
using namespace kcan::dbc;

class Can
{
  private:
    
    // ROS Subscriber and publisher
    ros::NodeHandle& nh_;
    ros::Subscriber sub_signals_;
    ros::Publisher pub_signals_;
    ros::Publisher pub_signals_2_;

    ros::Rate rate_;

    // CAN Variable
    CANController ctrl_A {  CANBus::A };
    CANController ctrl_B {  CANBus::B };
    CANController ctrl_C {  CANBus::C };
    CANSender can_sender_A { ctrl_A };
    CANSender can_sender_B { ctrl_B };
    CANSender can_sender_C { ctrl_C };
    CANReceiver can_receiver_A { ctrl_A };
    CANReceiver can_receiver_B { ctrl_B };
    CANReceiver can_receiver_C { ctrl_C };

    std::map<std::string, std::string> signals_friendly_map{{AdActvnOkFromVehDyn, "ADMode_Status"}, {AdPrimSteerStsSafeGroupAdSteerSts, "Steering_DS"}, {AdSecSteerStsSafeGroupAdSteerSts, "Steering_RDS"},
        {BrkDegradedSts, "Brake_DS"}, {BrkDegradedRdntSts, "Brake_RDS"}, {SSMDegradedssmdegraded, "SSM_DS"},
        {SSMBDegradedSSMBDegraded, "SSMB_DS"}, {ClstrSts1ForAutnmsDrvClstr1Sts, "PrimaryVolt_S"}, {ClstrSts2ForAutnmsDrvClstr2Sts, "SecondaryVolt_S"},
        {WhlLockStsDegradedSts, "EPB_S"}, {SecWhlLockStsDegradedSts, "SEPB_S"}, {DrvrPrsnt, "DriverPr"}, {DrvrPrsntQf, "DriverPrQF"}, {AutnmsDrvModMngtGlbSafe1AutnmsDrvModSts1, "ADMode_Act"}};

    struct signal_bus {
        std::string signal_name;
        CANBus can_bus;

        bool operator==(const signal_bus& s) const {
            return can_bus == s.can_bus && signal_name == s.signal_name;
        }

        bool operator<(const signal_bus& s) const {
            return signal_name < s.signal_name;
        }
    };

    std::map<signal_bus, std::vector<int>> signals{{{AdActvnOkFromVehDyn, CANBus::A}, {1}}, {{AdPrimSteerStsSafeGroupAdSteerSts, CANBus::A}, {0}}, {{AdSecSteerStsSafeGroupAdSteerSts, CANBus::C}, {0}},
        {{BrkDegradedSts, CANBus::A}, {0}}, {{BrkDegradedRdntSts, CANBus::C}, {0}}, {{SSMDegradedssmdegraded, CANBus::B}, {2,3,4}},
        {{SSMBDegradedSSMBDegraded, CANBus::C}, {2,3,4}}, {{ClstrSts1ForAutnmsDrvClstr1Sts, CANBus::A}, {3}}, {{ClstrSts2ForAutnmsDrvClstr2Sts, CANBus::A}, {3}},
        {{WhlLockStsDegradedSts, CANBus::A}, {1}}, {{SecWhlLockStsDegradedSts, CANBus::C}, {1}}, {{DrvrPrsnt, CANBus::A}, {3}}, {{DrvrPrsntQf, CANBus::A}, {2}},
        {{AutnmsDrvModMngtGlbSafe1AutnmsDrvModSts1, CANBus::A}, {1}}};

    enum Commands { ADMode_command, HL_command, VIM_command, VEHOP_command, STEERING_command, WLOCK_command };
    std::map<std::string, Commands> commands {{"ADMode_command", ADMode_command}, {"HL_command", HL_command}, {"VIM_command", VIM_command}, {"VEHOP_command", VEHOP_command}, 
        {"STEERING_command", STEERING_command}, {"WLOCK_command", WLOCK_command}};

    /*!
     * \brief Get Bus Sender : Return the correct can receiver variable of the signal. 
     * \param name The signal's name.
     */
    CANReceiver& getBusReceiver(const CANBus bus, const string& name) {
        using namespace dbc;
        string parent_name = DBCReader::getSignalInfo(bus, name).parent_name;
        string frame_name;
        try {
            frame_name = DBCReader::getSignalGroupInfo(bus, parent_name).parent_name;
        } catch (invalid_argument) {
            frame_name = parent_name;
        }
        if (frame_name.find("Mid3") != string::npos) {
            return can_receiver_A;
        }
        else if (frame_name.find("Mid5") != string::npos) {
            return can_receiver_B;
        }
        else if (frame_name.find("Mid6") != string::npos) {
            return can_receiver_C;
        }
    }

    /*!
     * \brief Can Receiving : Send signals' value to the /receiving_signals topic.
    */
    void CanReceiving () {
        std::string message = "{";
        uint64_t signal_value;
        std_msgs::String signals_;
        std::string status;

        for (map<signal_bus, std::vector<int>>::iterator it = signals.begin(); it != signals.end(); it++) {
            signal_bus signal_properties = it->first;
            std::string signal_name = signal_properties.signal_name;
            signal_value = getBusReceiver(signal_properties.can_bus, signal_name).getSignal(signal_name);
            std::vector<int> good_values = it->second;
            std::string friendly_signal_name = signals_friendly_map[signal_name];

            if (std::find(good_values.begin(), good_values.end(), signal_value) != good_values.end()) {
                status = "good";
            }
            else {
                status = "bad";
            }

            message.append('"' + friendly_signal_name + '"' + ":[" + std::to_string(signal_value) + "," + '"' + status + '"' + "], ");
        }
        message = message.substr(0, message.size()-2);
        message.append("}");

        signals_.data = message;
        pub_signals_.publish(signals_);
    }

    void wheelReceiving () {
        SignalValues signal;
        std_msgs::Float64 wheel_angle_;

        wheel_angle_.data = can_receiver_B.getSignal(AdPrimWhlAgEstimdGroupSafeWhlAg);

        pub_signals_2_.publish(wheel_angle_);
    }

    /*!
     * \brief Split Message : Split the message into a vector of two that contains the signal's name and its value.
     * \param msg The message contains signal's name and its value.
     * \param separator The separator between the name and the value.
     */
    std::vector<std::string> SplitMessage(std::string msg, std::string separator) {
        std::vector<std::string> split_message{"", ""};
        int j = msg.find(separator);
        split_message[0].append(msg.substr(0, j));
        split_message[1].append(msg.substr(j + 1, msg.length()));
        return split_message;
    }

    /*!
     * \brief String To Map : Return a map of signals and their value. 
     * \param msg The message contains signals' name and their value.
     */
    std::map<string, float> StringToMap (std::string msg) {
        int j = msg.find(",");
        std::map<string, float> dictionary_signals;
        while (j != string::npos) {
            std::vector<std::string> msg_split = SplitMessage(msg.substr(0, j), ":");
            dictionary_signals[msg_split[0]] = std::stof(msg_split[1]);
            msg.erase(msg.begin(), msg.begin() + j + 1);
            j = msg.find(",");
        }
        std::vector<std::string> msg_split = SplitMessage(msg.substr(0, j), ":");
        dictionary_signals[msg_split[0]] = std::stof(msg_split[1]);
        return dictionary_signals;
    }

    /*!
     * \brief Signals Callback : Called when a signal is send from the gui.
     * \param msg The message contains the signals and the values that need to be send to the car.
     * \details Send to the car the values of the signals.
     */
    void SignalsCallback (const std_msgs::String::ConstPtr& msg) {
        std::string signal_message = msg->data;
        std::map<string, float> signal_message_split = StringToMap(signal_message);

        for (map<string, float>::iterator it = signal_message_split.begin(); it != signal_message_split.end(); it++)
        {
            std::cout << "command_name: " << it->first << std::endl;
            std::cout << "value: " << it->second << std::endl;

            switch(commands[it->first]) {
                case ADMode_command:
                    ADMode_function(it->second);
                    ROS_WARN_STREAM("ADMODE");
                    break;
                case HL_command:
                    HL_function(it->second);
                    ROS_WARN_STREAM("HL");
                    break;
                case VIM_command:
                    VIM_function();
                    break;
                case VEHOP_command:
                    VEHOP_function(it->second);
                    break;
                case STEERING_command:
                    STEERING_function(it->second);
                    break;
                case WLOCK_command:
                    WLOCK_function(it->second);
                    break;

            }
        }
    }

    void ADMode_function(int value) {
        SignalValues sv;

        sv.addSignal(AutnmsDrvStReqAutnmsDrvStReq, value);
        can_sender_A.sendSignalGroup(AutnmsDrvStReq, sv, true);
        can_sender_A.sendSignal(AutnmsDrvStReq_UB, 1);
    }

    void HL_function(int value) {
        SignalValues sv;

        if (value == 1) {
            sv.addSignal(AdpLiReqFromAPIHzrdLiActvnReq, 1);
            sv.addSignal(AdpLiReqFromAPIHzrdLiDeactnReq, 0);
        }
        else {
            sv.addSignal(AdpLiReqFromAPIHzrdLiActvnReq, 0);
            sv.addSignal(AdpLiReqFromAPIHzrdLiDeactnReq, 1);
        }

        can_sender_A.sendSignalGroup(AdpLiReqFromAPI, sv, true);
        can_sender_A.sendSignal(AdpLiReqFromAPI_UB, 1);
    }

    void VIM_function() {
        SignalValues empty_sv;

        can_sender_A.sendFrame(VIMMid3CanFr07, empty_sv, true, true);
        can_sender_A.sendFrame(VIMMid3CanFr08, empty_sv, true, true);
        can_sender_A.sendFrame(VIMMid3CanFr15, empty_sv, true, true);

        can_sender_B.sendFrame(VIMMid5CanFdFr12, empty_sv, true, true);

        can_sender_C.sendFrame(VIMBMid6CanFdFr04, empty_sv, true, true);
        can_sender_C.sendFrame(VIMBMid6CanFdFr14, empty_sv, true, true);
        can_sender_C.sendFrame(VIMBMid6CanFdFr28, empty_sv, true, true);
    }

    void VEHOP_function(int value) {
        SignalValues sv;

        sv.addSignal(VehOperStReqVehOperStReq, value);
        can_sender_A.sendSignalGroup(VehOperStReq, sv, true);
        can_sender_A.sendSignal(VehOperStReq_UB, 1);
    }

    void STEERING_function(float value) {
        float offset = -0.85;
        float scalling = 5.249e-5;
        
        float steer_val = value;
        float a_lat_req;

        SignalValues sv_prim(SVMode::ZERO);
        SignalValues sv_sec(SVMode::ZERO);

        a_lat_req = (steer_val - offset) / scalling;

        std::cout << a_lat_req << std::endl;

        sv_prim.addSignal(AdPrimWhlAgReqGroupSafeWhlAgReq, a_lat_req);
        sv_sec.addSignal(AdSecWhlAgReqGroupSafeWhlAgReq, a_lat_req);
        can_sender_B.sendSignalGroup(AdPrimWhlAgReqGroupSafe, sv_prim, true);
        can_sender_C.sendSignalGroup(AdSecWhlAgReqGroupSafe, sv_sec, true);
        can_sender_B.sendSignal(AdPrimWhlAgReqGroupSafe_UB, 1);
        can_sender_C.sendSignal(AdSecWhlAgReqGroupSafe_UB, 1);
    }

    void WLOCK_function(int value) {
        float lock = value;

        uint64_t hstatus_val;
        uint64_t wstatus_val;
        uint64_t pstatus_val;
        uint64_t mstatus_val;

        if (lock == 1) {
            SignalValues sv(SVMode::ZERO);
            sv.addSignal(AdStandStillReqReq, 1);
            can_sender_A.sendSignalGroup(AdStandStillReq, sv, true);
            do {
                hstatus_val = can_receiver_A.getSignal(StandStillMgrStsForHldSafeStandStillSts);
                ROS_WARN_STREAM(StandStillMgrStsForHldSafeStandStillSts << hstatus_val);
                sleep(1);
            } while (hstatus_val != 3);
            SignalValues sv1(SVMode::ZERO);
            sv1.addSignal(AdWhlLockReqNoReqApplyRel, 2);
            can_sender_A.sendSignalGroup(AdWhlLockReq, sv1, true);
            do {
                wstatus_val = can_receiver_A.getSignal(WhlLockStsLockSts);
                ROS_WARN_STREAM(WhlLockStsLockSts << wstatus_val);
                sleep(1);
            } while (wstatus_val != 1);
            SignalValues sv2(SVMode::ZERO);
            sv2.addSignal(AdDirReqDirReq, 1);
            can_sender_A.sendSignalGroup(AdDirReq, sv2, true);
            do {
                pstatus_val = can_receiver_A.getSignal(PrpsnTqDirAct);
                ROS_WARN_STREAM(PrpsnTqDirAct << pstatus_val);
                sleep(1);
            } while (pstatus_val != 1);
            SignalValues sv3(SVMode::ZERO);
            sv3.addSignal(AdStandStillReqReq, 2);
            can_sender_A.sendSignalGroup(AdStandStillReq, sv3, true);
            do {
                mstatus_val = can_receiver_A.getSignal(PrimVehSpdGroupSafeMovDir);
                ROS_WARN_STREAM(PrimVehSpdGroupSafeMovDir << mstatus_val);
                sleep(1);
            } while (mstatus_val != 2);
        }
    }

  public:
    Can(ros::NodeHandle& nh) : nh_(nh), rate_(1)
    {
        pub_signals_ = nh_.advertise<std_msgs::String>("/receiving_status", 1, true);
        sub_signals_ = nh_.subscribe<std_msgs::String>("/sending_commands", 1, &Can::SignalsCallback, this);
        pub_signals_2_ = nh_.advertise<std_msgs::Float64>("/sending_angle", 1, true);
    }
    
    void run() {
        can_receiver_A.monitorSignal(AdActvnOkFromVehDyn);
        can_receiver_A.monitorSignal(AdPrimSteerStsSafeGroupAdSteerSts);
        can_receiver_C.monitorSignal(AdSecSteerStsSafeGroupAdSteerSts);
        can_receiver_A.monitorSignal(BrkDegradedSts);
        can_receiver_C.monitorSignal(BrkDegradedRdntSts);
        can_receiver_B.monitorSignal(SSMDegradedssmdegraded);
        can_receiver_C.monitorSignal(SSMBDegradedSSMBDegraded);
        can_receiver_A.monitorSignal(ClstrSts1ForAutnmsDrvClstr1Sts);
        can_receiver_A.monitorSignal(ClstrSts2ForAutnmsDrvClstr2Sts);
        can_receiver_A.monitorSignal(WhlLockStsDegradedSts);
        can_receiver_C.monitorSignal(SecWhlLockStsDegradedSts);
        can_receiver_A.monitorSignal(DrvrPrsnt);
        can_receiver_A.monitorSignal(DrvrPrsntQf);
        can_receiver_A.monitorSignal(AutnmsDrvModMngtGlbSafe1AutnmsDrvModSts1);

        can_receiver_A.monitorSignal(PrimVehSpdGroupSafeMax);
        can_receiver_A.monitorSignal(PrimVehSpdGroupSafeMin);
        can_receiver_B.monitorSignal(AdPrimWhlAgEstimdGroupSafeWhlAg);
        can_receiver_A.monitorSignal(StandStillMgrStsForHldSafeStandStillSts);
        
        while (nh_.ok()) {
            ros::spinOnce();
            CanReceiving();
            wheelReceiving();
            rate_.sleep();
        }
    }
};

int main(int argc, char* argv[]) {
    DBCReader::init();
    ros::init(argc, argv, "CanCar");
    ros::NodeHandle nh;
    Can VM(nh);
    VM.run();
    return 0;
}