#!/usr/bin/env python

import rospy
from geometry_msgs.msg import PoseStamped


def get_goal(x, y):
    pose_msg = PoseStamped()
    pose_msg.header.frame_id = "world"
    pose_msg.pose.position.x = x
    pose_msg.pose.position.y = y
    pose_msg.pose.position.z = 0
    pose_msg.pose.orientation.x = 0
    pose_msg.pose.orientation.y = 0
    pose_msg.pose.orientation.z = 0.707
    pose_msg.pose.orientation.w = 0.707
    return pose_msg


if __name__ == '__main__':
    rospy.init_node('sample_goal_publisher', anonymous=True)

    x = float(rospy.get_param('~x'))
    y = float(rospy.get_param('~y'))

    pub = rospy.Publisher('/adeye/goals', PoseStamped, queue_size=1)

    rate = rospy.Rate(0.5)
    while not rospy.is_shutdown():
        pub.publish(get_goal(x, y))
        rate.sleep()
