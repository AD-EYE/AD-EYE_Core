#!/usr/bin/env python
# license removed for brevity
import time
import rospy
from std_msgs.msg import Int32
from std_msgs.msg import Bool
from roslaunch import rlutil, parent, configure_logging

#  --------------Config: Common to more files and will be exported out--------------------------------------------------
# TODO add subscriber to get config from Simulink for enabled features, all enabled for now.
FEATURE_ENABLED = [True for i in range(8)]
# Symbolic names to access FEATURE_ENABLED
RVIZ = 1
MAPPING = 2
LOCALIZATION = 3
SENSING = 4
DETECTION = 5
SWITCH = 6
MISSION_PLANNING = 7
MOTION_PLANNING = 8

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

# Sleep times for system to finish resource intensive tasks/ receive control signals
LOCALIZATION_START_WAIT_TIME = 10
LOCALIZATION_STOP_WAIT_TIME = 10
DETECTION_STOP_WAIT_TIME = 10
MISSION_PLANNING_START_WAIT_TIME = 5
MISSION_PLANNING_STOP_WAIT_TIME = 10
MOTION_PLANNING_STOP_WAIT_TIME = 10

DEFAULT_WAIT_TIME = 0.1

POINT_MAP_SLEEP_TIME = 0.05
#  ---------------------------------------------------------------------------------------------------------------------

state = 0  # 0=wait | 1=run
point_map_ready = False


class FeatureControl:

    def __init__(self, filepath):
        self.uuid = rlutil.get_or_generate_uuid(None, False)
        configure_logging(self.uuid)
        self.Launch = parent.ROSLaunchParent(self.uuid, [filepath])


def mycallback(data):
    global state
    global Localization_launch
    global Localization_uuid
    global Detection_launch
    global Detection_uuid
    global Mission_planning_launch
    global Mission_planning_uuid
    global Motion_planning_launch
    global Motion_planning_uuid
    global Switch_launch
    global Switch_uuid

    if data.data == 1 and state == 0:
        state = 1
        rospy.loginfo(state)
        Localization_launch.start()
        time.sleep(LOCALIZATION_START_WAIT_TIME)
        rospy.loginfo("started3")

        Detection.Launch.start()
        rospy.loginfo("started4")

        Mission_planning.Launch.start()
        time.sleep(MISSION_PLANNING_START_WAIT_TIME)
        rospy.loginfo("started5")

        Motion_planning.Launch.start()
        rospy.loginfo("started6")

        Switch.Launch.start()
        rospy.loginfo("MANAGER: Switch launched")

    if data.data == 0 and state == 1:
        state = 0
        rospy.loginfo(state)
        Localization_launch.shutdown()
        time.sleep(LOCALIZATION_STOP_WAIT_TIME)
        Mission_planning_launch.shutdown()
        time.sleep(MISSION_PLANNING_STOP_WAIT_TIME)
        # Detection_launch.shutdown()
        # time.sleep(DETECTION_STOP_WAIT_TIME)
        Motion_planning_launch.shutdown()
        time.sleep(MOTION_PLANNING_STOP_WAIT_TIME)
        Switch_launch.shutdown()
        # state=0


def point_map_status_callback(point_map_loader_status):
    global point_map_ready
    point_map_ready = point_map_loader_status.data


if __name__ == '__main__':
    rospy.init_node('manager', anonymous=True)
    rospy.loginfo(" Hello , ROS! ")

    # Create Feature Control object
    Rviz = FeatureControl(RVIZ_FULL_PATH)
    Mapping = FeatureControl(MAPPING_FULL_PATH)
    Localization = FeatureControl(LOCALIZATION_FULL_PATH)
    Sensing = FeatureControl(SENSING_FULL_PATH)
    Detection = FeatureControl(DETECTION_FULL_PATH)
    Switch = FeatureControl(SWITCH_FULL_PATH)
    Mission_planning = FeatureControl(MISSION_PLANNING_FULL_PATH)
    Motion_planning = FeatureControl(MOTION_PLANNING_FULL_PATH)

    # Launch Switch
    Switch.Launch.start()
    rospy.loginfo("MANAGER: Switch launched")

    # Launch Rviz
    Rviz.Launch.start()
    rospy.loginfo("MANAGER: Rviz launched")

    # Launch the map
    Mapping.Launch.start()
    rospy.loginfo("MANAGER: Map launched")

    rospy.Subscriber("/pmap_stat", Bool, point_map_status_callback)
    # Wait for point map to be loaded and signal to be received
    while not point_map_ready:
        time.sleep(POINT_MAP_SLEEP_TIME)
    rospy.loginfo("MANAGER: Map finished")

    # Launch the sensing
    Sensing.Launch.start()
    rospy.loginfo("MANAGER: Sensing launched")

    # Subscribe to the Simulink_state topic
    rospy.Subscriber("/Simulink_state", Int32, mycallback)
    rospy.spin()
