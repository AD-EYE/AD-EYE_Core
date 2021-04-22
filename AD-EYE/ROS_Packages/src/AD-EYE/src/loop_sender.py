#!/usr/bin/env python
import roslib
import rospy
import math
import tf 
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

#Make a list of the three goal positions
class goal:
    def __init__(self, Px, Py):
        self.Px = Px
        self.Py = Py      

        #Setting the parameters and variables
        self.Pz = 0.0
        self.Qx = 0.0
        self.Qy = 0.0
        self.Qw = 1.0
        self.Qz = 0.0
        self.seq = 1
        self.stamp = rospy.Time.now()
        self.frame_id = "map"

class loopgoal:
    

    def __init__(self):
    #Set the Publisher and Subscriber

        self.postion_sub = rospy.Subscriber('/gnss_pose', PoseStamped, self.gnssPosecallback)
        self.goal_pub = rospy.Publisher('move_base_simple/goal', PoseStamped, queue_size=1)

        #create list
        self.goal_List=[]

        #appending instances to list
        self.goal_List.append( goal(257.0, 170.0) )
        self.goal_List.append( goal(223.0, 226.0) )
        self.goal_List.append( goal(84.0, 170.0) )   

        self.val = 0            

    
    '''#Funtion to calculate the distance between the car and the goal 
    def getDistance(self, egoPose, goalPose):
        distance = ( (goalPose.x-egoPose.x)**2 + (goalPose.y-egoPose.y)**2 ) ** 0.5
        return (distance)'''
    
    def getDistance(self, egoPose, x2,y2):
        distance = ( (x2-egoPose.x)**2 + (y2-egoPose.y)**2 ) ** 0.5
        print('distance')
        print(distance)
        return (distance)
    
    def gnssPosecallback(self,egoPose):
        goal = PoseStamped()
        if(self.val == 0):
            goal.pose.position.x = self.goal_List[0].Px
            goal.pose.position.y = self.goal_List[0].Py
        print(egoPose.pose.position)
        print(goal.pose.position.x)
        print(goal.pose.position.y)

        # Publish the next goal after checking the conditions.
        #if self.getDistance(egoPose.pose.position, 257.0,170) <= 20:
        if (self.getDistance(egoPose.pose.position, 257.0,170) <= 30 and
            goal.pose.position.x == 257.0 and goal.pose.position.y ==170):
            self.val = 1
            print('Goal 1 (257.0,170) is set')
            goal.pose.position.x = self.goal_List[1].Px
            goal.pose.position.y = self.goal_List[1].Py
            goal.pose.position.z = self.goal_List[1].Pz

            goal.pose.orientation.x = self.goal_List[1].Qx
            goal.pose.orientation.y = self.goal_List[1].Qy
            goal.pose.orientation.z = self.goal_List[1].Qz
            goal.pose.orientation.w = self.goal_List[1].Qw
            
            goal.header.seq = self.goal_List[1].seq
            goal.header.stamp = self.goal_List[1].stamp
            goal.header.frame_id = self.goal_List[1].frame_id
            self.goal_pub.publish(goal)

        elif (self.getDistance(egoPose.pose.position, 223.0,226) <= 30 and
            goal.pose.position.x == 223.0 and goal.pose.position.y ==226):
            self.val = 2
            print('Goal 2 (223.0,226) is set')
            goal.pose.position.x = self.goal_List[2].Px
            goal.pose.position.y = self.goal_List[2].Py
            goal.pose.position.z = self.goal_List[2].Py
            goal.pose.orientation.x = self.goal_List[2].Qx
            goal.pose.orientation.y = self.goal_List[2].Qy
            goal.pose.orientation.z = self.goal_List[2].Qz
            goal.pose.orientation.w = self.goal_List[2].Qw

            goal.header.seq = self.goal_List[2].seq
            goal.header.stamp = self.goal_List[2].stamp
            goal.header.frame_id = self.goal_List[2].frame_id
            self.goal_pub.publish(goal)

        elif (self.getDistance(egoPose.pose.position, 84.0,170) <= 30 and
            goal.pose.position.x == 84.0 and goal.pose.position.y ==170):
            self.val = 3
            print('Goal 3 (84.0,170) is set')
            goal.pose.position.x = self.goal_List[0].Px
            goal.pose.position.y = self.goal_List[0].Py
            goal.pose.position.z = self.goal_List[0].Pz
            goal.pose.orientation.x = self.goal_List[0].Qx
            goal.pose.orientation.y = self.goal_List[0].Qy
            goal.pose.orientation.z = self.goal_List[0].Qz
            goal.pose.orientation.w = self.goal_List[0].Qw

            goal.header.seq = self.goal_List[0].seq
            goal.header.stamp = self.goal_List[0].stamp
            goal.header.frame_id = self.goal_List[0].frame_id
            self.goal_pub.publish(goal)
        else:
            print ('.')#"The distance between the car and the goal point is")#,self.getDistance(egoPose.pose.position, goalPose.pose.positon))

       
if __name__=="__main__":
    print ("The hello")
    rospy.init_node('loop_sender')
    #Set the initial position of the goal
    #goal_publisher = rospy.Publisher("move_base_simple/goal", PoseStamped, queue_size=5)
    '''
    goal = PoseStamped()
    goal.pose.position.x = 257.0 #goal_List[0].Px
    goal.pose.position.y = 170.0 #goal_List[0].Py
    goal.pose.position.z = 0.0 #goal_List[0].Pz

    goal.pose.orientation.x = 0.0 #goal_List[0].Qx
    goal.pose.orientation.y = 0.0 #goal_List[0].Qy
    goal.pose.orientation.z = 0.0 #goal_List[0].Qz
    goal.pose.orientation.w = 1.0 #goal_List[0].Qw

    goal.header.seq = 1 #goal_List[0].seq
    goal.header.stamp = rospy.Time.now() #goal_List[0].stamp
    goal.header.frame_id = "Map" #goal_List[0].frame_id
    goal_publisher.publish(goal)
    '''
    loopgoal()
    rospy.spin()
    

