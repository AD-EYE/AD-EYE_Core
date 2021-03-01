#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import PointCloud2
from sensor_msgs.msg import PointField
import numpy as np


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


def talker():
 
    goal_publisher = rospy.Publisher("/move_base_simple/goal", PoseStamped, queue_size=10)

    goal = PoseStamped()
    goal.header.seq = 1 
    goal.header.stamp = rospy.Time.now()
    goal.header.frame_id = 'world'

    goal.pose.position.x = 257.0
    goal.pose.position.y = 170.0
    goal.pose.position.z = 0.0

    goal.pose.orientation.x = 1.0
    goal.pose.orientation.y = 0.0
    goal.pose.orientation.z = 0.0
    goal.pose.orientation.2 = 0.0

    goal_publisher.publish(goal)
    rate = rospy.Rate(1)

if __name__ == '__main__':
    rospy.init_node('point_cloud_receiver', anonymous=True)
    talker()
    rospy.Subscriber("/points_raw_float32", Float32MultiArray, mycallback)
    pub = rospy.Publisher('/points_raw', PointCloud2, queue_size=1)
    rospy.spin()
