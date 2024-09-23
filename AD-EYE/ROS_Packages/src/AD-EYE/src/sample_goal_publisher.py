#!/usr/bin/env python

import rospy
from geometry_msgs.msg import PoseStamped

if __name__ == '__main__':
    rospy.init_node('sample_goal_publisher', anonymous=True)
    rate = rospy.Rate(10.0)
    pub = rospy.Publisher('/adeye/goals', PoseStamped, queue_size=1)

    pose_msg = PoseStamped()
    pose_msg.header.frame_id = "world"
    pose_msg.pose.position.x = -434
    pose_msg.pose.position.y = 530
    pose_msg.pose.position.z = 0
    pose_msg.pose.orientation.x = 0
    pose_msg.pose.orientation.y = 0
    pose_msg.pose.orientation.z = 0
    pose_msg.pose.orientation.w = 1

    while not rospy.is_shutdown():
        pub.publish(pose_msg)
        rate.sleep()
