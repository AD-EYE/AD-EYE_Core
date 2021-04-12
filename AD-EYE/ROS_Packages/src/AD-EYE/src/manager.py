#!/usr/bin/env python
# license removed for brevity

import os  # to record rosbags using the command line, os is used to manage SIGINT
import subprocess  # for recording feature
import time  # to put timestamp in rosbag names
from enum import Enum  # to make enumeration (in particular the features enumeration)

import rospkg  # to find path to AD-EYE package
import rospy  # for ROS
from std_msgs.msg import Bool
from std_msgs.msg import Int32
from std_msgs.msg import Int32MultiArray
from std_msgs.msg import Int8

from FeatureControl import FeatureControl  # handles start and stop of features
from collections import OrderedDict  # to have the features ordered


## ManagerStateMachine only contains the state machine for the manager
#
# The state machine has four states defined in the States enum. The class listens to the topic containing the
# transition requests and performs the allowed transitions or prints an error message.
class ManagerStateMachine:
    # States of the machine
    class States(Enum):
        INITIALIZING_STATE = 0
        ENABLED_STATE = 1
        ENGAGED_STATE = 2
        FAULT_STATE = 3
    current_state = States.INITIALIZING_STATE  # this is the current state of the state machine

    ## Constructor
    def __init__(self):
        # Set up subscriber for registering state switch commands
        rospy.Subscriber("/initial_checks", Bool, self.initial_checks_callback)
        rospy.Subscriber("/activation_request", Bool, self.activation_request_callback)
        rospy.Subscriber("/fault", Bool, self.fault_callback)

    ## Returns the state the machine is currently in
    def getState(self):
        return self.current_state

    ## Help function for message display when invalid transition is requested
    def printRefusedRequest(self):
        rospy.loginfo("Request refused. Manager will stay in" + self.getState().name)

    ## Callback to switch from initializing to enabled, listens to /initial_checks
    def initial_checks_callback(self, msg):
        if msg.data and self.current_state == self.States.INITIALIZING_STATE:
            rospy.loginfo("Entering Enabled state")
            self.current_state = self.States.ENABLED_STATE
            rospy.loginfo("System can be activated")
        else:
            self.printRefusedRequest()

    ## Callback to switch from enabled to engaged or the other way, listens to /activation_request
    def activation_request_callback(self, msg):
        if msg.data and self.current_state == self.States.ENABLED_STATE:
            rospy.loginfo("Entering Engaged state")
            self.current_state = self.States.ENGAGED_STATE
        elif not msg.data and self.current_state == self.States.ENGAGED_STATE:  # deactivation
            rospy.loginfo("Entering Enabled state from Engaged")
            self.current_state = self.States.ENABLED_STATE
        else:
            self.printRefusedRequest()

    ## Callback to switch to the fault state from any state, listens to /fault
    def fault_callback(self, msg):
        if msg.data:
            rospy.loginfo("Entering Fault state")
            self.current_state = self.States.FAULT_STATE
        else:
            self.printRefusedRequest()

## Feature wrapper for convininence of the ManagerFeaturesHandler class
class Feature:
    name = ""
    path = ""
    start_delay = 0
    stop_delay = 0

    ## Constructor
    #  @param name Feature name
    #  @param path Path to feature launch file
    #  @param start_delay How long should we wait before starting the feature
    #  @param stop_delay How long should we wait before stopping the feature
    def __init__(self, name, path, start_delay, stop_delay):
        self.name = name
        self.path = path
        self.start_delay = start_delay
        self.stop_delay = stop_delay

    ## Creates the FeatureControl object whcich will be used to start and stop the features
    def createFeatureControl(self):
        self.featureControl = FeatureControl(self.path, self.name, self.start_delay, self.stop_delay)

