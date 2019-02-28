#!/usr/bin/env python
# license removed for brevity
import rospy
from sensor_msgs.msg import CameraInfo

# --------------Config: To be imported from Simulink -------------------------------------------------
# TODO Camera parameters should come from Simulink once, hardcoded for now

msg = CameraInfo()
msg.header.frame_id = 'camera'
msg.height = 240
msg.width = 320
msg.D = [0.0, 0.0, 0.0, 0.0, 0.0]
msg.K = [375, 0.0, 160, 0.0, 375, 120, 0.0, 0.0, 1.0]
msg.R = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
msg.P = [375, 0.0, 160, 0.0, 0.0, 375, 120, 0.0, 0.0, 0.0, 1.0, 0.0]

# --------------------------------------------------------------------------------------------------------------------

if __name__ == '__main__':
    rospy.init_node('camera_info_publisher', anonymous=True)
    rate = rospy.Rate(10.0)
    pub = rospy.Publisher('/camera_info', CameraInfo, queue_size=1)
    while not rospy.is_shutdown():
        pub.publish(msg)
        rate.sleep()
