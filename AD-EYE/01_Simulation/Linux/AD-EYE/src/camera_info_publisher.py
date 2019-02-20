#!/usr/bin/env python
# license removed for brevity
import rospy
from sensor_msgs.msg import CameraInfo

if __name__ == '__main__':
    rospy.init_node('camera_info_publisher', anonymous=True)
    rate = rospy.Rate(10.0)
    pub = rospy.Publisher('/camera_info', CameraInfo, queue_size=1)
    while not rospy.is_shutdown():
        msg = CameraInfo()
        msg.header.frame_id = 'camera'
        msg.height = 240
        msg.width = 320
        msg.D = [0.0, 0.0, 0.0, 0.0, 0.0]
        msg.K = [375, 0.0, 160, 0.0, 375, 120, 0.0, 0.0, 1.0]
        msg.R = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
        msg.P = [375, 0.0, 160, 0.0, 0.0, 375, 120, 0.0, 0.0, 0.0, 1.0, 0.0]

        pub.publish(msg)
        rate.sleep()
