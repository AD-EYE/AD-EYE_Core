//
// Created by adeye on 2021-10-11.
//

#include "safety_fault_monitors/sensor_checker.h"

SensorChecker::SensorChecker(int increment_value, int decrement_value, int high_threshold, int low_threshold,
                             SENSOR_TYPE sensor_to_monitor)
  : SafetyFaultMonitor(increment_value, decrement_value, high_threshold, low_threshold)
  , sensor_to_monitor_(sensor_to_monitor)
{
    sub_sensor_fov_ = nh_.subscribe("/sensor_fov", 1, &SensorChecker::sensorFovCallback, this);
}

void SensorChecker::sensorFovCallback(const jsk_recognition_msgs::PolygonArrayConstPtr& msg)
{
    sensors_fov_ = *msg;
    sensors_fov_flag_ = true;
}

bool SensorChecker::hasTestFailed()
{
    return !isSensorActive();
}

std::string SensorChecker::getMonitoredSensor()
{
    switch (sensor_to_monitor_)
    {
        case SENSOR_TYPE::radar:
            return "radar";
        case SENSOR_TYPE::lidar:
            return "lidar";
        case SENSOR_TYPE::camera1:
            return "camera1";
        /* case SENSOR_TYPE::camera2:
            return "camera2"; */
    }
}

bool SensorChecker::isSensorActive()
{
    if (!sensors_fov_flag_)
    {
        ROS_WARN("Sensor monitor node is not publishing");
        return false;
    }
    else if (!sensors_fov_.polygons.at(sensor_to_monitor_).polygon.points.empty())
    {
        return true;
    }
    ROS_WARN_STREAM("Sensor " << getMonitoredSensor() << " timed out");
    return false;
}

SensorChecker::~SensorChecker()
{
}
