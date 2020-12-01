#!/usr/bin/env python
# license removed for brevity
import roslib
import os
import rospy
from std_msgs.msg import Bool
from std_msgs.msg import Float32
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import TwistStamped
from autoware_msgs.msg import NDTStat
import tf


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


class ExperimentBRecorder:

    start = False
    firstStore = True

    groud_truth_poses  = []
    esimated_poses  = []
    localization_stats = []
    new_ground_truth = False #this aims to run storeData() only when new data are published on both nodes /gnss_pose and /ndt_pose
    new_estimate = False


    def __init__(self):
        rospy.Subscriber("/ndt_stat", NDTStat, self.localizationStatCallback)
        rospy.Subscriber("/ndt_pose", PoseStamped, self.estimatedPoseCallback)
        rospy.Subscriber("/gnss_pose", PoseStamped, self.groundTruthPoseCallback)
        rospy.Subscriber("/current_velocity", TwistStamped, self.egoSpeedCallback)
        self.stop_pub = rospy.Publisher("/simulink/stop_experiment",Bool, queue_size = 1) # stop_publisher


    def groundTruthPoseCallback(self, data):
        Px = data.pose.position.x
        Py = data.pose.position.y
        Pz = data.pose.position.z
        T = self.getTime()
        L = [Px,Py,Pz,T,data.pose.orientation.x, data.pose.orientation.y, data.pose.orientation.z, data.pose.orientation.w]
        self.groud_truth_poses.append(L)
        self.new_ground_truth = True
        if (self.start == True) and (self.new_ground_truth==True) and (self.new_estimate == True) :
            self.storeData(self.groud_truth_poses,self.esimated_poses,self.localization_stats)


    def estimatedPoseCallback(self, data):
        Px = data.pose.position.x
        Py = data.pose.position.y
        Pz = data.pose.position.z
        T = self.getTime()
        L = [Px,Py,Pz,T,data.pose.orientation.x, data.pose.orientation.y, data.pose.orientation.z, data.pose.orientation.w]
        self.esimated_poses.append(L)
        self.new_estimate = True
        if (self.start == True) and (self.new_ground_truth==True) and (self.new_estimate == True) :
            self.storeData(self.groud_truth_poses,self.esimated_poses,self.localization_stats)


    def localizationStatCallback(self, data):
        itterations = data.iteration
        score = data.score
        exe_time = data.exe_time
        T = self.getTime()
        L = [itterations,T,score,exe_time]
        self.localization_stats.append(L)


    def egoSpeedCallback (self, data):
        print("got speed")
        Sp = data.twist.linear.x
        if self.start == False :
            print("not started")
            if Sp > 0.0 :
                self.start = True
        else :
            print("started")
            if Sp == 0.0 :
                print("stopping")
                self.start = False
                self.stop_pub.publish(True) # stop_publisher


    def getTime(self):
        now = rospy.get_rostime()
        return now.secs + now.nsecs * 10**9


    def writeParameter(self):
        if self.firstStore :
            self.firstStore = False
            max_velocity = rospy.get_param("adeye/motion_planning/op_common_params/maxVelocity")
            file.write("Set speed ,"+str(max_velocity)+" , ")
            rain_intensity = rospy.get_param("/simulink/rain_intensity")
            file.write("Set rain intensity ,"+str(rain_intensity)+" , ")
            reflectivity = rospy.get_param("/simulink/reflectivity")
            file.write("Set reflectivity ,"+str(reflectivity)+" \n")


    def storeData (self, groud_truth_poses,esimated_poses,I):
        self.new_estimate = False # when this function is called, we "reset" the variables that indicates if new data is written or not
        self.new_ground_truth = False

        self.writeParameter()

        stat_len = len(self.localization_stats)-1
        ground_truth_len = len(self.groud_truth_poses)-1
        estimates_len = len(self.esimated_poses)-1
        if (stat_len>0) and (ground_truth_len)>0 and (estimates_len)>0:
            ground_truth_index = ground_truth_len
            estimate_index = estimates_len
            stat_index = stat_len

            if (round(self.groud_truth_poses[ground_truth_index][0],4)==round(self.esimated_poses[estimate_index][0],4)) and (round(self.groud_truth_poses[ground_truth_index][0],4)==round(self.localization_stats[stat_index][0],4)):
                None #we need the if to have the else (and it is easier to write it that way than making all configurations of the else in an if)

            else :
                m=min( round(self.groud_truth_poses[ground_truth_index][0],4),round(self.esimated_poses[estimate_index][0],4),round(self.localization_stats[stat_index][0],4) ) #we found here the data written at the same time step
                while (round(self.groud_truth_poses[ground_truth_index][0],4)>m) and (ground_truth_index >= 0):
                    ground_truth_index -= 1
                while (round(self.esimated_poses[estimate_index][0],4)>m) and (estimate_index>=0) :
                    estimate_index -= 1
                while (round(self.localization_stats[stat_index][0],4)>m) and (stat_index>=0) :
                    stat_index -= 1

            xg,yg,zg = self.groud_truth_poses[ground_truth_index][0],self.groud_truth_poses[ground_truth_index][1],self.groud_truth_poses[ground_truth_index][2]
            xe,ye,ze = self.esimated_poses[estimate_index][0],self.esimated_poses[estimate_index][1],self.esimated_poses[estimate_index][2]
            nb_iter = self.localization_stats[stat_index][0]


            file.write("Ground Truth Pos (x;y;z), "+str(xg)+" , "+str(yg)+" , "+str(zg)+" , ")
            file.write("Perceived Pos (x;y;z), "+str(xe)+" , "+str(ye)+" , "+str(ze)+" , ")
            file.write("Localization, nb of iterrations , "+str(nb_iter)+" , ")
            file.write("Localization score , "+str(self.localization_stats[stat_index][2])+" , ")
            file.write("Localization execution time , "+str(self.localization_stats[stat_index][3]))

            file.write("\n")





# subscribes to the topics
if __name__ == '__main__':
    rospy.init_node('ExperimentB',anonymous = True)
    ExperimentBRecorder()
    rospy.spin()
