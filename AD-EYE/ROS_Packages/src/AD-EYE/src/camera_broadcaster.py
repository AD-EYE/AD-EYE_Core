#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Image


def callback_1(data):
    pub1.publish(data)


def callback_2(data):
    pub2.publish(data)


if __name__ == '__main__':
    rospy.init_node('camera_broadcaster', anonymous=True)

    if rospy.get_param("sensing/camera_source", "Simulation"):
        rospy.Subscriber("/camera_1/image_raw_simulink", Image, callback_1)
	rospy.Subscriber("/camera_2/image_raw_simulink", Image, callback_2)
    
    if rospy.get_param("sensing/camera_source", "RealWorld"):
        rospy.Subscriber("/camera_1/image_raw_zed", Image, callback_1)
	rospy.Subscriber("/camera_2/image_raw_zed", Image, callback_2)
    
    pub1 = rospy.Publisher('/camera_1/image_raw', Image, queue_size=1)
    pub2 = rospy.Publisher('/camera_2/image_raw', Image, queue_size=1)
    rospy.spin()
