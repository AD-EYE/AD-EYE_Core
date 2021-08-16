#include <ros/ros.h> // ROS
#include <grid_map_ros/grid_map_ros.hpp> // for ROS gridmap support
#include <string> // for string support
#include <cmath> // for math functions
#include <cmath> // for math functions
#include <dirent.h> // for directory search

// ROS messages
#include <geometry_msgs/PolygonStamped.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/Image.h>
#include <jsk_recognition_msgs/PolygonArray.h>

// Used to define points of polygons
#include <geometry_msgs/Point32.h>

#define PI 3.1415

/*!
 * \brief The SensorFoV generates sectors representing sensors field of view.
 * \details Sensor sectors are sent to the gridmap creator to then visualize them.
 */
class SensorFoV
{
private:
    // publishers and subscribers
    ros::NodeHandle &nh_;
    ros::Publisher pub_sensor_fov_;
    ros::Subscriber sub_radar_;
    ros::Subscriber sub_lidar_;
    ros::Subscriber sub_camera_tl_;
    ros::Subscriber sub_camera_1_;
    ros::Subscriber sub_camera_2_;

    //Polygon Array that represent sensors field of view
    jsk_recognition_msgs::PolygonArray sensor_fov_;

    // The number of sensors
    static const int NB_SENSORS_ = 5;

    // Enumeration useful to have an easy access to indexes of following arrays.
    enum sensor_type_ {radar, lidar, camera1, camera2, cameratl};

    // The following arrays contain information about sensors in this order [radar, lidar, camera1, camera2, cameratl].
    const float SENSOR_TIMEOUTS_[NB_SENSORS_] = {0.05, 0.1, 0.05, 0.05, 0.10}; // Time period in seconds, values obtained in PreScan.
    const float SENSOR_RANGES_[NB_SENSORS_] = {30, 100, 750, 750, 750}; // Beam ranges of the sectors in meter, values obtained in PreScan.
    const float SENSOR_ORIENTATIONS_[NB_SENSORS_] = {0, 0, 0, PI, -15 * PI / 180}; // Orientations of the sectors compared to the ego car in rad, values obtained in PreScan.
    const float SENSOR_OPENING_ANGLES_[NB_SENSORS_] = {45.0 * PI / 180.0, 2 * PI, 46.21 * PI / 180.0, 46.21 * PI / 180.0, 46.21 * PI / 180.0}; // Opening angles of the sectors in rad, values obtained in PreScan.
    const float SENSOR_POS_X_[NB_SENSORS_] = {2.3, -0.66, 0.55, -2.21, -0.16}; // x coordinates of the sensors positions in the ego car in meter, values obtained in PreScan.
    const float SENSOR_POS_Y_[NB_SENSORS_] = {0, 0, 0, 0, -0.7}; // y coordinates of the sensors positions in the ego car in meter, values obtained in PreScan.
    bool sensor_active_[NB_SENSORS_] = {false, false, false, false, false}; // Indicates if sensors information have changed.

    //Names for indexes in lists
    sensor_type_ radar_ = radar;
    sensor_type_ lidar_ = lidar;
    sensor_type_ camera1_ = camera1;
    sensor_type_ camera2_ = camera2;
    sensor_type_ cameratl_ = cameratl;

    //Ros utils
    ros::Rate rate_;

    /*!
     * \brief Radar Callback : called when information from the radar changed.
     * \param msg A smart pointer to the message from the topic.
     * \details This function changes the value of sensor_active for the radar to then update the radar polygon.
     */
    void radarCallback(const std_msgs::Float32MultiArray::ConstPtr& msg) {
        sensor_active_[radar_] = true;
    }

    /*!
     * \brief Lidar Callback : called when information from the lidar changed.
     * \param msg A smart pointer to the message from the topic.
     * \details This function changes the value of sensor_active for the lidar to then update the lidar polygon.
     */
    void lidarCallback(const std_msgs::Float32MultiArray::ConstPtr& msg) {
        sensor_active_[lidar_] = true;
    }

