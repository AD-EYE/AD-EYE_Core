#!usr/bin/env python

import roslib
import rospy
import math
import tf 
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

#Make a list of the three goal positions
class goal

    def __init__(self,Px, Py, Ox, Oy, Ow ):
        self.Px = Px
        self.Py = Py
        self.Ox = Ox
        self.Oy = Oy
        self.Ow = Ow
        
#Setting the parameters and variables
        self.Pz = 0.0
        self.Oz = 0.0
        self.seq = 1
        self.stamp = rospy.Time.now()
        self.frame_id = "Map"


class loopgoal
    #create list
    Goallist=[]

    def __init__(self):
    #Set the Publisher and Subscriber

        self.postion_sub = rospy.Subscriber('/gnss_pose', PoseStamped, self.gnssPosecallback)
        self.goal_pub = rospy.Publisher('move_base_simple/goal', PoseStamped, queue_size=1)

    #appending instances to list
        Goallist.append( goal(257.0, 170.0, 0.0, 0.0, 1.0) )
        Goallist.append( goal(223.0, 226.0, 0.0, 1.0, 0.0) )
        Goallist.append( goal(84.0, 170.0, 1.0, 0.0, 0.0) )    
    
#Funtion to calculate the distance between the car and the goal 
    def getDistance(self, egoPose, goalPose):
        distance = ( (goalPose.x-egoPose.x)**2 + (goalPose.y-egoPose.y)**2 ) ** 0.5
        return (distance)


    def gnssPosecallback(self,egoPose):
        goal = PoseStamped()
       
# Publish the next goal after checking the conditions.
        if self.getDistance(egoPose.pose.position, goalPose.pose.postion) <= 20:
            if (goal.pose.position.x == 257.0 and goal.pose.positon.y ==170):
                goal.pose.position.x = Goallist[1].Px
                goal.pose.position.y = Goallist[1].Py
                goal.pose.position.z = Goallist[1].Pz

                goal.pose.orientation.x = Goallist[1].Ox
                goal.pose.orientation.y = Goallist[1].Oy
                goal.pose.orientation.z = Goallist[1].Oz
                goal.pose.orientation.w = Goallist[1].Ow

                goal.header.seq = Goallist[1].seq
                goal.header.stamp = Goallist[1].stamp
                goal.header.frame_id = Goallist[1].frame_id


                self.goal_pub.publish(goal)

            elif (goal.pose.position.x == 223.0 and goal.pose.positon.y ==226):
                goal.pose.position.x = Goallist[2].Px
                goal.pose.position.y = Goallist[2].Py
                goal.pose.position.z = Goallist[2].Py
                goal.pose.orientation.x = Goallist[2].Ox
                goal.pose.orientation.y = Goallist[2].Oy
                goal.pose.orientation.z = Goallist[2].Oz
                goal.pose.orientation.w = Goallist[2].Ow

                goal.header.seq = Goallist[2].seq
                goal.header.stamp = Goallist[2].stamp
                goal.header.frame_id = Goallist[2].frame_id


                self.goal_pub.publish(goal)

            elif (goal.pose.position.x == 84.0 and goal.pose.positon.y ==170):
                goal.pose.position.x = Goallist[0].Px
                goal.pose.position.y = Goallist[0].Py
                goal.pose.position.z = Goallist[0].Pz
                goal.pose.orientation.x = Goallist[0].Ox
                goal.pose.orientation.y = Goallist[0].Oy
                goal.pose.orientation.z = Goallist[0].Oz
                goal.pose.orientation.w = Goallist[0].Ow

                goal.header.seq = Goallist[0].seq
                goal.header.stamp = Goallist[0].stamp
                goal.header.frame_id = Goallist[0].frame_id



                self.goal_pub.publish(goal)
        else:
            print ("The distance between the car and the goal point is",self.getDistance(egoPose.pose.position, goalPose.pose.positon))



        
if __name__=="__main__":
    rospy.init_node('loop_sender')

#Set the initial position of the goal
    goal.pose.position.x = Goallist[0].Px
    goal.pose.position.y = Goallist[0].Py
    goal.pose.position.z = Goallist[0].Pz

    goal.pose.orientation.x = Goallist[0].Ox
    goal.pose.orientation.y = Goallist[0].Oy
    goal.pose.orientation.z = Goallist[0].Oz
    goal.pose.orientation.w = Goallist[0].Ow

    goal.header.seq = Goallist[0].seq
    goal.header.stamp = Goallist[0].stamp
    goal.header.frame_id = Goallist[0].frame_id




loopgoal()
rospy.spin()



