//
// Created by adeye on 2021-10-08.
//

#ifndef ADEYE_ACTIVE_NODES_CHECKER_H
#define ADEYE_ACTIVE_NODES_CHECKER_H

#include "safety_fault_detector.h"

class ActiveNodeChecker: public SafetyFaultDetector {
private:
    bool isFailingRightNow();

public:
    ActiveNodeChecker(int increment_value, int decrement_value, int high_threshold, int low_threshold, int criticality_level);
};

#endif //ADEYE_ACTIVE_NODES_CHECKER_H
