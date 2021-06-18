#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import PointCloud2
from sensor_msgs.msg import PointField
import numpy as np

##A function to turn the raws points from floats to strings and publish them to the /points_raw topic
#@param data A Float32MultiArray message 
def mycallback(data):
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
