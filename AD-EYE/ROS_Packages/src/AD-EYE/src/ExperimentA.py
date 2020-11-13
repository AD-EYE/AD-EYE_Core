#!/usr/bin/env python
# license removed for brevity
import roslib
import os
import rospy
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import TwistStamped
from geometry_msgs.msg import Point
from std_msgs.msg import Bool
import numpy as np
import tf

Store = True

if Store == True :
    if os.path.isdir('/home/adeye/Experiment_Results/') == False : # checks if the folder exists and creates it if not
        os.mkdir('/home/adeye/Experiment_Results/')
    file = open('/home/adeye/Experiment_Results/ExperimentA.csv','a')


class ExperimentARecorder:
    ego_speeds = []
    collision_speed = 'N/A'
    collision = False
    pedestrian_position = [0,0]
    ego_pose = [0,0,0]
    distances_ego_pedestrian = []


    def __init__(self):
        

        rospy.Subscriber("/gnss_pose", PoseStamped, self.egoPoseCallback)
        rospy.Subscriber("/current_velocity", TwistStamped, self.egoSpeedCallback)
        rospy.Subscriber("/simulink/pedestrian_pose", Point, self.pedestrianPositionCallback)

        self.stop_pub = rospy.Publisher("/simulink/stop_experiment",Bool, queue_size = 1) # stop_publisher



    def egoPoseCallback(self, data):
        Px = data.pose.position.x
        Py = data.pose.position.y
        quaternion = (data.pose.orientation.x, data.pose.orientation.y, data.pose.orientation.z, data.pose.orientation.w)
        euler = tf.transformations.euler_from_quaternion(quaternion)
        self.ego_pose =  [Px, Py, euler[0]]
        if Store == True :
            self.storeData(self.ego_pose, self.ego_speeds, self.pedestrian_position)

    def pedestrianPositionCallback(self, data):
        x = data.x
        y = data.y
        self.pedestrian_position = [x,y]

    def egoSpeedCallback(self, data):
        current_ego_speed = data.twist.linear.x
        self.ego_speeds.append(current_ego_speed)


    # procedure that procsses and stores the data
    def storeData (self, ego_pose, ego_speeds, pedestrian_position):
        if len(ego_speeds)>1 : # in order to have access to the previous speed
            spL = len(ego_speeds)-1
        
            d = np.sqrt( (ego_pose[1]-pedestrian_position[1])**2 + (ego_pose[0]-pedestrian_position[0])**2 )
            self.distances_ego_pedestrian.append(d)

            if len(self.distances_ego_pedestrian)>2 :

                if self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-3]<self.distances_ego_pedestrian[len(self.distances_ego_pedestrian)-2] : # if the distance is rising, so the pedestrian has been passed,
                                                                                                    # we don't compare distance_Ego_P[len(distance_Ego_P)-2] with d
                                                                                                    # because they are equal when the car stops
                    if self.collision == False : # if the collision didn't occurred

                        self.writeParameters()

                        file.write("The pedestrian wasn't on the road when the car passed him --> no collision, no stop \n")
                        file.close()

                        self.stop_pub.publish(True) # stop_publisher
                    else : #if the collision occurred
                        if (ego_speeds[spL]==0.0) and (ego_speeds[spL-1]!=0.0): # if the car just stoped (to test it only once)
                            Collision = 'Yes'
                            StopDistance = - d

                            self.writeParameters()

                            file.write("Collision, "+Collision) # then we write all the data needed in ExperimentA.csv
                            file.write(', ')
                            file.write("Coll speed, "+self.collision_speed)
                            file.write(', ')
                            file.write("Stop dist, "+str(StopDistance))
                            file.write('\n')
                            file.close()

                            self.stop_pub.publish(True) # stop_publisher

                else :
                    if d<2.5 : # if there is a collision
                        if self.collision == False : # we set the collision speed
                            self.collision = True
                            self.collision_speed = str(ego_speeds[spL-1])
                    if (ego_speeds[spL]==0.0) and (ego_speeds[spL-1]!=0.0): # if the car just stoped (to test it only once)
                        Collision = 'No'
                        StopDistance = d

                        self.writeParameters()

                        file.write("Collision, "+str(Collision)) # then we write all the data needed in ExperimentA.csv
                        file.write(', ')
                        file.write("Coll speed, "+self.collision_speed)
                        file.write(', ')
                        file.write("Stop dist, "+str(StopDistance))
                        file.write('\n')
                        file.close()

                        self.stop_pub.publish(True) # stop_publisher

    def writeParameters(self):
        MaxVel = rospy.get_param("adeye/motion_planning/op_common_params/maxVelocity")
        file.write("Set speed, "+str(MaxVel)+" , ")
        Rain = rospy.get_param("/simulink/rain_intensity")
        file.write("Set rain intensity, "+str(Rain)+" , ")
        Reflectivity = rospy.get_param("/simulink/reflectivity")
        file.write("Set reflectivity, "+str(Reflectivity)+" , ")
        Distance = 0
        if(rospy.has_param("/simulink/trigger_distance")):
            Distance = rospy.get_param("/simulink/trigger_distance")
        file.write("Set trigger distance, "+str(Distance)+" , ")




#listens to the topics
if __name__ == '__main__':
    rospy.init_node('ExperimentA_recorder')
    exp_A_recorder = ExperimentARecorder()
    rospy.spin()
