#! /usr/bin/env python
import rospy
import roslib
import math
import tf
import time
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

#Initiate the class loopgoal which will publish the goals one by one and make the car loop around these goal points.
class LoopGoal ():

    #Constructor
    def __init__(self,goal_list):
        
        self.goal_list_ = goal_list
        self.current_goal_index_ = 0
               
        #Set thePublishers Subscribers 
        self.position_sub_ = rospy.Subscriber('/gnss_pose', PoseStamped, self.gnssPoseCallback)
        self.goal_pub_ = rospy.Publisher('/adeye/goals', PoseStamped, queue_size=1)  
          
    #Function for publishing new goals 
    def publishNewGoal(self,index): 
        print("Publish New Goal: ",index)
        self.goal_pub_.publish(self.goal_list_[index])        
        self.current_goal_index_ = index

    #Function for calculating the euclidean distance between egopose and goalpose
    def getDistance(self, ego_pose, x2, y2):
        distance = ( (x2 - ego_pose.x) ** 2 + (y2 - egoPose.y) ** 2 ) ** 0.5
        print("Distance to goal: ",distance)
        return(distance)

    #Callback function which checks whether the car is within a distance of the goal and if so calls the function to publish the next goal,listens to the topic /gnss_pose   
    def gnssPoseCallback(self,ego_pose):

        x = self.goal_list_[self.current_goal_index_].pose.position.x
        y = self.goal_list_[self.current_goal_index_].pose.position.y        
        
        rate = rospy.Rate(1)               #Rate at which the goals are being published in hz
        DISTANCE_TOLERANCE = 50            #in meters
        if(self.getDistance(ego_pose.pose.position, x, y) <= DISTANCE_TOLERANCE ): 
            index_counter = 0                       #Initiate the Index counter
            if( self.current_goal_index_ < (len(self.goal_list_) - 1) ):
                index_counter = self.current_goal_index_ + 1

            print("index_Counter: ",index_counter, "; current_goal_index_: ",self.current_goal_index_)            
            self.publishNewGoal(index_counter)
        else:
            self.publishNewGoal(self.current_goal_index_)
                    
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
    
    rospy.init_node('loop_sender') #Initialising the node.

    #Creating a list for storing the goal points.
    goal_list = []
    goal_list.append( createGoal(257.0, 170.0, 0.0, 0.0, 1.0) )
    goal_list.append( createGoal(223.0, 226.0, 0.0, 1.0, 0.0) )
    goal_list.append( createGoal(84.0, 170.0, 0.0, 0.0, 1.0) )
   
    LoopGoal(goal_list)
    rospy.spin()