/////////////////////////////////////////////////////////////////////////////////////////
// This code contains NVIDIA Confidential Information and is disclosed
// under the Mutual Non-Disclosure Agreement.
//
// Notice
// ALL NVIDIA DESIGN SPECIFICATIONS AND CODE ("MATERIALS") ARE PROVIDED "AS IS" NVIDIA MAKES
// NO REPRESENTATIONS, WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ANY IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
//
// NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. No third party distribution is allowed unless
// expressly authorized by NVIDIA.  Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2015-2018 NVIDIA Corporation. All rights reserved.
//
// NVIDIA Corporation and its licensors retain all intellectual property and proprietary
// rights in and to this software and related documentation and any modifications thereto.
// Any use, reproduction, disclosure or distribution of this software and related
// documentation without an express license agreement from NVIDIA Corporation is
// strictly prohibited.
//
/////////////////////////////////////////////////////////////////////////////////////////
// ROS
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/image_encodings.h"
#include <sstream>

// Core
#include <dw/core/Context.h>
#include <dw/core/Logger.h>
#include <dw/core/VersionCurrent.h>
#include <dw/core/NvMedia.h>

// HAL
#include <dw/sensors/Sensors.h>
#include <dw/sensors/SensorSerializer.h>
#include <dw/sensors/camera/Camera.h>

// Image
#include <dw/image/ImageStreamer.h>

#include <dw/image/FormatConverter_vibrante.h>

// nvmedia for surface map
#include <nvmedia_2d.h>
#include "nvmedia_image.h"
#include "nvmedia_ijpe.h"
#include "nvmedia_surface.h"

// Renderer
#include <dw/renderer/Renderer.h>

// Sample Includes
#include <framework/DriveWorksSample.hpp>
#include <framework/Log.hpp>
#include <framework/WindowGLFW.hpp>

using namespace dw_samples::common;


class CameraGMSL
{
private:
    // ------------------------------------------------
    // Driveworks Context and SAL
    // ------------------------------------------------
    dwContextHandle_t sdk_                  = DW_NULL_HANDLE;
    dwSALHandle_t sal_                      = DW_NULL_HANDLE;
    
    // ROS variables 
    ros::Publisher gmsl_pub_, gmsl_pub_img_;
    sensor_msgs::ImagePtr ros_img_ptr_; 


    // Image handles and properties
    dwImageHandle_t frame_rgb_ = DW_NULL_HANDLE; 
    dwSensorHandle_t camera_ = DW_NULL_HANDLE;
    dwImageProperties camera_image_properties_;
    dwCameraProperties camera_properties_;

    ProgramArguments args_;
     
public:
    CameraGMSL(const ProgramArguments& args): args_(args)
    {

    
        // -----------------------------------------
        // Initialize DriveWorks context and SAL
        // -----------------------------------------
        {
            // create a Logger to log to console
            // we keep the ownership of the logger at the application level
            CHECK_DW_ERROR(dwLogger_initialize(getConsoleLoggerCallback(true)));
            CHECK_DW_ERROR(dwLogger_setLogLevel(DW_LOG_VERBOSE));

            // instantiate Driveworks SDK context
            dwContextParameters sdk_params = {};
            sdk_params.dataPath = DataPath::get_cstr();
            CHECK_DW_ERROR(dwInitialize(&sdk_, DW_VERSION, &sdk_params));

            // create HAL module of the SDK
            CHECK_DW_ERROR(dwSAL_initialize(&sal_, sdk_));

        }

        //------------------------------------------------------------------------------
        // initializes camera
        // - the SensorCamera module
        // -----------------------------------------
        {


            dwSensorParams params;
            std::string parameter_string = std::string("output-format=yuv,fifo-size=3");

            parameter_string             += std::string(",camera-type=") + args_.get("camera-type").c_str();
            parameter_string             += std::string(",csi-port=") + args_.get("camera-port").c_str();
            parameter_string             += std::string(",slave=") + args_.get("tegra-slave").c_str();

            if (args_.get("custom-board").compare("1") == 0)
            {
                // it's a custom board, use the board specific extra configurations
                parameter_string             += ",custom-board=1";

                // pass an extra set of parameter in custom-config
                params.auxiliarydata           = args_.get("custom-config").c_str();
            }

            params.parameters           = parameter_string.c_str();
            params.protocol             = "camera.gmsl";

            CHECK_DW_ERROR(dwSAL_createSensor(&camera_, params, sal_));

            // sensor can take some time to start, it's possible to call the read function and check if the return status is ok
            // before proceding
            CHECK_DW_ERROR(dwSensor_start(camera_));

            dwCameraFrameHandle_t frame;
            dwStatus status = DW_NOT_READY;
            do {
                status = dwSensorCamera_readFrame(&frame, 0, 66000, camera_);
            } while (status == DW_NOT_READY);

            // something wrong happened, aborting
            if (status != DW_SUCCESS) {
                throw std::runtime_error("Cameras did not start correctly");
            }

            CHECK_DW_ERROR(dwSensorCamera_returnFrame(&frame));

            CHECK_DW_ERROR(dwSensorCamera_getSensorProperties(&camera_properties_, camera_));
            log("Successfully initialized camera with resolution of %dx%d at framerate of %f FPS\n",
                camera_properties_.resolution.x, camera_properties_.resolution.y, camera_properties_.framerate);

        }

         //ROS initialization
        {
            ros::VP_string ros_str;
            ros::init(ros_str, "camera_gmsl");
            ros::NodeHandle n;
            gmsl_pub_ = n.advertise<std_msgs::String>("gmsl_cam_txt", 1000);
            gmsl_pub_img_ = n.advertise<sensor_msgs::Image>("gmsl_cam_img", 1);

            ros_img_ptr_ = boost::make_shared<sensor_msgs::Image>();
            log("Successfully initialized ros\n" );
        }

        //Nvmedia initialization
        {
            dwImageProperties rgb_img_prop{};
            rgb_img_prop.height = camera_properties_.resolution.y;
            rgb_img_prop.width = camera_properties_.resolution.x;
            rgb_img_prop.type = DW_IMAGE_NVMEDIA;
            rgb_img_prop.format = DW_IMAGE_FORMAT_RGBA_UINT8;
            CHECK_DW_ERROR(dwImage_create(&frame_rgb_,  rgb_img_prop,sdk_	));
            log("Successfully initialized nvmedia img.\n" );
        }
        
    }

