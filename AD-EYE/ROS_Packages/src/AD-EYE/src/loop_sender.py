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

        #Set thePublishers Subscribers 
        self.position_sub = rospy.Subscriber('/gnss_pose', PoseStamped, self.gnssPoseCallback)
        self.planner_pub = rospy.Publisher('/adeye/update_local_planner', Int32, queue_size=1)
        self.goal_pub = rospy.Publisher('move_base_simple/goal', PoseStamped, queue_size=1)  
        self.goalPose_sub = rospy.Subscriber('move_base_simple/goal', PoseStamped, self.goalPoseCallback)

        time.sleep(50)
        self.publishGoalFromIndex(0)
        #self.publishFirstGoal()
       
        
    def publishPlanner(self):
        reset_local_planner_msg = Int32()
        reset_local_planner_msg.data = 1
        time.sleep(9)
        print("Planner data: ",reset_local_planner_msg)
        self.planner_pub.publish(reset_local_planner_msg)

    #def publishFirstGoal(self):
        #ctr = 0
        #while(ctr < 25):       
            #time.sleep(1)
            #print("Publish First Goal ",ctr)
            #self.publishGoalFromIndex(0)
            #ctr = ctr + 1

    #Function for publishing the goal   
    def publishGoalFromIndex(self,index): 
        print("Publish New Goal: ",index)
        self.goal_pub.publish(self.goal_List[index])        
        self.current_goal_Index = index
        #self.publishPlanner()

    def goalPoseCallback(self,goalPose):
        print("Goal Position: (",goalPose.pose.position.x, goalPose.pose.position.y,")")
        if(goalPose.pose.position.x == self.goal_List[self.current_goal_Index].pose.position.x):
            print("New Goal Set")
            self.goalID = 1
        else:
            print("Goal not set")
    
    #Calculates euclidean distance between egopose and goalpose
    def getDistance(self, egoPose, x2, y2):
        distance = ( (x2 - egoPose.x) ** 2 + (y2 - egoPose.y) ** 2 ) ** 0.5
        print("Distance to goal: ",distance)
        return(distance)
        
    def gnssPoseCallback(self,egoPose):
        #set initial goal
        #if(self.goalID == 0):
         #   self.publishGoalFromIndex(0)

        x = self.goal_List[self.current_goal_Index].pose.position.x
        y = self.goal_List[self.current_goal_Index].pose.position.y 

        print("Car position: (",egoPose.pose.position.x, egoPose.pose.position.y,"); Goal Position: (",x,y,")")       
    
        if(self.getDistance(egoPose.pose.position, x, y) <= 30 and self.goalID > 0):
            index_Counter = 0
            if( self.current_goal_Index < (len(self.goal_List) - 1) ):
                index_Counter = self.current_goal_Index + 1

            print("index_Counter: ",index_Counter, "; current_goal_Index: ",self.current_goal_Index)            
            self.publishGoalFromIndex(index_Counter)
            #time.sleep(9)
            self.publishPlanner()


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