#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

## A class to get the position of the car as a Pose message from simulink and 
## to tranfer it to the topic /gnss_pose as a PoseStamped message.
# This node is a placeholder for receiving and decoding gps strings in the future
class GnssBroadcaster:

    ##The constructor
    #
    #@param self The object pointer
    def __init__(self):
        self.gnss_sub = rospy.Subscriber('/gnss_pose_simulink', PoseStamped, self.gnssCallback)
        self.gnss_pub = rospy.Publisher('/gnss_pose', PoseStamped, queue_size=1)

    ##A Method to publish the position of the ego car as a PoseStamped message to the /gnss_pose topic.
    #@param self The object pointer
    #@param msg A Pose message received from /gnss_pose_simulink
    def gnssCallback(self, msg):
        self.gnss_pub.publish(msg)



if __name__ == '__main__':
    rospy.init_node('GNSS_broadcaster')
    GnssBroadcaster()
    rospy.spin()
