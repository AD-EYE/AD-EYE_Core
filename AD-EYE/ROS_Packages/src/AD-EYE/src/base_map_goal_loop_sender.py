#! /usr/bin/env python
import rospy
import roslib
import math
import tf
import time
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

##A class that will publish the goals one by one and make the car loop around these goal points.
class BaseMapGoalLooper ():

    ##The constructor
    #
    #@param self The object pointer
    #@param goal_list An array of positions 
    def __init__(self,goal_list):
        
        self.goal_list_ = goal_list
        self.current_goal_index_ = 0
        self.DISTANCE_TOLERANCE_ = 50     #in meters 
        self.loop_counter_ = 1       # Counter to count the number of loops the car has completed
        self.goal_counter_ = 1       #Counter to count the number of goals published
        self.print_flag_ = 1         #Flag used for printing the total goals published once after each goal is being published and also the loop number once after the car completes one loop around

        #print("Total Goals Published: ",self.goal_counter_, "; Current Loop Number: ",self.loop_counter_)
        #Set thePublishers Subscribers 
        self.position_sub_ = rospy.Subscriber('/gnss_pose', PoseStamped, self.gnssPoseCallback)
        self.goal_pub_ = rospy.Publisher('/adeye/goals', PoseStamped, queue_size=1)  
          
    ##A method for publishing new goals.
    #@param self The object pointer
    #@param index The index (Integer) for the new goal in the list of goals
    def publishNewGoal(self,index):        
        self.goal_pub_.publish(self.goal_list_[index])        
        self.current_goal_index_ = index
        if(self.print_flag_ == 1):
            print("Total Goals Published: ",self.goal_counter_, "; Current Loop Number: ",self.loop_counter_)
            self.print_flag_ = 0

    ##A method for calculating the euclidean distance between egopose and goalpose.
    #@param self The object pointer
    #@param ego_pos the position of the ego vehicle
    #@param x2 The first coordinate of the point to which we want to measure the distance from the ego vehicle
    #@param y2 The second coordinate of the point to which we want to measure the distance from the ego vehicle
    def getDistance(self, ego_pose, x2, y2):
        distance = ( (x2 - ego_pose.x) ** 2 + (y2 - ego_pose.y) ** 2 ) ** 0.5
        return(distance)

    ##Callback method which checks whether the car is within a distance of the goal and if so calls the method to publish the next goal, listens to the topic /gnss_pose   
    #@param self The object pointer
    #@param ego_pos A PoseStamped message representing the position of the ego vehicle
    def gnssPoseCallback(self,ego_pose):

        x = self.goal_list_[self.current_goal_index_].pose.position.x
        y = self.goal_list_[self.current_goal_index_].pose.position.y                            
                  
        if(self.getDistance(ego_pose.pose.position, x, y) <= self.DISTANCE_TOLERANCE_): 
            
            if( self.current_goal_index_ < (len(self.goal_list_) - 1) ):
                self.publishNewGoal(self.current_goal_index_ + 1)        
            else:
                self.publishNewGoal(0)
                self.loop_counter_ = self.loop_counter_+ 1

            self.goal_counter_ = self.goal_counter_+ 1        
            self.print_flag_ = 1

        else:
            self.publishNewGoal(self.current_goal_index_)
                                 
##A function to set the goal Position and Orientation coordinates
#@param Px x position of the goal to create
#@param Py y position of the goal to create
#@param Qx x orientation with quaternions
#@param Qy y orientation with quaternions
#@param Qw w orientation with quaternions
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
    
    rospy.init_node('base_map_goal_loop_sender') #Initialising the node.

    #Creating a list for storing the goal points.
    goal_list = []
    goal_list.append( createGoal(257.0, 170.0, 0.0, 0.0, 1.0) )
    goal_list.append( createGoal(223.0, 226.0, 0.0, 1.0, 0.0) )
    goal_list.append( createGoal(84.0, 170.0, 0.0, 0.0, 1.0) )
   
    BaseMapGoalLooper(goal_list)
    rospy.spin()
