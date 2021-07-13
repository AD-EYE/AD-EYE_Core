#! /usr/bin/env python
import rospy
import roslib
import tf
import math
from std_msgs.msg import Int64
from adeye_msgs.msg import categorized_poses
from adeye_msgs.msg import categorized_pose
from geometry_msgs.msg import PoseArray
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

## A class that will publish the poses to various types of actors
# The class ActorsPosesPublisher publishes poses of 20 pedestrians,20 cars,10 cyclists and 5 motorcycles to the topic
# actors_poses. The actors are initially placed far away from the world in the position (2000,2000,0)
 
class ActorsPosesPublisher():
    ## The constructor
    #@param self The object pointer
    def __init__(self):

        self.INCREMENT_CONSTANT_= 2  # This variable is used for incrementing the poses by a constant value

        #Set the publisher
        self.actors_pose_array_pub_= rospy.Publisher('/actors_poses', categorized_poses, queue_size=1)

        self.publishPoses()

    ##This function sets the initial pose of the actors and also the poses to which actors are to be moved.
    #@param self The object pointer
    #@param Px x position of the pose
    #@param Py y position of the pose
    #@param pose_increment_value Value by which the pose is incremented in each count 
    #@param number_of_actors The total number of actors of each type/category
    #@param actor_category The type of actor
    def getPoseArray(self,Px,Py,pose_increment_value,number_of_actors,actor_category) :
        actors_pose_array = categorized_poses() # Defining the array to which the poses are appended
        
        #Setting the initial pose of the actors
        actor_initial_pose =Pose()
        actor_initial_pose.position.x = 2000
        actor_initial_pose.position.y = 2000
        actor_initial_pose.position.z = 0
        actor_initial_pose.orientation.x = 0
        actor_initial_pose.orientation.y = 0
        actor_initial_pose.orientation.z = 0
        actor_initial_pose.orientation.w = 1

        #For loop to append poses each of the 55 actors 
        for i in range(0,number_of_actors):
            actors_pose = categorized_pose()
            actors_pose.category = actor_category   # Defining the type of actor like car,pedestrain etc
            
            #(Subtract the initial pose of the actors because in matlab the actors initial position is taken as the starting position ie,origin )
            actors_pose.pose.position.x = Px - actor_initial_pose.position.x + pose_increment_value  
            actors_pose.pose.position.y = Py - actor_initial_pose.position.y + pose_increment_value 
            actors_pose.pose.position.z = 0
            actors_pose.pose.orientation.x = 0
            actors_pose.pose.orientation.y = 0
            actors_pose.pose.orientation.z = 0 
            actors_pose.pose.orientation.w = 1
            actors_pose.header.seq = 1 
            actors_pose.header.stamp = rospy.Time.now() 
            actors_pose.header.frame_id = "map"

            actors_pose_array.poses.append(actors_pose)
            
            #Incrementing the poses to form the array of poses for 55 actors.
            Px = Px + self.INCREMENT_CONSTANT_   
            Py = Py + self.INCREMENT_CONSTANT_
        return(actors_pose_array)

    ## The function which publishes the array of poses of all 55 actors in each count.
    #@param self The object pointer 
    def publishPoses(self):
        
        COUNTER = 0 # Setting up a counter to increment the poses by a value so as to make the actors move 
        while not rospy.is_shutdown() and COUNTER < 50:
            pose_increment_value = self.INCREMENT_CONSTANT_ * COUNTER  
            
                      
            array_of_pedestrian_poses = self.getPoseArray(54,168,pose_increment_value, 20,1 )
            array_of_car_poses = self.getPoseArray(96,171,pose_increment_value, 20, 2 )
            array_of_cycle_poses = self.getPoseArray(63,171,pose_increment_value, 10, 3 )
            array_of_motorcycle_poses = self.getPoseArray(208,171,pose_increment_value, 5, 4 )
            
            actors_pose_array = categorized_poses()

            #Appending the poses of all actors to the array and publishing
            actors_pose_array.poses.extend(
                 array_of_pedestrian_poses.poses + array_of_car_poses.poses 
                + array_of_cycle_poses.poses + array_of_motorcycle_poses.poses)
          
          

            rate = rospy.Rate(1)
            self.actors_pose_array_pub_.publish(actors_pose_array)
            rate.sleep()

            COUNTER = COUNTER + 1
            

if __name__=="__main__":
    rospy.init_node('actors_poses') #Initialising the node
    ActorsPosesPublisher()
    