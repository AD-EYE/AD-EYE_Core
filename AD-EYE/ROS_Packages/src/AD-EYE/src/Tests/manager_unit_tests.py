
#!/usr/bin/env python


import os
import sys
import rospy


import unittest
import subprocess
from rosnode import get_node_names
from rosnode import rosnode_ping
from std_msgs.msg import Bool
from std_msgs.msg import Int32MultiArray

sys.path.insert(1, os.path.join(sys.path[0], '..')) #to access the manager source file
from manager import ManagerStateMachine
from manager import ManagerFeaturesHandler
from manager import Manager

PKG = 'adeye'
import roslib; roslib.load_manifest(PKG) 

##A function to start ROS.
def startROS():
    ROSCORE_SLEEP_TIME = 2
    subprocess.Popen(['xterm', '-e', 'rosmaster', '--core'])
    rospy.sleep(ROSCORE_SLEEP_TIME)

##A function to stop ROS.
def stopROS():
    ROSCORE_SLEEP_TIME = 3
    subprocess.Popen(['rosnode', 'kill', '-a'])
    subprocess.Popen(['xterm', '-e', 'killall', 'rosmaster'])
    rospy.sleep(ROSCORE_SLEEP_TIME)

##Function getStateMachineToEnabled
#
# Helper function to get the given state machine in the Enabled state.
# @param manager_state_machine State machine to be transitioned
def getStateMachineToEnabled(manager_state_machine):
    test_msg = Bool(True)
    manager_state_machine.initialChecksCallback(test_msg)
    if manager_state_machine.getState() != manager_state_machine.States.ENABLED_STATE:
        raise Exception('State machine could not get in Enabled state to start test, check getStateMachineToEnabled '
                        'function')


##Helper function to get the given state machine in the Engaged state.
#@param manager_state_machine State machine to be transitioned
def getStateMachineToEngaged(manager_state_machine):
    test_msg = Bool(True)
    manager_state_machine.initialChecksCallback(test_msg)
    manager_state_machine.activationRequestCallback(test_msg)
    if manager_state_machine.getState() != manager_state_machine.States.ENGAGED_STATE:
        raise Exception('State machine could not get in Engaged state to start test, check getStateMachineToEngaged '
                        'function')


##Helper function to get the given state machine in the Fault state.
#@param manager_state_machine State machine to be transitioned
def getStateMachineToFault(manager_state_machine):
    test_msg = Bool(True)
    manager_state_machine.initialChecksCallback(test_msg)
    manager_state_machine.activationRequestCallback(test_msg)
    manager_state_machine.faultCallback(test_msg)
    if manager_state_machine.getState() != manager_state_machine.States.FAULT_STATE:
        raise Exception('State machine could not get in Fault state to start test, check getStateMachineToFault '
                        'function')


##A class to tests every transition possible in the state machine (4 states, 3 boolean transition topics so 24 tests)
class ManagerStateMachineTester(unittest.TestCase):

    #A method to test all transitions from initial state
    #@param self the object pointer
    def test_initial_initial_checks_true(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(True)
        manager_state_machine.initialChecksCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE)

    ##Method test_initial_initial_checks_false
    #
    #@param self the object pointer
    def test_initial_initial_checks_false(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(False)
        manager_state_machine.initialChecksCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.INITIALIZING_STATE)

    ##Method test_initial_activation_request_true
    #
    #@param self the object pointer
    def test_initial_activation_request_true(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(True)
        manager_state_machine.activationRequestCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.INITIALIZING_STATE)

    ##Method test_initial_activation_request_false
    #
    #@param self the object pointer
    def test_initial_activation_request_false(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(False)
        manager_state_machine.activationRequestCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.INITIALIZING_STATE)

    ##Method test_initial_fault_true
    #
    #@param self the object pointer
    def test_initial_fault_true(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(True)
        manager_state_machine.faultCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    ##Method test_initial_fault_false
    #
    #@param self the object pointer
    def test_initial_fault_false(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(False)
        manager_state_machine.faultCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.INITIALIZING_STATE)

    ##A method to test all transitions from enabled state
    #@param self the object pointer
    def test_enabled_initial_checks_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.initialChecksCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE)

    ##Method test_enabled_initial_checks_false
    #
    #@param self the object pointer
    def test_enabled_initial_checks_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.initialChecksCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE)

    ##Method test_enabled_activation_request_true
    #
    #@param self the object pointer
    def test_enabled_activation_request_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.activationRequestCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE)

    ##Method test_enabled_activation_request_false
    #
    #@param self the object pointer
    def test_enabled_activation_request_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.activationRequestCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE)

    ##Method test_enabled_fault_true
    #
    #@param self the object pointer
    def test_enabled_fault_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.faultCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    ##Method test_enabled_fault_false
    #
    #@param self the object pointer
    def test_enabled_fault_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.faultCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE)


    ##A method to test all transitions from engaged state
    #@param self the object pointer
    def test_engaged_initial_checks_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.initialChecksCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE)

    ##Method test_engaged_initial_checks_false
    #
    #@param self the object pointer
    def test_engaged_initial_checks_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.initialChecksCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE)

    ##Method test_engaged_activation_request_true
    #
    #@param self the object pointer
    def test_engaged_activation_request_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.activationRequestCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE)

    ##Method test_engaged_activation_request_false
    #
    #@param self the object pointer
    def test_engaged_activation_request_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.activationRequestCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE)

    ##Method test_engaged_fault_true
    #
    #@param self the object pointer
    def test_engaged_fault_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.faultCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    ##Method test_engaged_fault_false
    #
    #@param self the object pointer
    def test_engaged_fault_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.faultCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE)

    ##A method to test all transitions from fault state
    #@param self the object pointer
    def test_fault_initial_checks_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.initialChecksCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    ##Method test_fault_initial_checks_false
    #
    #@param self the object pointer
    def test_fault_initial_checks_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.initialChecksCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    ##Method test_fault_activation_request_true
    #
    #@param self the object pointer
    def test_fault_activation_request_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.activationRequestCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    ##Method test_fault_activation_request_false
    #
    #@param self the object pointer
    def test_fault_activation_request_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.activationRequestCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    ##Method test_fault_fault_true
    #
    #@param self the object pointer
    def test_fault_fault_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.faultCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

    ##Method test_fault_fault_false
    #
    #@param self the object pointer
    def test_fault_fault_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.faultCallback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE)

