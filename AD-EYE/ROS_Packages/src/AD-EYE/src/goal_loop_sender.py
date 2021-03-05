#!/usr/bin/env python  
import roslib
import rospy
import tf
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

class loopgoals:
    def __init__(self):
        self.loopgoal_sub = rospy.Subscriber("/gnss_pose", PoseStamped, self.loopcallback)
        # self.loopgoal_pub = rospy.Publisher("/move_base_simple/goal", PoseStamped, queue_size=10) 








if __name__ == '__main__':
    rospy.init_node('loop', anonymous=True)
    loopgoal_pub = rospy.Publisher("/move_base_simple/goal", PoseStamped, queue_size=1)
    goal = PoseStamped()
    goal.header.seq = 1 
    goal.header.stamp = rospy.Time.now()
    goal.header.frame_id = "world"

    goal.pose.position.x = 257.0
    goal.pose.position.y = 170.0
    goal.pose.position.z = 0.0

    goal.pose.orientation.x = 1.0
    goal.pose.orientation.y = 0.0
    goal.pose.orientation.z = 0.0
    goal.pose.orientation.w = 0.0
    rospy.sleep(2)
    loopgoal_pub.publish(goal)
    rospy.loginfo("loop goal")
    rospy.spin()

