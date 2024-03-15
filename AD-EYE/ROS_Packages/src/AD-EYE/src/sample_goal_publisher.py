#!/usr/bin/env python

import rospy
from geometry_msgs.msg import PoseStamped

if __name__ == '__main__':
    rospy.init_node('sample_goal_publisher', anonymous=True)
    rate = rospy.Rate(10.0)
    pub = rospy.Publisher('/adeye/goals', PoseStamped, queue_size=1)
    counter = 0

    pose_msg = PoseStamped()
    pose_msg.header.frame_id = "world"
    pose_msg.header.seq = 1
    pose_msg.pose.position.x = 345.0
    pose_msg.pose.position.y = -605.0
    pose_msg.pose.position.z = 0
    pose_msg.pose.orientation.x = 0.0
    pose_msg.pose.orientation.y = 0.0
    pose_msg.pose.orientation.z = 0.839
    pose_msg.pose.orientation.w = 0.545
    
    #simulation only publishes a single adeye goal message. so publishing message only after a subscriber has registered
    while not rospy.is_shutdown():
        if (pub.get_num_connections() != 0):
            break
        rate.sleep()

    pub.publish(pose_msg)
    rospy.spin()