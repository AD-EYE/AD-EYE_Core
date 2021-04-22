#!/usr/bin/env python  
import roslib
import rospy
import tf
import sys
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped


class FakeLocalizer:

    def __init__(self, map_frame, base_link_frame):
        self.gnss_sub = rospy.Subscriber('/gnss_pose_simulink', Pose, self.gnssCallback)
        self.br = tf.TransformBroadcaster()
        self.map_frame = map_frame
        self.base_link_frame = base_link_frame

    def gnssCallback(self, data):
        print("sending one transform")
        self.br.sendTransform((data.position.x, data.position.y, data.position.z),
                         (data.orientation.x, data.orientation.y, data.orientation.z, data.orientation.w),
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
