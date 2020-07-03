#!/usr/bin/env python
# license removed for brevity
import rospy
import rospkg
from std_msgs.msg import Int32MultiArray
from std_msgs.msg import Bool
from FeatureControl import FeatureControl
import subprocess, os, signal # to record rosbags using the command line

#  --------------Config: Common to more files and will be exported out--------------------------------------------------
# TODO add subscriber to get config from Simulink for enabled features, all enabled for now.
ENABLED = 1
DISABLED = 0

NB_FEATURES = 9
# Symbolic names to access FEATURE_ENABLED
RVIZ = 0
MAP = 1
SENSING = 2
LOCALIZATION = 3
FAKE_LOCALIZATION = 4
DETECTION = 5
MISSION_PLANNING = 6
MOTION_PLANNING = 7
SWITCH = 8
SSMP = 9

rospack = rospkg.RosPack()


# Basic folder locations
ADEYE_PACKAGE_LOCATION = rospack.get_path('adeye')+"/"
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
MAP_START_WAIT_TIME = 10
LOCALIZATION_START_WAIT_TIME = 10
LOCALIZATION_STOP_WAIT_TIME = 10
DETECTION_STOP_WAIT_TIME = 10
MISSION_PLANNING_START_WAIT_TIME = 5
MISSION_PLANNING_STOP_WAIT_TIME = 10
MOTION_PLANNING_STOP_WAIT_TIME = 10

#  ---------------------------------------------------------------------------------------------------------------------
# states numbering
INITIALIZING_STATE_NO = 0
ENABLED_STATE_NO = 1
ENGAGED_STATE_NO = 3
FAULT_STATE_NO = 4
current_state_no = INITIALIZING_STATE_NO


# actual states (what features they have enables)
# FEATURES ORDER:         [RVIZ,     MAP,      SENSING,  LOCALIZATION, FAKE_LOCALIZATION, DETECTION, MISSION_PLANNING, MOTION_PLANNING, SWITCH,   SSMP]      # DISABLED = 0 = wait | ENABLED = 1 = run
INITIALIZING_STATE =      [ENABLED,  ENABLED,  DISABLED, DISABLED,     DISABLED,          DISABLED,  ENABLED,          DISABLED,        ENABLED,  DISABLED]
ENABLED_STATE =           [ENABLED,  ENABLED,  DISABLED, DISABLED,     DISABLED,          DISABLED,  ENABLED,          DISABLED,        ENABLED,  DISABLED]
ENGAGED_STATE =           [ENABLED,  ENABLED,  ENABLED,  DISABLED,     ENABLED,           ENABLED,   ENABLED,          ENABLED,         ENABLED,  ENABLED]
FAULT_STATE =             [ENABLED,  ENABLED,  ENABLED,  DISABLED,     ENABLED,           ENABLED,   ENABLED,          ENABLED,         ENABLED,  ENABLED]
previous_simulink_state = [DISABLED, DISABLED, DISABLED, DISABLED,     DISABLED,          DISABLED,  DISABLED,         DISABLED,        DISABLED, DISABLED]
current_simulink_state =  INITIALIZING_STATE
# current_simulink_state =  [DISABLED, DISABLED, DISABLED, DISABLED,     DISABLED,          DISABLED,  DISABLED,         DISABLED,        DISABLED, DISABLED]

ROSBAG_PATH = "~/test.bag"
ROSBAG_COMMAND = "rosbag record /fault -O " + ROSBAG_PATH +" __name:=rosbag_recorder"
# ROSBAG_COMMAND_PROCESS = "rosbag record -O " + ROSBAG_PATH + " /fault"
rosbag_proc = 0

def simulink_state_callback(msg):
    global current_simulink_state

    if msg.data != current_simulink_state:
        rospy.loginfo("Message received")
        current_simulink_state = msg.data

def initial_check_callback(msg):
    global current_state_no
    global current_simulink_state
    global INITIALIZING_STATE_NO
    global ENABLED_STATE_NO
    global ENABLED_STATE
    if msg.data == True:
        rospy.loginfo("Entering Enabled state")
        if current_state_no == INITIALIZING_STATE_NO:
            current_state_no = ENABLED_STATE_NO
            current_simulink_state = ENABLED_STATE
        rospy.loginfo("System can be activated")


