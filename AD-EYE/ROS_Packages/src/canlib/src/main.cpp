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

    CANSender can_sender_A { CANBus::A };

    // Signals name
    std::string ADMode_Status = "AdActvnOkFromVehDyn";
    std::string Steering_DS = "AdPrimSteerStsSafeGroupAdSteerSts";
    std::string Steering_RDS = "AdSecSteerStsSafeGroupAdSteerSts";
    std::string Brake_DS = "BrkDegradedSts";
    std::string Brake_RDS = "BrkDegradedssmdegraded";
    std::string SSM_DS = "SSMDegradedssmdegraded";
    std::string SSMB_DS = "SSMBDegradedSSMBDegraded";
    std::string PrimaryVolt_S = "ClstrSts1ForAutnmsDrvClstr1Sts";
    std::string SecondaryVolt_S = "ClstrSts2ForAutnmsDrvClstr2Sts";
    std::string EPB_S = "WhlLockStsDegradedSts";
    std::string SEPB_S = "SecWhlLockStsDegradedSts";
    std::string DriverPr = "DrvrPrsnt";
    std::string DriverPrQF = "DrvrPrsntQF";

    std::vector<std::string> signals{ADMode_Status, Steering_DS, Steering_RDS, Brake_DS, Brake_RDS, SSM_DS, SSMB_DS, PrimaryVolt_S, SecondaryVolt_S, EPB_S, SEPB_S, DriverPr, DriverPrQF};

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

    /*!
     * \brief Signals Callback : Called when a signal is send from the gui.
     * \param msg The message contains the signals and the values that need to be send to the car.
     * \details Send to the car the values of the signals.
     */
    void SignalsCallback (const std_msgs::String::ConstPtr& msg) {
        std::string signal_message = msg->data;
        std::map<string, int> signal_message_split = StringToMap(signal_message);
        SignalValues sv(SVMode::ZERO);
        for (map<string, int>::iterator it = signal_message_split.begin(); it != signal_message_split.end(); it++)
        {
            std::cout << it->first << ":" << it->second << std::endl;
            sv.addSignal(it->first, it->second);
        }
        can_sender_A.sendSignals(sv);
    }

    /*!
     * \brief CanReceiving.
     */
    std::string CanReceiving () {
        std::string message = "{";
        int signals_size = signals.size();
        
        for (int i = 0; i < signals_size; i++) {
            message.append('"' + signals[i] + '"' + ":" + std::to_string(rand() % 5) + ", ");
        }
        message = message.substr(0, message.size()-2);
        message.append("}");
        ROS_WARN_STREAM(message);
        return message;
    }

  public:
    Can(ros::NodeHandle& nh) : nh_(nh), rate_(1)
    {
        pub_signals_ = nh_.advertise<std_msgs::String>("/receiving_signals", 1, true);
        sub_signals_ = nh_.subscribe<std_msgs::String>("/sending_signals", 1, &Can::SignalsCallback, this);
    }
    
    void run() {
        bool test = true;
        std_msgs::String signals_;
        while (nh_.ok()) {
            rate_.sleep();
            ros::spinOnce();
            if (test) {
                test = false;
                signals_.data = CanReceiving();
                pub_signals_.publish(signals_);
            }
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