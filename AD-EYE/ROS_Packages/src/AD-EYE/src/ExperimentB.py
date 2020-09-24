#!/usr/bin/env python
# license removed for brevity
import roslib
import os
import rospy
from std_msgs.msg import Float32
from datetime import datetime
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import TwistStamped
from autoware_msgs.msg import NDTStat

Store = True
FirstStore = True
if Store == True :

    if os.path.isdir('/home/adeye/Experiment_Results/ExperimentB/') == False : # checks if the folder exists and creates it if not
        os.mkdir('/home/adeye/Experiment_Results/ExperimentB/')
    NumberFound = False
    k=1
    while NumberFound == False :
        if os.path.isfile('/home/adeye/Experiment_Results/ExperimentB/ExperimentB'+str(k)+'.csv')==True: # creates a file for each experiment
            k+=1
        else :
            file = open('/home/adeye/Experiment_Results/ExperimentB/ExperimentB'+str(k)+'.csv','a')
            NumberFound=True

# procedures that edits the global variables
def storeGTP(list):
    global NewEP
    global NewGTP
    global GTP
    global EP
    global I
    global CdayGTP
    global countDayGTP
    if NewGTP == False : # when this function is called, then new data is written on /gnss_pose
        NewGTP = True
    if list[3]!= CdayGTP : # if we change day (it is != and not > to make it work even if we change of month)
        CdayGTP = I[3]
        countDayGTP += 1
    T = 3600*list[4] + 60*list[5] + list[6] + 86400*countDayGTP # Time is in seconds (easier to compare)
    L = [list[0],list[1],list[2],T]
    GTP.append(L)


    if (Store == True) and (start == True) and (NewGTP==True) and (NewEP == True) :
        storeData(GTP,EP,I)

def storeEP(list):
    global NewEP
    global NewGTP
    global EP
    global GTP
    global I
    global CdayEP
    global countDayEP
    if NewEP == False : # when this function is called, then new data is written on /ndt_pose
        NewEP = True
    if list[3]!= CdayEP :
        CdayEP = I[3]
        countDayEP += 1
    T = 3600*list[4] + 60*list[5] + list[6] + 86400*countDayEP
    L = [list[0],list[1],list[2],T]
    EP.append(L)

    if (Store == True) and (start == True) and (NewGTP==True) and (NewEP == True) :
        storeData(GTP,EP,I)


def storeIter(list):
    global I
    global CdayI
    global countDayI
    if list[1]!= CdayI :
        CdayI = I[1]
        countDayI += 1
    T = 3600*list[2] + 60*list[3] + list[4] + 86400*countDayI
    L = [list[0],T,list[5],list[6]]
    I.append(L)


def storespeed(Sp): # the recording may start when the car is moving
    global start
    if Store == True:
        if start == False :
            if Sp > 0.0 :
                start = True
        else :
            if Sp == 0.0 :
                start = False
# procedures that reads what is published on the topics
def speedf (data):
    Sp = data.twist.linear.x
    storespeed(Sp)

def fstoreIter(data):
    d = datetime.now().day
    h = datetime.now().hour
    m = datetime.now().minute
    s = datetime.now().second + 0.000001*datetime.now().microsecond
    i = data.iteration
    score = data.score
    exe_time = data.exe_time
    storeIter([i,d,h,m,s,score,exe_time])

def fstoreGTP(data):
    d = datetime.now().day
    h = datetime.now().hour
    m = datetime.now().minute
    s = datetime.now().second + 0.000001*datetime.now().microsecond

    Px = data.pose.position.x
    Py = data.pose.position.y
    Pz = data.pose.position.z

    storeGTP([Px,Py,Pz,d,h,m,s])

def fstoreEP(data):
    d = datetime.now().day
    h = datetime.now().hour
    m = datetime.now().minute
    s = datetime.now().second + 0.000001*datetime.now().microsecond

    Px = data.pose.position.x
    Py = data.pose.position.y
    Pz = data.pose.position.z

    storeEP([Px,Py,Pz,d,h,m,s])

# procedure that processes and write the data into the file
def storeData (GTP,EP,I):
    global FirstStore
    global NewEP
    global NewGTP
    NewEP = False # when this function is called, we "reset" the variables that indicates if new data is written or not
    NewGTP = False

    # we write the parameters of the experiment
    if Store == True and FirstStore :
        FirstStore = False
        MaxVel = rospy.get_param("adeye/motion_planning/op_common_params/maxVelocity")
        file.write("Set speed = "+str(MaxVel)+" , ")
        Rain = rospy.get_param("/simulink/rain_intensity")
        file.write("Set rain intensity = "+str(Rain)+" , ")
        Reflectivity = rospy.get_param("/simulink/reflectivity")
        file.write("Set reflectivity = "+str(Reflectivity)+" \n ")

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

        xg,yg,zg = GTP[Gindex][0],GTP[Gindex][1],GTP[Gindex][2]
        xe,ye,ze = EP[Eindex][0],EP[Eindex][1],EP[Eindex][2]
        NbrIter = I[Iindex][0]

        # The data are written in the file
        file.write("Ground Truth Pos (x;y;z), "+str(xg)+" , "+str(yg)+" , "+str(zg)+" , ")
        file.write("Perceived Pos (x;y;z), "+str(xe)+" , "+str(ye)+" , "+str(ze)+" , ")
        file.write("Localization, nb of iterrations , "+str(NbrIter)+" , ")
        file.write("Localization score , "+str(I[Iindex][2])+" , ")
        file.write("Localization execution time , "+str(I[Iindex][3]))

        # if (round(xg,1)==round(xe,1) ) and (round(yg,1)==round(ye,1) ) and (round(zg,1)==round(ze,1) ):
        #     file.write("Converge? = Yes \n")
        # else :
        #     file.write("Converge? = No \n")

#global variable declaration
GTP =[]
EP = []
I = []
CdayI, CdayEP, CdayGTP = datetime.now().day, datetime.now().day, datetime.now().day
countDayI , countDayGTP, countDayEP = 0,0,0
start = False
NewGTP = False #this aims to run storeData() only when new data are published on both nodes /gnss_pose and /ndt_pose
NewEP = False



# subscribes to the topics
if __name__ == '__main__':
    rospy.init_node('ExperimentB',anonymous = True)

    rospy.Subscriber("/ndt_stat", NDTStat, fstoreIter)
    rospy.Subscriber("/ndt_pose", PoseStamped, fstoreEP)
    rospy.Subscriber("/gnss_pose", PoseStamped, fstoreGTP)

    rospy.Subscriber("/current_velocity", TwistStamped, speedf)

    rospy.spin()
