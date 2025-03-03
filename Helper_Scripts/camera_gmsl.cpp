// ROS
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/image_encodings.h"
#include "ros/console.h"

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

#include <sstream>
#include <boost/program_options.hpp>

#define CHECK_DW_ERROR(x) { \
                    dwStatus result = x; \
                    if(result!=DW_SUCCESS) { \
                        throw std::runtime_error(std::string("DW Error ") \
                                                + dwGetStatusName(result) \
                                                + std::string(" executing DW function:\n " #x) \
                                                + std::string("\n at " __FILE__ ":") + std::to_string(__LINE__)); \
                    }};

namespace po = boost::program_options;

class CameraGMSL
{
private:
    // Driveworks Context and SAL
    dwContextHandle_t SDK_ = DW_NULL_HANDLE;
    dwSALHandle_t SAL_ = DW_NULL_HANDLE;
    
    // ROS variables 
    ros::Publisher gmsl_pub_, gmsl_pub_img_;
    sensor_msgs::ImagePtr ros_img_ptr_; 

    // Image handles and properties
    dwImageHandle_t frame_resized_ = DW_NULL_HANDLE; // Resized image handle
    dwSensorHandle_t camera_ = DW_NULL_HANDLE;
    dwImageProperties camera_image_properties_;
    dwCameraProperties camera_properties_;

    po::variables_map args_;
     
public:
    CameraGMSL(const po::variables_map args) : args_(args)
    {
        // Initialize DriveWorks context and SAL
        {
            dwContextParameters SDK_params = {};
            CHECK_DW_ERROR(dwInitialize(&SDK_, DW_VERSION, &SDK_params));
            CHECK_DW_ERROR(dwSAL_initialize(&SAL_, SDK_));
        }

        // Initialize camera
        {
            dwSensorParams params;
            std::string parameter_string = "output-format=yuv,fifo-size=3";
            parameter_string += ",camera-type=" + args_["camera-type"].as<std::string>();
            parameter_string += ",csi-port=" + args_["camera-port"].as<std::string>();
            parameter_string += ",slave=" + args_["tegra-slave"].as<std::string>();

            if (args_["custom-board"].as<std::string>() == "1")
            {
                parameter_string += ",custom-board=1";
                params.auxiliarydata = args_["custom-board"].as<std::string>().c_str();
            }

            params.parameters = parameter_string.c_str();
            params.protocol = "camera.gmsl";

            CHECK_DW_ERROR(dwSAL_createSensor(&camera_, params, SAL_));
            CHECK_DW_ERROR(dwSensor_start(camera_));

            dwCameraFrameHandle_t frame;
            dwStatus status = DW_NOT_READY;
            do {
                status = dwSensorCamera_readFrame(&frame, 0, 66000, camera_);
            } while (status == DW_NOT_READY);

            if (status != DW_SUCCESS) {
                throw std::runtime_error("Cameras did not start correctly");
            }

            CHECK_DW_ERROR(dwSensorCamera_returnFrame(&frame));
            CHECK_DW_ERROR(dwSensorCamera_getSensorProperties(&camera_properties_, camera_));
            ROS_INFO("Successfully initialized camera with resolution of %dx%d at framerate of %f FPS\n",
                camera_properties_.resolution.x, camera_properties_.resolution.y, camera_properties_.framerate);
        }

        // ROS initialization with parameter reading
        {
            ros::init(ros_str, "camera_gmsl");
            ros::NodeHandle n;
            gmsl_pub_img_ = n.advertise<sensor_msgs::Image>("camera_1/image_raw", 1);
            ros_img_ptr_ = boost::make_shared<sensor_msgs::Image>();
            ROS_INFO("Successfully initialized ros\n");

            double scaling_factor;
            if (!n.getParam("scaling_factor", scaling_factor)) {
                scaling_factor = 1.0; // default, no scaling
            }
            if (scaling_factor <= 0 || scaling_factor > 1) {
                ROS_ERROR("Invalid scaling_factor. Using default 1.0");
                scaling_factor = 1.0;
            }
            int new_width = static_cast<int>(camera_properties_.resolution.x * scaling_factor);
            int new_height = static_cast<int>(camera_properties_.resolution.y * scaling_factor);

            // Create resized image handle
            dwImageProperties resized_prop{};
            resized_prop.height = new_height;
            resized_prop.width = new_width;
            resized_prop.type = DW_IMAGE_NVMedia;
            resized_prop.format = DW_IMAGE_FORMAT_RGBA_UINT8;
            CHECK_DW_ERROR(dwImage_create(&frame_resized_, resized_prop, SDK_));
            ROS_INFO("Successfully initialized resized img with resolution %dx%d\n", new_width, new_height);
        }
    }

