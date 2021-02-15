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

#include <iostream>
#include <string>
#include <utility>

#include "prescan/api/AirSensor.hpp"
#include "prescan/api/Trajectory.hpp"

#include "prescan/sim/ISimulationModel.hpp"
#include "prescan/sim/AirSensorUnit.hpp"
#include "prescan/sim/PathUnit.hpp"
#include "prescan/sim/SelfSensorUnit.hpp"
#include "prescan/sim/SpeedProfileUnit.hpp"
#include "prescan/sim/StateActuatorUnit.hpp"
#include "prescan/sim/Simulation.hpp"


// Code to simulate object along it's active trajectory
class TrajectorySimulationModel : public prescan::sim::ISimulationModel
{
public:
  explicit TrajectorySimulationModel(std::string egoName) : m_egoName(std::move(egoName)) {}

  void registerSimulationUnits(const prescan::api::Experiment& experiment, prescan::sim::ISimulation* simulation) override
  {
    auto egoVehicle = experiment.getObjectByName<prescan::api::WorldObject>(m_egoName);
    auto egoTrajectory = prescan::api::Trajectory::getActiveTrajectory(egoVehicle);

    m_speedProfileUnit = prescan::sim::registerUnit<prescan::sim::SpeedProfileUnit>(simulation, egoTrajectory.speedProfile());
    m_pathUnit = prescan::sim::registerUnit<prescan::sim::PathUnit>(simulation, egoTrajectory.path(), egoVehicle);

    m_egoStateUnit = prescan::sim::registerUnit<prescan::sim::StateActuatorUnit>(simulation, egoVehicle);

    auto airSensor = experiment.getObjectByName<prescan::api::AirSensor>("AIR_1");
    m_airSensorUnit = prescan::sim::registerUnit<prescan::sim::AirSensorUnit>(simulation, airSensor);
    m_egoSelfUnit = prescan::sim::registerUnit<prescan::sim::SelfSensorUnit>(simulation, egoVehicle);
  }

  void updateTrajectory() const
  {
    // Copy data between simulation units
    m_pathUnit->motionInput() = m_speedProfileUnit->motionOutput();
    m_egoStateUnit->stateActuatorInput() = m_pathUnit->stateActuatorOutput();
  }

  void initialize(prescan::sim::ISimulation* simulation) override
  {
    updateTrajectory();
    const PRESCAN_MOTION_DATA& motionData = m_speedProfileUnit->motionOutput();
  }

  void step(prescan::sim::ISimulation* simulation) override
  {
    auto airData = m_airSensorUnit->airSensorOutput(); // Triggers step for airsensor unit
    if (!airData.empty())
    {
      std::cout << "AIR sensor range output: " << airData[0]->Range << std::endl;
    }
    updateTrajectory();
  }

  void terminate(prescan::sim::ISimulation* simulation) override
  {
    const PRESCAN_MOTION_DATA& motionData = m_speedProfileUnit->motionOutput();
  }

protected:
  const std::string m_egoName;

  prescan::sim::StateActuatorUnit* m_egoStateUnit{ nullptr };
  prescan::sim::SelfSensorUnit* m_egoSelfUnit{ nullptr };
  prescan::sim::PathUnit* m_pathUnit{ nullptr };
  prescan::sim::SpeedProfileUnit* m_speedProfileUnit{ nullptr };
  prescan::sim::AirSensorUnit* m_airSensorUnit{ nullptr };
};


int main(int argc, const char* argv[])
{
  std::string experimentPath = "Demo_trajectory.pb"; // Executable needs to be called from experiment folder
  double simulationTime = 3.0; // Simulate for 3 seconds

  TrajectorySimulationModel code("EGO");
  prescan::sim::Simulation sim(&code);
  prescan::api::Experiment experiment(experimentPath);
  sim.run(experiment, simulationTime);

  return EXIT_SUCCESS;
}
