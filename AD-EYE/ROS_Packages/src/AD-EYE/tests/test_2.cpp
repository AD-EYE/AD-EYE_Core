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


void SensorFoV::sensorUpdate(SENSOR_TYPE_ sensor_index){
    sensor_active_[sensor_index] = true;
}

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

//TEST_F(SensorFoVTest, test_sensor_update){
//    my_sfv->sensorUpdate(SensorFoV::SENSOR_TYPE_::RADAR);
//    ASSERT_TRUE(my_sfv->sensor_active_[SensorFoV::SENSOR_TYPE_::RADAR]);
//}

TEST_F(SensorFoVTest, test_sensor_update){
    my_sfv->sensorUpdate(SensorFoV::SENSOR_TYPE_::RADAR);
    ASSERT_TRUE(my_sfv->sensor_active_[SensorFoV::SENSOR_TYPE_::RADAR]);
}

int main(int argc, char** argv){
    argc_ = argc;
    argv_ = argv;
    //ros::init(argc, argv, "SensorFoV_Test");
    testing::InitGoogleTest(&argc, argv);
    //testing::GTEST_FLAG(filter)="SensorFoVTest";
    return RUN_ALL_TESTS();

}