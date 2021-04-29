#! /usr/bin/env python
import rospy
import roslib
import math
import tf
import time
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Int32

class loopgoal ():

    def __init__(self,goalList):
        
        self.goal_List = goalList
        self.current_goal_Index = -1
        self.goalID = 0
         #self.publishGoalFromIndex(0)
        #time.sleep(10) 

        #Set thePublishers Subscribers 
        self.goal_pub = rospy.Publisher('move_base_simple/goal', PoseStamped, queue_size=1)        
        self.position_sub = rospy.Subscriber('/gnss_pose', PoseStamped, self.gnssPoseCallback)
        self.planner_pub = rospy.Publisher('/adeye/update_local_planner', Int32, queue_size=1)
        self.goalPose_sub = rospy.Subscriber('move_base_simple/goal', PoseStamped, self.goalPoseCallback)
    
    #Function for publishing the goals    
    def publishGoalFromIndex(self,index): 
        print("Publish New Goal")
        self.goal_pub.publish(self.goal_List[index])        
        self.current_goal_Index = index

    def goalPoseCallback(self,goalPose):
        print(goalPose.pose.position)
        if(goalPose.pose.position.x == self.goal_List[self.current_goal_Index].pose.position.x):
               print("New Goal Set")
               self.goalID = 1
    
    #Calculates the distance between egopose and goalpose
    def getDistance(self, egoPose, x2, y2):
        distance = ( (x2-egoPose.x)**2 + (y2-egoPose.y)**2 ) ** 0.5
        print("Distance to goal is ")
        print(distance)
        return(distance)
        
    def gnssPoseCallback(self,egoPose):

        #set initial goal
        if(self.goalID == 0):
            self.publishGoalFromIndex(0)

        self.reset_local_planner_msg = Int32()
        self.reset_local_planner_msg.data = 1

        x = self.goal_List[self.current_goal_Index].pose.position.x
        y = self.goal_List[self.current_goal_Index].pose.position.y        
    
        if(self.getDistance(egoPose.pose.position, x, y) <= 30 ):
            index_Counter = 0
            if( self.current_goal_Index < len(self.goal_List) ):
                index_Counter = self.current_goal_Index + 1

            print(index_Counter)
            
            self.publishGoalFromIndex(index_Counter)
            time.sleep(8)
            self.planner_pub.publish(self.reset_local_planner_msg)

#Setting the goalpoints
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
    rospy.init_node('loop_sender')
    goal_List = []
    goal_List.append( createGoal(257.0, 170.0, 0.0, 0.0, 1.0) )
    goal_List.append( createGoal(223.0, 226.0, 0.0, 1.0, 0.0) )
    goal_List.append( createGoal(84.0, 170.0, 1.0, 0.0, 0.0) )
    
    loopgoal(goal_List)
    rospy.spin()