## Class handling all the features as well as performing the launch files paths construction
class ManagerFeaturesHandler:
    features = OrderedDict()
    # Ordered dictionary object                 = Feature(Feature_name,                    launch_file_name,              start_delay, stop_delay)
    features["Recording"]                       = Feature("Recording",                     "",                            0,           0)
    features["Map"]                             = Feature("Map",                           "my_map.launch",               8,           0)
    features["Sensing"]                         = Feature("Sensing",                       "my_sensing.launch",           0,           0)
    features["Localization"]                    = Feature("Localization",                  "my_localization.launch",      8,           5)
    features["Fake_Localization"]               = Feature("Fake_Localization",             "my_fake_localization.launch", 0,           0)
    features["Detection"]                       = Feature("Detection",                     "my_detection.launch",         0,           5)
    features["Mission_Planning"]                = Feature("Mission_Planning",              "my_mission_planning.launch",  2,           5)
    features["Motion_Planning"]                 = Feature("Motion_Planning",               "my_motion_planning.launch",   0,           5)
    features["Switch"]                          = Feature("Switch",                        "switch.launch",               0,           0)
    features["SSMP"]                            = Feature("SSMP",                          "SSMP.launch",                 0,           0)
    features["Rviz"]                            = Feature("Rviz",                          "my_rviz.launch",              0,           0)
    features["Experiment_specific_recording"]   = Feature("Experiment_specific_recording", "",                            0,           0)

    ## Constructor
    def __init__(self):
        self.createLaunchPaths()
        self.createFeaturesControls()

    ## Constructs the launch files paths from their names and whether we use Test Automation or not
    def createLaunchPaths(self):
        # Basic folder locations
        rospack = rospkg.RosPack()
        adeye_package_path = rospack.get_path('adeye') + "/"
        launch_folder = "launch/"

        if rospy.get_param("test_automation", False):
            launch_folder = "modified_launch_files/"
            for key in self.features:
                self.features[key].path = "rp_" + self.features[key].path

        for key in self.features:
            self.features[key].path = adeye_package_path + launch_folder + self.features[key].path

        self.features["Experiment_specific_recording"].path = "/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE" \
                                                              "/launch/ExperimentA.launch "
        self.features["Recording"].path = ""

    ## Creates the FeaturesControl objects, must be called after the launch paths are constructed
    def createFeaturesControls(self):
        for key in self.features:
            self.features[key].createFeatureControl()


