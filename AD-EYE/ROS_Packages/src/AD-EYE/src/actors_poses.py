#! /usr/bin/env python
import rospy
import roslib
import tf
import math
import pyproj
import time
from std_msgs.msg import Int64
from std_msgs.msg import String
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

        self.MAX_ACTOR_PEDESTRIAN = 20
        self.MAX_ACTOR_CAR = 20
        self.MAX_ACTOR_BICYCLE = 10
        self.MAX_ACTOR_MOTORCYCLE = 5

        self.CLEAN_ACTOR = ["0", 2000, 2000, 0, 0, 0, 0, 0]

        ##The period at which the app sends data through ROSbridge, in seconds
        self.SENDING_PERIOD = 3.

        ##An integer representing the number of periods we wait between checks for finding disconnected users
        self.CHECK_DELAY = 3

        ##An integer that get incremented at every itteration of the rospy loop. Used to know when to check for disconnected users
        self.period_counter = 0

        ##A list representing the number of actors in each category
        self.actors_count_by_type = [0, 0, 0, 0] 

        ##A list with the maximum number of actors for each type, sorted by category order
        self.MAX_ACTOR_BY_TYPE = [self.MAX_ACTOR_PEDESTRIAN, self.MAX_ACTOR_CAR, self.MAX_ACTOR_BICYCLE, self.MAX_ACTOR_MOTORCYCLE]

        ##A list of list of information about the differents actors, including the ip of the sender (for identification purpose), the position and orientation relative to the origin of the digital twin
        self.actors_by_type = [[self.CLEAN_ACTOR for j in range(self.MAX_ACTOR_BY_TYPE[i])] for i in range(len(self.MAX_ACTOR_BY_TYPE))]
        ##The previous state of the actors_by_type list.
        self.previous_actors_by_type = [[self.CLEAN_ACTOR for j in range(self.MAX_ACTOR_BY_TYPE[i])] for i in range(len(self.MAX_ACTOR_BY_TYPE))]
        
        ##The subscriber to the topic where the information is sent from the android apps
        self.sub = rospy.Subscriber("/Android_GPS_Data", String, self.UpdateList)
        ##The projector that transforms the latitudes and longitudes into 2D carthesian coordinates
        self.P = pyproj.Proj(proj='utm', zone=31, ellps='WGS84', preserve_units=True)
        ##A list that contains in this order : sender_ip (String), user_id (int), latitude, longitude, altitude, euler_angle1, euler_angle2, euler_angle3 (floats)
        self.msg = []
        ##The origin of the digital twin, in latitude-longitude format
        self.originll = [59.35379833333333, 18.065075]
        ##The origin of the digital twin, in x-y format
        self.originxy = self.P(self.originll[0], self.originll[1])


        self.publishPoses()


    ##A method to find a free index to put the new user in the list of actors
    #Returns the index (int) or None if no index were available
    #@param self the object pointer
    #@param user_type An int indicting the type of actor considered
    def add(self, user_type):
        p_actors = self.previous_actors_by_type[user_type - 1]
        for i in range(len(p_actors)):
            if p_actors[i] == self.CLEAN_ACTOR:
                return i
        return None


    ##A method to find out if an actor was already in the simulation at the previous step, and if so at which index
    #Returns the index (int) of the actor in the previous array or None if the actor was not present.
    #Actors are differentiated by the ip of the sending device
    #@param self the object pointer
    #@param ip A String indicating the IPV4 adress of the sending device, used to differentiate the actors
    #@param user_type An int indicting the type of actor considered
    def was_present(self, ip, user_type):
        for i in range(len(self.previous_actors_by_type[user_type - 1])):
            previous_actor_ip = self.previous_actors_by_type[user_type - 1][i][0]
            if previous_actor_ip == ip:
                return i
        return None


    ##GPS_to_prescan method
    #
    #A method to get the carthesian coordinates of the point given its latitude and longitude relatively to the origin of the digital twin
    #
    #@param self the object pointer
    #@param latitude A float representing the latitude of a point
    #@param longitude A float representing the longitude of a point
    #@param altitude A float representing the altitude of a point
    def GPS_to_prescan(self, latitude, longitude, altitude):
        
        x, y = self.P(latitude, longitude)
        z = altitude

        return [x-self.originxy[0], y-self.originxy[1], z]



    ##This method parse the information received from the android app through Rosbridge and add the informations about the actor to the correct list
    #@param self The object pointer
    def UpdateList(self, data):

        self.previous_actors_by_type = [[list(actor) for actor in actors] for actors in self.actors_by_type] ##Creating the previous step without linking the lists

        self.msg = []
        c=0
        for e in data.data.split(','):
            if c != 0:
                self.msg.append(eval(e))
            else:
                self.msg.append(e)
                c += 1
        
        eulers = self.msg[-4:-1]
        update_count = self.msg[-1]
        quat = tf.transformations.quaternion_from_euler(eulers[0], eulers[1], eulers[2])

        #A list that contains in this order : sender_ip (String), user_id (int), PoseX, PoseY, PoseZ, QuaternionX, QuaternionY, QuaternionZ, QuaternionW (floats)
        actor = self.msg[:2] 
        actor.extend(self.GPS_to_prescan(self.msg[2], self.msg[3],0)) ##altitude is null on the digital twin
        actor.extend(quat)

        user_type = actor[1]
        del actor[1]
        actor.append(time.time())

        if user_type in [1, 2, 3, 4] and self.actors_count_by_type[user_type -1 ] < self.MAX_ACTOR_BY_TYPE[user_type -1]: ##if there is room for more user of this category
            ip = actor[0]
            previous_index = self.was_present(ip, user_type)
            if type(previous_index) == int: ##update the user's position if he was already in the simulation
                self.actors_by_type[user_type - 1][previous_index] = actor
            else:  ##Add the user in the simulation if there is room for more
                place = self.add(user_type)
                if type(place) == int:
                    self.actors_by_type[user_type - 1][place] = actor
                    self.actors_count_by_type[user_type - 1] += 1

        else:
            pass

    

    

    ##A method that disconnects a user if the node did not receive updates in a long time
    #
    #@param self the object pointer
    def Check_disconnection(self):
        now = time.time()
        for actor_list in self.actors_by_type:
            i = self.actors_by_type.index(actor_list) # i represent the user's id - 1
            for actor in actor_list:
                j = actor_list.index(actor) # j represents the index of an actor of type i + 1
                received_time = actor[-1]
                if now - received_time > self.CHECK_DELAY*self.SENDING_PERIOD:
                    self.actors_by_type[i][j] = self.CLEAN_ACTOR

    

    ##This method sets the initial pose of the actors and also the poses to which actors are to be moved.
    #@param self The object pointer
    #@param actor_category an integer representing the user's category (1:pedestrian 2:car 3:bicycle 4:motorcycle)
    def getPoseArray(self, actor_category):
        actors_pose_array = categorized_poses() # Defining the array to which the poses are appended
        

        #Setting the initial pose of the actors
        actor_initial_pose =Pose()
        actor_initial_pose.position.x = self.CLEAN_ACTOR[1]
        actor_initial_pose.position.y = self.CLEAN_ACTOR[2]
        actor_initial_pose.position.z = self.CLEAN_ACTOR[3]
        actor_initial_pose.orientation.x = self.CLEAN_ACTOR[4]
        actor_initial_pose.orientation.y = self.CLEAN_ACTOR[5]
        actor_initial_pose.orientation.z = self.CLEAN_ACTOR[6]
        actor_initial_pose.orientation.w = self.CLEAN_ACTOR[7]

        actors = self.actors_by_type[actor_category - 1]
        previous_actors = self.previous_actors_by_type[actor_category - 1]

        for i in range(len(actors)):
            present = False ##A boolean to indicate if the user was already in the simulation or not

            actors_pose = categorized_pose()
            actors_pose.category = actor_category   # Defining the type of actor like car,pedestrain etc

            actor = actors[i]
            p_actor = previous_actors[i]


            if p_actor != self.CLEAN_ACTOR: ##Was already present
                Px = p_actor[1]
                Py = p_actor[2]
                dx = actor[1] - p_actor[1]
                dy = actor[2] - p_actor[2]
                present = True
                
            elif actor == self.CLEAN_ACTOR: ##Is not linked to a user
                Px = actor_initial_pose.position.x
                Py = actor_initial_pose.position.y
                dx = 0.0
                dy = 0.0
            
            else: ##Is a new user
                Px = actor_initial_pose.position.x
                Py = actor_initial_pose.position.y
                dx = actor[1]
                dy = actor[2]
            
                
            
            
            #(Subtract the initial pose of the actors because in matlab the actors initial position is taken as the starting position ie,origin )
            actors_pose.pose.position.x = dx + Px - actor_initial_pose.position.x
            actors_pose.pose.position.y = dy + Py - actor_initial_pose.position.y
            actors_pose.pose.position.z = 0
            actors_pose.pose.orientation.x = actor[4]
            actors_pose.pose.orientation.y = actor[5]
            actors_pose.pose.orientation.z = actor[6] 
            actors_pose.pose.orientation.w = actor[7]
            actors_pose.header.seq = 1 
            actors_pose.header.stamp = rospy.Time.now() 
            actors_pose.header.frame_id = "map"

            actors_pose_array.poses.append(actors_pose)
            
            
        return(actors_pose_array)



    ## The method which publishes the array of poses of all 55 actors in each count.
    #@param self The object pointer 
    def publishPoses(self):
        
        while not rospy.is_shutdown():    

            if self.period_counter == self.CHECK_DELAY:
                self.period_counter = 0
                self.Check_disconnection()
                      
            array_of_pedestrian_poses = self.getPoseArray(1)
            array_of_car_poses = self.getPoseArray(2)
            array_of_cycle_poses = self.getPoseArray(3)
            array_of_motorcycle_poses = self.getPoseArray(4)
            
            actors_pose_array = categorized_poses()

            #Appending the poses of all actors to the array and publishing
            actors_pose_array.poses.extend(
                 array_of_pedestrian_poses.poses + array_of_car_poses.poses 
                + array_of_cycle_poses.poses + array_of_motorcycle_poses.poses)
          
          

            rate = rospy.Rate(self.SENDING_PERIOD)
            self.actors_pose_array_pub_.publish(actors_pose_array)
            self.period_counter += 1
            rate.sleep()
            

if __name__=="__main__":
    rospy.init_node('actors_poses') #Initialising the node
    ActorsPosesPublisher()