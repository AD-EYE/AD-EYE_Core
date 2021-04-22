#!/usr/bin/env python  
import roslib
import rospy
import tf
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped


class FakeLocalizer:

    def __init__(self):
        self.gnss_sub = rospy.Subscriber('/gnss_pose_simulink', Pose, self.gnssCallback)
        self.br = tf.TransformBroadcaster()

    def gnssCallback(self, data):
        print("sending one transform")
        self.br.sendTransform((data.position.x, data.position.y, data.position.z),
                         (data.orientation.x, data.orientation.y, data.orientation.z, data.orientation.w),
                         rospy.Time.now(),
                         "/base_link",
                         "/map")


if __name__ == '__main__':
    rospy.init_node('fake_localizer')
    FakeLocalizer()
    rospy.spin()
