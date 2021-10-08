//
// Created by adeye on 2021-10-08.
//

#include "safety_fault_detectors/safety_fault_detector.h"

SafetyFaultDetector::SafetyFaultDetector(int increment_value, int decrement_value, int high_threshold, int low_threshold)
        : DECREMENT_VALUE_(decrement_value), HIGH_THRESHOLD_(high_threshold), INCREMENT_VALUE_(increment_value),
          LOW_THRESHOLD_(low_threshold) {}

void SafetyFaultDetector::updateCounter() {
    if(isFailingRightNow())
        incrementAndSaturateCounter();
    else
        decrementAndSaturateCounter();
}

bool SafetyFaultDetector::isFaulty() {
    return !is_test_passing_;
}

void SafetyFaultDetector::incrementAndSaturateCounter() {
    counter_value_ += INCREMENT_VALUE_;
    if(counter_value_ >= HIGH_THRESHOLD_)
    {
        counter_value_ = HIGH_THRESHOLD_;
        is_test_passing_ = false;
    }
}

void SafetyFaultDetector::decrementAndSaturateCounter() {
    counter_value_ -= DECREMENT_VALUE_;
    if(counter_value_ <= LOW_THRESHOLD_)
    {
        counter_value_ = LOW_THRESHOLD_;
        is_test_passing_ = true;
    }
}
