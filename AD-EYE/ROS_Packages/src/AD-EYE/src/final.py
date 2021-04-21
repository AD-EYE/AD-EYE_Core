#!usr/bin/env python

import roslib
import rospy
import math
import tf 
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

class loopgoal

    def __init__(self):
        #Set the Publisher and Subscriber
        self.postion_sub = rospy.Subscriber('/gnss_pose', PoseStamped, self.gnssPosecallback)
        self.goal_pub = rospy.Publisher('move_base_simple/goal', PoseStamped, queue_size=1)
        
if __name__=="__main__":

