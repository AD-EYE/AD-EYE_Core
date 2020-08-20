#!/usr/bin/env python
# license removed for brevity
import roslib
import os
import rospy
from std_msgs import Float32
from datetime import datetime
from geometry_msgs.msg import PoseStamped

Store = True
if Store == True :

    if os.path.isdir('/home/adeye/Experiment_Results/') == False : # checks if the folder exists and creates it if not
        os.mkdir('/home/adeye/Experiment_Results/')
    NumberFound = False
    k=1
    while NumberFound == False :
        if os.path.isfile('/home/adeye/Experiment_Results/EstimLocalisation'+str(k)+'.csv')==True:
            k+=1
        else :
            file = open('/home/adeye/Experiment_Results/EstimLocalisation'+str(k)+'.csv','a')
            NumberFound=True

def storeGTP(list):
    global GTP
    GTP = list

def fstoreGTP(data):

    Px = data.pose.position.x
    Py = data.pose.position.y
    Pz = data.pose.position.z

    storeGTP( [Px,Py,Pz])

def storeEP(list):
    global EP
    EP = list

def fstoreEP(data):

    Px = data.pose.position.x
    Py = data.pose.position.y
    Pz = data.pose.position.z

    storeEP([Px,Py,Pz])

def storeIter(val):
    global I
    I = val

def fstoreIter(data):
    storeIter(data.iteration)

def storeData (GTP,EP,I):
    xg,yg,zg = GTP[0],GTP[1],GTP[2]
    xe,ye,ze = EP[0],EP[1],EP[2]

    file.write("Ground Truth Pos = "+str(xg)+" , "+str(yg)+" , "+str(zg)+" , ")
    file.write("Perceived Pos = "+str(xe)+" , "+str(ye)+" , "+str(ze)+" , ")
    file.write("Nbr of iter = "+str(I)+" , ")

    if (round(xg,1)==round(xe,1) ) and (round(yg,1)==round(ye,1) ) and (round(zg,1)==round(ze,1) ):
        file.write("Converge? = Yes \n")
    else :
        file.write("Converge? = No \n")

GTP =[]
EP = []
I = 0
if Store == True :
    MaxVel = rospy.get_param("adeye/motion_planning/op_common_params/maxVelocity")
    file.write("Set speed = "+str(MaxVel)+" \n ")

if __name__ == '__main__':
    rospy.init_node('ExperimentB',anonymous = True)

    rospy.Subscriber("/std_stat", Float32, fstoreIter)
    rospy.Subscriber("/ndt_pose", PoseStamped, fstoreEP)
    rospy.Subscriber("/gnss_pose", PoseStamped, fstoreIter)
    storeData(GTP,EP,I)
    rospy.spin()