    ~CameraGMSL()
    {
        log("Destructor!!!");
        if (camera_) {
            dwSensor_stop(camera_);
            dwSAL_releaseSensor(&camera_);
        }

        //destroy created image
        dwImage_destroy(&frame_rgb_);

        dwSAL_release(&sal_);
        dwRelease(&sdk_);
        dwLogger_release();

    }

    void publish()
    {
        std::string cam_type = args_.get("camera-type");
        // log("Camera type - %s \n", cam_type);
        std::cout<<"Camera type "<<cam_type<<std::endl;

        try
        {
            ros::Rate loop_rate(15);
            int count = 0;
            while (ros::ok())
            {
                dwTime_t timeout = 132000; 
                dwCameraFrameHandle_t frame;
                uint32_t camera_sibling_id = 0;
                dwImageHandle_t frame_yuv;
                dwImageNvMedia* nvmedia_yuv_img_ptr;
                dwImageNvMedia* nvmedia_rgb_img_ptr;

                sensor_msgs::Image &img_msg = *ros_img_ptr_; // >> message to be sent
                std_msgs::Header header; // empty header
                size_t img_size;

                
                // read from camera will update the low level buffers frame of the camera
                // those frames are images with NATIVE properties that depend on the type and sensor properties set at creation
                CHECK_DW_ERROR(dwSensorCamera_readFrame(&frame, camera_sibling_id, timeout, camera_));

                CHECK_DW_ERROR(dwSensorCamera_getImageNvMedia(&nvmedia_yuv_img_ptr, DW_CAMERA_OUTPUT_NATIVE_PROCESSED, frame));
                CHECK_DW_ERROR(dwImage_getNvMedia(&nvmedia_rgb_img_ptr, frame_rgb_));
                CHECK_DW_ERROR(dwImage_createAndBindNvMedia(&frame_yuv, nvmedia_yuv_img_ptr->img));
                CHECK_DW_ERROR(dwImage_copyConvert(frame_rgb_, frame_yuv, sdk_));
                CHECK_DW_ERROR(dwImage_getNvMedia(&nvmedia_rgb_img_ptr, frame_rgb_));

                
                header.seq = count; // user defined counter
                header.stamp = ros::Time::now(); 
                    
                img_msg.header = header;
                img_msg.height = nvmedia_rgb_img_ptr->prop.height;
                img_msg.width = nvmedia_rgb_img_ptr->prop.width;
                img_msg.encoding = sensor_msgs::image_encodings::RGBA8;
                
                img_msg.step = img_msg.width * 4; // 1 Byte per 4 Channels of the RGBA format

                img_size = img_msg.step * img_msg.height;
                img_msg.data.resize(img_size);
                    NvMediaImageSurfaceMap surfaceMap;
                if (NvMediaImageLock(nvmedia_rgb_img_ptr->img, NVMEDIA_IMAGE_ACCESS_READ, &surfaceMap) == NVMEDIA_STATUS_OK)
                {
                        unsigned char* buffer = (unsigned char*)surfaceMap.surface[0].mapping;
                        memcpy((char *)( &img_msg.data[0] ) , buffer , img_size);
                        gmsl_pub_img_.publish(ros_img_ptr_);
                        NvMediaImageUnlock(nvmedia_rgb_img_ptr->img);
                }
                //   cleanup
                CHECK_DW_ERROR(dwImage_destroy(&frame_yuv));       
                // return frame
                CHECK_DW_ERROR(dwSensorCamera_returnFrame(&frame));
                ros::spinOnce();
                loop_rate.sleep();
                ++count;
            }
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << "\n";
        }
    }

};

//------------------------------------------------------------------------------
int main(int argc, const char *argv[])
{

    ProgramArguments args(argc, const_cast<const char**>(argv),
    {
        ProgramArguments::Option_t("camera-type", "ar0231-rccb-bae-sf3324", "camera gmsl type (see sample_sensors_info for all available camera types on this platform)\n"),

        ProgramArguments::Option_t("camera-port", "a", "Camera CSI port [default a]\n"
                              "a - port AB on px2, A on ddpx\n"
                              "c - port CD on px2, C on ddpx\n"
                              "e - port EF on px2, E on ddpx\n"
                              "g - G on ddpx only\n"
                              ),

        ProgramArguments::Option_t("tegra-slave", "0", "Optional parameter used only for Tegra B, enables slave mode.\n"),
        ProgramArguments::Option_t("custom-board", "0", "If true, then the configuration for board and camera "
                              "will be input from the config-file\n"),
        ProgramArguments::Option_t("custom-config", "", "Set of custom board extra configuration\n"),

    }, "DriveWorks camera GMSL");

    CameraGMSL cam(args);
    cam.publish();    

    return 0;
}
