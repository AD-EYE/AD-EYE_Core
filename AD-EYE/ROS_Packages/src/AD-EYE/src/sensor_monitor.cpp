#include <ros/ros.h>                      // ROS
#include <grid_map_ros/grid_map_ros.hpp>  // for ROS gridmap support
#include <string>                         // for string support
#include <cmath>                          // for math functions
#include <cmath>                          // for math functions
#include <dirent.h>                       // for directory search
#include <iostream>
#include <sensor_fov.h>

// ROS messages
#include <geometry_msgs/PolygonStamped.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/Image.h>
#include <jsk_recognition_msgs/PolygonArray.h>

// Used to define points of polygons
#include <geometry_msgs/Point32.h>


void SensorFoV::sensorUpdate(SENSOR_TYPE_ sensor_index){
    sensor_active_[sensor_index] = true;
    sensor_last_time_[sensor_index] = sensor_current_time_[sensor_index];
    sensor_current_time_[sensor_index] = ros::Time::now().toSec();
    sensor_time_elapsed_[sensor_index] = sensor_current_time_[sensor_index] - sensor_last_time_[sensor_index];
}

    /*!
     * \brief Radar Callback : called when information from the radar changed.
     * \param msg A smart pointer to the message from the topic.
     */
void SensorFoV::radarCallback(const std_msgs::Float32MultiArray::ConstPtr& msg){
    sensorUpdate(RADAR);
}

    /*!
     * \brief Lidar Callback : called when information from the lidar changed.
     * \param msg A smart pointer to the message from the topic.
     */
void SensorFoV::lidarCallback(const std_msgs::Float32MultiArray::ConstPtr& msg){
    sensorUpdate(LIDAR);
    // initialize the value of the parity loop
    even_loop_lidar_ = false;
    odd_loop_lidar_ = true;
}

    /*!
     * \brief Camera 1 Callback : called when information from the camera 1 changed.
     * \param msg A smart pointer to the message from the topic.
     */
void SensorFoV::camera1Callback(const sensor_msgs::Image::ConstPtr& msg){
    sensorUpdate(CAMERA1);
}

    /*!
     * \brief Camera 2 Callback : called when information from the camera 2 changed.
     * \param msg A smart pointer to the message from the topic.
     */
void SensorFoV::camera2Callback(const sensor_msgs::Image::ConstPtr& msg){
        sensorUpdate(CAMERA2);
}

    /*!
     * \brief camera tl Callback : called when information from the camera tl changed.
     * \param msg A smart pointer to the message from the topic.
     */
void SensorFoV::cameraTlCallback(const sensor_msgs::Image::ConstPtr& msg){
    sensorUpdate(CAMERATL);
    // initialize the value of the parity loop
    even_loop_cameratl_ = false;
    odd_loop_cameratl_ = true;
}

    /*!
     * \brief Polygon Creator : called when at least one sensor send information.
     * \details This function creates polygons corresponding to the sensor that send information, and stores them into
     * the sensor_fov_ array.
     */
