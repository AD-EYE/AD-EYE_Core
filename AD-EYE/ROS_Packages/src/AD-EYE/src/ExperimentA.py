#!/usr/bin/env python
# license removed for brevity
import roslib
import os
import rospy
from geometry_msgs.msg import PoseStamped
from datetime import datetime
from geometry_msgs.msg import TwistStamped

Store = True
if Store == True :

    if os.path.isdir('/home/adeye/Experiment_Results/') == False : # checks if the folder exists and creates it if not
        os.mkdir('/home/adeye/Experiment_Results/')
    file = open('/home/adeye/Experiment_Results/ExperimentA.csv','a')

def storespeed(Sp):
    global speed
    speed = Sp

def speedf(data):
    speed = data.twist.linear.x
    storespeed(speed)

def storePosition (L):
    global Loc
    Loc = L

def Position(data):

    Px = data.pose.position.x
    Py = data.pose.position.y
    Pz = data.pose.position.z

    L =  [Px,Py,Pz]
    storePosition(L)

def storeData (Loc,speed,Prevspeed) :
    if Loc[1]> 230 :
        if (speed==0.0) and (Prevspeed!=0.0):
            Collision = 'No'
            Collspeed = 'N/A'
            StopDistance = np.sqrt( (Loc[1]+524.58)**2 + (Loc[0]-261.75)**2 )
            if Loc[1]<=-524.58:
                Collsion = 'Y'
                StopDistance = - StopDistance
                Collspeed = str(speed)

            file.write("Collision? "+str(Collision)) # then we write all the data needed in ExperimentA.csv
            file.write(',')
            file.write("Coll speed = "+Collspeed)
            file.write(',')
            file.write("Stop dist = "+str(StopDistance))
            file.write('\n')
    Prevspeed = speed
    return(Prevspeed)

Loc = [0,0,0]
speed = 0
Prevspeed = 0

if Store == True :
    MaxVel = rospy.get_param("adeye/motion_planning/op_common_params/maxVelocity")
    file.write("Set speed = "+str(MaxVel)+" , ")

if __name__ == '__main__':
    rospy.init_node('ExperimentA',anonymous = True)

    rospy.Subscriber("/gnss_pose", PoseStamped, Position)
    rospy.Subscriber("/current_velocity", TwistStamped, speedf)
    if Store == True :
        Prevspeed = storeData(Loc,speed,Prevspeed)
    rospy.spin()
