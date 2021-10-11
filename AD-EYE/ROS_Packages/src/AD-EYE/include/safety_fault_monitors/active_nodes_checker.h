//
// Created by adeye on 2021-10-08.
//

#ifndef ADEYE_ACTIVE_NODES_CHECKER_H
#define ADEYE_ACTIVE_NODES_CHECKER_H

#include <vector>
#include <string>
#include "safety_fault_monitor.h"

class ActiveNodeChecker: public SafetyFaultMonitor {
private:
    std::vector<std::string> nodes_to_check_;
    bool isFailingRightNow() override;
    void retrieveNodesToCheckParam(const char*  param_name);
    bool areNodesAlive();


public:
    ActiveNodeChecker(int increment_value, int decrement_value, int high_threshold, int low_threshold, int criticality_level);
};

#endif //ADEYE_ACTIVE_NODES_CHECKER_H
