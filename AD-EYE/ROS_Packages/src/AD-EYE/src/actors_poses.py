#! /usr/bin/env python
import rospy
import roslib
import tf
import math
import pyproj
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

        self.CLEAN_ACTOR = ["0", 0, 0, 0, 0, 0, 0, 0]

        self.actors_count_by_type = [0, 0, 0, 0] ##Represent the number of actors in each category

        ##A list of informations about the pedestrian typed actors, including the ip of the sender (for identification purpose), the position and orientation relative to the origin of the digital twin
        self.pedestrians = [self.CLEAN_ACTOR for i in range(self.MAX_ACTOR_PEDESTRIAN)]
        ##A list of informations about the cars typed actors, including the ip of the sender (for identification purpose), the position and orientation relative to the origin of the digital twin
        self.cars = [self.CLEAN_ACTOR for i in range(self.MAX_ACTOR_CAR)]
        ##A list of informations about the bicycle typed actors, including the ip of the sender (for identification purpose), the position and orientation relative to the origin of the digital twin
        self.bicycles = [self.CLEAN_ACTOR for i in range(self.MAX_ACTOR_BICYCLE)]
        ##A list of informations about the motorcycle typed actors, including the ip of the sender (for identification purpose), the position and orientation relative to the origin of the digital twin
        self.motorcycles = [self.CLEAN_ACTOR for i in range(self.MAX_ACTOR_MOTORCYCLE)]
        ##A list of informations about the pedestrian typed actors at the precedent step, including the ip of the sender (for identification purpose), the position and orientation relative to the origin of the digital twin
        self.previous_pedestrians = [self.CLEAN_ACTOR for i in range(self.MAX_ACTOR_PEDESTRIAN)]
        ##A list of informations about the cars typed actors at the precedent step, including the ip of the sender (for identification purpose), the position and orientation relative to the origin of the digital twin
        self.previous_cars = [self.CLEAN_ACTOR for i in range(self.MAX_ACTOR_CAR)]
        ##A list of informations about the bicycle typed actors at the precedent step, including the ip of the sender (for identification purpose), the position and orientation relative to the origin of the digital twin
        self.previous_bicycles = [self.CLEAN_ACTOR for i in range(self.MAX_ACTOR_BICYCLE)]
        ##A list of informations about the motorcycle typed actors at the precedent step, including the ip of the sender (for identification purpose), the position and orientation relative to the origin of the digital twin
        self.previous_motorcycles = [self.CLEAN_ACTOR for i in range(self.MAX_ACTOR_MOTORCYCLE)]

        self.actors_by_type = [self.pedestrians, self.cars, self.bicycles, self.motorcycles]
        self.previous_actors_by_type = [self.previous_pedestrians, self.previous_cars, self.previous_bicycles, self.previous_motorcycles]
        self.MAX_ACTOR_BY_TYPE = [self.MAX_ACTOR_PEDESTRIAN, self.MAX_ACTOR_CAR, self.MAX_ACTOR_BICYCLE, self.MAX_ACTOR_MOTORCYCLE]

        ##The subscriber to the topic where th information is sent from the android apps
        self.sub = rospy.Subscriber("/chatter", String, self.UpdateList)
        ##The projector that transforms the latitudes and longitudes into 2D carthesian coordinates
        self.P = pyproj.Proj(proj='utm', zone=31, ellps='WGS84', preserve_units=True)
        ##A list that contains in this order : sender_ip (String), user_id (int), latitude, longitude, altitude, euler_angle1, euler_angle2, euler_angle3 (floats)
        self.msg = []
        ##The origin of the digital twin, in latitude-longitude format
        self.originll = [59.35379833333333, 18.065075]
        ##The origin of the digital twin, in x-y format
        self.originxy = self.P(self.originll[0], self.originll[1])

        self.publishPoses()


    ##This method parse the information received from the android app through Rosbridge and add the informations about the actor to the correct list
    #@param self The object pointer
    def UpdateList(self):
        self.msg = []
        c=0
        for e in data.data.split(','):
            if c != 0:
                self.msg.append(eval(e))
            else:
                self.msg.append(e)
                c += 1
        
        eulers = self.msg[-3:]
        quat = tf.transformations.quaternion_from_euler(eulers[0], eulers[1], eulers[2])

        #A list that contains in this order : sender_ip (String), user_id (int), PoseX, PoseY, PoseZ, QuaternionX, QuaternionY, QuaternionZ, QuaternionW (floats)
        actor = self.msg[:2] 
        actor.extend(self.GPS_to_prescan(self.msg[2], self.msg[3],0)) ##altitude is null on the digital twin
        actor.extend(quat)

        user_type = actor[1]
        del actor[1]

        if user_type == 1 and self.actors_count_by_type[user_type -1 ] < self.MAX_ACTOR_BY_TYPE[user_type -1]: ##if the user is a pedestrian and there is room for more
            ip = actor[0]
            previous_index = self.was_present(ip, user_type)
            if type(previous_index) == int: ##update the user's position if he was already in the simulation
                self.actors_by_type[user_type - 1][previous_index] = actor
            else:  ##Add the user in the simulation if there is room for more
                place = self.add(user_type)
                if type(place) == int:
                    self.actors_by_type[user_type - 1][place] = actor
                    self.actors_count_by_type[user_type - 1] += 1

        elif user_type == 2 and self.actors_count_by_type[user_type -1 ] < self.MAX_ACTOR_BY_TYPE[user_type -1]: ##if the user is a pedestrian and there is room for more
            ip = actor[0]
            previous_index = self.was_present(ip, user_type)
            if type(previous_index) == int: ##update the user's position if he was already in the simulation
                self.actors_by_type[user_type - 1][previous_index] = actor
            else:  ##Add the user in the simulation if there is room for more
                place = self.add(user_type)
                if type(place) == int:
                    self.actors_by_type[user_type - 1][place] = actor
                    self.actors_count_by_type[user_type - 1] += 1

        elif user_type == 3 and self.actors_count_by_type[user_type -1 ] < self.MAX_ACTOR_BY_TYPE[user_type -1]: ##if the user is a pedestrian and there is room for more
            ip = actor[0]
            previous_index = self.was_present(ip, user_type)
            if type(previous_index) == int: ##update the user's position if he was already in the simulation
                self.actors_by_type[user_type - 1][previous_index] = actor
            else:  ##Add the user in the simulation if there is room for more
                place = self.add(user_type)
                if type(place) == int:
                    self.actors_by_type[user_type - 1][place] = actor
                    self.actors_count_by_type[user_type - 1] += 1

        elif user_type == 4 and self.actors_count_by_type[user_type -1 ] < self.MAX_ACTOR_BY_TYPE[user_type -1]: ##if the user is a pedestrian and there is room for more
            ip = actor[0]
            previous_index = self.was_present(ip, user_type)
            if type(previous_index) == int: ##update the user's position if he was already in the simulation
                self.actors_by_type[user_type - 1][previous_index] = actor
            else:  ##Add the user in the simulation if there is room for more
                place = self.add(user_type)
                if type(place) == int:
                    self.actors_by_type[user_type - 1][place] = actor
                    self.actors_count_by_type[user_type - 1] += 1

        elif user_type == -1:
            pass
        
        else:
            pass


    ##A method to find a free index to put the new user in the list of actors
    #Returns the index (int) or None if no index were available
    #@param self the object pointer
    #@param user_type An int indicting the type of actor considered
    def add(self, user_type):
        p_actors = self.previous_actors_by_type[user_type - 1]
        for i in range(len(actors)):
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


    ##This method sets the initial pose of the actors and also the poses to which actors are to be moved.
    #@param self The object pointer
    #@param actor_category an integer representing the user's category (1:pedestrian 2:car 3:bicycle 4:motorcycle)
    def getPoseArray(self, actor_category):
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

        actors = self.actors_by_type[actor_category - 1]
        previous_actors = self.previous_actors_by_type[actor_category - 1]

        for i in range(len(actors)):
            present = False ##A boolean to indicate if he user was already in the simulation or not
            new = False ##A boolean to indicate if the actor must be initialized

            actors_pose = categorized_pose()
            actors_pose.category = actor_category   # Defining the type of actor like car,pedestrain etc

            actor = actors[i]
            p_actor = previous_actors[i]


            if p_actor != self.CLEAN_ACTOR: ##Was already present
                Px = p_actor[1]
                Py = p_actor[2]
                dx = actor[1]-Px
                dy = actor[2]-Py
                present = True
                
            elif actor == self.CLEAN_ACTOR: ##Is not linked to a user
                Px = actor_initial_pose.position.x
                Py = actor_initial_pose.position.y
                dx = 0
                dy = 0
            
            else: ##Is a new user
                Px = actor_initial_pose.position.x
                Py = actor_initial_pose.position.y
                dx = actor[1]
                dy = actor[2]
            
                
            
            
            #(Subtract the initial pose of the actors because in matlab the actors initial position is taken as the starting position ie,origin )
            actors_pose.pose.position.x = Px - actor_initial_pose.position.x + dx  
            actors_pose.pose.position.y = Py - actor_initial_pose.position.y + dy 
            actors_pose.pose.position.z = 0
            actors_pose.pose.orientation.x = actor[4]
            actors_pose.pose.orientation.y = actor[5]
            actors_pose.pose.orientation.z = actor[6] 
            actors_pose.pose.orientation.w = actor[7]
            actors_pose.header.seq = 1 
            actors_pose.header.stamp = rospy.Time.now() 
            actors_pose.header.frame_id = "map"

            actors_pose_array.poses.append(actors_pose)
            
            
        self.previous_actors_by_type[actor_category - 1] = list(self.actors_by_type[actor_category - 1])
        return(actors_pose_array)



    ## The method which publishes the array of poses of all 55 actors in each count.
    #@param self The object pointer 
    def publishPoses(self):
        
        s=0
        for actor_type in self.actors_by_type:
            s+=len(actor_type)
        while not rospy.is_shutdown() and s>0:            
                      
            array_of_pedestrian_poses = self.getPoseArray(1)
            array_of_car_poses = self.getPoseArray(2)
            array_of_cycle_poses = self.getPoseArray(3)
            array_of_motorcycle_poses = self.getPoseArray(4)
            
            actors_pose_array = categorized_poses()

            #Appending the poses of all actors to the array and publishing
            actors_pose_array.poses.extend(
                 array_of_pedestrian_poses.poses + array_of_car_poses.poses 
                + array_of_cycle_poses.poses + array_of_motorcycle_poses.poses)
          
          

            rate = rospy.Rate(1)
            self.actors_pose_array_pub_.publish(actors_pose_array)
            rate.sleep()
            

if __name__=="__main__":
    rospy.init_node('actors_poses') #Initialising the node
    ActorsPosesPublisher()