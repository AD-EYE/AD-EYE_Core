//
// (c)Copyright 2019 by Siemens Industry Software and Services B.V.
// All rights reserved.
//
// Simcenter Prescan(r) has been developed at Siemens Industry Software and
// Services B.V.
//
// This document contains proprietary and confidential information of Siemens.
// The contents of this document may not be disclosed to third parties, copied
// or duplicated in any form, in whole or in part, without prior written
// permission of Siemens.
//
// The terms and conditions governing the license of Simcenter Prescan(r)
// software consist solely of those set forth in the written contracts between
// Siemens or Siemens authorized third parties and its customers. The software
// may only be used or copied in accordance with the terms of these contracts.
//

#include "ProximityDemo.h"

#include "prescan/api/Trajectory.hpp"
#include "prescan/sim/SpeedProfileUnit.hpp"
#include "prescan/sim/PathUnit.hpp"

#include "Utils.h"

void ProximityDemo::registerSimulationUnits(const prescan::api::Experiment & experiment, prescan::sim::ISimulation* simulation)
{
  registerAudiUnits(experiment, simulation);
  registerBmwUnits(experiment, simulation);
}

void ProximityDemo::initialize(prescan::sim::ISimulation * simulation)
{
  // This is equivalent to the SpeedProfile -> Path -> StateActuator blocks on the compilation sheet in simulink
  m_audiPathUnit->motionInput() = m_audiSpeedProfileUnit->motionOutput();
  m_audiActuatorUnit->stateActuatorInput() = m_audiPathUnit->stateActuatorOutput();

  // SpeedProfile -> Path -> StateActuator
  m_bmwPathUnit->motionInput() = m_bmwSpeedProfileUnit->motionOutput();
  m_bmwActuatorUnit->stateActuatorInput() = m_bmwPathUnit->stateActuatorOutput();
}

void ProximityDemo::step(prescan::sim::ISimulation * simulation)
{
  // step logic for Actors
  bmwStep();
  audiStep();
  
  // get camera image 
  cv::Mat cameraImage = convertToOpenCVImage(m_audiCameraUnit->imageOutput());

  showEdgeDetection(&cameraImage);
  showSensorOutputs(&cameraImage);
}

void ProximityDemo::terminate(prescan::sim::ISimulation * simulation)
{
}

void ProximityDemo::bmwStep()
{
  m_bmwPathUnit->motionInput() = m_bmwSpeedProfileUnit->motionOutput();
  m_bmwActuatorUnit->stateActuatorInput() = m_bmwPathUnit->stateActuatorOutput();
}

void ProximityDemo::audiStep()
{
  if (!m_isVehicleStopped)
  {
    m_audiPathUnit->motionInput() = m_audiSpeedProfileUnit->motionOutput();
    m_audiActuatorUnit->stateActuatorInput() = m_audiPathUnit->stateActuatorOutput();
  }

  // Stopping Condition - check for stopping condition based on sensor data
  // and proximity of another vehichle on the road to Audi
  std::vector<const PRESCAN_AIRSENSORDATA*> airSensorDataEntries = m_audiAirUnit->airSensorOutput();
  if (airSensorDataEntries.size() != 0)
  {
    const PRESCAN_AIRSENSORDATA& airData = *airSensorDataEntries[0];
    if (airData.Range <= 2.0)  // 2 meters
    {
      m_audiActuatorUnit->stateActuatorInput().VelocityX = 0.0;
      m_isVehicleStopped = true;
    }
  }
}

void ProximityDemo::registerAudiUnits(const prescan::api::Experiment & experiment, prescan::sim::ISimulation* simulation)
{
  // Object Handles
  auto audi = experiment.getObjectByName<prescan::api::WorldObject>("Vehicle_1");
  auto audiCamera = experiment.getObjectByName<prescan::api::CameraSensor>("CameraSensor_1");
  auto airSensorObject = experiment.getObjectByName<prescan::api::AirSensor>("AIR_1");
  auto lidarSensorObject = experiment.getObjectByName<prescan::api::LidarSensor>("Lidar_1");
  auto tisSensorObject1 = experiment.getObjectByName<prescan::api::TisSensor>("TIS_1");

  // Register state actuator unit for Audi
  m_audiActuatorUnit = prescan::sim::registerUnit<prescan::sim::StateActuatorUnit>(simulation, audi);

  // Audi - TIS sensor registeration
  m_audiTisUnit = prescan::sim::registerUnit<prescan::sim::TisSensorUnit>(simulation, tisSensorObject1);

  // Audi - SpeedProfile & Path registeration 
  auto trajectoryAudi = prescan::api::Trajectory::getActiveTrajectory(audi);
  m_audiSpeedProfileUnit = prescan::sim::registerUnit<prescan::sim::SpeedProfileUnit>(simulation, trajectoryAudi.speedProfile());
  m_audiPathUnit = prescan::sim::registerUnit<prescan::sim::PathUnit>(simulation, trajectoryAudi.path(), audi);

  // Audi - Air, Camera, Lidar sensors registeration
  m_audiCameraUnit = prescan::sim::registerUnit<prescan::sim::CameraSensorUnit>(simulation, audiCamera);
  m_audiAirUnit = prescan::sim::registerUnit<prescan::sim::AirSensorUnit>(simulation, airSensorObject);
  m_audiLidarUnit = prescan::sim::registerUnit<prescan::sim::LidarSensorUnit>(simulation, lidarSensorObject);
}