void SensorFoV::polygonCreator(){
    for (int type = RADAR; type <= CAMERATL; type++)
    {
        // For each sensor, the polygon is created if information about this sensor is sent. If not, there will be
        // an empty polygon for this sensor.
        if (sensor_active_[type] || (type == LIDAR && even_loop_lidar_) ||
            (type == CAMERATL && even_loop_cameratl_))
        {
            // The polygon array is updated with each sensor polygon created.
            sensor_field_of_views_.polygons.at(type) =
                createCircleSection(SENSOR_POSITION_X_[type], SENSOR_POSITION_Y_[type], SENSOR_RANGES_[type],
                                        SENSOR_ORIENTATIONS_[type], SENSOR_OPENING_ANGLES_[type]);
            sensor_active_[type] = false;

            if (type == LIDAR){
                bool parity_storage;
                // exchange the value of parity loop for lidar
                parity_storage = even_loop_lidar_;
                even_loop_lidar_ = odd_loop_lidar_;
                odd_loop_lidar_ = parity_storage;
            }

            if (type == CAMERATL){
                bool parity_storage;
                // exchange the value of parity loop for camera tl
                parity_storage = even_loop_cameratl_;
                even_loop_cameratl_ = odd_loop_cameratl_;
                odd_loop_cameratl_ = parity_storage;
            }
        }
    }
}

    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initializes the node and its components such as publishers and subscribers.
     */
        SensorFoV::SensorFoV(ros::NodeHandle& nh) : nh_(nh), rate_(20){
            // Initialize node and publishers/subscribers
            pub_sensor_fovs_ = nh.advertise<jsk_recognition_msgs::PolygonArray>("/sensor_fov", 1);
            sub_radar_ = nh.subscribe<std_msgs::Float32MultiArray>("/radarDetections", 1, &SensorFoV::radarCallback, this);
            sub_lidar_ =
            nh.subscribe<std_msgs::Float32MultiArray>("/points_raw_float32", 1, &SensorFoV::lidarCallback, this);
            sub_camera_1_ = nh.subscribe<sensor_msgs::Image>("/camera_1/image_raw", 1, &SensorFoV::camera1Callback, this);
            sub_camera_2_ = nh.subscribe<sensor_msgs::Image>("/camera_2/image_raw", 1, &SensorFoV::camera2Callback, this);
            sub_camera_tl_ = nh.subscribe<sensor_msgs::Image>("/tl/image_raw", 1, &SensorFoV::cameraTlCallback, this);

        // The sensor sectors are set on the same frame than the car.
        sensor_field_of_views_.header.frame_id = "SSMP_base_link";
        }

    /*!
     * \brief The main function of the Node. Contains the main loop
     * \brief Basically, updates the sensor sectors, and then, publish.
     */
    void SensorFoV::run()
    {
        // Initialize current time and the time elapsed between 2 callbacks for sensors.
        float first_time = ros::Time::now().toSec();
        for (int i = RADAR; i <= CAMERATL; i++)
        {
            sensor_current_time_[i] = first_time;
        }
        // time elapsed is initialize this way because if a sensor is broken, the callback function will never be called
        // and no warning message will be sent.
        sensor_time_elapsed_[RADAR] = 2 * SENSOR_TIMEOUTS_[RADAR];
        sensor_time_elapsed_[LIDAR] = 2 * SENSOR_TIMEOUTS_[LIDAR];
        sensor_time_elapsed_[CAMERA1] = 2 * SENSOR_TIMEOUTS_[CAMERA1];
        sensor_time_elapsed_[CAMERA2] = 2 * SENSOR_TIMEOUTS_[CAMERA2];
        sensor_time_elapsed_[CAMERATL] = 2 * SENSOR_TIMEOUTS_[CAMERATL];

        // Main loop
        while (nh_.ok())
        {
            // Initialize the polygon array that will be published later
            // Definition of different sensor polygons.
            geometry_msgs::PolygonStamped radar_poly;
            geometry_msgs::PolygonStamped lidar_poly;
            geometry_msgs::PolygonStamped camera1_poly;
            geometry_msgs::PolygonStamped camera2_poly;
            geometry_msgs::PolygonStamped cameratl_poly;
            // The polygon array is filled with each sensor polygon.
            sensor_field_of_views_.polygons = { radar_poly, lidar_poly, camera1_poly, camera2_poly, cameratl_poly };

            ros::Time rostime = ros::Time::now();
            ros::spinOnce();

            // Update sensor polygons
            polygonCreator();

            ros::Duration rostime_elapsed = ros::Time::now() - rostime;
            if (rostime_elapsed > rate_.expectedCycleTime())
            {
                ROS_WARN("SensorFoV : frequency is not met!");
            }

            // Check if messages from sensors are received. Time elapsed is compared to 2 times the time period of the
            // sensor to have a margin of error.
            for (int sensor_index = RADAR; sensor_index <= CAMERATL; sensor_index++)
            {
                // Array that is useful to write the name in the warning message
                std::string SENSOR_NAME[NB_SENSORS_] = { "Radar", "Lidar", "Camera 1", "Camera 2",
                                                         "Camera traffic light" };
                if (sensor_time_elapsed_[sensor_index] > SENSOR_TIMEOUTS_[sensor_index])
                {
                    sensor_field_of_views_.polygons.at(sensor_index).polygon.points.clear();
                    ROS_WARN_STREAM("No message received from sensor " << SENSOR_NAME[sensor_index]);
                }
            }

            sensor_field_of_views_.header.stamp = ros::Time::now();
            pub_sensor_fovs_.publish(sensor_field_of_views_);

            rate_.sleep();
        }
    }


int main(int argc, char** argv)
{
    // init node
    ros::init(argc, argv, "SensorFoV");
    ros::NodeHandle nh;
    SensorFoV sfv(nh);
    sfv.run();
    return 0;
}