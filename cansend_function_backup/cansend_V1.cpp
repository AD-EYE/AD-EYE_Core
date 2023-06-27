/*-- Code to send a can mframe on bus A-D --*/

// Writen by Titouan Voisin and Anthony Dyck


#include <iostream>
#include <signal.h>
#include <sstream>
#include <memory>
#include <cstring>
#include <iomanip>
#include <chrono>
#include <thread>
using namespace std;

// DBC
#include "/home/adeye08u/Desktop/ros2can/ros2can-master/databases/spa4710_configurations_spa3_ad_mid3_can_cfg_210226_.c"

// framework
#include <framework/ProgramArguments.hpp>
#include <framework/DataPath.hpp>
#include <framework/Log.hpp>

// CORE
#include <dw/core/Logger.h>
#include <dw/core/Context.h>
#include <dw/core/VersionCurrent.h>

// HAL
#include <dw/sensors/Sensors.h>
#include <dw/sensors/canbus/CAN.h>


//------------------------------------------------------------------------------
// VariablesdwLogger_initialize
//------------------------------------------------------------------------------
static volatile bool gRun = true;

//------------------------------------------------------------------------------
void sig_int_handler(int /*sig*/)
{
    gRun = false;
}


/* Send a can message on a specified bus*/
int can_send(const char bus[2], const struct dwCANMessage *frame) {
       
        // install signal handler to react on ctrl+c
    {
        struct sigaction action = {};
        action.sa_handler       = sig_int_handler;
        
        sigaction(SIGHUP, &action, NULL);  // controlling terminal closed, Ctrl-D
        sigaction(SIGINT, &action, NULL);  // Ctrl-C
        sigaction(SIGQUIT, &action, NULL); // Ctrl-\, clean quit with core dump
        sigaction(SIGABRT, &action, NULL); // abort() called.
        sigaction(SIGTERM, &action, NULL); // kill command
    }

    dwContextHandle_t sdk = DW_NULL_HANDLE;
    dwSALHandle_t hal     = DW_NULL_HANDLE;
    { 
        // create a Logger to log to console
        // we keep the ownership of the logger at the application level
        dwLogger_initialize(getConsoleLoggerCallback(true));
        dwLogger_setLogLevel(DW_LOG_VERBOSE);

        // instantiate Driveworks SDK context
        dwContextParameters sdkParams = {};
        dwInitialize(&sdk, DW_VERSION, &sdkParams);

        // create HAL module of the SDK
        dwSAL_initialize(&hal, sdk);
    }

    // create CAN bus interface
    dwSensorHandle_t canSensor = DW_NULL_HANDLE;
    {
        dwSensorParams params;
        char str[25] = "ip=10.42.0.146,bus=";
        strcat(str,bus);
        params.parameters = str;
        params.protocol   = "can.aurix"; //arguments.get("driver").c_str()
        if (dwSAL_createSensor(&canSensor, params, hal) != DW_SUCCESS)
        {
            std::cout << "Cannot create sensor "
                      << params.protocol << " with " << params.parameters << std::endl;

            dwSAL_release(&hal);
            dwRelease(&sdk);
            dwLogger_release();

            return -1;
        }
    }


    // do not use HW timestamping if explicitly requested so

    dwSensorCAN_setUseHwTimestamps(false, canSensor);

    gRun = dwSensor_start(canSensor) == DW_SUCCESS;

    dwTime_t sendInterval = 1000;
    dwTime_t tNow;
    dwContext_getCurrentTime(&tNow, sdk);
    dwTime_t tSend = tNow + sendInterval * 1000;

    dwTime_t lastTime = 0;

    while (gRun)
    {

        std::this_thread::sleep_for(std::chrono::microseconds(10));

        dwCANMessage msg;
        dwStatus status = dwSensorCAN_readMessage(&msg, sendInterval > 0 ? 0 : 100000, canSensor); // !!!!


        dwContext_getCurrentTime(&tNow, sdk);

        // send a message over can bus
        if (tNow >= tSend && sendInterval > 0)
        {
            dwSensorCAN_sendMessage(frame, 1000, canSensor);
            tSend = tNow + sendInterval * 1000;
        }

        if (status == DW_TIME_OUT)
        {
            continue;
        }
        if (status == DW_END_OF_STREAM)
        {
            std::cout << "EndOfStream" << std::endl;
            gRun = false;
            break;
        }

        // log message
        if (lastTime == 0)
        {
            std::cout << msg.timestamp_us;
        }
        else
        {
            std::cout << msg.timestamp_us << " (dt=" << static_cast<int64_t>(msg.timestamp_us - lastTime) << ")";
        }

        if (msg.timestamp_us < lastTime)
        {
            std::cout << " ERROR msg out of order - ";
        }
        lastTime = msg.timestamp_us;
        if (status != DW_SUCCESS)
        {
            std::cout << " ERROR " << dwGetStatusName(status);
            break;
        }
        else
        {
            std::cout << std::uppercase
                      << " -> " << std::setfill('0') << std::setw(3) << std::hex
                      << msg.id << std::dec << "  [" << msg.size << "] ";
            for (auto i = 0; i < msg.size; i++)
                std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)msg.data[i] << " ";
            std::cout << std::dec;
        }
        std::cout << std::endl;
    }

    dwSensor_stop(canSensor);
    dwSAL_releaseSensor(&canSensor);

    // release used objects in correct order
    dwSAL_release(&hal);
    dwRelease(&sdk);
    dwLogger_release();

    return 0;
}


//int main(int argc, char **argv){
int main() {

    struct spa4710_configurations_spa3_ad_mid3_can_cfg_210226__etcvcu1_dev_send_mid3_fr1_t src_p; //struct for data to package
    uint8_t dst_p[8]; //tab for packaging of datas
    int size = 8; //size of the message
    struct dwCANMessage frame; //declare frame
    //struct spa4710_configurations_spa3_ad_mid3_can_cfg_210226__etcvcu1_dev_send_mid3_fr1_t* src_pointer = &src_p;
    
    src_p = {0xAB,0x05,0x02,0x03,0x04,0x05,0x07,0x08}; //fill the message

    //fill the frame
    frame.id = SPA4710_CONFIGURATIONS_SPA3_AD_MID3_CAN_CFG_210226__ETCVCU1_DEV_SEND_MID3_FR1_FRAME_ID; //fill the ID
    frame.size = spa4710_configurations_spa3_ad_mid3_can_cfg_210226__etcvcu1_dev_send_mid3_fr1_pack(dst_p, &src_p, size); //fill the size of the frame and package it
    for(int i=0; i<size; i++){ //cpy the pack datas into the frame
        frame.data[i] = dst_p[i];
    }

    //struct dwCANMessage *ptr_frame = &frame;
    //send the frame
    can_send("a",&frame);

    //recapitulative msg
    cout << "Id: " << hex << frame.id << endl;
    cout << "Data length: " << frame.size << endl;
    cout << "Data : ";
    for(int i=0; i<size; i++){
        cout << hex << (int)frame.data[i] << " ";
    }
    cout << endl;

    return 0;
}


