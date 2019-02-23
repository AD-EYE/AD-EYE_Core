#!/usr/bin/env python
# license removed for brevity
import time
import rospy
from std_msgs.msg import Int32
from std_msgs.msg import Bool
from roslaunch import rlutil, parent, configure_logging

state = 0  # 0=wait | 1=run

uuid3 = rlutil.get_or_generate_uuid(None, False)
configure_logging(uuid3)
launch3 = parent.ROSLaunchParent(uuid3, [
    "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/quick_start/my_localization.launch"])

uuid4 = rlutil.get_or_generate_uuid(None, False)
configure_logging(uuid4)
launch4 = parent.ROSLaunchParent(uuid4, [
    "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/quick_start/my_detection.launch"])

uuid5 = rlutil.get_or_generate_uuid(None, False)
configure_logging(uuid5)
launch5 = parent.ROSLaunchParent(uuid5, [
    "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/quick_start/my_mission_planning.launch"])

uuid6 = rlutil.get_or_generate_uuid(None, False)
configure_logging(uuid6)
launch6 = parent.ROSLaunchParent(uuid6, [
    "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/quick_start/my_motion_planning.launch"])

uuid7 = rlutil.get_or_generate_uuid(None, False)
configure_logging(uuid7)
launch7 = parent.ROSLaunchParent(uuid7, [
    "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/quick_start/launch/switch.launch"])

pmap_stat_bool = False


def mycallback(data):
    global state
    global launch3
    global uuid3
    global launch4
    global uuid4
    global launch5
    global uuid5
    global launch6
    global uuid6
    global launch7
    global uuid7

    if data.data == 1 and state == 0:
        state = 1
        rospy.loginfo(state)
        launch3 = parent.ROSLaunchParent(uuid3, [
            "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/quick_start/my_localization.launch"])
        launch3.start()
        time.sleep(10)
        rospy.loginfo("started3")

        launch4 = parent.ROSLaunchParent(uuid4, [
            "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/quick_start/my_detection.launch"])
        launch4.start()
        rospy.loginfo("started4")

        launch5 = parent.ROSLaunchParent(uuid5, [
            "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/quick_start/my_mission_planning.launch"])
        launch5.start()
        time.sleep(5)
        rospy.loginfo("started5")

        launch6 = parent.ROSLaunchParent(uuid6, [
            "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/quick_start/my_motion_planning.launch"])
        launch6.start()
        rospy.loginfo("started6")

        launch7 = parent.ROSLaunchParent(uuid7, [
            "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/launch/switch.launch"])
        launch7.start()
        rospy.loginfo("MANAGER: Switch launched")

    if data.data == 0 and state == 1:
        state = 0
        rospy.loginfo(state)
        launch3.shutdown()
        time.sleep(10)
        launch5.shutdown()
        time.sleep(10)
        # launch4.shutdown()
        # time.sleep(10)
        launch6.shutdown()
        time.sleep(10)
        launch7.shutdown()

        # state=0


def pmap_stat_callback(data):
    global pmap_stat_bool
    pmap_stat_bool = data.data


if __name__ == '__main__':
    rospy.init_node('manager', anonymous=True)
    rospy.loginfo(" Hello , ROS! ")

    # Launch Switch
    # uuid7 = rlutil.get_or_generate_uuid(None, False)
    # configure_logging(uuid7)
    # launch7 = parent.ROSLaunchParent(uuid7, ["/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/launch/switch.launch"])
    # launch7.start()
    # rospy.loginfo("MANAGER: Switch launched")

    # Launch Rviz
    uuid0 = rlutil.get_or_generate_uuid(None, False)
    configure_logging(uuid0)
    launch0 = parent.ROSLaunchParent(uuid0, [
        "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/quick_start/my_rviz.launch"])
    launch0.start()
    rospy.loginfo("MANAGER: Rviz launched")

    # Launch the map
    uuid1 = rlutil.get_or_generate_uuid(None, False)
    configure_logging(uuid1)
    launch1 = parent.ROSLaunchParent(uuid1, [
        "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/quick_start/my_map.launch"])
    launch1.start()
    rospy.loginfo("MANAGER: Map launched")
    rospy.Subscriber("/pmap_stat", Bool, pmap_stat_callback)
    global pmap_stat_bool
    while pmap_stat_bool == False:
        time.sleep(0.05)
    rospy.loginfo("MANAGER: Map finished")

    # Launch the sensing
    uuid2 = rlutil.get_or_generate_uuid(None, False)
    configure_logging(uuid2)
    launch2 = parent.ROSLaunchParent(uuid2, [
        "/home/naveenm/AD-EYE-WASP/AD-EYE/ROS_Packages/src/AD-EYE/quick_start/my_sensing.launch"])
    launch2.start()
    rospy.loginfo("MANAGER: Sensing launched")

    # Subscribe to the Simulink_state topic
    rospy.Subscriber("/Simulink_state", Int32, mycallback)
    rospy.spin()
