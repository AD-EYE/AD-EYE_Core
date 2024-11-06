#!/usr/bin/env python

import time
import rospy
from geometry_msgs.msg import PoseStamped


def get_goal(x, y, z, qx, qy, qz, qw):
    pose_msg = PoseStamped()
    pose_msg.header.frame_id = "world"
    pose_msg.pose.position.x = x
    pose_msg.pose.position.y = y
    pose_msg.pose.position.z = z
    pose_msg.pose.orientation.x = qx
    pose_msg.pose.orientation.y = qy
    pose_msg.pose.orientation.z = qz
    pose_msg.pose.orientation.w = qw
    return pose_msg


if __name__ == '__main__':
    rospy.init_node('sample_goal_publisher', anonymous=True)

    x = float(rospy.get_param('~x'))
    y = float(rospy.get_param('~y'))
    z = float(rospy.get_param('~z'))

    qx = float(rospy.get_param('~qx'))
    qy = float(rospy.get_param('~qy'))
    qz = float(rospy.get_param('~qz'))
    qw = float(rospy.get_param('~qw'))

    pub = rospy.Publisher('/adeye/goals', PoseStamped, queue_size=1)

    time.sleep(5)

    rate = rospy.Rate(0.5)
    while not rospy.is_shutdown():
        pub.publish(get_goal(x, y, z, qx, qy, qz, qw))
        rate.sleep()
