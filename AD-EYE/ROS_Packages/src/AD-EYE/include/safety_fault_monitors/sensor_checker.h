//
// Created by adeye on 2021-10-11.
//

#ifndef ADEYE_SENSOR_CHECKER_H
#define ADEYE_SENSOR_CHECKER_H

#include <ros/ros.h>
#include <jsk_recognition_msgs/PolygonArray.h>
#include "safety_fault_monitor.h"

enum SENSOR_TYPE
{
    radar,
    lidar,
    camera1,
    camera2,
    cameratl,
    NB_SENSORS
};  // sensors indices as defined in the sensor monitor

class SensorChecker : public SafetyFaultMonitor
{
  private:
    ros::NodeHandle nh_;
    ros::Subscriber sub_sensor_fov_;
    jsk_recognition_msgs::PolygonArray sensors_fov_;
    bool sensors_fov_flag_ = false;
    SENSOR_TYPE sensor_to_monitor_;

    /*!
     * \brief Sensor field of view callback : Called when the sensors information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores polygons that represent sensor field of view
     */
    void sensorFovCallback(const jsk_recognition_msgs::PolygonArrayConstPtr& msg);

  public:
    SensorChecker(int increment_value, int decrement_value, int high_threshold, int low_threshold,
                  SENSOR_TYPE sensor_to_monitor);
    ~SensorChecker();

    bool hasTestFailed() override;

    std::string getMonitoredSensor();

    bool isSensorActive();
};

#endif  // ADEYE_SENSOR_CHECKER_H
