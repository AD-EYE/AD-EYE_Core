#!/usr/bin/env python
# license removed for brevity
import rospy
import math as m
from autoware_msgs.msg import VehicleCmd
from geometry_msgs.msg import TwistStamped
from std_msgs.msg import UInt32
import sys

##A class to get the vehicle's commands from the vehicle_cmd topic and to send them to the corresponding topic
class ControlSignalForwarder:

    ##The constructor
    #
    #@param self The object pointer
    #@param use_only_twist Boolean defining whether only twist is published or if steering, brake, acceleration and gear as well.
    def __init__(self, use_only_twist):
        self.use_only_twist = use_only_twist
        if not self.use_only_twist:
            self.steer_pub = rospy.Publisher('steer', UInt32, queue_size=1)
            self.brake_pub = rospy.Publisher('brake', UInt32, queue_size=1)
            self.accel_pub = rospy.Publisher('accel', UInt32, queue_size=1)
            self.gear_pub = rospy.Publisher('gear', UInt32, queue_size=1)
        self.twist_pub = rospy.Publisher('autowareTwist', TwistStamped, queue_size=1)  # autowareTwist - TwistS
        rospy.Subscriber("vehicle_cmd", VehicleCmd, self.autowareCmdCallback)

    ##A method to publish each vehicle command to the corresponding topic from the vehicle_cmd topic
    #@param self The object pointer
    #@param data A VehicleCmd message 
    def autowareCmdCallback(self, data):
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
        if not self.use_only_twist:
            self.steer_pub.publish(steer)
            self.brake_pub.publish(brake)
            self.accel_pub.publish(accel)
            self.gear_pub.publish(gear)
        self.twist_pub.publish(Twist)


if __name__ == '__main__':
    rospy.init_node('control_signal_forwarder', anonymous=True)
    if len(sys.argv) < 3:
        ControlSignalForwarder(True)
    else:
        if sys.argv[1]=="false":
            ControlSignalForwarder(False)
        else:
            ControlSignalForwarder(True)
    rospy.spin()
