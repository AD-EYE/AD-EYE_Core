#!/usr/bin/env python  
import roslib
import rospy
import tf
import sys
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

##A class to link the map frame to the base_link frame
class FakeLocalizer:

    ##The constructor
    #
    #@param self the object pointer
    #@param map_frame The map frame
    #@param base_link_frame The base_link frame
    def __init__(self, map_frame, base_link_frame):
        self.gnss_sub = rospy.Subscriber('/ground_truth_pose', PoseStamped, self.gnssCallback)
        self.gnss_sub = rospy.Subscriber('/gnss_pose', PoseStamped, self.gnssCallback)
        self.br = tf.TransformBroadcaster()
        self.map_frame = map_frame
        self.base_link_frame = base_link_frame

    ##A method to send the data to the transform broadcaster.
    #@param self the object pointer
    #@param data A PoseStamped message
    def gnssCallback(self, data):
        print("sending one transform")
        self.br.sendTransform((data.pose.position.x, data.pose.position.y, data.pose.position.z),
                         (data.pose.orientation.x, data.pose.orientation.y, data.pose.orientation.z, data.pose.orientation.w),
                         rospy.Time.now(),
                         self.base_link_frame,
                         self.map_frame)


if __name__ == '__main__':
    node_name = "fake_localizer"
    map_frame = "/map"
    base_link_frame = "/base_link"
    if len(sys.argv) < 3:
        print("usage: my_node.py arg1(node_name) arg2(map_frame) arg3(base_link_frame)")
    else:
        node_name = sys.argv[1]
        map_frame = sys.argv[2]
        base_link_frame = sys.argv[3]
    rospy.init_node(node_name)
    FakeLocalizer(map_frame, base_link_frame)
    rospy.spin()
