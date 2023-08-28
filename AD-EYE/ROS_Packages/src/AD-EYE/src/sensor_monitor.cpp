#include <ros/ros.h>                      // ROS
#include <grid_map_ros/grid_map_ros.hpp>  // for ROS gridmap support
#include <string>                         // for string support
#include <cmath>                          // for math functions
#include <cmath>                          // for math functions
#include <dirent.h>                       // for directory search

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
    static const int NB_SENSORS_ = 2;

    // Enumeration of all the sensors types.
    enum SENSOR_TYPE_
    {
        LIDAR,
        CAMERA1
    };

    // The following arrays contain information about sensors in this order [radar, lidar, camera1].
    const float SENSOR_RANGES_[NB_SENSORS_] = {100, 750};  // Beam ranges of the sectors in meter,
                                                                           // values obtained in PreScan.
    const float SENSOR_ORIENTATIONS_[NB_SENSORS_] = {0, 0};  // Orientations of the sectors
                                                                                      // compared to the ego car in rad,
                                                                                      // values obtained in PreScan.
    const float SENSOR_OPENING_ANGLES_[NB_SENSORS_] = {
        2 * PI, 46.21 * PI / 180.0
    };  // Opening angles of the sectors in rad, values obtained in PreScan.
    const float SENSOR_POSITION_X_[NB_SENSORS_] = {
        -0.66, 0.55
    };  // x coordinates of the sensors positions in the ego car in meter, values obtained in PreScan.
    const float SENSOR_POSITION_Y_[NB_SENSORS_] = {0, 0};  // y coordinates of the sensors positions in
                                                                         // the ego car in meter, values obtained in
                                                                         // PreScan.
    bool sensor_active_[NB_SENSORS_] = { false, false
                                        };  // Indicates if sensors information have changed.
    // The timeouts of the sensors are the following : 0.05s (radar), 0.1s (lidar), 0.05s (camera 1).
    // When the time between 2 messages received from the sensors will be compared to the sensor timeouts, a margin of
    // error will be taken.
    // The time elapsed will be compared to 3 times the sensor timeouts.
    const float SENSOR_TIMEOUTS_[NB_SENSORS_] = { 0.3, 0.15
    };       // Time period in seconds, values obtained in PreScan.
    float sensor_last_time_[NB_SENSORS_] = { 0, 0};  // The last time the callback function has been called.
    float sensor_current_time_[NB_SENSORS_];                   // The current time when the callback function is called.
    float sensor_time_elapsed_[NB_SENSORS_];                   // The time elapsed between two callbacks.

    // Ros utils
    ros::Rate rate_;

    // The frequencies of lidar and camera for traffic lights are twice less than other sensors frequencies so they are
    // called once on 2
    bool even_loop_lidar_;
    bool odd_loop_lidar_;

    /*!
     * \brief Sensor Update: called when a sensor is activated
     * \param sensor_index The type of sensor that needs to be updated.
     * \details This function changes the value of sensor_active for the corresponding sensor to then update the sensor
     * polygon.
     */
    void sensorUpdate(SENSOR_TYPE_ sensor_index)
    {
        sensor_active_[sensor_index] = true;
        sensor_last_time_[sensor_index] = sensor_current_time_[sensor_index];
        sensor_current_time_[sensor_index] = ros::Time::now().toSec();
        sensor_time_elapsed_[sensor_index] = sensor_current_time_[sensor_index] - sensor_last_time_[sensor_index];
    }

    /*!
     * \brief Radar Callback : called when information from the radar changed.
     * \param msg A smart pointer to the message from the topic.
     */