##A class to test for the feature starting and stopping, to be developed
#A child class to the unittest.TestCase class. 
class ManagerFeaturesHandlerTester(unittest.TestCase):

    @unittest.skip("demonstrating skipping")
    ##A method to test the start of all of the features without test automation.
    #@param self the object pointer
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
    ##A method to test the start of all of the features with test automation.
    #@param self the object pointer
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
            

##A class to realise tests of the manager class, child class of the @unittest.TestCase class.
# A few functions of the manager class have been skipped out of testing :- 
# switchCallBack() and checkSafetyChannel()  - these functions listens to switch messages and prints out an warning message to a logger file if the safety channel is not active
# startRecording() and stopRecording() - these functions starts the rosbag recording process and starts the scrits for stopping the process
# Manger class publishes on three topics.Tests are written only for one topic manger/features.
# Since the tests written for checking the major features of manager node, are running ok, we can assume that the main functionalities of the manager node are working okay and the other test functions can be skipped for now.
class ManagerTester(unittest.TestCase):

    ##A method to test if the manager remains alive despite an invalid XML syntax in a feature launch file.
    #@param self the object pointer
    def testInvalidXML(self):
        with open("../../launch/my_map.launch", "r+") as f:
            old_content = f.read()  # back up the launch file
            f.seek(0)  # rewind
            f.write("!" + old_content)  # add a character making the launch file invalid
        startROS()
        rospy.init_node('AD-EYE_Manager')
        manager = Manager()
        try:
            manager.runOnce()
        except Exception as exc:  # errors happened and test failed but we should clean up
            stopROS()
            with open("../../launch/my_map.launch", "r+") as f:  # restore the original launch file if it failed
                f.write(old_content)
            raise exc
        rospy.sleep(5)  # let nodes start a bit
        # number_of_nodes_running = len(get_node_names())
        is_manager_alive = rosnode_ping("/AD-EYE_Manager", 1)  # checks if /manager is still alive
        with open("../../launch/my_map.launch", "w") as f:  # restore the original launch file
            f.write(old_content)
        stopROS()
        self.assertEquals(is_manager_alive, True)

    #The following methods are used to test whether the features added are allowed for the initial state
    #
    #@param self the object pointer
    def test_initial_feature_request_1(self):
        startROS()
        manager = Manager()    
        test_msg = Int32MultiArray()
        test_msg.data = [1,1,1,1,1,1,1,1,1,1,1,1]
        manager.featuresRequestCallback(test_msg)
        expected_features = manager.INITIALIZING_ALLOWED_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i], expected_features[i])

    def test_initial_feature_request_2(self):
        startROS()
        manager = Manager()    
        test_msg = Int32MultiArray()
        test_msg.data = [0,0,0,0,0,0,0,0,0,0,0,0]
        manager.featuresRequestCallback(test_msg)
        expected_features = []
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i], expected_features[i])

    def test_initial_feature_request_3(self):
        startROS()
        manager = Manager()    
        test_msg = Int32MultiArray()
        test_msg.data = [0,1,1,0,1,0,1,1,1,1,1,0]
        manager.featuresRequestCallback(test_msg)
        expected_features = manager.INITIALIZING_ALLOWED_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i], expected_features[i]) 
    #The following methods are used to test whether the features added are allowed for the enabled state
    #
    #@param self the object pointer   
    def test_enabled_feature_request_1(self):
        startROS()
        manager = Manager() 
        getStateMachineToEnabled(manager.manager_state_machine)  
        test_msg = Int32MultiArray()
        test_msg.data = [1,1,1,1,1,1,1,1,1,1,1,1]
        manager.featuresRequestCallback(test_msg)
        expected_features = manager.ENABLED_ALLOWED_FEATURES 
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i], expected_features[i])

    def test_enabled_feature_request_2(self):
        startROS()
        manager = Manager()  
        getStateMachineToEnabled(manager.manager_state_machine)  
        test_msg = Int32MultiArray()
        test_msg.data = [0,0,0,0,0,0,0,0,0,0,0,0]
        manager.featuresRequestCallback(test_msg)
        expected_features = [ ]
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i], expected_features[i])

    def test_enabled_feature_request_3(self):
        startROS()
        manager = Manager() 
        getStateMachineToEnabled(manager.manager_state_machine)   
        test_msg = Int32MultiArray()
        test_msg.data = [0,1,1,0,1,1,1,1,1,1,1,0]
        manager.featuresRequestCallback(test_msg)
        expected_features = manager.ENABLED_ALLOWED_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i], expected_features[i])

    #The following methods are used to test whether the features added are allowed for the engaged state
    #
    #@param self the object pointer

    def test_engaged_feature_request_1(self):
        startROS() 
        manager = Manager()
        getStateMachineToEngaged(manager.manager_state_machine)
        test_msg = Int32MultiArray()
        test_msg.data = [1,1,1,1,1,1,1,1,1,1,1,1]
        manager.featuresRequestCallback(test_msg)
        expected_features = manager.ENGAGED_ALLOWED_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i], expected_features[i])

    def test_engaged_feature_request_2(self):
        startROS()
        manager = Manager() 
        getStateMachineToEngaged(manager.manager_state_machine) 
        test_msg = Int32MultiArray()
        test_msg.data = [0,0,0,0,0,0,0,0,0,0,0,0]
        manager.featuresRequestCallback(test_msg)
        expected_features = []
        stopROS()
        for i in range(len(expected_features)):
            self.assertEqual(manager.current_features[i],expected_features[i])

    #The following methods are used to test whether the features added are allowed for the fault state
    #
    #@param self the object pointer
    def test_fault_feature_request_1(self):
        startROS()
        manager = Manager() 
        getStateMachineToFault(manager.manager_state_machine)   
        test_msg = Int32MultiArray()
        test_msg.data = [1,1,1,1,1,1,1,1,1,1,1,1]
        manager.featuresRequestCallback(test_msg)
        expected_features = manager.FAULT_ALLOWED_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])

    def test_fault_feature_request_2(self):
        startROS()
        manager = Manager()  
        getStateMachineToFault(manager.manager_state_machine)  
        test_msg = Int32MultiArray()
        test_msg.data = [0,0,0,0,0,0,0,0,0,0,0,0]
        manager.featuresRequestCallback(test_msg)
        expected_features = [ ]
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])

    def test_fault_feature_request_3(self):
        startROS() 
        manager = Manager() 
        getStateMachineToFault(manager.manager_state_machine)   
        test_msg = Int32MultiArray()
        test_msg.data = [0,1,1,1,1,0,1,1,1,1,1,0]
        manager.featuresRequestCallback(test_msg)
        expected_features = manager.FAULT_ALLOWED_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])

    #The following method is  used to test whether the Manager state has the corresponding features when it is in  the initial_state
    #
    #@param self the object pointer

    def test_manager_initial_state(self):
        startROS()
        manager = Manager()
        manager.checkManagerState()
        expected_features = manager.INITIALIZING_DEFAULT_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])

    #The following method is  used to test whether the Manager state, when it is changed to the enabled_state from the other three states has the corresponding features 
    #
    #@param self the object pointer
    def test_manager_enabled_state_1(self):
        startROS()
        manager = Manager()  
        manager.state =manager.manager_state_machine.States.INITIALIZING_STATE
        getStateMachineToEnabled(manager.manager_state_machine)
        manager.checkManagerState()
        expected_features = manager.ENABLED_DEFAULT_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])

    def test_manager_enabled_state_2(self):
        startROS()
        manager = Manager()
        manager.state = manager.manager_state_machine.States.ENGAGED_STATE
        getStateMachineToEnabled(manager.manager_state_machine)
        manager.checkManagerState()
        expected_features = manager.ENABLED_DEFAULT_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])

    def test_manager_enabled_state_3(self):
        startROS()
        manager = Manager() 
        manager.state =manager.manager_state_machine.States.FAULT_STATE
        getStateMachineToEnabled(manager.manager_state_machine)
        manager.checkManagerState()
        expected_features = manager.ENABLED_DEFAULT_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])


    #The following methods are  used to test whether the Manager state, when it is changed to the engaged_state ,from the other three states, has the corresponding features 
    #
    #@param self the object pointer
    def test_manager_engaged_state_1(self):
        startROS()
        manager = Manager()
        manager.state = manager.manager_state_machine.States.INITIALIZING_STATE
        getStateMachineToEngaged(manager.manager_state_machine)
        manager.checkManagerState()
        expected_features = manager.ENGAGED_DEFAULT_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])

    def test_manager_engaged_state_2(self):
        startROS()
        manager = Manager()
        manager.state = manager.manager_state_machine.States.ENABLED_STATE
        getStateMachineToEngaged(manager.manager_state_machine)
        manager.checkManagerState()
        expected_features = manager.ENGAGED_DEFAULT_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])

    def test_manager_engaged_state_3(self):
        startROS()
        manager = Manager()
        manager.state = manager.manager_state_machine.States.FAULT_STATE
        getStateMachineToEngaged(manager.manager_state_machine)
        manager.checkManagerState()
        expected_features = manager.ENGAGED_DEFAULT_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])

    #The following methods are  used to test whether the Manager state when it is changed to the enabled_state from the other three states has the corresponding features 
    #
    #@param self the object pointer
    def test_manager_fault_state_1(self):
        startROS()
        rospy.init_node('AD-EYE_Manager')
        manager = Manager()
        manager.state = manager.manager_state_machine.States.INITIALIZING_STATE
        getStateMachineToFault(manager.manager_state_machine)
        manager.checkManagerState()
        expected_features = manager.FAULT_DEFAULT_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])

    def test_manager_fault_state_2(self):
        startROS()
        rospy.init_node('AD-EYE_Manager')
        manager = Manager()
        manager.state = manager.manager_state_machine.States.ENGAGED_STATE
        getStateMachineToFault(manager.manager_state_machine)
        manager.checkManagerState()
        expected_features = manager.FAULT_DEFAULT_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])

    def test_manager_fault_state_3(self):
        startROS()
        rospy.init_node('AD-EYE_Manager')
        manager = Manager()
        manager.state = manager.manager_state_machine.States.ENABLED_STATE
        getStateMachineToFault(manager.manager_state_machine)
        manager.checkManagerState()
        expected_features = manager.FAULT_DEFAULT_FEATURES
        stopROS()
        for i in range(len(expected_features)):
            self.assertSequenceEqual(manager.current_features[i],expected_features[i])

    #The following methods are used to test whether the Manager is publishing the corresponding boolean list of active features 
    #
    #@param self the object pointer
    def test_booleanlist_active_features_case_1(self):
        startROS()
        manager = Manager()
        expected_output = [0 for i in range(len(manager.manager_features_handler.features))]
        manager.current_features = []
        for feature_index in range(len(manager.manager_features_handler.features)):
            if expected_output[feature_index] == 1:
                manager.current_features.append(manager.manager_features_handler.features.keys()[feature_index])
        state_array = Int32MultiArray()
        state_array = manager.getBooleanListActiveFeatures() 
        stopROS()
        self.assertEqual(state_array.data,expected_output)

    def test_booleanlist_active_features_case_2(self):
        startROS()
        manager = Manager()             
        expected_output = [1 for i in range(len(manager.manager_features_handler.features))]
        manager.current_features = []
        for feature_index in range(len(manager.manager_features_handler.features)):
            if expected_output[feature_index] == 1:
                manager.current_features.append((manager.manager_features_handler.features.keys()[feature_index]))
        state_array = Int32MultiArray()      
        state_array = manager.getBooleanListActiveFeatures() 
        stopROS()
        self.assertEqual(state_array.data,expected_output)

    def test_booleanlist_active_features_case_3(self):
        startROS()
        manager = Manager()             
        expected_output = [1 if i%2 == 0 else 0 for i in range(len(manager.manager_features_handler.features))]
        manager.current_features = []
        for feature_index in range(len(manager.manager_features_handler.features)):
            if expected_output[feature_index] == 1:
                manager.current_features.append((manager.manager_features_handler.features.keys()[feature_index]))
        state_array = Int32MultiArray()      
        state_array = manager.getBooleanListActiveFeatures()
        stopROS()
        self.assertEqual(state_array.data,expected_output)

if __name__ == '__main__':
    import rosunit
    import rostest
    rostest.unitrun(PKG, 'Manager_test_results_features_handler', ManagerFeaturesHandlerTester)
    # rostest.rosrun(PKG, 'Manager_test_results', ManagerTester)
    rostest.unitrun(PKG, 'Manager_test_results_state_machine', ManagerStateMachineTester)