def activation_callback(msg):
    global current_state_no
    global current_simulink_state
    global ENABLED_STATE_NO
    global ENGAGED_STATE
    global INITIALIZING_STATE_NO
    global FAULT_STATE_NO
    global ROSBAG_COMMAND
    global rosbag_proc
    if msg.data == True:
        if current_state_no == ENABLED_STATE_NO:
            rospy.loginfo("Entering Engaged state")
            current_simulink_state = ENGAGED_STATE
            current_state_no = ENGAGED_STATE_NO
            # TODO start rosbag
            rosbag_proc = subprocess.Popen(command, shell=True, executable='/bin/bash')

        else:
            if current_state_no == INITIALIZING_STATE_NO:
                rospy.loginfo("Activation attempt failed as system was still initializing")
            if current_state_no == FAULT_STATE_NO:
                rospy.loginfo("Activation attempt failed as system was in fault state")
    else: #deactivation
        if current_state_no == ENGAGED_STATE_NO:
            rospy.loginfo("Entering Enabled state from Engaged")
            current_simulink_state = ENABLED_STATE
            current_state_no = ENABLED_STATE_NO
            # TODO save rosbag
            subprocess.call("rosnode kill /rosbag_recorder", shell=True, executable='/bin/bash')


def fault_callback(msg):
    global current_state_no
    global current_simulink_state
    global ENABLED_STATE_NO
    global ENGAGED_STATE_NO
    global FAULT_STATE_NO
    global FAULT_STATE
    global rosbag_proc
    if msg.data == True:
        if current_state_no == ENABLED_STATE_NO:
            rospy.loginfo("Entering Fault state")
            current_simulink_state = FAULT_STATE
            current_state_no = FAULT_STATE_NO
            rospy.loginfo("Previous state was Enabled so no data will be saved")
        elif current_state_no == ENGAGED_STATE_NO:
            rospy.loginfo("Entering Fault state")
            current_state_no = FAULT_STATE_NO
            current_simulink_state = FAULT_STATE
            rospy.loginfo("Previous state was Engaged, should the data be saved? [y/N]): ")
            txt = raw_input().lower()
            if str(txt) == "y":
                rospy.loginfo("Saving Rosbag") # TODO where it is saved
                # TODO save rosbag
                subprocess.call("rosnode kill /rosbag_recorder", shell=True, executable='/bin/bash')
            else:
                # TODO delete rosbag
                subprocess.call("rosnode kill /rosbag_recorder", shell=True, executable='/bin/bash')
                subprocess.call("rm "+ROSBAG_PATH, shell=True, executable='/bin/bash')
                rospy.loginfo("Data was deleted")
        else:
            rospy.loginfo("Entering Fault state")
            rospy.loginfo("Previous state was Initializing")
            current_state_no = FAULT_STATE_NO
            current_simulink_state = FAULT_STATE




if __name__ == '__main__':
    command = "rosparam set /use_sim_time false"
    subprocess.call(command, shell=True, executable='/bin/bash')
    # subprocess.Popen(command)

    command = "rosbag record /fault -O " + ROSBAG_PATH +" __name:=rosbag_recorder"
    rosbag_proc = subprocess.Popen(command, shell=True, executable='/bin/bash')
    rospy.sleep(1.)
    subprocess.call("rosnode kill /rosbag_recorder", shell=True, executable='/bin/bash')


    rospy.init_node('ADEYE_Manager')
    rospy.loginfo("ADEYE Manager: Started")

    # Set up subscribers for registering simulink control command
    rospy.Subscriber("/Simulink_state", Int32MultiArray, simulink_state_callback)

    rospy.Subscriber("/initial_check", Bool, initial_check_callback)
    rospy.Subscriber("/activation", Bool, activation_callback)
    rospy.Subscriber("/fault", Bool, fault_callback)

    # Create Feature Control objects and put them in the active_feature list
    active_features = []
    active_features.append(FeatureControl(RVIZ_FULL_PATH, "Rviz"))
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



    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():

        # print("in loop")

        if current_simulink_state != previous_simulink_state:

            # for i in range(0,NB_FEATURES):
            #     if previous_simulink_state[i] != current_simulink_state[i]:
            #         if current_simulink_state[i] == ENABLED:
            #             active_features[i].start()
            #         if current_simulink_state[i] == DISABLED:
            #             active_features[i].stop()

            previous_simulink_state = current_simulink_state

        # print("before sleep")
        rate.sleep()
        # rospy.spinonce()
