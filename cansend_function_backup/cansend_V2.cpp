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
#include "/home/adeye08u/ros2can/ros2can-master/databases/spa4710_configurations_spa3_ad_mid3_can_cfg_210226_.c"

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


/* Send a can message on a specified bus*/
int can_send(const char bus[2], const struct dwCANMessage *frame) {

    dwContextHandle_t sdk = DW_NULL_HANDLE;
    dwSALHandle_t hal     = DW_NULL_HANDLE;
    {
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
        params.protocol   = "can.aurix";

        if (dwSAL_createSensor(&canSensor, params, hal) != DW_SUCCESS)
        {
            std::cout << "Cannot create sensor "
                      << params.protocol << " with " << params.parameters << std::endl;
            dwSAL_release(&hal);
            dwRelease(&sdk);
            return -1;
        }
    }

    dwSensor_start(canSensor);

    // send a message over can bus
    while(1){
        dwSensorCAN_sendMessage(frame, 1000, canSensor);
    }

    dwSensor_stop(canSensor);
    dwSAL_releaseSensor(&canSensor);

    // release used objects in correct order
    dwSAL_release(&hal);
    dwRelease(&sdk);

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

    //printing recapitulative msg
    cout << "-- Sending dataframe --" << endl;
    cout << "Id: " << hex << frame.id << endl;
    cout << "Data length: " << frame.size << endl;
    cout << "Data : ";
    for(int i=0; i<size; i++){
        cout << hex << (int)frame.data[i] << " ";
    }
    cout << endl;

    //send the frame
    can_send("a",&frame);

    //printing end of sending
    cout << "-- End of transmission --" << endl;

    return 0;
}


