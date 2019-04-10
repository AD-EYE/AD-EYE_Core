#!/usr/bin/env python
# license removed for brevity
import rospy
#import math as m
#from autoware_msgs.msg import VehicleCmd
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import Pose
from std_msgs.msg import Int32

class safetySupervisor:
    def __init__(self):
        # Define the constants
        self.SAFE = 0
        self.UNSAFE = 1

        # Define the subscribers
        rospy.Subscriber("gnss_pose", PoseStamped, self.gnss_callback)

        # Define the publishers
        self.switch_pub = rospy.Publisher('switchCommand', Int32, queue_size=1)

        # Initialize the variables
        self.pose = Pose()
        self.state = self.SAFE

        # Initialize the flags
        self.gnss_flag = 0

    def evaluate(self):
        if self.pose.position.x > 100:
            self.state = self.UNSAFE
        else:
            self.state = self.SAFE

    def publish(self):
        msg = Int32()
        msg = self.state
        self.switch_pub.publish(msg)
        rospy.loginfo(self.state)

    def gnss_callback(self, data):
        self.pose = data.pose
        self.gnss_flag = 1;

    def loop(self):
        rate = rospy.Rate(10.0)
        while not rospy.is_shutdown():
            if self.gnss_flag == 1:
                self.evaluate()
                self.publish()
                rate.sleep()

if __name__ == '__main__':
    rospy.init_node('safetySupervisor', anonymous=True)
    sS = safetySupervisor()
    sS.loop()
