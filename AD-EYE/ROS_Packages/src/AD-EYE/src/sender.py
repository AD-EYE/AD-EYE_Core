#!/usr/bin/env python
# license removed for brevity
"""
This file contains the RCV sender
It allows the user to publish various parameters of the RCV
"""


import rospy
import math as m
from autoware_msgs.msg import VehicleCmd
from geometry_msgs.msg import TwistStamped
from std_msgs.msg import UInt32


def mycallback1(data):

    """
    The callback function of the subscriped topic /vehicle_cmd
    Parameters:
    msg: VehicleCmd
        The published message on the topic /vehicle_cmd
    
    Returns:
    None (Although publishes several importantant params on various topics; see function code for details)
    """

    pub = rospy.Publisher('steer', UInt32, queue_size=1)
    pub1 = rospy.Publisher('brake', UInt32, queue_size=1)
    pub2 = rospy.Publisher('accel', UInt32, queue_size=1)
    pub3 = rospy.Publisher('gear', UInt32, queue_size=1)
    pub4 = rospy.Publisher('autowareTwist', TwistStamped, queue_size=1)  # autowareTwist - TwistS
    steer = UInt32()
    brake = UInt32()
    accel = UInt32()
    gear = UInt32()
    Twist = TwistStamped()
    brake = data.brake_cmd.brake
    steer = data.steer_cmd.steer
    accel = data.accel_cmd.accel
    gear = data.gear
    Twist = data.twist_cmd
    pub.publish(steer)
    pub1.publish(brake)
    pub2.publish(accel)
    pub3.publish(gear)
    pub4.publish(Twist)


def listener():

    """
    The initialization function for the ros node sender /n
    Also Subscribes to the vehicle_cmd topic
    Parameters:
    None

    Returns:
    None
    """

    rospy.init_node('sender', anonymous=True)
    rospy.Subscriber("vehicle_cmd", VehicleCmd, mycallback1)
    rospy.spin()


if __name__ == '__main__':
    listener()
