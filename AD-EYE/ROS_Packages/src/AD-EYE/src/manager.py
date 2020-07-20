#!/usr/bin/env python
# license removed for brevity
##@image rcv_state_machine.png
"""
This file contains the RCV state manager.
The file allows the user to define states numbers in order to know which state the vehicle is in.
Also, the features of each state can be activated via features list defined in this file.

The script saves the rosbags in the path defined by the variable 'ROSBAG_PATH'

"""

import rospy
import rospkg
from std_msgs.msg import Int32MultiArray
from FeatureControl import FeatureControl

#  --------------Config: Common to more files and will be exported out--------------------------------------------------
# TODO add subscriber to get config from Simulink for enabled features, all enabled for now.
ENABLED = 1
DISABLED = 0
FEATURE_ENABLED = [True for i in range(9)]

# Symbolic names to access FEATURE_ENABLED
RVIZ = 1
MAPPING = 2
LOCALIZATION = 3
SENSING = 4
DETECTION = 5
SWITCH = 6
MISSION_PLANNING = 7
MOTION_PLANNING = 8
SSMP = 9

rospack = rospkg.RosPack()


# Basic folder locations
ADEYE_PACKAGE_LOCATION = rospack.get_path('adeye')+"/"
LAUNCH_FOLDER_LOCATION = "launch/"

# Names of each launch file
RVIZ_LAUNCH_FILE_NAME = "my_rviz.launch"
MAPPING_LAUNCH_FILE_NAME = "my_map.launch"
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
MAPPING_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, MAPPING_LAUNCH_FILE_NAME))
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
MAPPING_START_WAIT_TIME = 10
LOCALIZATION_START_WAIT_TIME = 10
LOCALIZATION_STOP_WAIT_TIME = 10
DETECTION_STOP_WAIT_TIME = 10
MISSION_PLANNING_START_WAIT_TIME = 5
MISSION_PLANNING_STOP_WAIT_TIME = 10
MOTION_PLANNING_STOP_WAIT_TIME = 10

#  ---------------------------------------------------------------------------------------------------------------------

previous_simulink_state = [DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED]  # DISABLED = 0 = wait | ENABLED = 1 = run
current_simulink_state = [DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED, DISABLED]
point_map_ready = False


def simulink_state_callback(msg):
    """
    The callback function of the subscriped topic /Simulink_state

    Parameters:
    msg: Int32MultiArray
        The published message on the topic /Simulink_state
    
    Returns:
    Creates a global variable current_simulink_state
    """
    global current_simulink_state

    if msg.data != current_simulink_state:
        rospy.loginfo("Message received")
        current_simulink_state = msg.data

if __name__ == '__main__':
    rospy.init_node('ADEYE_Manager')
    rospy.loginfo("ADEYE Manager: Started")

    # Set up subscribers for registering simulink control command
    rospy.Subscriber("/Simulink_state", Int32MultiArray, simulink_state_callback)

    # Create Feature Control objects
    Rviz = FeatureControl(RVIZ_FULL_PATH, "Rviz")
    Mapping = FeatureControl(MAPPING_FULL_PATH, "Mapping", MAPPING_START_WAIT_TIME)
    Sensing = FeatureControl(SENSING_FULL_PATH, "Sensing")
    Localization = FeatureControl(LOCALIZATION_FULL_PATH, "Localization", LOCALIZATION_START_WAIT_TIME,
                                  LOCALIZATION_STOP_WAIT_TIME)
    Fake_Localization = FeatureControl(FAKE_LOCALIZATION_FULL_PATH, "Fake_Localization")
    Detection = FeatureControl(DETECTION_FULL_PATH, "Detection", sleep_time_on_stop=DETECTION_STOP_WAIT_TIME)
    Mission_planning = FeatureControl(MISSION_PLANNING_FULL_PATH, "Mission_Planning", MISSION_PLANNING_START_WAIT_TIME,
                                      MISSION_PLANNING_STOP_WAIT_TIME)
    Motion_planning = FeatureControl(MOTION_PLANNING_FULL_PATH, "Motion_Planning",
                                     sleep_time_on_stop=MOTION_PLANNING_STOP_WAIT_TIME)
    Switch = FeatureControl(SWITCH_FULL_PATH, "Switch")
    Ssmp = FeatureControl(SSMP_FULL_PATH, "SSMP")

    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():
        if current_simulink_state != previous_simulink_state:
            if previous_simulink_state[0] != current_simulink_state[0]:
                if current_simulink_state[0] == ENABLED:
                    Rviz.start()
                if current_simulink_state[0] == DISABLED:
                    Rviz.stop()

            if previous_simulink_state[1] != current_simulink_state[1]:
                if current_simulink_state[1] == ENABLED:
                    Mapping.start()
                if current_simulink_state[1] == DISABLED:
                    Mapping.stop()

            if previous_simulink_state[2] != current_simulink_state[2]:
                if current_simulink_state[2] == ENABLED:
                    Sensing.start()
                if current_simulink_state[2] == DISABLED:
                    Sensing.stop()

            if previous_simulink_state[3] != current_simulink_state[3]:
                if current_simulink_state[3] == ENABLED:
                    Localization.start()
                if current_simulink_state[3] == DISABLED:
                    Localization.stop()

            if previous_simulink_state[4] != current_simulink_state[4]:
                if current_simulink_state[4] == ENABLED:
                    Fake_Localization.start()
                if current_simulink_state[4] == DISABLED:
                    Fake_Localization.stop()

            if previous_simulink_state[5] != current_simulink_state[5]:
                if current_simulink_state[5] == ENABLED:
                    Detection.start()
                if current_simulink_state[5] == DISABLED:
                    Detection.stop()

            if previous_simulink_state[6] != current_simulink_state[6]:
                if current_simulink_state[6] == ENABLED:
                    Mission_planning.start()
                if current_simulink_state[6] == DISABLED:
                    Mission_planning.stop()

            if previous_simulink_state[7] != current_simulink_state[7]:
                if current_simulink_state[7] == ENABLED:
                    Motion_planning.start()
                if current_simulink_state[7] == DISABLED:
                    Motion_planning.stop()

            if previous_simulink_state[8] != current_simulink_state[8]:
                if current_simulink_state[8] == ENABLED:
                    Switch.start()
                if current_simulink_state[8] == DISABLED:
                    Switch.stop()

            if previous_simulink_state[9] != current_simulink_state[9]:
                if current_simulink_state[9] == ENABLED:
                    Ssmp.start()
                if current_simulink_state[9] == DISABLED:
                    Ssmp.stop()
            previous_simulink_state = current_simulink_state
        rate.sleep()
    # Launch basic features
    #Switch.start()
    #Rviz.start()
    #Mapping.start()
    #Sensing.start()
