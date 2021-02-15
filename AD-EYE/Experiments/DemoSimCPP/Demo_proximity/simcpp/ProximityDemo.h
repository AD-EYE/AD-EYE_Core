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

#pragma once

#include "prescan/api/WorldObject.hpp"
#include "prescan/api/CameraSensor.hpp"
#include "prescan/api/AirSensor.hpp"
#include "prescan/api/TisSensor.hpp"
#include "prescan/api/LidarSensor.hpp"
#include "prescan/api/Path.hpp"
#include "prescan/api/SpeedProfile.hpp"

#include "prescan/sim/Simulation.hpp"
#include "prescan/sim/StateActuatorUnit.hpp"
#include "prescan/sim/CameraSensorUnit.hpp"
#include "prescan/sim/AirSensorUnit.hpp"
#include "prescan/sim/TisSensorUnit.hpp"
#include "prescan/sim/LidarSensorUnit.hpp"
#include "prescan/sim/SpeedProfileUnit.hpp"
#include "prescan/sim/PathUnit.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// ------------------
// Proximity-Demo:
// ------------------
// This project demonstrates how SimCpp can be used to: 
//   1. Read sensor data from Air, Lidar, TIS and Camera.
//   2. Drive the actuator states of actors based on their SpeedProfile and Path.
//   3. Visualize data from sensors using OpenCV.
// The experiment consists of two actors, a BMW and an Audi, on a single road each following a predefined path. 
// The Audi starts behind and slowly catches up with the BMW in front. 
// The Audi has an AIR sensor, a Camera, a Lidar and a TIS sensor attached to it. 
// When the Air sensor detects an obstacle within a range of 2 meter, then Audi is stopped. 
// Since the Audi is initially moving faster than the BMW, it slowly gets closer and closer to the BMW, 
// until it is less than a meter apart. At this point the, the Audi stops while the BMW continues onwards.
// At each timestep, the output from the camera sensor's image frame is displayed using OpenCV image library.
// It is also demonstrated how image processing can be done on the sensor data.

class ProximityDemo : public prescan::sim::ISimulationModel
{
public:
  void registerSimulationUnits(const prescan::api::Experiment& experiment, prescan::sim::ISimulation* simulation) override;
  void initialize(prescan::sim::ISimulation* simulation) override;
  void step(prescan::sim::ISimulation* simulation) override;
  void terminate(prescan::sim::ISimulation* simulation) override;

private:
  void registerAudiUnits(const prescan::api::Experiment & experiment, prescan::sim::ISimulation* simulation);
  void registerBmwUnits(const prescan::api::Experiment & experiment, prescan::sim::ISimulation* simulation);

  void bmwStep();
  void audiStep();
  
  void showSensorOutputs(cv::Mat* cameraImage);
  void showTisSensorMessages(cv::Mat* image);
  void showLidarMessages(cv::Mat* image);
  void showAirSensorMessages(cv::Mat* image);
  void showAudiActuatorMessages(cv::Mat* image);
  void showEdgeDetection(cv::Mat* image);

private:
  // BMW - The leading car on the track.
  prescan::sim::StateActuatorUnit*  m_bmwActuatorUnit;
  prescan::sim::SpeedProfileUnit*   m_bmwSpeedProfileUnit;
  prescan::sim::PathUnit*           m_bmwPathUnit;

  // Audi- The car which follows behind the BMW. It has Camera, AIR and four LIDAR sensors attached. 
  prescan::sim::StateActuatorUnit*          m_audiActuatorUnit;
  prescan::sim::CameraSensorUnit*           m_audiCameraUnit;
  prescan::sim::AirSensorUnit*              m_audiAirUnit;
  prescan::sim::LidarSensorUnit*            m_audiLidarUnit;
  prescan::sim::SpeedProfileUnit*           m_audiSpeedProfileUnit;
  prescan::sim::PathUnit*                   m_audiPathUnit;
  prescan::sim::TisSensorUnit*              m_audiTisUnit;
  
  bool m_isVehicleStopped = false; // set to true when Audi approaching an obstacle
};