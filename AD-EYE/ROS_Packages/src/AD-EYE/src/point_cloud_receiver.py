#!/usr/bin/env python
# license removed for brevity

"""
This file is used to collect the raw data points of the Lidar.
It further converts these collected data points into a point cloud 
"""

import rospy
import roslaunch
import math as m
from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import PointCloud2
from sensor_msgs.msg import PointField
import numpy as np


def mycallback(data):

    """
    The callback function of the subscriped topic /points_raw_float32
    Parameters:
    msg: Float32MultiArray
        The published message on the topic /points_raw_float32
    
    Returns:
    None (Although publishes the PointCloud2 message on /points_raw topic)
    """

    msg = PointCloud2()
    msg.header.stamp = rospy.Time.now()
    msg.header.frame_id = "velodyne"  # MO "velodyne"
    msg.height = 1
    msg.width = len(data.data) / 4  # ADD data.size # ??

    msg.fields = [
        PointField('x', 0, PointField.FLOAT32, 1),
        PointField('y', 4, PointField.FLOAT32, 1),
        PointField('z', 8, PointField.FLOAT32, 1),
        PointField('intensity', 12, PointField.FLOAT32, 1)]
    msg.is_bigendian = False
    msg.point_step = 16
    msg.row_step = msg.point_step * msg.width
    msg.is_dense = False
    msg.data = np.asarray(data.data, np.float32).tostring()

    pub.publish(msg)


if __name__ == '__main__':
    rospy.init_node('point_cloud_receiver', anonymous=True)

    rospy.Subscriber("/points_raw_float32", Float32MultiArray, mycallback)
    pub = rospy.Publisher('/points_raw', PointCloud2, queue_size=1)
    rospy.spin()
