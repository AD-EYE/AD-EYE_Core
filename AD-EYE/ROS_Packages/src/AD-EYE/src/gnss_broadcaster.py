#!/usr/bin/env python  
"""
This file takes the data of the gps module in order to publish the gnss state of the vehicle.
"""

import roslib
import rospy
import tf
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped


def mycallback(data):

    """
    The callback function of the subscriped topic /gnss_pose_simulink
    Parameters:
    msg: Pose
        The published message on the topic /gnss_pose_simulink
    
    Returns:
    None (Although publishes the poseStamped message on /gnss_pose topic)
    """

    pub = rospy.Publisher('/gnss_pose', PoseStamped, queue_size=1)
    car = PoseStamped()
    car.pose.position = data.position
    car.pose.orientation = data.orientation
    car.header.stamp = rospy.Time.now()
    car.header.frame_id = 'map'
    br = tf.TransformBroadcaster()
    br.sendTransform((data.position.x, data.position.y, data.position.z),
                     (data.orientation.x, data.orientation.y, data.orientation.z, data.orientation.w),
                     rospy.Time.now(),
                     "gps",
                     "world")
    # br2 = tf.TransformBroadcaster()
    # br2.sendTransform((2.0,0.0,1.32),tf.transformations.quaternion_from_euler(0,0,0),
    #                rospy.Time.now(),
    #	     "camera",
    #            "base_link")
    pub.publish(car)


if __name__ == '__main__':
    rospy.init_node('tf_broadcaster')
    rospy.Subscriber('/gnss_pose_simulink', Pose, mycallback)
    rospy.spin()
