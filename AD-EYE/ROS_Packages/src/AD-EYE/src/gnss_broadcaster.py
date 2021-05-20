#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

## this node is a placeholder for receiving and decoding gps strings in the future
class GnssBroadcaster:

    def __init__(self):
        self.gnss_sub = rospy.Subscriber('/gnss_pose_simulink', PoseStamped, self.gnssCallback)
        self.gnss_pub = rospy.Publisher('/gnss_pose', PoseStamped, queue_size=1)

    def gnssCallback(self, msg):
        self.gnss_pub.publish(msg)


if __name__ == '__main__':
    rospy.init_node('GNSS_broadcaster')
    GnssBroadcaster()
    rospy.spin()
