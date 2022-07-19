#! /usr/bin/env python
import rospy
import roslib
import tf
import math
import pyproj ##A library used to convert the GPS coordinates (latitude and longitude) to planar (x y) coordinates 
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
# actors_poses. The actors are initially placed far away from the world in the position (2000,2000,0).
# Because of the value expected by Matlab, the integer representing the user type must be set between 1 and 4 (1:pedestrian 2:car 3:bicycle 4:motorcycle). Thus, we need to offset it by one to use it as a list index.
class ActorsPosesPublisher():
    ## The constructor
    #@param self The object pointer
    def __init__(self):

        #Set the publisher
        self.actors_pose_array_pub_= rospy.Publisher('/actors_poses', categorized_poses, queue_size=1)

        self.MAX_ACTOR_PEDESTRIAN_ = 20
        self.MAX_ACTOR_CAR_ = 20
        self.MAX_ACTOR_BICYCLE_ = 10
        self.MAX_ACTOR_MOTORCYCLE_ = 5

        self.DEFAULT_POSE_ = ["0", 2000, 2000, 0, 0, 0, 0, 0]

        ##The period at which the app sends data through ROSbridge, in seconds
        self.SENDING_PERIOD_ = 3.

        ##An integer representing the number of periods we wait between checks for finding disconnected users
        self.CHECK_DELAY_ = 3

        ##An integer that get incremented at every itteration of the rospy loop. Used to know when to check for disconnected users
        self.period_counter_ = 0

        ##A list representing the number of actors in each category
        self.actors_count_by_type_ = [0, 0, 0, 0] 

        ##A list with the maximum number of actors for each type, sorted by category order
        self.MAX_ACTOR_BY_TYPE_ = [self.MAX_ACTOR_PEDESTRIAN_, self.MAX_ACTOR_CAR_, self.MAX_ACTOR_BICYCLE_, self.MAX_ACTOR_MOTORCYCLE_]

        ##A list of list of information about the differents actors, including the ip of the sender (for identification purpose), the position and orientation relative to the origin of the digital twin
        self.actors_by_type_ = [[self.DEFAULT_POSE_ for j in range(self.MAX_ACTOR_BY_TYPE_[i])] for i in range(len(self.MAX_ACTOR_BY_TYPE_))]
        ##The previous state of the actors_by_type_ list.
        self.previous_actors_by_type_ = [[self.DEFAULT_POSE_ for j in range(self.MAX_ACTOR_BY_TYPE_[i])] for i in range(len(self.MAX_ACTOR_BY_TYPE_))]
        
        ##The subscriber to the topic where the information is sent from the android apps
        self.app_info_sub_ = rospy.Subscriber("/Android_GPS_Data", String, self.appInfoCallback)
        ##The projector that transforms the latitudes and longitudes into 2D carthesian coordinates
        self.gps_projector_ = pyproj.Proj(proj='utm', zone=31, ellps='WGS84', preserve_units=True)
        ##The origin of the digital twin, in latitude-longitude format
        self.originll_ = [59.35379833333333, 18.065075]
        ##The origin of the digital twin, in x-y format
        self.originxy_ = self.gps_projector_(self.originll_[0], self.originll_[1])


        self.mainLoop()


    ##A method to find a free index to put the new user in the list of actors
    #Returns the index (int) or None if no index were available
    #@param self the object pointer
    #@param user_type An int indicting the type of actor considered
    def getEmptyIndex(self, user_type):
        p_actors = self.previous_actors_by_type_[user_type - 1]
        for i in range(len(p_actors)):
            if p_actors[i] == self.DEFAULT_POSE_:
                return i
        return None


    ##A method to find out if an actor was already in the simulation at the previous step, and if so at which index
    #Returns the index (int) of the actor in the previous array or None if the actor was not present.
    #Actors are differentiated by the ip of the sending device
    #@param self the object pointer
    #@param ip A String indicating the IPV4 adress of the sending device, used to differentiate the actors
    #@param user_type An int indicting the type of actor considered
    def getPreviousIndex(self, ip, user_type):
        for i in range(len(self.previous_actors_by_type_[user_type - 1])):
            previous_actor_ip = self.previous_actors_by_type_[user_type - 1][i][0]
            if previous_actor_ip == ip:
                return i
        return None


    ##gpsToPrescan method
    #
    #A method to get the carthesian coordinates of the point given its latitude and longitude relatively to the origin of the digital twin
    #
    #@param self the object pointer
    #@param latitude A float representing the latitude of a point
    #@param longitude A float representing the longitude of a point
    #@param altitude A float representing the altitude of a point
    def gpsToPrescan(self, latitude, longitude, altitude):
        
        x, y = self.gps_projector_(latitude, longitude)
        z = altitude

        return [x-self.originxy_[0], y-self.originxy_[1], z]



    ##This method parse the information received from the android app through Rosbridge and add the informations about the actor to the correct list
    #@param self The object pointer
    def appInfoCallback(self, data):

        self.previous_actors_by_type_ = [[list(actor) for actor in actors] for actors in self.actors_by_type_] ##Creating the previous step without linking the lists

        ##A list that contains in this order : sender_ip (String), user_id (int), latitude, longitude, altitude, euler_angle1, euler_angle2, euler_angle3 (floats)
        msg = []
        c=0
        for e in data.data.split(','):
            if c != 0:
                msg.append(eval(e))
            else:
                msg.append(e)
                c += 1
        
        eulers = msg[-4:-1]
        update_count = msg[-1]
        quat = tf.transformations.quaternion_from_euler(eulers[0], eulers[1], eulers[2])

        #A list that contains in this order : sender_ip (String), user_id (int), PoseX, PoseY, PoseZ, QuaternionX, QuaternionY, QuaternionZ, QuaternionW (floats)
        actor = msg[:2] 
        actor.extend(self.gpsToPrescan(msg[2], msg[3],0)) ##altitude is null on the digital twin
        actor.extend(quat)

        user_type = actor[1]
        del actor[1]
        actor.append(time.time())

        if user_type in [1, 2, 3, 4] and self.actors_count_by_type_[user_type -1 ] < self.MAX_ACTOR_BY_TYPE_[user_type -1]: ##if there is room for more user of this category
            ip = actor[0]
            previous_index = self.getPreviousIndex(ip, user_type)
            if type(previous_index) == int: ##update the user's position if he was already in the simulation
                self.actors_by_type_[user_type - 1][previous_index] = actor
            else:  ##Add the user in the simulation if there is room for more
                place = self.getEmptyIndex(user_type)
                if type(place) == int:
                    self.actors_by_type_[user_type - 1][place] = actor
                    self.actors_count_by_type_[user_type - 1] += 1

        else:
            pass

    

    

    ##A method that disconnects a user if the node did not receive updates in a long time
    #
    #@param self the object pointer
    def checkDisconnection(self):
        now = time.time()
        for actor_list in self.actors_by_type_:
            i = self.actors_by_type_.index(actor_list) # i represent the user's id - 1
            for actor in actor_list:
                j = actor_list.index(actor) # j represents the index of an actor of type i + 1
                received_time = actor[-1]
                if now - received_time > self.CHECK_DELAY_*self.SENDING_PERIOD_:
                    self.actors_by_type_[i][j] = self.DEFAULT_POSE_


    ##This method returns the variation of position between this step and the previous position, and the previous coordinates
    # It returns the tuple (Px, Py, dx, dy) made of floats
    #@param self The object pointer
    #@param actor A list with the informations about the actor at the current step
    #@param p_actor A list with the informations about the actor at the previous step
    def getPreviousPoseAndDisplacement(self, actor, p_actor, actor_initial_pose):
        if p_actor != self.DEFAULT_POSE_: ##Was already present
            Px = p_actor[1]
            Py = p_actor[2]
            dx = actor[1] - p_actor[1]
            dy = actor[2] - p_actor[2]
                
        elif actor == self.DEFAULT_POSE_: ##Is not linked to a user
            Px = actor_initial_pose.position.x
            Py = actor_initial_pose.position.y
            dx = 0.0
            dy = 0.0
            
        else: ##Is a new user
            Px = actor_initial_pose.position.x
            Py = actor_initial_pose.position.y
            dx = actor[1]
            dy = actor[2]

        return (Px, Py, dx, dy)


    ##This method updates the actors_poses variable with the correct coordinates to place the actor at the right place in the simulation
    #It subtract the initial pose of the actors because in matlab the actors initial position is taken as the starting position ie,origin 
    #@param self The object pointer
    #@param actors_pose A categorized_posed object that will be modified to represent the new position of the user according to the displacement and previous pose parameters 
    #@param actor A list with all of the informations on the actor
    #@param actor_initial_pose A categorized_pose object representing the default position of an actor when it isn't in the simulation
    #@param Px A float representing the x position of the actor at the previous step
    #@param Py A float representing the x position of the actor at the previous step
    #@param dx A float representing the x displacement of the actor relative to its previous position
    #@param dy A float representing the y displacement of the actor relative to its previous position
    def updateActorPose(self, actors_pose, actor, actor_initial_pose, Px, Py, dx, dy):
        
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


    ##This method sets the initial pose of the actors and also the poses to which actors are to be moved.
    #@param self The object pointer
    #@param actor_category an integer representing the user's category (1:pedestrian 2:car 3:bicycle 4:motorcycle).
    def getPoseArray(self, actor_category):
        actors_pose_array = categorized_poses() # Defining the array to which the poses are appended
        

        #Setting the initial pose of the actors
        actor_initial_pose =Pose()
        actor_initial_pose.position.x = self.DEFAULT_POSE_[1]
        actor_initial_pose.position.y = self.DEFAULT_POSE_[2]
        actor_initial_pose.position.z = self.DEFAULT_POSE_[3]
        actor_initial_pose.orientation.x = self.DEFAULT_POSE_[4]
        actor_initial_pose.orientation.y = self.DEFAULT_POSE_[5]
        actor_initial_pose.orientation.z = self.DEFAULT_POSE_[6]
        actor_initial_pose.orientation.w = self.DEFAULT_POSE_[7]

        actors = self.actors_by_type_[actor_category - 1]
        previous_actors = self.previous_actors_by_type_[actor_category - 1]

        for i in range(len(actors)):

            actors_pose = categorized_pose()
            actors_pose.category = actor_category   # Defining the type of actor like car,pedestrain etc

            actor = actors[i]
            p_actor = previous_actors[i]


            
            
            Px, Py, dx, dy = self.getPreviousPoseAndDisplacement(actors[i], previous_actors[i], actor_initial_pose)
            

            self.updateActorPose(actors_pose, actors[i], actor_initial_pose, Px, Py, dx, dy)
            

            actors_pose_array.poses.append(actors_pose)
            
            


        return(actors_pose_array)



    ## The method which publishes the array of poses of all 55 actors in each count.
    #@param self The object pointer 
    def mainLoop(self):
        
        while not rospy.is_shutdown():    

            if self.period_counter_ == self.CHECK_DELAY_:
                self.period_counter_ = 0
                self.checkDisconnection()
                      
            array_of_pedestrian_poses = self.getPoseArray(1)
            array_of_car_poses = self.getPoseArray(2)
            array_of_cycle_poses = self.getPoseArray(3)
            array_of_motorcycle_poses = self.getPoseArray(4)
            
            actors_pose_array = categorized_poses()

            #Appending the poses of all actors to the array and publishing
            actors_pose_array.poses.extend(
                 array_of_pedestrian_poses.poses + array_of_car_poses.poses 
                + array_of_cycle_poses.poses + array_of_motorcycle_poses.poses)
          
          

            rate = rospy.Rate(self.SENDING_PERIOD_)
            self.actors_pose_array_pub_.publish(actors_pose_array)
            self.period_counter_ += 1
            rate.sleep()
            

if __name__=="__main__":
    rospy.init_node('actors_poses') #Initialising the node
    ActorsPosesPublisher()