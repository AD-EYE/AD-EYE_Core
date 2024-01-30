#include <ros/ros.h>                      // ROS
#include <grid_map_ros/grid_map_ros.hpp>  // for ROS gridmap support
#include <string>                         // for string support
#include <cmath>                          // for math functions
#include <cmath>                          // for math functions
#include <dirent.h>                       // for directory search
#include <iostream>

// ROS messages
#include <geometry_msgs/PolygonStamped.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/Image.h>
#include <jsk_recognition_msgs/PolygonArray.h>

// Used to define points of polygons
#include <geometry_msgs/Point32.h>

#include <gtest/gtest.h>

#ifndef SENSORFOV_H
#define SENSORFOV_H

#define PI 3.1415
/*!
 * \brief The SensorFoV generates sectors representing sensors field of view.
 * \details Sensor sectors are sent to the gridmap creator to then visualize them.
 */
class SensorFoV
{
    private:
        FRIEND_TEST(SensorFoVTest,test_sensor_update);
    // friend class SensorFoVTest;
    // publishers and subscribers
        ros::NodeHandle& nh_;
        ros::Publisher pub_sensor_fovs_;
        ros::Subscriber sub_radar_;
        ros::Subscriber sub_lidar_;
        ros::Subscriber sub_camera_tl_;
        ros::Subscriber sub_camera_1_;
        ros::Subscriber sub_camera_2_;

        // Polygon Array that represent sensors field of view
        jsk_recognition_msgs::PolygonArray sensor_field_of_views_;

        // The number of sensors
        static const int NB_SENSORS_ = 5;

        // Enumeration of all the sensors types.
        enum SENSOR_TYPE_
        {
            RADAR,
            LIDAR,
            CAMERA1,
            CAMERA2,
            CAMERATL
        };

        // The following arrays contain information about sensors in this order [radar, lidar, camera1, camera2, cameratl].
        const float SENSOR_RANGES_[NB_SENSORS_] = { 30, 100, 750, 750, 750 };  // Beam ranges of the sectors in meter,
                                                                           // values obtained in PreScan.
        const float SENSOR_ORIENTATIONS_[NB_SENSORS_] = { 0, 0, 0, PI, -15 * PI / 180 };  // Orientations of the sectors
                                                                                        // compared to the ego car in rad,
                                                                                        // values obtained in PreScan.
        const float SENSOR_OPENING_ANGLES_[NB_SENSORS_] = {
            45.0 * PI / 180.0, 2 * PI, 46.21 * PI / 180.0, 46.21 * PI / 180.0, 46.21 * PI / 180.0
        };  // Opening angles of the sectors in rad, values obtained in PreScan.
        const float SENSOR_POSITION_X_[NB_SENSORS_] = {
            2.3, -0.66, 0.55, -2.21, -0.16
        };  // x coordinates of the sensors positions in the ego car in meter, values obtained in PreScan.
        const float SENSOR_POSITION_Y_[NB_SENSORS_] = { 0, 0, 0, 0, -0.7 };  // y coordinates of the sensors positions in
                                                                            // the ego car in meter, values obtained in
                                                                            // PreScan.
        bool sensor_active_[NB_SENSORS_] = { false, false, false, false,
                                            false };  // Indicates if sensors information have changed.
        // The timeouts of the sensors are the following : 0.05s (radar), 0.1s (lidar), 0.05s (camera 1), 0.05s (camera 2),
        // 0.1s (camera tl).
        // When the time between 2 messages received from the sensors will be compared to the sensor timeouts, a margin of
        // error will be taken.
        // The time elapsed will be compared to 3 times the sensor timeouts.
        const float SENSOR_TIMEOUTS_[NB_SENSORS_] = { 0.15, 0.3, 0.15, 0.15,
                                                    0.3 };       // Time period in seconds, values obtained in PreScan.
        float sensor_last_time_[NB_SENSORS_] = { 0, 0, 0, 0, 0 };  // The last time the callback function has been called.
        float sensor_current_time_[NB_SENSORS_];                   // The current time when the callback function is called.
        float sensor_time_elapsed_[NB_SENSORS_];                   // The time elapsed between two callbacks.

