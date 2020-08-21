#!/usr/bin/env python
# license removed for brevity
import roslib
import os
import rospy
from geometry_msgs.msg import PoseStamped
from datetime import datetime
from geometry_msgs.msg import TwistStamped
import numpy as np

Store = True
if Store == True :

    if os.path.isdir('/home/adeye/Experiment_Results/') == False : # checks if the folder exists and creates it if not
        os.mkdir('/home/adeye/Experiment_Results/')
    file = open('/home/adeye/Experiment_Results/ExperimentA.csv','a')

def storespeed(Sp):
    global speed
    speed.append(Sp)

def speedf(data):
    Sp = data.twist.linear.x
    storespeed(Sp)

def storePosition (L):
    global Loc
    global Prevspeed
    global speed
    Loc = L
    storeData(Loc,speed)


def Position(data):

    Px = data.pose.position.x
    Py = data.pose.position.y
    Pz = data.pose.position.z

    L =  [Px,Py,Pz]
    storePosition(L)

def storeData (Loc,speed) :
    print(Loc,speed,'\n')
    if len(speed)>1 :
        spL = len(speed)-1
        if Loc[1]> -423.30 :
            if (speed[spL]==0.0) and (speed[spL-1]!=0.0):
                Collision = 'No'
                Collspeed = 'N/A'
                StopDistance = np.sqrt( (Loc[1]+343.3)**2 + (Loc[0]-150.5)**2 )
                if Loc[1]>-343.3:
                    Collision = 'Yes'
                    StopDistance = - StopDistance
                    Collspeed = str(speed[spL-1])

                file.write("Collision? "+str(Collision)) # then we write all the data needed in ExperimentA.csv
                file.write(', ')
                file.write("Coll speed = "+Collspeed)
                file.write(', ')
                file.write("Stop dist = "+str(StopDistance))
                file.write('\n')

Loc = []
speed = [0.0]
Prevspeed = 0.0

if Store == True :
    MaxVel = rospy.get_param("adeye/motion_planning/op_common_params/maxVelocity")
    file.write("Set speed = "+str(MaxVel)+" , ")

if __name__ == '__main__':
    rospy.init_node('ExperimentA',anonymous = True)

    rospy.Subscriber("/gnss_pose", PoseStamped, Position)
    rospy.Subscriber("/current_velocity", TwistStamped, speedf)
    # if Store == True :
    #     Prevspeed = storeData(Loc,speed,Prevspeed)
    rospy.spin()
