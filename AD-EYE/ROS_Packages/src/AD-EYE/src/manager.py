#!/usr/bin/env python
# license removed for brevity
import rospy
import rospkg
from std_msgs.msg import Int32MultiArray
from std_msgs.msg import Bool
from std_msgs.msg import Int8
from FeatureControl import FeatureControl # it handles the starting and stopping of features (launch files)
import subprocess, os # to record rosbags using the command line, os is used to manage SIGINT
from enum import Enum # to make enumaration (in particular the features enumeration)
import time # to put timestamp in rosbags' names
import sys



# Symbolic names to access active_features (basically an enum)
class Features(Enum):
    RECORDING = 0
    MAP = 1
    SENSING = 2
    LOCALIZATION = 3
    FAKE_LOCALIZATION = 4
    DETECTION = 5
    MISSION_PLANNING = 6
    MOTION_PLANNING = 7
    SWITCH = 8
    SSMP = 9
    RVIZ = 10



# Basic folder locations
rospack = rospkg.RosPack()
ADEYE_PACKAGE_LOCATION = rospack.get_path('adeye')+"/"
MODIFIED_LAUNCH_FILES_LOCATION = "modified_launch_files/"
LAUNCH_FOLDER_LOCATION = "launch/"

# Names of each launch file
RVIZ_LAUNCH_FILE_NAME = "my_rviz.launch"
MAP_LAUNCH_FILE_NAME = "my_map.launch"
LOCALIZATION_LAUNCH_FILE_NAME = "my_localization.launch"
FAKE_LOCALIZATION_LAUNCH_FILE_NAME = "my_fake_localization.launch"
SENSING_LAUNCH_FILE_NAME = "my_sensing.launch"
DETECTION_LAUNCH_FILE_NAME = "my_detection.launch"
SWITCH_LAUNCH_FILE_NAME = "switch.launch"
MISSION_PLANNING_LAUNCH_FILE_NAME = "my_mission_planning.launch"
MOTION_PLANNING_LAUNCH_FILE_NAME = "my_motion_planning.launch"
SSMP_LAUNCH_FILE_NAME = "SSMP.launch"

# Full path to each launch file
RVIZ_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, RVIZ_LAUNCH_FILE_NAME))
MAP_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, MAP_LAUNCH_FILE_NAME))
LOCALIZATION_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, LOCALIZATION_LAUNCH_FILE_NAME))
FAKE_LOCALIZATION_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, FAKE_LOCALIZATION_LAUNCH_FILE_NAME))
SENSING_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, SENSING_LAUNCH_FILE_NAME))
DETECTION_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, DETECTION_LAUNCH_FILE_NAME))
SWITCH_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, SWITCH_LAUNCH_FILE_NAME))
MISSION_PLANNING_FULL_PATH = (
        "%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, MISSION_PLANNING_LAUNCH_FILE_NAME))
MOTION_PLANNING_FULL_PATH = (
        "%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, MOTION_PLANNING_LAUNCH_FILE_NAME))
SSMP_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, SSMP_LAUNCH_FILE_NAME))



# Sleep times for system to finish resource intensive tasks/ receive control signals
MAP_START_WAIT_TIME = 8
LOCALIZATION_START_WAIT_TIME = 8
LOCALIZATION_STOP_WAIT_TIME = 5
DETECTION_STOP_WAIT_TIME = 5
MISSION_PLANNING_START_WAIT_TIME = 2
MISSION_PLANNING_STOP_WAIT_TIME = 5
MOTION_PLANNING_STOP_WAIT_TIME = 5

#  ---------------------------------------------------------------------------------------------------------------------
# states numbering, a number is given to each state to make sure they are unique
INITIALIZING_STATE_NB = 0
ENABLED_STATE_NB = 1
ENGAGED_STATE_NB = 2
FAULT_STATE_NB = 3
current_state_nb = INITIALIZING_STATE_NB #this is the current state of the state machine


# actual states (what features they have enables)
# FEATURES ORDER:         [RECORDING,     MAP,      SENSING,  LOCALIZATION, FAKE_LOCALIZATION, DETECTION, MISSION_PLANNING, MOTION_PLANNING, SWITCH,   SSMP, RVIZ]      # DISABLED = false = wait | ENABLED = True = run
INITIALIZING_STATE =      [    False,    True,        False,         False,             False,     False,             True,           False,   True,  False, True]
ENABLED_STATE =           [    False,    True,        False,         False,             False,     False,             True,           False,   True,  False, True]
ENGAGED_STATE =           [     True,    True,         True,          False,             True,      True,             True,            True,   True,   True, True]
FAULT_STATE =             [    False,    True,         True,          False,             True,      True,             True,           False,   True,   True, True]
FEATURES_STATE_LIST = [INITIALIZING_STATE, ENABLED_STATE, ENGAGED_STATE, FAULT_STATE]

# saves the previous state so that we can detect changes
previous_state =          [    False,   False,        False,         False,             False,     False,            False,           False,  False,   False,False]
# holds the current state of  the features
current_state =  INITIALIZING_STATE





