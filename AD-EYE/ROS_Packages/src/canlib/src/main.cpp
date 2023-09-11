#include <iostream>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <ros/ros.h>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <std_msgs/String.h>

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

    // Signals name
    std::string ADMode_Status = "AdActvnOkFromVehDyn";
    std::string Steering_DS = "AdPrimSteerStsSafeGroupAdSteerSts";
    std::string Steering_RDS = "AdSecSteerStsSafeGroupAdSteerSts";
    std::string Brake_DS = "BrkDegradedSts";
    std::string Brake_RDS = "BrkDegradedRdntSts";
    std::string SSM_DS = "SSMDegradedssmdegraded";
    std::string SSMB_DS = "SSMBDegradedSSMBDegraded";
    std::string PrimaryVolt_S = "ClstrSts1ForAutnmsDrvClstr1Sts";
    std::string SecondaryVolt_S = "ClstrSts2ForAutnmsDrvClstr2Sts";
    std::string EPB_S = "WhlLockStsDegradedSts";
    std::string SEPB_S = "SecWhlLockStsDegradedSts";
    std::string DriverPr = "DrvrPrsnt";
    std::string DriverPrQF = "DrvrPrsntQf";

    std::vector<std::string> signals{AutnmsDrvModMngtGlbSafe1AutnmsDrvModSts1, ADMode_Status, Steering_DS, Steering_RDS, Brake_DS, Brake_RDS, SSM_DS, SSMB_DS, PrimaryVolt_S, SecondaryVolt_S, EPB_S, SEPB_S, DriverPr, DriverPrQF};
    // std::map<std::string, CANSender> can_senders;

    // std::map<std::string, CANReceiver> signals { {AdActvnOkFromVehDyn, can_receiver_A} ,{AdPrimSteerStsSafeGroupAdSteerSts, can_receiver_A} ,{AdSecSteerStsSafeGroupAdSteerSts, can_receiver_C}, {BrkDegradedSts, can_receiver_A}, {BrkDegradedRdntSts, can_receiver_C}, {SSMDegradedssmdegraded, can_receiver_B}, {SSMBDegradedSSMBDegraded, can_receiver_C}, {ClstrSts1ForAutnmsDrvClstr1Sts, can_receiver_A}, {ClstrSts2ForAutnmsDrvClstr2Sts, can_receiver_A}, {WhlLockStsDegradedSts, can_receiver_A}, {SecWhlLockStsDegradedSts, can_receiver_C}, {DrvrPrsnt, can_receiver_A}, {DrvrPrsntQf, can_receiver_A} };
    // std::map<std::string, string> signals { {AdActvnOkFromVehDyn, "A"} ,{AdPrimSteerStsSafeGroupAdSteerSts, "A"} ,{AdSecSteerStsSafeGroupAdSteerSts, "C"}, {BrkDegradedSts, "A"}, {BrkDegradedRdntSts, "C"}, {SSMDegradedssmdegraded, "B"}, {SSMBDegradedSSMBDegraded, "C"}, {ClstrSts1ForAutnmsDrvClstr1Sts, "A"}, {ClstrSts2ForAutnmsDrvClstr2Sts, "A"}, {WhlLockStsDegradedSts, "A"}, {SecWhlLockStsDegradedSts, "C"}, {DrvrPrsnt, "A"}, {DrvrPrsntQf, "A"} };


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
    std::map<string, int> StringToMap (std::string msg) {
        int j = msg.find(",");
        std::map<string, int> dictionary_signals;
        while (j != string::npos) {
            std::vector<std::string> msg_split = SplitMessage(msg.substr(0, j), ":");
            dictionary_signals[msg_split[0]] = std::stoi(msg_split[1]);
            msg.erase(msg.begin(), msg.begin() + j + 1);
            j = msg.find(",");
        }
        std::vector<std::string> msg_split = SplitMessage(msg.substr(0, j), ":");
        dictionary_signals[msg_split[0]] = std::stoi(msg_split[1]);
        return dictionary_signals;
    }

    CANSender getBusSender(const string& name) {
        using namespace dbc;
        string parent_name = DBCReader::getSignalInfo(name).parent_name;
        string frame_name;
        try {
            frame_name = DBCReader::getSignalGroupInfo(parent_name).parent_name;
        } catch (invalid_argument) {
            frame_name = parent_name;
        }
        if (frame_name.find("Mid3") != string::npos) {
            ROS_WARN_STREAM("AAAA");
            return can_sender_A;
        }
        else if (frame_name.find("Mid5") != string::npos) {
            return can_sender_B;
        }
        else if (frame_name.find("Mid6") != string::npos) {
            return can_sender_C;
        }
    }

    /*!
     * \brief Signals Callback : Called when a signal is send from the gui.
     * \param msg The message contains the signals and the values that need to be send to the car.
     * \details Send to the car the values of the signals.
     */
    void SignalsCallback (const std_msgs::String::ConstPtr& msg) {
        std::string signal_message = msg->data;
        std::map<string, int> signal_message_split = StringToMap(signal_message);
        SignalValues sv(SVMode::ZERO);
        std::string signal_group;
        for (map<string, int>::iterator it = signal_message_split.begin(); it != signal_message_split.end(); it++)
        {
            std::cout << it->first << ":" << it->second << std::endl;
            std::cout << "name: " << it->first << std::endl;
            std::cout << "value: " << it->second << std::endl;
            sv.addSignal(it->first, it->second);
            signal_group = DBCReader::getSignalInfo(it->first).parent_name;
            ROS_WARN_STREAM(signal_group << it->first);
        }
        ROS_WARN_STREAM(signal_message_split.begin()->first);
        // getBusSender(signal_message_split.begin()->first).sendSignals(sv);
        // getBusSender(signal_message_split.begin()->first).sendSignalGroup(signal_group, sv);
        can_sender_A.sendSignalGroup(signal_group, sv);
    }

    CANReceiver getBusReceiver(const string& name) {
        using namespace dbc;
        string parent_name = DBCReader::getSignalInfo(name).parent_name;
        string frame_name;
        try {
            frame_name = DBCReader::getSignalGroupInfo(parent_name).parent_name;
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
     * \brief CanReceiving.
     */
    void CanReceiving () {
        std::string message = "{";
        int signals_size = signals.size();
        SignalValues signal;
        std_msgs::String signals_;

        for (int i = 1; i < signals_size; i++) {
            signal = getBusReceiver(signals[i]).getSignal(signals[i]);
            message.append('"' + signals[i] + '"' + ":" + std::to_string(signal.getValue(signals[i])) + ", ");
        }

        // for (map<string, CANReceiver>::iterator it = signals.begin(); it != signals.end(); it++) {
        //     string signal_name = it->first;
        //     ROS_WARN_STREAM(signal_name);
        //     CANReceiver can_receiver = it->second;
        //     signal = can_receiver_A.getSignal(signal_name);
        //     message.append('"' + signal_name + '"' + ":" + std::to_string(signal.getValue(signal_name)) + ", ");
        // }

        // for (map<string, string>::iterator it = signals.begin(); it != signals.end(); it++) {
        //     string signal_name = it->first;
        //     ROS_WARN_STREAM(signal_name);
        //     switch (it->second) {
        //         case "A":
        //             signal = can_receiver_A.getSignal(signal_name);
        //         case "B":
        //             signal = can_receiver_B.getSignal(signal_name);
        //         case "C":
        //             signal = can_receiver_C.getSignal(signal_name);
        //     }
        //     message.append('"' + signal_name + '"' + ":" + std::to_string(signal.getValue(signal_name)) + ", ");
        // }

        message = message.substr(0, message.size()-2);
        message.append("}");

        signals_.data = message;
        pub_signals_.publish(signals_);
    }

  public:
    Can(ros::NodeHandle& nh) : nh_(nh), rate_(1)
    {
        pub_signals_ = nh_.advertise<std_msgs::String>("/receiving_signals", 1, true);
        sub_signals_ = nh_.subscribe<std_msgs::String>("/sending_signals", 1, &Can::SignalsCallback, this);
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
        while (nh_.ok()) {
            ros::spinOnce();
            CanReceiving();
            rate_.sleep();
        }
        
        
        // bool test = true;
        // std_msgs::String signals_;
        // while (nh_.ok()) {
        //     rate_.sleep();
        //     ros::spinOnce();
        //     if (test) {
        //         test = false;
        //         signals_.data = CanReceiving();
        //         pub_signals_.publish(signals_);
        //     }
        // }
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