    /*!
     * \brief Camera 1 Callback : called when information from the camera 1 changed.
     * \param msg A smart pointer to the message from the topic.
     * \details This function changes the value of sensor_active for the camera 1 to then update the camera 1 polygon.
     */
    void camera1Callback(const sensor_msgs::Image::ConstPtr& msg){
        sensor_active_[camera1_] = true;
    }

    /*!
     * \brief Camera 2 Callback : called when information from the camera 2 changed.
     * \param msg A smart pointer to the message from the topic.
     * \details This function changes the value of sensor_active for the camera 2 to then update the camera2 polygon.
     */
    void camera2Callback(const sensor_msgs::Image::ConstPtr& msg){
        sensor_active_[camera2_] = true;
    }

    /*!
     * \brief camera tl Callback : called when information from the camera tl changed.
     * \param msg A smart pointer to the message from the topic.
     * \details This function changes the value of sensor_active for the camera tl to then update the camera tl polygon.
     */
    void cameraTlCallback(const sensor_msgs::Image::ConstPtr& msg){
        sensor_active_[cameratl_] = true;
    }

    /*!
     * \brief Polygon Creator : called when at least one sensor send information.
     * \details This function creates polygons corresponding to the sensor that send information, and stores them into the sensor_fov_ array.
     */
    void polygonCreator() {
        // Definition of different polygons.
        geometry_msgs::PolygonStamped radar_poly;
        geometry_msgs::PolygonStamped lidar_poly;
        geometry_msgs::PolygonStamped camera1_poly;
        geometry_msgs::PolygonStamped camera2_poly;
        geometry_msgs::PolygonStamped cameratl_poly;

        // The polygon array is filled with each sensor polygon.
        sensor_fov_.polygons = {radar_poly, lidar_poly, camera1_poly, camera2_poly, cameratl_poly};

        for(int type = radar; type <= cameratl; type++) {
            // For each sensor, the polygon is created if information about this sensor has changed.
            if(sensor_active_[type]) {
                // The polygon array is updated with each sensor polygon created.
                sensor_fov_.polygons.at(type) = circle_section_creator(SENSOR_POS_X_[type], SENSOR_POS_Y_[type], SENSOR_RANGES_[type], SENSOR_ORIENTATIONS_[type], SENSOR_OPENING_ANGLES_[type]);
            }
        }
    }

