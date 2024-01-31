#include <gtest/gtest.h>
#include <sensor_fov.h>
#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
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

static int argc_;
static char** argv_;

 /*!
* \brief SensorFoVTest: this class will test class SensorFoV.
* \details Use TEST_F(test fixture) to setup and tear down object and run several tests with one object.
*/

class SensorFoVTest : public::testing::Test
{
public:
    SensorFoV *my_sfv;
    void SetUp(){
        ros::init(argc_, argv_, "SensorFoV_Test");
        ros::NodeHandle nh_;
        my_sfv = new SensorFoV(nh_);
    };
    void TearDown(){
        delete my_sfv;
    };
};


TEST_F(SensorFoVTest, test_sensor_update){
    my_sfv->sensorUpdate(SensorFoV::SENSOR_TYPE_::RADAR);
    ASSERT_TRUE(my_sfv->sensor_active_[SensorFoV::SENSOR_TYPE_::RADAR]);
}

int main(int argc, char** argv){
    argc_ = argc;
    argv_ = argv;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}