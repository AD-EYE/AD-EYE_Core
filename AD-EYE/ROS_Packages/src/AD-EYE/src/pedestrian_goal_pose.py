#! /usr/bin/env python
import rospy
import roslib
import tf
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

def publishGoal():
    goal = PoseStamped()
    goal.pose.position.x = 257.0
    goal.pose.position.y = 170.0
    goal.pose.position.z = 0.0

    goal.pose.orientation.x = 0.0
    goal.pose.orientation.y = 0.0
    goal.pose.orientation.z = 0.0
    goal.pose.orientation.w = 1.0

    goal.header.seq = 1 
    goal.header.stamp = rospy.Time.now() 
    goal.header.frame_id = "map"

    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        goal_pub.publish(goal)
        rospy.loginfo(goal)
        rate.sleep()
  

if __name__=="__main__":
    rospy.init_node('pedestrian_goal_pose')
    goal_pub = rospy.Publisher('/pedestrian_goal', PoseStamped, queue_size=1)
    publishGoal()
   
    


