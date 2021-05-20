#! /usr/bin/env python
import rospy
import roslib
import math
import tf
import time
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Int32

#Initiate the class loopgoal which will publish the goals one by one and make the car loop around these goal points.
class loopgoal ():

    #Constructor
    def __init__(self,goalList):
        
        self.goal_List = goalList
        self.current_goal_Index = 0
               
        #Set thePublishers Subscribers 
        self.position_sub = rospy.Subscriber('/gnss_pose', PoseStamped, self.gnssPoseCallback)
        self.goal_pub = rospy.Publisher('/adeye/goals', PoseStamped, queue_size=1)  
          
    #Function for publishing new goals 
    def publishNewGoal(self,index): 
        print("Publish New Goal: ",index)
        self.goal_pub.publish(self.goal_List[index])        
        self.current_goal_Index = index

    #Function for calculating the euclidean distance between egopose and goalpose
    def getDistance(self, egoPose, x2, y2):
        distance = ( (x2 - egoPose.x) ** 2 + (y2 - egoPose.y) ** 2 ) ** 0.5
        print("Distance to goal: ",distance)
        return(distance)

    #Callback function which checks whether the car is within a distance of the goal and if so calls the function to publish the next goal,listens to the topic /gnss_pose   
    def gnssPoseCallback(self,egoPose):

        x = self.goal_List[self.current_goal_Index].pose.position.x
        y = self.goal_List[self.current_goal_Index].pose.position.y        
        
        rate = rospy.Rate(1)               #Rate at which the goals are being published in hz
        
        if(self.getDistance(egoPose.pose.position, x, y) <= 50 ): 
            index_Counter = 0
            if( self.current_goal_Index < (len(self.goal_List) - 1) ):
                index_Counter = self.current_goal_Index + 1

            print("index_Counter: ",index_Counter, "; current_goal_Index: ",self.current_goal_Index)            
            self.publishNewGoal(index_Counter)
        else:
            self.publishNewGoal(self.current_goal_Index)
                    
        rate.sleep()
                 
#Setting the goal Position and Orientation coordinates
def createGoal(Px, Py, Qx, Qy, Qw):
    goal = PoseStamped()
    goal.pose.position.x = Px
    goal.pose.position.y = Py
    goal.pose.position.z = 0.0 
    goal.pose.orientation.x = Qx
    goal.pose.orientation.y = Qy
    goal.pose.orientation.z = 0.0 
    goal.pose.orientation.w = Qw

    goal.header.seq = 1 
    goal.header.stamp = rospy.Time.now() 
    goal.header.frame_id = "map" 
    return goal

if __name__=="__main__":
    print("the car loop")
    rospy.init_node('loop_sender') #Initialising the node.

    #Creating a list for storing the goal points.
    goal_List = []
    goal_List.append( createGoal(257.0, 170.0, 0.0, 0.0, 1.0) )
    goal_List.append( createGoal(223.0, 226.0, 0.0, 1.0, 0.0) )
    goal_List.append( createGoal(84.0, 170.0, 0.0, 0.0, 1.0) )
   
    loopgoal(goal_List)
    rospy.spin()