    /*!
     * \brief This function creates a circle section.
     * \param x x coordinate of the center location compared to the car.
     * \param y y coordinate of the center location compared to the car.
     * \param radius Sensor beam range in meter.
     * \param orientation Orientation of the section compared to the car, seen from above.
     * \param angle Openning angle of the section.
     * \return A circle section created corresponding to the given parameters.
     * \details This function is especially used to create sensor sectors arround the car.
     * The circle section will be approximate by a succession of points close enough.
     * Angles need to be in rad.
     */
    geometry_msgs::PolygonStamped circle_section_creator(float x, float y, float radius, float orientation, float angle) {
        geometry_msgs::PolygonStamped polygon;
        float dangle = 0.0017; // The angle step for the succession of points. Random choice: 0.1 deg = 0.0017rad.
        polygon.header.frame_id = "SSMP_base_link";
        // Definition of the point that will be added to the polygon.
        geometry_msgs::Point32 point1;
        point1.x = x;
        point1.y = y;
        polygon.polygon.points.emplace_back(point1);
        for (float i = (orientation - (angle / 2.0)); i <= (orientation + (angle / 2.0)); i=i+dangle){ // Approximate circle section by a succession of points
            // Definition of the points that will be added to the polygon.
            geometry_msgs::Point32 point2;
            point2.x = x + radius * cos(i);
            point2.y = y + radius * sin(i);
            polygon.polygon.points.emplace_back(point2);
        } 

        if (fmodf(angle, dangle) != 0) { // If the discretion of the circle section by step doesn't fall right, we add the last point.
            // Definition of the point that will be added to the polygon.
            geometry_msgs::Point32 point3;
            point3.x = x + radius * cos(orientation + (angle / 2.0));
            point3.y = y + radius * sin(orientation + (angle / 2.0));
            polygon.polygon.points.emplace_back(point3);
        }

        return polygon;
    }

public:

    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initializes the node and its components such as publishers and subscribers.
     */
    SensorFoV(ros::NodeHandle& nh) : nh_(nh), rate_(1)
    {
        // Initialize node and publishers/subscribers
        pub_sensor_fov_ = nh.advertise<jsk_recognition_msgs::PolygonArray>("/sensor_fov", 1);
        sub_radar_ = nh.subscribe<std_msgs::Float32MultiArray>("/radarDetections", 1, &SensorFoV::radarCallback, this);
        sub_lidar_ = nh.subscribe<std_msgs::Float32MultiArray>("/points_raw_float32", 1, &SensorFoV::lidarCallback, this);
        sub_camera_1_ = nh.subscribe<sensor_msgs::Image>("/camera_1/image_raw", 1, &SensorFoV::camera1Callback, this);
        sub_camera_2_ = nh.subscribe<sensor_msgs::Image>("/camera_2/image_raw", 1, &SensorFoV::camera2Callback, this);
        sub_camera_tl_ = nh.subscribe<sensor_msgs::Image>("/tl/image_raw", 1, &SensorFoV::cameraTlCallback, this);

        rate_ = ros::Rate(20);

        //The sensor sectors are set on the same frame than the car.
        sensor_fov_.header.frame_id = "SSMP_base_link"; 

    }

    /*!
     * \brief The main function of the Node. Contains the main loop
     * \brief Basically, updates the sensor sectors, and then, publish.
     */
    void run() {

        //Main loop
        while (nh_.ok()) {
            ros::Time rostime = ros::Time::now();
            ros::spinOnce();
            
            ros::Duration rostime_elapsed_sensors = ros::Time::now() - rostime;

            if(sensor_active_[radar_] || sensor_active_[lidar_] || sensor_active_[camera1_] || sensor_active_[camera2_] || sensor_active_[cameratl_])
            {
                // Update sensor layer
                polygonCreator();                                
            }

            sensor_fov_.header.stamp = ros::Time::now();
            pub_sensor_fov_.publish(sensor_fov_);

            ros::Duration rostime_elapsed = ros::Time::now() - rostime;
            if(rostime_elapsed > rate_.expectedCycleTime()){
                ROS_WARN("SensorFoV : frequency is not met!");
            }

            // Check if messages from sensors are received. Time elapsed is compared to 2 times the time period of the sensor to have a margin of error.
            float time_elapsed_sensors = rostime_elapsed_sensors.toNSec();
            if(time_elapsed_sensors > (2 * SENSOR_TIMEOUTS_[radar_])){
                ROS_WARN("Radar : Message not received!");
            }
            if(time_elapsed_sensors > (2 * SENSOR_TIMEOUTS_[lidar_])){
                ROS_WARN("Lidar : Message not received!");
            }
            if(time_elapsed_sensors > (2 * SENSOR_TIMEOUTS_[camera1_])){
                ROS_WARN("Camera 1 : Message not received!");
            }
            if(time_elapsed_sensors > (2 * SENSOR_TIMEOUTS_[camera2_])){
                ROS_WARN("Camera 2 : Message not received!");
            }
            if(time_elapsed_sensors > (2 * SENSOR_TIMEOUTS_[cameratl_])){
                ROS_WARN("Camera tl : Message not received!");
            }

            rate_.sleep();

        }
    }
};

int main(int argc, char **argv)
{
    if(argc < 1) {
        exit(EXIT_FAILURE);
    }

    // init node
    ros::init(argc, argv, "SensorFoV");
    ros::NodeHandle nh;
    SensorFoV sfv(nh);
    sfv.run();
    return 0;
}