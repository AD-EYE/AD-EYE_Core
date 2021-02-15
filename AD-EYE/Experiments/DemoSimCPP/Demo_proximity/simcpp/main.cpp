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
#include <cassert> 

#include "ProximityDemo.h"

#include "prescan/api/Experiment.hpp"
#include "prescan/sim/Simulation.hpp"

int main(int argc, const char* argv[])
{
  std::string pathToPb = "Demo_proximity.pb";
  double simulationDuration = 10; // [seconds]

  ProximityDemo code;
  prescan::sim::Simulation sim(&code);
  prescan::api::Experiment experiment(pathToPb);
  sim.run(experiment, simulationDuration);

  return EXIT_SUCCESS;
}
