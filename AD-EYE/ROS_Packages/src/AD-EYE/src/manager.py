#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Int32
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

# Basic folder locations
ADEYE_PACKAGE_LOCATION = "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/"
QUICK_START_LOCATION = "quick_start/"
LAUNCH_FOLDER_LOCATION = "launch/"

# Names of each launch file
RVIZ_LAUNCH_FILE_NAME = "my_rviz.launch"
MAPPING_LAUNCH_FILE_NAME = "my_map.launch"
LOCALIZATION_LAUNCH_FILE_NAME = "my_localization.launch"
SENSING_LAUNCH_FILE_NAME = "my_sensing.launch"
DETECTION_LAUNCH_FILE_NAME = "my_detection.launch"
SWITCH_LAUNCH_FILE_NAME = "switch.launch"
MISSION_PLANNING_LAUNCH_FILE_NAME = "my_mission_planning.launch"
MOTION_PLANNING_LAUNCH_FILE_NAME = "my_motion_planning.launch"
SSMP_LAUNCH_FILE_NAME = "SSMP.launch"

# Full path to each launch file
RVIZ_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, QUICK_START_LOCATION, RVIZ_LAUNCH_FILE_NAME))
MAPPING_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, QUICK_START_LOCATION, MAPPING_LAUNCH_FILE_NAME))
LOCALIZATION_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, QUICK_START_LOCATION, LOCALIZATION_LAUNCH_FILE_NAME))
SENSING_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, QUICK_START_LOCATION, SENSING_LAUNCH_FILE_NAME))
DETECTION_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, QUICK_START_LOCATION, DETECTION_LAUNCH_FILE_NAME))
SWITCH_FULL_PATH = ("%s%s%s" % (ADEYE_PACKAGE_LOCATION, LAUNCH_FOLDER_LOCATION, SWITCH_LAUNCH_FILE_NAME))
MISSION_PLANNING_FULL_PATH = (
        "%s%s%s" % (ADEYE_PACKAGE_LOCATION, QUICK_START_LOCATION, MISSION_PLANNING_LAUNCH_FILE_NAME))
MOTION_PLANNING_FULL_PATH = (
        "%s%s%s" % (ADEYE_PACKAGE_LOCATION, QUICK_START_LOCATION, MOTION_PLANNING_LAUNCH_FILE_NAME))
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

previous_simulink_state = DISABLED  # DISABLED = 0 = wait | ENABLED = 1 = run
point_map_ready = False


def simulink_state_callback(current_simulink_state):
    global previous_simulink_state

    if previous_simulink_state != current_simulink_state.data:

        if current_simulink_state.data == ENABLED:
            Localization.start()
            Detection.start()
            Mission_planning.start()
            Motion_planning.start()
            Ssmp.start()

        if current_simulink_state.data == DISABLED:
            Localization.stop()
            Detection.stop()
            Mission_planning.stop()
            Motion_planning.stop()
            Ssmp.stop()

        previous_simulink_state = current_simulink_state.data
        rospy.loginfo("Simulink command change registered")


if __name__ == '__main__':
    rospy.init_node('ADEYE_Manager')
    rospy.loginfo("ADEYE Manager: Started")

    # Set up subscribers for registering simulink control command
    rospy.Subscriber("/Simulink_state", Int32, simulink_state_callback)

    # Create Feature Control objects
    Rviz = FeatureControl(RVIZ_FULL_PATH, "Rviz")
    Mapping = FeatureControl(MAPPING_FULL_PATH, "Mapping", MAPPING_START_WAIT_TIME)
    Localization = FeatureControl(LOCALIZATION_FULL_PATH, "Localization", LOCALIZATION_START_WAIT_TIME,
                                  LOCALIZATION_STOP_WAIT_TIME)
    Sensing = FeatureControl(SENSING_FULL_PATH, "Sensing")
    Detection = FeatureControl(DETECTION_FULL_PATH, "Detection", sleep_time_on_stop=DETECTION_STOP_WAIT_TIME)
    Switch = FeatureControl(SWITCH_FULL_PATH, "Switch")
    Mission_planning = FeatureControl(MISSION_PLANNING_FULL_PATH, "Mission_Planning", MISSION_PLANNING_START_WAIT_TIME,
                                      MISSION_PLANNING_STOP_WAIT_TIME)
    Motion_planning = FeatureControl(MOTION_PLANNING_FULL_PATH, "Motion_Planning",
                                     sleep_time_on_stop=MOTION_PLANNING_STOP_WAIT_TIME)
    Ssmp = FeatureControl(SSMP_FULL_PATH, "SSMP")

    # Launch basic features
    Switch.start()
    Rviz.start()
    Mapping.start()
    Sensing.start()

    rospy.spin()
