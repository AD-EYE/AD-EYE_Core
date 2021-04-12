import os
import sys
import rospy
from std_msgs.msg import Bool
import subprocess
import unittest
from rosnode import get_node_names

sys.path.insert(1, os.path.join(sys.path[0], '..'))

from manager import ManagerStateMachine
from manager import ManagerFeaturesHandler
from manager import Manager


def startROS():
    ROSCORE_SLEEP_TIME = 1
    subprocess.Popen(['xterm', '-e', 'rosmaster', '--core'])
    rospy.sleep(ROSCORE_SLEEP_TIME)


def stopROS():
    ROSCORE_SLEEP_TIME = 1
    subprocess.Popen(['rosnode', 'kill', '-a'])
    subprocess.Popen(['xterm', '-e', 'killall', 'rosmaster'])
    rospy.sleep(ROSCORE_SLEEP_TIME)

## Helper function to get the given state machine in the Enabled state
# @param manager_state_machine State machine to be transitioned
def getStateMachineToEnabled(manager_state_machine):
    test_msg = Bool(True)
    manager_state_machine.initial_checks_callback(test_msg)
    if manager_state_machine.getState() != manager_state_machine.States.ENABLED_STATE:
        raise Exception('State machine could not get in Enabled state to start test, check getStateMachineToEnabled '
                        'function')

## Helper function to get the given state machine in the Engaged state
# @param manager_state_machine State machine to be transitioned
def getStateMachineToEngaged(manager_state_machine):
    test_msg = Bool(True)
    manager_state_machine.initial_checks_callback(test_msg)
    manager_state_machine.activation_request_callback(test_msg)
    if manager_state_machine.getState() != manager_state_machine.States.ENGAGED_STATE:
        raise Exception('State machine could not get in Engaged state to start test, check getStateMachineToEngaged '
                        'function')

## Helper function to get the given state machine in the Fault state
# @param manager_state_machine State machine to be transitioned
def getStateMachineToFault(manager_state_machine):
    test_msg = Bool(True)
    manager_state_machine.initial_checks_callback(test_msg)
    manager_state_machine.activation_request_callback(test_msg)
    manager_state_machine.fault_callback(test_msg)
    if manager_state_machine.getState() != manager_state_machine.States.FAULT_STATE:
        raise Exception('State machine could not get in Fault state to start test, check getStateMachineToFault '
                        'function')


## Tests every transition possible in the state machine (4 states, 3 boolean transition topics so 24 tests)
class ManagerStateMachineTester(unittest.TestCase):

    # Test all transitions from initial state
    def test_initial_initial_checks_true(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(True)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE)

    def test_initial_initial_checks_false(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(False)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.INITIALIZING_STATE)

    def test_initial_activation_request_true(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(True)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.INITIALIZING_STATE)

    def test_initial_activation_request_false(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(False)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.INITIALIZING_STATE)

    def test_initial_fault_true(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(True)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    def test_initial_fault_false(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(False)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.INITIALIZING_STATE)

    # Test all transitions from enabled state
    def test_enabled_initial_checks_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE)

    def test_enabled_initial_checks_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE)

    def test_enabled_activation_request_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE)

    def test_enabled_activation_request_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE)

    def test_enabled_fault_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    def test_enabled_fault_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE)

    # Test all transitions from engaged state
    def test_engaged_initial_checks_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE)

    def test_engaged_initial_checks_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE)

    def test_engaged_activation_request_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE)

    def test_engaged_activation_request_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE)

    def test_engaged_fault_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    def test_engaged_fault_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE)

    # Test all transitions from fault state
    def test_fault_initial_checks_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    def test_fault_initial_checks_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    def test_fault_activation_request_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    def test_fault_activation_request_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    def test_fault_fault_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    def test_fault_fault_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

## Tests for the feature starting and stopping, to be developped
class ManagerFeaturesHandlerTester(unittest.TestCase):

    @unittest.skip("demonstrating skipping")
    def testStartAllFeaturesWithoutTA(self):
        startROS()
        rospy.set_param("test_automation", False)
        manager_features_handler = ManagerFeaturesHandler()
        for feature_name in manager_features_handler.features.keys():
            print("starting feature " + feature_name)
            try:
                manager_features_handler.features[feature_name].featureControl.start()
            except:
                self.fail("Failed to start" + feature_name)
        number_of_nodes_running = len(get_node_names())
        rospy.sleep(20)
        stopROS()
        self.assertGreater(number_of_nodes_running, len(manager_features_handler.features.keys()))

    @unittest.skip("demonstrating skipping")
    def testStartAllFeaturesWithTA(self):
        startROS()
        rospy.set_param("test_automation", True)
        manager_features_handler = ManagerFeaturesHandler()
        for feature_name in manager_features_handler.features.keys():
            print("starting feature " + feature_name)
            try:
                manager_features_handler.features[feature_name].featureControl.start()
            except:
                self.fail("Failed to start" + feature_name)
        number_of_nodes_running = len(get_node_names())
        rospy.sleep(20)
        stopROS()
        self.assertGreater(number_of_nodes_running, len(manager_features_handler.features.keys()))




# class ManagerTester(unittest.TestCase):
#
#
#     def testInvalidXML(self):
#         with open("../launch/my_map.launch", "r+") as f:
#             old_content = f.read()  # back up the launch file
#             f.seek(0)  # rewind
#             f.write("!\n" + old_content)  # add a character making the launch file invalid
#         startROS()
#         rospy.init_node('AD-EYE_Manager')
#         manager = Manager()
#         manager.run()
#         rospy.sleep(5)
#         number_of_nodes_running = len(get_node_names())
#         stopROS()
#         self.assertGreater(number_of_nodes_running, 2)
#         with open("../launch/my_map.launch", "r+") as f:
#             f.write("!\n" + old_content)


if __name__ == '__main__':
    # Ros unit testing framework is used to run all tests and save in .xml format
    import rosunit
    #
    rosunit.unitrun('adeye', 'Manager_test_results_state_machine', ManagerStateMachineTester)
    # rosunit.unitrun('adeye', 'Manager_test_results_features_handler', ManagerFeaturesHandlerTester)
    # rosunit.unitrun('adeye', 'Manager_test_results', ManagerTester)
    # unittest.main()
