#include <ros/ros.h> // ROS
#include <grid_map_ros/grid_map_ros.hpp> // for ROS gridmap support
#include <string> // for string support
#include <cmath> // for math functions
#include <cmath> // for math functions
#include <dirent.h> // for directory search

#include <cpp_utils/pose_datatypes.h> // for cpp_utils::extract_yaw

// ROS messages
#include <geometry_msgs/PolygonStamped.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/Image.h>
#include <jsk_recognition_msgs/PolygonArray.h>

#include <tf/transform_broadcaster.h>

using namespace grid_map;

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

    //Ego car dimensions
    float length_ego_ = 4.6;

    jsk_recognition_msgs::PolygonArray sensor_fov_;

    enum sensor_type_ {radar, lidar, camera1, camera2, cameratl};

    //Following lists contains information of sensor in this order [radar, lidar, camera1, camera2, cameratl].
    float sensor_timeouts_[5] = {0.05, 0.1, 0.05, 0.05, 0.10}; //Frequency values get in PreScan.
    float sensor_ranges_[5] = {30, 100, 750, 750, 750}; //Beam range of the sectors, values get in PreScan, in meter.
    float sensor_orientations_[5] = {0, 0, 0, PI, -15 * PI / 180}; //Orientation of the sectors compared to the ego car, values get in PreScan, in rad.
    float sensor_opening_angles_[5] = {45.0 * PI / 180.0, 2 * PI, 46.21 * PI / 180.0, 46.21 * PI / 180.0, 46.21 * PI / 180.0}; //Opening angle of the sectors, values get in PreScan, in rad.
    float sensor_pos_x_[5] = {2.3, -0.66, 0.55, -2.21, -0.16}; //x coordinate of the sensor position in the ego car, values get in PreScan, in meter.
    float sensor_pos_y_[5] = {0, 0, 0, 0, -0.7}; //y coordinate of the sensor position in the ego car, values get in PreScan, in meter.
    bool sensor_active_[5] = {false, false, false, false, false}; //Indicates if sensor information are well received.
    grid_map::Polygon sensor_sectors_[5]; // Polygons which represent sensor sectors.

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
     * \details This function takes radar information to create an area according to the parameters.
     */
    void radarCallback(const std_msgs::Float32MultiArray::ConstPtr& msg) {
        // check if information are received
        sensor_active_[radar_] = true;
    }

    /*!
     * \brief Lidar Callback : called when information from the lidar changed.
     * \param msg A smart pointer to the message from the topic.
     * \details This function takes lidar information to create an area according to the parameters.
     */
    void lidarCallback(const std_msgs::Float32MultiArray::ConstPtr& msg) {
        // check if information are received
        sensor_active_[lidar_] = true;
    }

    /*!
     * \brief Camera 1 Callback : called when information from the camera 1 changed.
     * \param msg A smart pointer to the message from the topic.
     * \details This function takes camera 1 information to create an area according to the parameters.
     */
    void camera1Callback(const sensor_msgs::Image::ConstPtr& msg){
        // check if information are received
        sensor_active_[camera1_] = true;
    }

    /*!
     * \brief Camera 2 Callback : called when information from the camera 2 changed.
     * \param msg A smart pointer to the message from the topic.
     * \details This function takes camera 1 information to create an area according to the parameters.
     */
    void camera2Callback(const sensor_msgs::Image::ConstPtr& msg){
        // check if information are received
        sensor_active_[camera2_] = true;
    }

    /*!
     * \brief camera tl Callback : called when information from the camera tl changed.
     * \param msg A smart pointer to the message from the topic.
     * \details This function takes camera tl information to create an area according to the parameters.
     */
    void cameraTlCallback(const sensor_msgs::Image::ConstPtr& msg){
        // check if information are received
        sensor_active_[cameratl_] = true;
    }

    /*!
     * \brief Polygon Creator : called when at least one sensor send information.
     * \details This function creates polygons corresponding to the sensor that send information
     */
    void polygonCreator() {
        
        //If the message is received, the corresponding polygon is created
        if(sensor_active_[radar_])
        {
            sensor_sectors_[radar_] = circle_section_creator(sensor_pos_x_[radar_], sensor_pos_y_[radar_], sensor_ranges_[radar_], sensor_orientations_[radar_], sensor_opening_angles_[radar_]);
            sensor_active_[radar_] = false;
        }
        if(sensor_active_[lidar_])
        {
            sensor_sectors_[lidar_] = circle_section_creator(sensor_pos_x_[lidar_], sensor_pos_y_[lidar_], sensor_ranges_[lidar_], sensor_orientations_[lidar_], sensor_opening_angles_[lidar_]);
            sensor_active_[lidar_] = false;
        }
        if(sensor_active_[camera1_])
        {
            sensor_sectors_[camera1_] = circle_section_creator(sensor_pos_x_[camera1_], sensor_pos_y_[camera1_], sensor_ranges_[camera1_], sensor_orientations_[camera1_], sensor_opening_angles_[camera1_]);
            sensor_active_[camera1_] = false;
        }
        if(sensor_active_[camera2_])
        {
            sensor_sectors_[camera2_] = circle_section_creator(sensor_pos_x_[camera2_], sensor_pos_y_[camera2_], sensor_ranges_[camera2_], sensor_orientations_[camera2_], sensor_opening_angles_[camera2_]);
            sensor_active_[camera2_] = false;
        }
        if(sensor_active_[cameratl_])
        {
            sensor_sectors_[cameratl_] = circle_section_creator(sensor_pos_x_[cameratl_], sensor_pos_y_[cameratl_], sensor_ranges_[cameratl_], sensor_orientations_[cameratl_], sensor_opening_angles_[cameratl_]);
            sensor_active_[cameratl_] = false;
        }
    }

    /*!
     * \brief This function creates a circle section in the gridmap.
     * \param x x coordinate of the center location in the gridmap.
     * \param y y coordinate of the center location in the gridmap.
     * \param radius Sensor beam range in meter.
     * \param orientation Orientation of the section, seen from above.
     * \param angle Openning angle of the section.
     * \return A circle section created corresponding to the given parameters.
     * \details This function is especially used to create sensor sectors arround the car.
     * The circle section will be approximate by a succession of points close enought.
     * Angles need to be in rad.
     */
    grid_map::Polygon circle_section_creator(float x, float y, float radius, float orientation, float angle) {
        grid_map::Polygon polygon;
        float dangle = 0.0017; //the angle step for the succession of points. Random choice: 0.1 deg = 0.0017rad.
        polygon.setFrameId("SSMP_base_link");
        polygon.addVertex(Position(x, y));
        
        for (float i = (orientation - (angle / 2.0)); i <= (orientation + (angle / 2.0)); i=i+dangle){ //approximate circle section by a succession of points
                polygon.addVertex(Position(x + radius * cos(i), y + radius * sin(i)));
        } 

        if (fmodf(angle, dangle) != 0) { //if the discretion of the circle section by step doesn't fall right, we add the last point
            polygon.addVertex(Position(x + radius * cos(orientation + (angle / 2.0)), y + radius * sin(orientation + (angle / 2.0))));
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

        sensor_fov_.header.frame_id = "SSMP_base_link"; //The sensor sectors are set on the same frame than the car.

    }

    /*!
     * \brief The main function of the Node. Contains the main loop
     * \brief Basically, updates the sensor sectors with the position of the
     * car, and then, publish.
     */
    void run() {

        //Main loop
        while (nh_.ok()) {
            ros::Time rostime = ros::Time::now();
            ros::spinOnce();

            if(sensor_active_[radar_] || sensor_active_[lidar_] || sensor_active_[camera1_] || sensor_active_[camera2_] || sensor_active_[cameratl_])
            {
                // Update sensor layer
                polygonCreator();                                
            }

            // publish

            sensor_fov_.header.stamp = ros::Time::now();
            pub_sensor_fov_.publish(sensor_fov_);

            ros::Duration rostime_elapsed = ros::Time::now() - rostime;
            if(rostime_elapsed > rate_.expectedCycleTime()){
                ROS_WARN("SensorFoV : frequency is not met!");
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