/*     void radarCallback(const std_msgs::Float32MultiArray::ConstPtr& msg)
    {
        sensorUpdate(RADAR);
    } */

    /*!
     * \brief Lidar Callback : called when information from the lidar changed.
     * \param msg A smart pointer to the message from the topic.
     */
    void lidarCallback(const std_msgs::Float32MultiArray::ConstPtr& msg)
    {
        sensorUpdate(LIDAR);
        // initialize the value of the parity loop
        even_loop_lidar_ = false;
        odd_loop_lidar_ = true;
    }

    /*!
     * \brief Camera 1 Callback : called when information from the camera 1 changed.
     * \param msg A smart pointer to the message from the topic.
     */
    void camera1Callback(const sensor_msgs::Image::ConstPtr& msg)
    {
        sensorUpdate(CAMERA1);
    }

    /*!
     * \brief Polygon Creator : called when at least one sensor send information.
     * \details This function creates polygons corresponding to the sensor that send information, and stores them into
     * the sensor_fov_ array.
     */
    void polygonCreator()
    {
        for (int type = LIDAR; type <= CAMERA1; type++)
        {
            // For each sensor, the polygon is created if information about this sensor is sent. If not, there will be
            // an empty polygon for this sensor.
            if (sensor_active_[type] || (type == LIDAR && even_loop_lidar_))
            {
                // The polygon array is updated with each sensor polygon created.
                sensor_field_of_views_.polygons.at(type) =
                    createCircleSection(SENSOR_POSITION_X_[type], SENSOR_POSITION_Y_[type], SENSOR_RANGES_[type],
                                        SENSOR_ORIENTATIONS_[type], SENSOR_OPENING_ANGLES_[type]);
                sensor_active_[type] = false;

                if (type == LIDAR)
                {
                    bool parity_storage;
                    // exchange the value of parity loop for lidar
                    parity_storage = even_loop_lidar_;
                    even_loop_lidar_ = odd_loop_lidar_;
                    odd_loop_lidar_ = parity_storage;
                }
            }
        }
    }

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
    geometry_msgs::PolygonStamped createCircleSection(float x, float y, float radius, float orientation, float angle)
    {
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
    SensorFoV(ros::NodeHandle& nh) : nh_(nh), rate_(20)
    {
        // Initialize node and publishers/subscribers
        pub_sensor_fovs_ = nh.advertise<jsk_recognition_msgs::PolygonArray>("/sensor_fov", 1);
        sub_lidar_ =
            nh.subscribe<std_msgs::Float32MultiArray>("/points_raw_float32", 1, &SensorFoV::lidarCallback, this);
        sub_camera_1_ = nh.subscribe<sensor_msgs::Image>("/camera_1/image_raw", 1, &SensorFoV::camera1Callback, this);
        // The sensor sectors are set on the same frame than the car.
        sensor_field_of_views_.header.frame_id = "SSMP_base_link";
    }

    /*!
     * \brief The main function of the Node. Contains the main loop
     * \brief Basically, updates the sensor sectors, and then, publish.
     */
    void run()
    {
        // Initialize current time and the time elapsed between 2 callbacks for sensors.
        float first_time = ros::Time::now().toSec();
        for (int i = LIDAR; i <= CAMERA1; i++)
        {
            sensor_current_time_[i] = first_time;
        }
        // time elapsed is initialize this way because if a sensor is broken, the callback function will never be called
        // and no warning message will be sent.
        sensor_time_elapsed_[LIDAR] = 2 * SENSOR_TIMEOUTS_[LIDAR];
        sensor_time_elapsed_[CAMERA1] = 2 * SENSOR_TIMEOUTS_[CAMERA1];

        // Main loop
        while (nh_.ok())
        {
            // Initialize the polygon array that will be published later
            // Definition of different sensor polygons.
            // geometry_msgs::PolygonStamped radar_poly;
            geometry_msgs::PolygonStamped lidar_poly;
            geometry_msgs::PolygonStamped camera1_poly;
            //geometry_msgs::PolygonStamped camera2_poly;
            //geometry_msgs::PolygonStamped cameratl_poly;
            // The polygon array is filled with each sensor polygon.
            sensor_field_of_views_.polygons = { lidar_poly, camera1_poly};

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
            for (int sensor_index = LIDAR; sensor_index <= CAMERA1; sensor_index++)
            {
                // Array that is useful to write the name in the warning message
                std::string SENSOR_NAME[NB_SENSORS_] = { "Lidar", "Camera 1"};
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
};

int main(int argc, char** argv)
{
    // init node
    ros::init(argc, argv, "SensorFoV");
    ros::NodeHandle nh;
    SensorFoV sfv(nh);
    sfv.run();
    return 0;
}