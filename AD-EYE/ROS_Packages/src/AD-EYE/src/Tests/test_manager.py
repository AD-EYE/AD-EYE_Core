#!/usr/bin/env python
from unittest import TestCase
from FeatureControl import FeatureControl
import importlib
from std_msgs.msg import Int32
import rosnode
import subprocess
import rospy

ROSCORE_SLEEP_TIME = 1
TIME_BETWEEN_SIMULINK_STATE_CHANGES = 5

ENABLE_SIMULINK_STATE = Int32(1)
DISABLE_SIMULINK_STATE = Int32(0)
INVALID_VALUE_SIMULINK_STATE_1 = Int32(5)
INVALID_VALUE_SIMULINK_STATE_2 = Int32(12)


manager = importlib.import_module('manager')

manager.Localization = FeatureControl(manager.LOCALIZATION_FULL_PATH, "Localization")
manager.Detection = FeatureControl(manager.DETECTION_FULL_PATH, "Detection")
manager.Mission_planning = FeatureControl(manager.MISSION_PLANNING_FULL_PATH, "Mission_Planning")
manager.Motion_planning = FeatureControl(manager.MOTION_PLANNING_FULL_PATH, "Motion_Planning")
manager.Ssmp = FeatureControl(manager.SSMP_FULL_PATH, "SSMP")


##A class to try different tests, child class of the TestCase Class.
#
#The tests compare the number of currently running nodes as the rationale for success/failure.
#
#Disable -> enable should increase number of nodes running in ROS and vice versa. (#Test_1 and #Test_2)
#
#Disable -> Disable OR Enable -> Enable should not change number of running nodes (#Test_3 and #Test_4)
class TestManager(TestCase):

    ##A method that checks that a change in simulink state enables the launch/kill of features.
    #The number of nodes running in ROS should increase.
    #@param self the object pointer
    def Test_1(self):
        subprocess.Popen('roscore')
        rospy.sleep(ROSCORE_SLEEP_TIME)
        manager.simulink_state_callback(DISABLE_SIMULINK_STATE)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        initial_node_count = len(rosnode.get_node_names())
        manager.simulink_state_callback(ENABLE_SIMULINK_STATE)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        final_node_count = len(rosnode.get_node_names())
        self.assertLess(initial_node_count, final_node_count)

    ##A method that checks that a change in simulink state enables the launch/kill of features.
    #The number of nodes running in ROS should decrease.
    #@param self the object pointer
    def Test_2(self):
        subprocess.Popen('roscore')
        rospy.sleep(ROSCORE_SLEEP_TIME)
        manager.simulink_state_callback(ENABLE_SIMULINK_STATE)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        initial_node_count = len(rosnode.get_node_names())
        manager.simulink_state_callback(DISABLE_SIMULINK_STATE)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        final_node_count = len(rosnode.get_node_names())
        self.assertLess(final_node_count, initial_node_count)

    ##A method that checks that a change in simulink state enables the launch/kill of features.
    #The number of nodes running in ROS should not be modified.
    #@param self the object pointer
    def Test_3(self):
        subprocess.Popen('roscore')
        rospy.sleep(ROSCORE_SLEEP_TIME)
        manager.simulink_state_callback(ENABLE_SIMULINK_STATE)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        initial_node_count = len(rosnode.get_node_names())
        manager.simulink_state_callback(ENABLE_SIMULINK_STATE)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        final_node_count = len(rosnode.get_node_names())
        self.assertEqual(final_node_count, initial_node_count)

    ##A method that checks that a change in simulink state enables the launch/kill of features.
    #The number of nodes running in ROS should not be modified.
    #@param self the object pointer
    def Test_4(self):
        subprocess.Popen('roscore')
        rospy.sleep(ROSCORE_SLEEP_TIME)
        manager.simulink_state_callback(DISABLE_SIMULINK_STATE)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        initial_node_count = len(rosnode.get_node_names())
        manager.simulink_state_callback(DISABLE_SIMULINK_STATE)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        final_node_count = len(rosnode.get_node_names())
        self.assertEqual(final_node_count, initial_node_count)

    ## A method that checks that an invalid simulink state command does not have any effect i.e. does not launch
    ## or kill  any new nodes
    #@param self the object pointer
    def Test_5(self):
        subprocess.Popen('roscore')
        rospy.sleep(ROSCORE_SLEEP_TIME)
        initial_node_count = len(rosnode.get_node_names())
        manager.simulink_state_callback(INVALID_VALUE_SIMULINK_STATE_1)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        final_node_count = len(rosnode.get_node_names())
        self.assertEqual(final_node_count, initial_node_count)

    ## A method that checks that a sequence of invalid simulink state commands does not have any effect i.e. does not launch
    ## or kill  any new nodes
    #@param self the object pointer
    def Test_6(self):
        subprocess.Popen('roscore')
        rospy.sleep(ROSCORE_SLEEP_TIME)
        initial_node_count = len(rosnode.get_node_names())
        manager.simulink_state_callback(INVALID_VALUE_SIMULINK_STATE_1)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        manager.simulink_state_callback(INVALID_VALUE_SIMULINK_STATE_2)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        final_node_count = len(rosnode.get_node_names())
        self.assertEqual(final_node_count, initial_node_count)

    ## A method that checks that a invalid  simulink state command followed by a valid enable command,
    ##launches nodes as expected
    #@param self the object pointer
    def Test_7(self):
        subprocess.Popen('roscore')
        rospy.sleep(ROSCORE_SLEEP_TIME)
        initial_node_count = len(rosnode.get_node_names())
        manager.simulink_state_callback(INVALID_VALUE_SIMULINK_STATE_1)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        manager.simulink_state_callback(ENABLE_SIMULINK_STATE)
        rospy.sleep(TIME_BETWEEN_SIMULINK_STATE_CHANGES)
        final_node_count = len(rosnode.get_node_names())
        self.assertGreater(final_node_count, initial_node_count)

if __name__ == '__main__':
    # Ros unit testing framework is used to run all tests and save in .xml format
    import rosunit

    rosunit.unitrun('adeye', 'Manager_test_results', TestManager)