class Manager:
    INITIALIZING_FEATURES = [
        # "Recording",
        "Map",
        # "Sensing",
        # "Localization",
        # "Fake_Localization",
        # "Detection",
        # "Mission_Planning",
        # "Motion_Planning",
        "Switch",
        # "SSMP",
        "Rviz",
        # "Experiment_specific_recording"
    ]
    ENABLED_FEATURES = [
        # "Recording",
        "Map",
        # "Sensing",
        # "Localization",
        # "Fake_Localization",
        # "Detection",
        # "Mission_Planning",
        # "Motion_Planning",
        "Switch",
        # "SSMP",
        "Rviz",
        # "Experiment_specific_recording"
    ]
    ENGAGED_FEATURES = [
        # "Recording",
        "Map",
        "Sensing",
        # "Localization",
        "Fake_Localization",
        "Detection",
        "Mission_Planning",
        "Motion_Planning",
        "Switch",
        "SSMP",
        "Rviz",
        # "Experiment_specific_recording"
    ]
    FAULT_FEATURES = [
        # "Recording",
        "Map",
        "Sensing",
        # "Localization",
        "Fake_Localization",
        # "Detection",
        # "Mission_Planning",
        # "Motion_Planning",
        "Switch",
        "SSMP",
        "Rviz",
        # "Experiment_specific_recording"
    ]
    previous_features = []
    current_features = INITIALIZING_FEATURES

    # Rosbag related constants
    ROSBAG_PATH = "/recording" + str(time.time()) + ".bag"  # ~ is added as a prefix, name of the bag
    ROSBAG_COMMAND = "rosbag record -a -O ~" + ROSBAG_PATH + " __name:=rosbag_recorder"  # command to start the rosbag

    # To output an error message when safety channel is not running
    last_switch_time = 0
    last_switch_time_initialized = False
    SWITCH_TIME_THRESHOLD = 3  # after this amount of time (sec) the manager will write an error message if nothing is received from the safety supervisor

    ## Constructor
    def __init__(self):
        self.manager_state_machine = ManagerStateMachine()
        self.current_state = self.manager_state_machine.States.INITIALIZING_STATE
        self.manager_features_handler = ManagerFeaturesHandler()
        rospy.Subscriber("/Features_state", Int32MultiArray, self.featuresRequestCallback)
        rospy.Subscriber("/switchCommand", Int32, self.switchCallback)
        self.state_pub = rospy.Publisher('manager/state', Int8, queue_size=1)  # for GUI
        self.features_pub = rospy.Publisher('manager/features', Int32MultiArray, queue_size=1)  # for GUI

    ## Main loop
    def run(self):
        rate = rospy.Rate(10.0)
        while not rospy.is_shutdown():
            self.checkSafetyChannel()  # checks if safety channel is active, if not prints warning
            self.checkManagerState()  # check state of the state machine and updates current features accordingly
            if self.current_features != self.previous_features:  # checks if the list of active features has changed
                self.updateFeatures()

            self.state_pub.publish(self.manager_state_machine.getState())  # publish the state machine state (for GUI)
            self.publishActiveFeatures()  # publish the current active features (for GUI)

            rate.sleep()

    ## Callback listening to the features requests (features that we want to activate/deactivate)
    def featuresRequestCallback(self, msg):
        message_features = []
        allowed_features = self.getAllowedFeatures()
        for i in range(len(msg.data)):
            if msg.data[i] == 1:
                if self.manager_features_handler.features.keys()[i] in allowed_features:
                    message_features.append(self.manager_features_handler.features.keys()[i])
        self.current_features = message_features

    ## Callback listening to switch messages, to make sure the safety channel is still active
    def switchCallback(self, msg):
        self.last_switch_time = rospy.Time.now()
        self.last_switch_time_initialized = True

    ## Checks if the a message from the safety channel has been recived recently, if not prints warning
    def checkSafetyChannel(self):
        if self.last_switch_time_initialized:
            if (rospy.Time.now() - self.last_switch_time).to_sec() > self.SWITCH_TIME_THRESHOLD:
                rospy.logerr("No message from the safety channel")

    ## Gets the list of allowed features based on the manager's state
    def getAllowedFeatures(self):
        state = self.manager_state_machine.getState()
        if state == self.manager_state_machine.States.INITIALIZING_STATE:
            return self.INITIALIZING_FEATURES
        elif state == self.manager_state_machine.States.ENABLED_STATE:
            return self.ENABLED_FEATURES
        elif state == self.manager_state_machine.States.ENGAGED_STATE:
            return self.ENGAGED_FEATURES
        elif state == self.manager_state_machine.States.FAULT_STATE:
            return self.FAULT_FEATURES

    ## Checks if the manager state has changed. If so, updates the current features list
    def checkManagerState(self):
        state = self.manager_state_machine.getState()
        if state != self.current_state:  # the state has changed since last iteration
            self.current_state = state
            if state == self.manager_state_machine.States.INITIALIZING_STATE:
                self.current_features = self.INITIALIZING_FEATURES
            elif state == self.manager_state_machine.States.ENABLED_STATE:
                self.current_features = self.ENABLED_FEATURES
            elif state == self.manager_state_machine.States.ENGAGED_STATE:
                self.current_features = self.ENGAGED_FEATURES
            elif state == self.manager_state_machine.States.FAULT_STATE:
                self.current_features = self.FAULT_FEATURES

    ## Starts the individual features based on the current feature list
    def updateFeatures(self):
        for feature_name in self.manager_features_handler.features:
            if feature_name in self.current_features and feature_name not in self.previous_features:
                if feature_name == "Recording":
                    self.startRecording()
                else:
                    self.manager_features_handler.features[feature_name].featureControl.start()
            elif feature_name not in self.current_features and feature_name in self.previous_features:
                if feature_name == "Recording":
                    self.stopRecording()
                else:
                    self.manager_features_handler.features[feature_name].featureControl.stop()
        self.previous_features = self.current_features

    ## Starts the rosbag recording process
    def startRecording(self):
        subprocess.Popen(self.ROSBAG_COMMAND, shell=True, executable='/bin/bash')

    ## Starts the scripts for stopping the rosbag recording
    def stopRecording(self):
        rospack = rospkg.RosPack()
        adeye_package_location = rospack.get_path('adeye') + "/"
        subprocess.Popen(
            "xterm -hold -e bash " + adeye_package_location + "/sh/rosbag_stop ~/" + self.ROSBAG_PATH,
            shell=True, preexec_fn=os.setpgrp, executable='/bin/bash')

    ## Publishes a list of integers (0 or 1) representig the active features (for GUI)
    def publishActiveFeatures(self):
        state_array = Int32MultiArray()
        for feature in self.manager_features_handler.features:
            if feature in self.current_features:
                state_array.data.append(1)
            else:
                state_array.data.append(0)
        self.features_pub.publish(state_array)


if __name__ == '__main__':
    rospy.init_node('AD-EYE_Manager')
    rospy.loginfo("ADEYE Manager: Started")
    manager = Manager()
    manager.run()
