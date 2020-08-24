#!/usr/bin/env python
# license removed for brevity
import roslib
import os
import rospy
from std_msgs.msg import Float32
from datetime import datetime
from geometry_msgs.msg import PoseStamped

Store = True
if Store == True :

    if os.path.isdir('/home/adeye/Experiment_Results/') == False : # checks if the folder exists and creates it if not
        os.mkdir('/home/adeye/Experiment_Results/')
    NumberFound = False
    k=1
    while NumberFound == False :
        if os.path.isfile('/home/adeye/Experiment_Results/ExperimentB'+str(k)+'.csv')==True: # creates a file for each experiment
            k+=1
        else :
            file = open('/home/adeye/Experiment_Results/ExperimentB'+str(k)+'.csv','a')
            NumberFound=True

# procedures that edits the global variables
def storeGTP(list):
    global GTP
    global CdayGTP
    global countDayGTP
    if EP[3]!= CdayGTP : # if we change day (it is != and not > to make it work even if we change of month)
        CdayGTP = I[3]
        countDayGTP += 1
    T = 3600*list[4] + 60*list[5] + list[6] + 86400*countDayGTP # Time is in seconds (easier to compare)
    L = [list[0],list[1],list[2],T]
    GTP.append(L)

def storeEP(list):
    global EP
    global CdayEP
    global countDayEP
    if EP[3]!= CdayEP :
        CdayEP = I[3]
        countDayEP += 1
    T = 3600*list[4] + 60*list[5] + list[6] + 86400*countDayEP
    L = [list[0],list[1],list[2],T]
    EP.append(L)


def storeIter(list):
    global I
    global CdayI
    global countDayI
    if I[1]!= CdayI :
        CdayI = I[1]
        countDayI += 1
    T = 3600*list[2] + 60*list[3] + list[4] + 86400*countDayI
    L = [list[0],T]
    I.append(L)
    if Store == True :
        storeData(GTP,EP,I)

# procedures that reads what is published on the topics
def fstoreIter(data):
    d = datetime.day
    h = datetime.hour
    m = datetime.minute
    s = datetime.second + 0.000001*datetime.microsecond
    i = data.iteration
    storeIter([i,d,h,m,s])

def fstoreGTP(data):
    d = datetime.day
    h = datetime.hour
    m = datetime.minute
    s = datetime.second + 0.000001*datetime.microsecond

    Px = data.pose.position.x
    Py = data.pose.position.y
    Pz = data.pose.position.z

    storeGTP( [Px,Py,Pz,d,h,m,s])

def fstoreEP(data):
    d = datetime.day
    h = datetime.hour
    m = datetime.minute
    s = datetime.second + 0.000001*datetime.microsecond

    Px = data.pose.position.x
    Py = data.pose.position.y
    Pz = data.pose.position.z

    storeEP([Px,Py,Pz,d,h,m,s])

# procedure that processes and write the data into the file
def storeData (GTP,EP,I):
    Ilen = len(I)-1
    GTPlen = len(GTP)-1
    EPlen = len(EP)-1
    if (Ilen>0) and (GTPlen)>0 and (EPlen)>0:
        Gindex = GTPlen
        Eindex = EPlen
        Iindex = Ilen

        if (round(GTP[Gindex][0],4)==round(EP[Eindex][0],4)) and (round(GTP[Gindex][0],4)==round(I[Iindex][0],4)):
            None #we need the if to have the else (and it is easier to write it that way than making all configurations of the else in an if)

        else :
            m=min( round(GTP[Gindex][0],4),round(EP[Eindex][0],4),round(I[Iindex][0],4) ) #we found here the data written at the same time step
            while (round(GTP[Gindex][0],4)>m) and (Gindex >= 0):
                Gindex -= 1
            while (round(EP[Eindex][0],4)>m) and (Eindex>=0) :
                Eindex -= 1
            while (round(I[Iindex][0],4)>m) and (Iindex>=0) :
                Iindex -= 1

        xg,yg,zg = GTP[Gindex][1],GTP[Gindex][2],GTP[Gindex][3]
        xe,ye,ze = EP[Eindex][1],EP[Eindex][2],EPEindex][3]
        NbrIter = I[Iindex][1]

        # The data are written in the file 
        file.write("Ground Truth Pos = "+str(xg)+" , "+str(yg)+" , "+str(zg)+" , ")
        file.write("Perceived Pos = "+str(xe)+" , "+str(ye)+" , "+str(ze)+" , ")
        file.write("Nbr of iter = "+str(NbrIter)+" , ")

        if (round(xg,1)==round(xe,1) ) and (round(yg,1)==round(ye,1) ) and (round(zg,1)==round(ze,1) ):
            file.write("Converge? = Yes \n")
        else :
            file.write("Converge? = No \n")

#global variable declaration
GTP =[]
EP = []
I = []
CdayI, CdayEP, CdayGTP = datetime.day, datetime.day, datetime.day
countDayI , countDayGTP, countDayEP = 0,0,0

# we write the parameters of the experiment
if Store == True :
    MaxVel = rospy.get_param("adeye/motion_planning/op_common_params/maxVelocity")
    file.write("Set speed = "+str(MaxVel)+" \n ")

# subscribes to the topics
if __name__ == '__main__':
    rospy.init_node('ExperimentB',anonymous = True)

    rospy.Subscriber("/std_stat", Float32, fstoreIter)
    rospy.Subscriber("/ndt_pose", PoseStamped, fstoreEP)
    rospy.Subscriber("/gnss_pose", PoseStamped, fstoreIter)
    rospy.spin()
