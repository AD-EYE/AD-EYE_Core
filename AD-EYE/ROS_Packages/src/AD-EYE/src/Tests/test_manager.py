#!/usr/bin/env python
from unittest import TestCase
from FeatureControl import FeatureControl
import importlib
from std_msgs.msg import Int32
import rosnode
import subprocess
import rospy

ROSCORE_SLEEP_TIME = 1

ENABLE_SIMULINK_STATE = Int32(1)
DISABLE_SIMULINK_STATE = Int32(0)
INVALID_VALUE_SIMULINK_STATE = Int32(5)

manager = importlib.import_module('manager')

manager.Localization = FeatureControl(manager.LOCALIZATION_FULL_PATH, "Localization")
manager.Detection = FeatureControl(manager.DETECTION_FULL_PATH, "Detection")
manager.Mission_planning = FeatureControl(manager.MISSION_PLANNING_FULL_PATH, "Mission_Planning")
manager.Motion_planning = FeatureControl(manager.MOTION_PLANNING_FULL_PATH, "Motion_Planning")
manager.Ssmp = FeatureControl(manager.SSMP_FULL_PATH, "SSMP")



class TestManager(TestCase):

    # Tests Test_1 ..Test_4 test that a change in simulink state enables the launch/kill of features
    # The tests compare the number of currently running nodes as the rationale for success/failure
    # Disable -> enable should increase number of nodes running in ROS and vice versa. (Tests 1 and 2)
    # Disable -> Disable OR Enable -> Enable should not change number of running nodes (Tests 3 and 4)
    def Test_1(self):
        subprocess.Popen('roscore')
        rospy.sleep(ROSCORE_SLEEP_TIME)
        manager.simulink_state_callback(DISABLE_SIMULINK_STATE)
        initial_node_count = len(rosnode.get_node_names())
        manager.simulink_state_callback(ENABLE_SIMULINK_STATE)
        final_node_count = len(rosnode.get_node_names())
        self.assertLess(initial_node_count, final_node_count)

    def Test_2(self):
        subprocess.Popen('roscore')
        rospy.sleep(ROSCORE_SLEEP_TIME)
        manager.simulink_state_callback(ENABLE_SIMULINK_STATE)
        initial_node_count = len(rosnode.get_node_names())
        manager.simulink_state_callback(DISABLE_SIMULINK_STATE)
        final_node_count = len(rosnode.get_node_names())
        self.assertLess(final_node_count, initial_node_count)

    def Test_3(self):
        subprocess.Popen('roscore')
        rospy.sleep(ROSCORE_SLEEP_TIME)
        manager.simulink_state_callback(ENABLE_SIMULINK_STATE)
        initial_node_count = len(rosnode.get_node_names())
        manager.simulink_state_callback(ENABLE_SIMULINK_STATE)
        final_node_count = len(rosnode.get_node_names())
        self.assertEqual(final_node_count, initial_node_count)

    def Test_4(self):
        subprocess.Popen('roscore')
        rospy.sleep(ROSCORE_SLEEP_TIME)
        manager.simulink_state_callback(DISABLE_SIMULINK_STATE)
        initial_node_count = len(rosnode.get_node_names())
        manager.simulink_state_callback(DISABLE_SIMULINK_STATE)
        final_node_count = len(rosnode.get_node_names())
        self.assertEqual(final_node_count, initial_node_count)

    # Test_5 checks that an invalid simulink state command does not have any effect i.e. does not launch any new nodes

    def Test_5(self):
        subprocess.Popen('roscore')
        rospy.sleep(ROSCORE_SLEEP_TIME)
        initial_node_count = len(rosnode.get_node_names())
        manager.simulink_state_callback(INVALID_VALUE_SIMULINK_STATE)
        final_node_count = len(rosnode.get_node_names())
        self.assertEqual(final_node_count, initial_node_count)


if __name__ == '__main__':
    # Ros unit testing framework is used to run all tests and save in .xml format
    import rosunit

    rosunit.unitrun('adeye', 'Manager_test_results', TestManager)
