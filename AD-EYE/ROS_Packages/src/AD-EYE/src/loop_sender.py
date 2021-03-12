#!/usr/bin/env python  
import roslib
import rospy
import tf
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped


class loopgoal:

    def __init__(self):
        # Set the publisher and subscriber
        self.postion_sub = rospy.Subscriber('/gnss_pose', PoseStamped, self.goalcallback)
        self.goal_pub = rospy.Publisher('move_base_simple/goal', PoseStamped, queue_size=1)

    def goalcallback(self, data):
        goal = PoseStamped()
        ''' Use absolute value for distance. 
        Since three points have different x positions, use x position to find the current goal'''
        if (data.pose.position.x == 257.0 and 
            data.pose.position.y == 170.0 and 
            data.pose.position.z == 0.0 and
            data.pose.orientation.x == 0,0 and
            data.pose.orientation.y == 0.0 and
            data.pose.orientation.z == 0.0 and
            data.pose.orientation.w == 1.0):
            goal.header.seq = 1
            goal.header.stamp = rospy.Time.now()
            goal.header.frame_id = "world"

            goal.pose.position.x = 223.0
            goal.pose.position.y = 226.0
            goal.pose.position.z = 0.0

            goal.pose.orientation.x = 0.0
            goal.pose.orientation.y = 1.0
            goal.pose.orientation.z = 0.0
            goal.pose.orientation.w = 0.0
            self.goal_pub.publish(goal)

        if (data.pose.position.x == 223.0 and
            data.pose.position.y == 226.0 and
            data.pose.position.z == 0.0 and
            data.pose.orientation.x == 0.0 and
            data.pose.orientation.y == 1.0 and
            data.pose.orientation.z == 0.0 and
            data.pose.orientation.w == 0.0):

            goal.header.seq = 1
            goal.header.stamp = rospy.Time.now()
            goal.header.frame_id = "world"

            goal.pose.position.x = 84.0
            goal.pose.position.y = 170.0
            goal.pose.position.z = 0.0

            goal.pose.orientation.x = 1.0
            goal.pose.orientation.y = 0.0
            goal.pose.orientation.z = 0.0
            goal.pose.orientation.w = 0.0
            self.goal_pub.publish(goal)



        if (data.pose.position.x == 84.0 and
            data.pose.position.y == 170.0 and
            data.pose.position.z == 0.0 and
            data.pose.orientation.x == 1.0 and
            data.pose.orientation.y == 0.0 and
            data.pose.orientation.z == 0.0 and
            data.pose.orientation.w == 0.0):


            goal.header.seq = 1
            goal.header.stamp = rospy.Time.now()
            goal.header.frame_id = "world"

            goal.pose.position.x = 257.0
            goal.pose.position.y = 170.0
            goal.pose.position.z = 0.0

            goal.pose.orientation.x = 0,0
            goal.pose.orientation.y = 0.0
            goal.pose.orientation.z = 0.0
            goal.pose.orientation.w = 1.0
            self.goal_pub.publish(goal)


if __name__ == '__main__':
    rospy.init_node('loop_sender')
    '''//Set the goal for simulation start
    goal_publisher = rospy.Publisher("move_base_simple/goal", PoseStamped, queue_size=5)

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
    goal_publisher.publish(goal)'''

    loopgoal()
    rospy.spin()
