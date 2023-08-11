#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Image


class camera_broadcaster_RealWorld():

    def __init__(self):
        self.cam1_sub = rospy.Subscriber("/camera_1/image_raw_zed", Image, self.callback_1)
        self.cam2_sub = rospy.Subscriber("/camera_2/image_raw_zed", Image, self.callback_2)

        self.cam1_pub = rospy.Publisher('/camera_1/image_raw', Image, queue_size=1)
        self.cam2_pub = rospy.Publisher('/camera_2/image_raw', Image, queue_size=1)


    def callback_1(self, data):
        self.cam1_pub.publish(data)


    def callback_2(self, data):
        self.cam2_pub.publish(data)


class camera_broadcaster_Sim():

    def __init__(self):
        self.cam1_sub = rospy.Subscriber("/camera_1/image_raw_simulink", Image, self.callback_1)
        self.cam2_sub = rospy.Subscriber("/camera_2/image_raw_simulink", Image, self.callback_2)

        self.cam1_pub = rospy.Publisher('/camera_1/image_raw', Image, queue_size=1)
        self.cam2_pub = rospy.Publisher('/camera_2/image_raw', Image, queue_size=1)


    def callback_1(self, data):
        self.cam1_pub.publish(data)


    def callback_2(self, data):
        self.cam2_pub.publish(data)


if __name__ == '__main__':
    rospy.init_node('camera_broadcaster', anonymous=True)

    if rospy.get_param("sensing/camera_source") == "Simulation":
        camera_broadcaster_Sim()
    
    if rospy.get_param("sensing/camera_source") == "RealWorld":
        camera_broadcaster_RealWorld()
    
    rospy.spin()