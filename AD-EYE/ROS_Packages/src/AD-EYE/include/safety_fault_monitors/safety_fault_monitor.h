//
// Created by adeye on 2021-10-08.
//

#ifndef ADEYE_SAFETY_FAULT_MONITOR_H
#define ADEYE_SAFETY_FAULT_MONITOR_H

/*!
     * \brief Mother class for safety fault detection
     * \details The class has a method that should be called periodically. That method updates a counter based on
     * whether or not the tested functionality is malfunctioning. When the counter reaches high or low thresholds the
     * test is respectively failed or passed. When the counter is between those threshold the test keep the same status
     * as previously.
     */
class SafetyFaultMonitor {

private:

    const int INCREMENT_VALUE_;
    const int DECREMENT_VALUE_;
    const int HIGH_THRESHOLD_;
    const int LOW_THRESHOLD_;
    int counter_value_ = 0;
    bool is_fault_confirmed_ = false;

    void incrementAndSaturateCounter();
    void decrementAndSaturateCounter();

public:

    /*!
     * \brief Constructor
     * \param increment_value How much the counter is incremented when the function tested is malfunctioning.
     * \param decrement_value How much the counter is decremented when the function tested is malfunctioning (should be positive).
     * \param high_threshold Upper value at which the counter is saturated. When the counter reaches this value the test is considered failed.
     * \param low_threshold Lower value at which the counter is saturated. When the counter reaches this value the test is considered successful.
     */
    SafetyFaultMonitor(int increment_value, int decrement_value, int high_threshold, int low_threshold);

    /*!
    * \brief Destructor
    */
    ~SafetyFaultMonitor();

    /*!
     * \brief Updates the counter based of the result of hasTestFailed
     */
    void update();

    /*!
     * \brief Purely virtual method that returns whether the functionality is malfunctioning.
     * \details This method must be overridden by the specific fault detector
     */
    virtual bool hasTestFailed() = 0;

    /*!
     * \brief Returns the conclusion of the fault detector
     */
    bool isFaultConfirmed() const;

};


#endif //ADEYE_SAFETY_FAULT_MONITOR_H
