#!/usr/bin/env python
# license removed for brevity
import rospy
#import math as m
#from autoware_msgs.msg import VehicleCmd
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import Pose
from std_msgs.msg import Int32
from vector_map_msgs.msg import PointArray
from vector_map_msgs.msg import Point
#from grid_map_msgs.msg import GridMap
#from grid_map_ros.hpp import grid_map_ros

class safetySupervisor:
    def __init__(self):
        # Define the constants
        self.SAFE = 0
        self.UNSAFE = 1

        # Define the subscribers
        rospy.Subscriber("gnss_pose", PoseStamped, self.gnss_callback)
        rospy.Subscriber("vector_map_info/point", PointArray, self.vecMapPoint_callback)

        # Define the publishers
        self.switch_pub = rospy.Publisher('switchCommand', Int32, queue_size=1)

        # Initialize the variables
        self.pose = Pose()
        self.state = self.SAFE
        self.vectormap_Points = []

        # Initialize the flags
        self.gnss_flag = 0
        self.vectormap_Points_flag = 0

    def evaluate(self):
        #if self.pose.position.x > 100:
        #    self.state = self.UNSAFE
        #else:
        #    self.state = self.SAFE
        self.state = self.UNSAFE
        for i in range(0, len(self.vectormap_Points)):
            if (abs(self.pose.position.x-self.vectormap_Points[i].ly)<1.75 and abs(self.pose.position.y-self.vectormap_Points[i].bx)<1.75):
                self.state = self.SAFE
                break

    def publish(self):
        msg = Int32()
        msg = self.state
        self.switch_pub.publish(msg)
        rospy.loginfo(self.state)

    def gnss_callback(self, data):
        self.pose = data.pose
        self.gnss_flag = 1;

    def vecMapPoint_callback(self, data):
        self.vectormap_Points = data.data
        self.vectormap_Points_flag = 1

    def loop(self):
        rate = rospy.Rate(10.0)
        while not rospy.is_shutdown():
            if (self.gnss_flag == 1 and self.vectormap_Points_flag == 1):
                self.evaluate()
                self.publish()
                rate.sleep()

if __name__ == '__main__':
    rospy.init_node('safetySupervisor', anonymous=True)
    sS = safetySupervisor()
    sS.loop()
