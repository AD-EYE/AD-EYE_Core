#!/usr/bin/env python  
import roslib
import rospy
import tf
import math
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

class loopgoal:

    def __init__(self):
        # Set the publisher and subscriber
        self.postion_sub = rospy.Subscriber('/gnss_pose', PoseStamped, self.gnssPosecallback)
        self.goal_pub = rospy.Publisher('move_base_simple/goal', PoseStamped, queue_size=1)
    
    def getDistance(self,x1,y1,x2,y2):
        distance = ( (x2-x1)**2 + (y2-y1)**2 ) ** 0.5
        return (distance)


    def gnssPosecallback(self, data):
        goal = PoseStamped()
        a=data.pose.position.x
        b=data.pose.position.y
        c=goal.pose.position.x
        d=goal.pose.position.y
 
        if self.getDistance(a,b,c,d) <= 20: 
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

               
        else:
         print ("The distance between the car and the goal point is",self.getDistance(a,b,c,d) )

        if  self.getDistance(a,b,c,d) <= 20: 
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
        else:
         print ("The distance between the car and the goal point is",self.getDistance(a,b,c,d) )    

        if  self.getDistance(a,b,c,d) <= 20:
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
        else:
         print ("The distance between the car and the goal point is",self.getDistance(a,b,c,d) )   


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

