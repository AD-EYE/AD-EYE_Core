#!/usr/bin/env python
"""
Example of interprocess communication between ROS and Python non-ROS script
(ROS node part)
"""
import rospy
from std_msgs.msg import Float32


class PythonNode(object):
    def __init__(self, rate=10):
        rospy.init_node('python_node')
        self.rate = rospy.Rate(rate)
        self._counter = None

        rospy.Subscriber('counter', Float32, self._counter_cb)
        self.higher_counter_publisher = rospy.Publisher(
            'higher_counter', Float32, queue_size=1
        )

    def _counter_cb(self, msg):
        self._counter = msg.data

    def publish_higher_counter(self):
        if self._counter is None:
            return

        self.higher_counter_publisher.publish(self._counter * 10)


if __name__ == '__main__':
    python_node = PythonNode()

    while not rospy.is_shutdown():
        python_node.publish_higher_counter()
        python_node.rate.sleep()
