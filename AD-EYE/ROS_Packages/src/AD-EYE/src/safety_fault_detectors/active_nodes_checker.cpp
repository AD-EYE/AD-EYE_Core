//
// Created by adeye on 2021-10-08.
//


#include "active_nodes_checker.h"

ActiveNodeChecker::ActiveNodeChecker(int increment_value, int decrement_value, int high_threshold, int low_threshold): SafetyFaultDetector(increment_value, decrement_value, high_threshold, low_threshold)
{

}

bool ActiveNodeChecker::isFailingRightNow() {
    return true;
}