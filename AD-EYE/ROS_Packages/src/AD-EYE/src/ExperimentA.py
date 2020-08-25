#!/usr/bin/env python
# license removed for brevity
import roslib
import os
import rospy
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import TwistStamped
import numpy as np

Store = True
if Store == True :

    if os.path.isdir('/home/adeye/Experiment_Results/') == False : # checks if the folder exists and creates it if not
        os.mkdir('/home/adeye/Experiment_Results/')
    file = open('/home/adeye/Experiment_Results/ExperimentA.csv','a')

# procedures that reads what is published on the topic
def storespeed(Sp):
    global speed
    speed.append(Sp)

def speedf(data):
    Sp = data.twist.linear.x
    storespeed(Sp)

# procedures that edit the global variales
def storePosition (L):
    global Loc
    global Prevspeed
    global speed
    Loc = L
    storeData(Loc,speed) # we call the procedure only once (errors with line 48 if not)


def Position(data):

    Px = data.pose.position.x
    Py = data.pose.position.y
    Pz = data.pose.position.z
    L =  [Px,Py,Pz]
    storePosition(L)

# procedure that procsses and stores the data
def storeData (Loc,speed) :
    global CollSp
    global Coll
    if len(speed)>1 : # in order to have access to the previous speed
        spL = len(speed)-1
        if Loc[1]> -423.30 : # if the car did almost the half of its path (to not have tests if it is not necessary)
            if Loc[1]>-343.3 :
                if Coll == False : # we set the collision speed
                    Coll = True
                    CollSp = str(speed[spL-1])
            if (speed[spL]==0.0) and (speed[spL-1]!=0.0): # if the car just stoped (to test it only once)
                Collision = 'No'
                StopDistance = np.sqrt( (Loc[1]+343.3)**2 + (Loc[0]-150.5)**2 )
                if Loc[1]>-343.3: #if there is a collision
                    Collision = 'Yes'
                    StopDistance = - StopDistance

                file.write("Collision? "+str(Collision)) # then we write all the data needed in ExperimentA.csv
                file.write(', ')
                file.write("Coll speed = "+CollSp)
                file.write(', ')
                file.write("Stop dist = "+str(StopDistance))
                file.write('\n')

# we declare the global values
Loc = []
speed = []
CollSp = 'N/A'
Coll = False

# writes the parameters of the experiment
if Store == True :
    MaxVel = rospy.get_param("adeye/motion_planning/op_common_params/maxVelocity")
    file.write("Set speed = "+str(MaxVel)+" , ")
    Rain = rospy.get_param("/simulink/rain_intensity")
    file.write("Set rain intensity = "+str(Rain)+" , ")
    Reflectivity = rospy.get_param("/simulink/reflectivity")
    file.write("Set reflectivity = "+str(Reflectivity)+" , ")

# listens to the topics
if __name__ == '__main__':
    rospy.init_node('ExperimentA',anonymous = True)

    rospy.Subscriber("/gnss_pose", PoseStamped, Position)
    rospy.Subscriber("/current_velocity", TwistStamped, speedf)
    rospy.spin()