void ProximityDemo::registerBmwUnits(const prescan::api::Experiment & experiment, prescan::sim::ISimulation* simulation)
{
  // Register Units for BMW - the leading car in the front
  auto bmw = experiment.getObjectByName<prescan::api::WorldObject>("Vehicle_2");
  m_bmwActuatorUnit = prescan::sim::registerUnit<prescan::sim::StateActuatorUnit>(simulation, bmw);

  auto trajectoryBmw = prescan::api::Trajectory::getActiveTrajectory(bmw);
  m_bmwSpeedProfileUnit = prescan::sim::registerUnit<prescan::sim::SpeedProfileUnit>(simulation, trajectoryBmw.speedProfile());
  m_bmwPathUnit = prescan::sim::registerUnit<prescan::sim::PathUnit>(simulation, trajectoryBmw.path(), bmw);
}


void ProximityDemo::showSensorOutputs(cv::Mat* cameraImage)
{
  // Show Sensor Messages
  showAirSensorMessages(cameraImage);
  showTisSensorMessages(cameraImage);
  showLidarMessages(cameraImage);
  showAudiActuatorMessages(cameraImage);
  cv::imshow("camera image", *cameraImage);
  cv::waitKey(25);
}

void ProximityDemo::showTisSensorMessages(cv::Mat* image)
{
  std::stringstream ss;
  if (!m_audiTisUnit->scannerSensorOutput().empty())
  {
    const PRESCAN_SCANNERSENSOR_DATA& tisData = *m_audiTisUnit->scannerSensorOutput()[0];
    ss << "TIS_1" << " detection at distance: " << tisData.Range;
  }
  else
  {
    ss << "TIS_1" << " no detection";
  }
  writeTextMessage(image, ss.str(), cv::Point(10, 50));
}

void ProximityDemo::showLidarMessages(cv::Mat * image)
{
  std::stringstream ss;
  if (!m_audiLidarUnit->scannerSensorOutput().empty())
  {
    const PRESCAN_SCANNERSENSOR_DATA& lidarData = *m_audiLidarUnit->scannerSensorOutput()[0];
    ss << "Lidar detection at distance: " << lidarData.Range;
  }
  else
  {
    ss << "No detection from Lidar";
  }
  writeTextMessage(image, ss.str(), cv::Point(10, 100) );
}

void ProximityDemo::showAirSensorMessages(cv::Mat * image)
{
  std::vector<const PRESCAN_AIRSENSORDATA*> airSensorDataEntries = m_audiAirUnit->airSensorOutput();
  if (!airSensorDataEntries.empty())
  {
    const PRESCAN_AIRSENSORDATA& airData = *airSensorDataEntries[0];
    std::stringstream ss;
    ss << "AIR Range: " << airData.Range;
    writeTextMessage(image, ss.str(), cv::Point(10, 20));
  }
}

void ProximityDemo::showAudiActuatorMessages(cv::Mat * image)
{
  if (m_isVehicleStopped)
  {
    writeTextMessage(image, std::string("Distance less than 2 meter. Vehicle Stopped."), cv::Point(10, 200));
  }
}

void ProximityDemo::showEdgeDetection(cv::Mat * image)
{
  // Create sobel edge detection
  cv::Mat grey;
  cvtColor(*image, grey, cv::COLOR_BGR2GRAY);

  cv::Mat sobelx;
  cv::Sobel(grey, sobelx, CV_32F, 1, 0);

  double minVal, maxVal;
  cv::minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities

  cv::Mat draw;
  sobelx.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));

  cv::imshow("Sobel edge detection", draw);
  cv::waitKey(25);
}

