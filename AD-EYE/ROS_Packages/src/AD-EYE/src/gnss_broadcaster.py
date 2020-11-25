#!/usr/bin/env python  
import roslib
import rospy
import tf
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped


class GnssBroadcaster:

    def __init__(self):
        self.gnss_sub = rospy.Subscriber('/gnss_pose_simulink', Pose, self.gnssCallback)
        self.gnss_pub = rospy.Publisher('/gnss_pose', PoseStamped, queue_size=1)

    def gnssCallback(self, data):
        ego_pose = PoseStamped()
        ego_pose.pose.position = data.position
        ego_pose.pose.orientation = data.orientation
        ego_pose.header.stamp = rospy.Time.now()
        ego_pose.header.frame_id = 'map'
        br = tf.TransformBroadcaster()
        br.sendTransform((data.position.x, data.position.y, data.position.z),
                        (data.orientation.x, data.orientation.y, data.orientation.z, data.orientation.w),
                        rospy.Time.now(),
                        "gps",
                        "world")
        self.gnss_pub.publish(ego_pose)


if __name__ == '__main__':
    rospy.init_node('tf_broadcaster')
    GnssBroadcaster()
    rospy.spin()