# Rosbag related constants
ROSBAG_PATH = "/test" + str(time.time()) + ".bag" # ~ is added as a prefix, name of the bag
ROSBAG_COMMAND = "rosbag record -a -O ~" + ROSBAG_PATH +" __name:=rosbag_recorder" # command to start the rosbag


# callback listening to
def state_callback(msg):
    global current_state
    if msg.data != current_state:
        rospy.loginfo("Message received")
        current_state = msg.data


## callback to switch from initializing to enabled, listens to /initial_check
def initial_check_callback(msg):
    global current_state_nb
    global current_state
    global INITIALIZING_STATE_NB
    global ENABLED_STATE_NB
    global ENABLED_STATE
    if msg.data == True:
        if current_state_nb == INITIALIZING_STATE_NB:
            rospy.loginfo("Entering Enabled state")
            current_state_nb = ENABLED_STATE_NB
            current_state = ENABLED_STATE
            rospy.loginfo("System can be activated")

## callback to switch from enabled to engaged or the other way
def activation_callback(msg):
    global current_state_nb
    global current_state
    global ENABLED_STATE_NB
    global ENGAGED_STATE
    global INITIALIZING_STATE_NB
    global FAULT_STATE_NB
    if msg.data == True:
        if current_state_nb == ENABLED_STATE_NB:
            rospy.loginfo("Entering Engaged state")
            current_state = ENGAGED_STATE
            current_state_nb = ENGAGED_STATE_NB
            # start rosbag
            # rosbag_proc = subprocess.Popen(ROSBAG_COMMAND, shell=True, executable='/bin/bash')

        else:
            if current_state_nb == INITIALIZING_STATE_NB:
                rospy.loginfo("Activation attempt failed as system was still initializing")
            if current_state_nb == FAULT_STATE_NB:
                rospy.loginfo("Activation attempt failed as system was in fault state")
    else: #deactivation
        if current_state_nb == ENGAGED_STATE_NB:
            rospy.loginfo("Entering Enabled state from Engaged")
            current_state = ENABLED_STATE
            current_state_nb = ENABLED_STATE_NB
            # save rosbag
            subprocess.Popen("rosnode kill /rosbag_recorder", shell=True, executable='/bin/bash')

## callback to switch to the fault state from any state
def fault_callback(msg):
    global current_state_nb
    global current_state
    global ENABLED_STATE_NB
    global ENGAGED_STATE_NB
    global FAULT_STATE_NB
    global FAULT_STATE
    if msg.data == True:
        if current_state_nb == ENABLED_STATE_NB:
            rospy.loginfo("Entering Fault state")
            current_state = FAULT_STATE
            current_state_nb = FAULT_STATE_NB
            rospy.loginfo("Previous state was Enabled so no data will be saved")
        elif current_state_nb == ENGAGED_STATE_NB:
            rospy.loginfo("Entering Fault state")
            current_state_nb = FAULT_STATE_NB
            current_state = FAULT_STATE
        else:
            rospy.loginfo("Entering Fault state")
            rospy.loginfo("Previous state was Initializing")
            current_state_nb = FAULT_STATE_NB
            current_state = FAULT_STATE




