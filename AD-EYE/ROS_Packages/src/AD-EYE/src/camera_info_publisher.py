#!/usr/bin/env python
# license removed for brevity
import rospy
from sensor_msgs.msg import CameraInfo
import sys

# --------------Config: To be imported from Simulink -------------------------------------------------
# TODO Camera parameters should come from Simulink once, hardcoded for now

msg = CameraInfo()
msg.header.frame_id = sys.argv[2]
msg.height = int(sys.argv[3])
msg.width = int(sys.argv[4])
msg.D = [float(sys.argv[5]), float(sys.argv[6]), float(sys.argv[7]), float(sys.argv[8]), float(sys.argv[9])]
msg.K = [float(sys.argv[10]), float(sys.argv[11]), float(sys.argv[12]), float(sys.argv[13]), float(sys.argv[14]), float(sys.argv[15]), float(sys.argv[16]), float(sys.argv[17]), float(sys.argv[18])]
msg.R = [float(sys.argv[19]), float(sys.argv[20]), float(sys.argv[21]), float(sys.argv[22]), float(sys.argv[23]), float(sys.argv[24]), float(sys.argv[25]), float(sys.argv[26]), float(sys.argv[27])]
msg.P = [float(sys.argv[28]), float(sys.argv[29]), float(sys.argv[30]), float(sys.argv[31]), float(sys.argv[32]), float(sys.argv[33]), float(sys.argv[34]), float(sys.argv[35]), float(sys.argv[36]), float(sys.argv[37]), float(sys.argv[38]), float(sys.argv[39])]


if __name__ == '__main__':
    rospy.init_node('camera_info_publisher', anonymous=True)
    rate = rospy.Rate(10.0)
    pub = rospy.Publisher(sys.argv[1], CameraInfo, queue_size=1)
    while not rospy.is_shutdown():
        pub.publish(msg)
        rate.sleep()
