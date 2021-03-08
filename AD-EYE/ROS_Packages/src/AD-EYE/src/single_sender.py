#!/usr/bin/env python  
import roslib
import rospy
import tf
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped



def talker():
    goal_publisher = rospy.Publisher("move_base_simple/goal", PoseStamped, queue_size=5)

    goal = PoseStamped()

    goal.header.seq = 1
    goal.header.stamp = rospy.Time.now()
    goal.header.frame_id = "world"

    goal.pose.position.x = 257.0
    goal.pose.position.y = 170.0
    goal.pose.position.z = 0.0

    goal.pose.orientation.x = 1.0
    goal.pose.orientation.y = 0.0
    goal.pose.orientation.z = 0.0
    goal.pose.orientation.w = 0.0
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        goal_publisher.publish(goal)
        rate.sleep()

if __name__ == '__main__':
    rospy.init_node('loop', anonymous=True)
    try:
        talker()
    except rospy.ROSInterruptException:
        pass