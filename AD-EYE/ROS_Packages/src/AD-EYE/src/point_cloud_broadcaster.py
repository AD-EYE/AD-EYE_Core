#!/usr/bin/env python

import rospy
from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import PointCloud2
from sensor_msgs.msg import PointField
import numpy as np


class point_cloud_broadcaster_Sim():

    def __init__(self):
        self.sub = rospy.Subscriber("/points_raw_float32", Float32MultiArray, self.callback)
        self.pub = rospy.Publisher('/points_raw', PointCloud2, queue_size=1)

        self.msg = PointCloud2()

    ##A function to turn the raws points from floats to strings and publish them to the /points_raw topic
    #@param data A Float32MultiArray message
    def callback(self, data):
        self.msg.header.stamp = rospy.Time.now()
        self.msg.header.frame_id = "os_sensor"  # MO "velodyne"
        self.msg.height = 1
        self.msg.width = len(data.data) / 4  # ADD data.size # ??

        self.msg.fields = [
            PointField('x', 0, PointField.FLOAT32, 1),
            PointField('y', 4, PointField.FLOAT32, 1),
            PointField('z', 8, PointField.FLOAT32, 1),
            PointField('intensity', 12, PointField.FLOAT32, 1)]
        self.msg.is_bigendian = False
        self.msg.point_step = 16
        self.msg.row_step = self.msg.point_step * self.msg.width
        self.msg.is_dense = False
        self.msg.data = np.asarray(data.data, np.float32).tostring()

        self.pub.publish(self.msg)


class point_cloud_broadcaster_RealWorld():

    def __init__(self):
        self.sub = rospy.Subscriber("/velodyne_points", PointCloud2, self.callback)
        self.pub = rospy.Publisher('/points_raw', PointCloud2, queue_size=1)


    def callback(self, data):
        self.pub.publish(data)


if __name__ == '__main__':
    rospy.init_node('point_cloud_broadcaster', anonymous=True)

    if rospy.get_param("sensing/lidar_source") == "Simulation":
        point_cloud_broadcaster_Sim()

    if rospy.get_param("sensing/lidar_source") == "RealWorld":
        point_cloud_broadcaster_RealWorld()

    rospy.spin()