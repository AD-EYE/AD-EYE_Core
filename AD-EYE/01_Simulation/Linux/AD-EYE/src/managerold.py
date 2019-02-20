#!/usr/bin/env python
# license removed for brevity
import rospy
import roslaunch
import math as m
from std_msgs.msg import Int32
import time
    
state=0 # 0=wait | 1=run

uuid3 = roslaunch.rlutil.get_or_generate_uuid(None, False)
roslaunch.configure_logging(uuid3)
launch3 = roslaunch.parent.ROSLaunchParent(uuid3, ["/home/adeye/Autoware/ros/src/adeye/quick_start/my_localization.launch"])

#uuid4 = roslaunch.rlutil.get_or_generate_uuid(None, False)
#roslaunch.configure_logging(uuid4)
#launch4 = roslaunch.parent.ROSLaunchParent(uuid4, ["/home/adeye/Autoware/ros/src/adeye/quick_start/my_detection.launch"])

uuid5 = roslaunch.rlutil.get_or_generate_uuid(None, False)
roslaunch.configure_logging(uuid5)
launch5 = roslaunch.parent.ROSLaunchParent(uuid5, ["/home/adeye/Autoware/ros/src/adeye/quick_start/my_mission_planning.launch"])

uuid6 = roslaunch.rlutil.get_or_generate_uuid(None, False)
roslaunch.configure_logging(uuid6)
launch6 = roslaunch.parent.ROSLaunchParent(uuid6, ["/home/adeye/Autoware/ros/src/adeye/quick_start/my_motion_planning.launch"])

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
    if (data.data==1 and state==0):
        state=1
        rospy.loginfo(state)
        launch3 = roslaunch.parent.ROSLaunchParent(uuid3, ["/home/adeye/Autoware/ros/src/adeye/quick_start/my_localization.launch"])
        launch3.start()
        time.sleep(30)
        rospy.loginfo("started3")
        
        #launch4 = roslaunch.parent.ROSLaunchParent(uuid4, ["/home/adeye/Autoware/ros/src/adeye/quick_start/my_detection.launch"])
        #launch4.start()
        #rospy.loginfo("started4")
        
        launch5 = roslaunch.parent.ROSLaunchParent(uuid5, ["/home/adeye/Autoware/ros/src/adeye/quick_start/my_mission_planning.launch"])
        launch5.start()
        time.sleep(5)
        rospy.loginfo("started5")
        
        launch6 = roslaunch.parent.ROSLaunchParent(uuid6, ["/home/adeye/Autoware/ros/src/adeye/quick_start/my_motion_planning.launch"])
        launch6.start()
        rospy.loginfo("started6")
        
        
    
    if (data.data==0 and state==1):
        state=1
        rospy.loginfo(state)
        launch3.shutdown()
        time.sleep(10)
        launch5.shutdown()
        time.sleep(10)
        #launch4.shutdown()
        #time.sleep(10)
        launch6.shutdown()
        time.sleep(10)
        
        state=0
        

if __name__ == '__main__':
    rospy.init_node('manager', anonymous=True)
    rospy.loginfo( " Hello , ROS! " );

    # Launch Rviz
    uuid0 = roslaunch.rlutil.get_or_generate_uuid(None, False)
    roslaunch.configure_logging(uuid0)
    launch0 = roslaunch.parent.ROSLaunchParent(uuid0, ["/home/adeye/Autoware/ros/src/adeye/quick_start/my_rviz.launch"])
    launch0.start()
    time.sleep(5)
    rospy.loginfo("started0")

    # Launch the map
    uuid1 = roslaunch.rlutil.get_or_generate_uuid(None, False)
    roslaunch.configure_logging(uuid1)
    launch1 = roslaunch.parent.ROSLaunchParent(uuid1, ["/home/adeye/Autoware/ros/src/adeye/quick_start/my_map.launch"])
    launch1.start()
    time.sleep(60)
    rospy.loginfo("started1")

    # Launch the sensing
    uuid2 = roslaunch.rlutil.get_or_generate_uuid(None, False)
    roslaunch.configure_logging(uuid2)
    launch2 = roslaunch.parent.ROSLaunchParent(uuid2, ["/home/adeye/Autoware/ros/src/adeye/quick_start/my_sensing.launch"])
    launch2.start()
    rospy.loginfo("started2")

    # Subscribe to the Simulink_state topic
    rospy.Subscriber("/Simulink_state", Int32, mycallback)
    rospy.spin()