if __name__ == '__main__':
    # command = "rosparam set /use_sim_time false"
    # subprocess.call(command, shell=True, executable='/bin/bash')
    #
    # rosbag_proc = subprocess.Popen(ROSBAG_COMMAND, shell=True, executable='/bin/bash')
    # rospy.sleep(1.0)
    # subprocess.Popen("rosnode kill /rosbag_recorder", shell=True, executable='/bin/bash')

 
    if rospy.get_param("test_automation",False) == True:
        RVIZ_LAUNCH_FILE_NAME = "rp_my_rviz.launch"
        MAP_LAUNCH_FILE_NAME = "rp_my_map.launch"
        LOCALIZATION_LAUNCH_FILE_NAME = "rp_my_localization.launch" #changes made in the manager file
        FAKE_LOCALIZATION_LAUNCH_FILE_NAME = "rp_my_fake_localization.launch"
        SENSING_LAUNCH_FILE_NAME = "rp_my_sensing.launch"
        DETECTION_LAUNCH_FILE_NAME = "rp_my_detection.launch" #changes made in the manager file
        SWITCH_LAUNCH_FILE_NAME = "switch.launch"
        MISSION_PLANNING_LAUNCH_FILE_NAME = "rp_my_mission_planning.launch" #changes made in the manager file
        MOTION_PLANNING_LAUNCH_FILE_NAME = "rp_my_motion_planning.launch" #changes made in the manager file
        SSMP_LAUNCH_FILE_NAME = "rp_SSMP.launch"
        RVIZ_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, MODIFIED_LAUNCH_FILES_LOCATION, RVIZ_LAUNCH_FILE_NAME))
        MAP_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, MODIFIED_LAUNCH_FILES_LOCATION, MAP_LAUNCH_FILE_NAME))
        LOCALIZATION_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, MODIFIED_LAUNCH_FILES_LOCATION, LOCALIZATION_LAUNCH_FILE_NAME)) #changes made in the manager file
        FAKE_LOCALIZATION_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, MODIFIED_LAUNCH_FILES_LOCATION, FAKE_LOCALIZATION_LAUNCH_FILE_NAME))
        SENSING_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, MODIFIED_LAUNCH_FILES_LOCATION, SENSING_LAUNCH_FILE_NAME))
        DETECTION_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, MODIFIED_LAUNCH_FILES_LOCATION, DETECTION_LAUNCH_FILE_NAME)) #changes made in the manager file
        SWITCH_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, SWITCH_LAUNCH_FILE_NAME))
        MISSION_PLANNING_FULL_PATH = (
                "%s%s%s" % (ADEYE_PACKAGE_LOCATION, MODIFIED_LAUNCH_FILES_LOCATION, MISSION_PLANNING_LAUNCH_FILE_NAME)) #changes made in the manager file
        MOTION_PLANNING_FULL_PATH = (
                "%s%s%s" % (ADEYE_PACKAGE_LOCATION, MODIFIED_LAUNCH_FILES_LOCATION, MOTION_PLANNING_LAUNCH_FILE_NAME)) #changes made in the manager file
        SSMP_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, MODIFIED_LAUNCH_FILES_LOCATION, SSMP_LAUNCH_FILE_NAME))




    rospy.init_node('ADEYE_Manager')
    rospy.loginfo("ADEYE Manager: Started")

    # Set up subscribers for registering simulink control command
    rospy.Subscriber("/Features_state", Int32MultiArray, state_callback)
    # Set up subscribers for registering state switch command
    rospy.Subscriber("/initial_checks", Bool, initial_check_callback)
    rospy.Subscriber("/activation_request", Bool, activation_callback)
    rospy.Subscriber("/fault", Bool, fault_callback)

    # publishers for the GUI
    state_pub = rospy.Publisher('manager/state', Int8, queue_size=1)
    features_pub = rospy.Publisher('manager/features', Int32MultiArray, queue_size=1)

    # Create a FeatureControl objects and put them in the active_feature list
    active_features = []
    active_features.append(FeatureControl(MAP_FULL_PATH, "MAP", MAP_START_WAIT_TIME))
    active_features.append(FeatureControl(SENSING_FULL_PATH, "Sensing"))
    active_features.append(FeatureControl(LOCALIZATION_FULL_PATH, "Localization", LOCALIZATION_START_WAIT_TIME,
                                  LOCALIZATION_STOP_WAIT_TIME))
    active_features.append(FeatureControl(FAKE_LOCALIZATION_FULL_PATH, "Fake_Localization"))
    active_features.append(FeatureControl(DETECTION_FULL_PATH, "Detection", sleep_time_on_stop=DETECTION_STOP_WAIT_TIME))
    active_features.append(FeatureControl(MISSION_PLANNING_FULL_PATH, "Mission_Planning", MISSION_PLANNING_START_WAIT_TIME,
                                      MISSION_PLANNING_STOP_WAIT_TIME))
    active_features.append(FeatureControl(MOTION_PLANNING_FULL_PATH, "Motion_Planning",
                                     sleep_time_on_stop=MOTION_PLANNING_STOP_WAIT_TIME))
    active_features.append(FeatureControl(SWITCH_FULL_PATH, "Switch"))
    active_features.append(FeatureControl(SSMP_FULL_PATH, "SSMP"))
    active_features.append(FeatureControl(RVIZ_FULL_PATH, "Rviz"))



    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():


        # regularly check at if the set of active features has changed
        if current_state != previous_state:

            # this ensures we do not have more features enables than the ones currently allowed (defined by FEATURES_STATE_LIST[current_state_nb])
            current_state = current_state and FEATURES_STATE_LIST[current_state_nb]



            for i in range(0,len(previous_state)):
                if previous_state[i] != current_state[i]:
                    # treat recording differently since it is a bash script and not a launch file
                    if i == Features.RECORDING.value:
                        if current_state[i] == True:
                            rosbag_proc = subprocess.Popen(ROSBAG_COMMAND, shell=True, executable='/bin/bash')
                        else:
                            subprocess.Popen("xterm -hold -e bash " + ADEYE_PACKAGE_LOCATION + "/sh/rosbag_stop ~/"+ROSBAG_PATH , shell=True, preexec_fn=os.setpgrp,  executable='/bin/bash')

                    else:
                        if current_state[i] == True:
                            active_features[i-1].start() #offset because recording is not in the active_features list
                        if current_state[i] == False:
                            active_features[i-1].stop()

            previous_state = current_state

        # publish the rcv state (for GUI)
        state_pub.publish(current_state_nb)
        #publish the current active features (for GUI)
        state_array = Int32MultiArray()
        state_array.data = current_state
        features_pub.publish(state_array)

        rate.sleep()
