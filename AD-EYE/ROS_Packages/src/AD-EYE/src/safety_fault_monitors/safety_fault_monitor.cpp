//
// Created by adeye on 2021-10-08.
//

#include <iostream>
#include "safety_fault_monitors/safety_fault_monitor.h"

SafetyFaultMonitor::SafetyFaultMonitor(int increment_value, int decrement_value, int high_threshold, int low_threshold)
  : DECREMENT_VALUE_(decrement_value)
  , HIGH_THRESHOLD_(high_threshold)
  , INCREMENT_VALUE_(increment_value)
  , LOW_THRESHOLD_(low_threshold)
{
    if (LOW_THRESHOLD_ > 0)
    {
        std::cerr << "the low threshold is positive, please review the parameters" << std::endl;
        exit(1);
    }
}

void SafetyFaultMonitor::update()
{
    if (hasTestFailed())
        incrementAndSaturateCounter();
    else
        decrementAndSaturateCounter();
}

bool SafetyFaultMonitor::isFaultConfirmed() const
{
    return is_fault_confirmed_;
}

void SafetyFaultMonitor::incrementAndSaturateCounter()
{
    counter_value_ += INCREMENT_VALUE_;
    if (counter_value_ >= HIGH_THRESHOLD_)
    {
        counter_value_ = HIGH_THRESHOLD_;
        is_fault_confirmed_ = true;
    }
}

void SafetyFaultMonitor::decrementAndSaturateCounter()
{
    counter_value_ -= DECREMENT_VALUE_;
    if (counter_value_ <= LOW_THRESHOLD_)
    {
        counter_value_ = LOW_THRESHOLD_;
        is_fault_confirmed_ = false;
    }
}

SafetyFaultMonitor::~SafetyFaultMonitor() = default;