        // Ros utils
        ros::Rate rate_;

        // The frequencies of lidar and camera for traffic lights are twice less than other sensors frequencies so they are
        // called once on 2
        bool even_loop_lidar_;
        bool odd_loop_lidar_;
        bool even_loop_cameratl_;
        bool odd_loop_cameratl_;

        /*!
        * \brief Sensor Update: called when a sensor is activated
        * \param sensor_index The type of sensor that needs to be updated.
        * \details This function changes the value of sensor_active for the corresponding sensor to then update the sensor
        * polygon.
        */
        void sensorUpdate(SENSOR_TYPE_ sensor_index);

        /*!
        * \brief Radar Callback : called when information from the radar changed.
        * \param msg A smart pointer to the message from the topic.
        */
        void radarCallback(const std_msgs::Float32MultiArray::ConstPtr& msg);

        /*!
        * \brief Lidar Callback : called when information from the lidar changed.
        * \param msg A smart pointer to the message from the topic.
        */
        void lidarCallback(const std_msgs::Float32MultiArray::ConstPtr& msg);

        /*!
        * \brief Camera 1 Callback : called when information from the camera 1 changed.
        * \param msg A smart pointer to the message from the topic.
        */
        void camera1Callback(const sensor_msgs::Image::ConstPtr& msg);

        /*!
        * \brief Camera 2 Callback : called when information from the camera 2 changed.
        * \param msg A smart pointer to the message from the topic.
        */
        void camera2Callback(const sensor_msgs::Image::ConstPtr& msg);

        /*!
        * \brief camera tl Callback : called when information from the camera tl changed.
        * \param msg A smart pointer to the message from the topic.
        */
        void cameraTlCallback(const sensor_msgs::Image::ConstPtr& msg);

        /*!
        * \brief Polygon Creator : called when at least one sensor send information.
        * \details This function creates polygons corresponding to the sensor that send information, and stores them into
        * the sensor_fov_ array.
        */
        void polygonCreator();

        /*!
        * \brief This function creates a circle section.
        * \param x x coordinate of the center location compared to the car.
        * \param y y coordinate of the center location compared to the car.
        * \param radius Sensor beam range in meter.
        * \param orientation Orientation of the section compared to the car, seen from above.
        * \param angle Opening angle of the section.
        * \return A circle section created corresponding to the given parameters.
        * \details This function is especially used to create sensor sectors around the car.
        * The circle section will be approximate by a succession of points close enough.
        * Angles need to be in rad.
        */
        geometry_msgs::PolygonStamped createCircleSection(float x, float y, float radius, float orientation, float angle){
            geometry_msgs::PolygonStamped polygon;
            float d_angle = 0.0017;  // The angle step for the succession of points. Random choice: 0.1 deg = 0.0017rad.
            polygon.header.frame_id = "SSMP_base_link";
            // Definition of the apex of the section that will be added to the polygon.
            geometry_msgs::Point32 apex;
            apex.x = x;
            apex.y = y;
            polygon.polygon.points.emplace_back(apex);
            for (float i = (orientation - (angle / 2.0)); i <= (orientation + (angle / 2.0)); i = i + d_angle)
            {  // Approximate circle section by a succession of points
            // Definition of the points that will be added to the polygon.
                geometry_msgs::Point32 point;
                point.x = x + radius * cos(i);
                point.y = y + radius * sin(i);
                polygon.polygon.points.emplace_back(point);
            }
            if (fmodf(angle, d_angle) != 0)
            {  // If the discretization of the circle section with the step d_angle doesn't fall right, we add the last
            // point.
            // Definition of the point that will be added to the polygon.
                geometry_msgs::Point32 last_point;
                last_point.x = x + radius * cos(orientation + (angle / 2.0));
                last_point.y = y + radius * sin(orientation + (angle / 2.0));
                polygon.polygon.points.emplace_back(last_point);
            }
            return polygon;
        } 

    public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initializes the node and its components such as publishers and subscribers.
     */
        SensorFoV(ros::NodeHandle& nh);

    /*!
     * \brief The main function of the Node. Contains the main loop
     * \brief Basically, updates the sensor sectors, and then, publish.
     */
        void run();
};

#endif