    ~CameraGMSL()
    {
        ROS_INFO("Destructor!!!");
        if (camera_) {
            dwSensor_stop(camera_);
            dwSAL_releaseSensor(&camera_);
        }

        // Destroy resized image
        dwImage_destroy(&frame_resized_);

        dwSAL_release(&SAL_);
        dwRelease(&SDK_);
        dwLogger_release();
    }

    void publish()
    {
        std::string cam_type = args_["camera-type"].as<std::string>();
        ROS_INFO("Camera type - %s \n", cam_type.c_str());
        ROS_INFO("Starting to publish images");

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

                sensor_msgs::Image &img_msg = *ros_img_ptr_; // message to be sent
                std_msgs::Header header; // empty header
                size_t img_size;

                // Read from camera
                CHECK_DW_ERROR(dwSensorCamera_readFrame(&frame, camera_sibling_id, timeout, camera_));

                CHECK_DW_ERROR(dwSensorCamera_getImageNvMedia(&nvmedia_yuv_img_ptr, DW_CAMERA_OUTPUT_NATIVE_PROCESSED, frame));
                CHECK_DW_ERROR(dwImage_createAndBindNvMedia(&frame_yuv, nvmedia_yuv_img_ptr->img));
                CHECK_DW_ERROR(dwImage_copyConvert(frame_resized_, frame_yuv, SDK_));
                CHECK_DW_ERROR(dwImage_getNvMedia(&nvmedia_rgb_img_ptr, frame_resized_));

                header.seq = count;
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
                    memcpy(&img_msg.data[0], buffer, img_size);
                    gmsl_pub_img_.publish(ros_img_ptr_);
                    NvMediaImageUnlock(nvmedia_rgb_img_ptr->img);
                }

                // Cleanup
                CHECK_DW_ERROR(dwImage_destroy(&frame_yuv));       
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
    po::options_description desc{"Options"};
    desc.add_options()
        ("help,h", "Help screen")
        ("camera-type", po::value<std::string>()-> default_value("ar0231-rccb-bae-sf3324"), 
            "camera gmsl type (see sample_sensors_info for all available camera types on this platform)\n")
        ("camera-port", po::value<std::string>()-> default_value("a"), "Camera CSI port [default a]\n"
                              "a - port AB on px2, A on ddpx\n"
                              "c - port CD on px2, C on ddpx\n"
                              "e - port EF on px2, E on ddpx\n"
                              "g - G on ddpx only\n")
        ("tegra-slave", po::value<std::string>()-> default_value("0"),
            "Optional parameter used only for Tegra B, enables slave mode.\n")
        ("custom-board", po::value<std::string>()-> default_value("0"), "If true, then the configuration for board and camera "
                              "will be input from the config-file\n")
        ("custom-config", po::value<std::string>()-> default_value(""), "Set of custom board extra configuration\n");

    po::variables_map args;
    po::store(parse_command_line(argc, argv, desc), args);
    po::notify(args);

    CameraGMSL cam(args);
    cam.publish();    

    return 0;
}
