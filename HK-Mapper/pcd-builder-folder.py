#!/usr/bin/env python
"""
    Filename: pcd-builder-folder.py
    Authors: J Roing, A De Val, F Larsson, H Lind, A Phan, V Hanefors, M Svjatoha, J Jungaker, C Jensen
    Date last modified: 3 Dec 2020
    Version: 1.0
    License: GPLv3
    Copyright: (C)Copyright 2020 Mechatronics HK AD-EYE Team
    Python version: Python 2.7.12

    Description: Starts ndt mapping of pre-recorded rosbags in a directory and create a PCD.
    
    Usage: python pcd-builder.py --rosbag-file <"Path to rosbag file"> <--output-dir> <"Path to PCD output dir"> <-rviz> <True>

    NOTE: Imu topic might change from /imu_raw to /imu/data when changing or updating IMU.

    See the full specifications with
    python pcd-builder.py --help 
"""

# ========================================================================
# Imports
# ========================================================================
import tf
import math
import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Quaternion
from autoware_config_msgs.msg import ConfigNDTMapping
import subprocess
from sensor_msgs.msg import Imu, PointCloud2
import argparse
from datetime import datetime
import os
import roslaunch
import time

# ========================================================================
# Global Variables
# ======================================================================== 
root_dir = os.path.dirname(os.path.abspath(__file__))

# ========================================================================
# Helper Functions
# ========================================================================
def create_parser(): 
    """Create a parser object"""

    parser = argparse.ArgumentParser(description='Description goes here')
    parser.add_argument('-r', '--rosbag', type=bool, default=True, help="Run with rosbag <True|False>")
    parser.add_argument("--rosbag-dir", type=str, help="Path to rosbag directory")
    parser.add_argument("--output-dir", type=str, help="Path to PCD output dir")
    parser.add_argument("-rviz","--rviz", type=bool, default=False, help="Runs rviz")
    parser.add_argument("-t", "--terminal", type=bool, default=False, help="Choose to see processed/input in terminal")
    my_args = parser.parse_args()

    return my_args

def generate_PCD_path(args): 
    """Geneate a timestamp for the PCD"""

    output_filename = os.path.basename(os.path.abspath(args.rosbag_dir)).split(".bag")[0] + ".pcd"
    output_path = os.path.join(args.output_dir, output_filename)
    output_path = "'{0}'".format(output_path)
    return output_path
    

def force_kill():
    """Killing any active rosmaster before start"""  
    cmd = ["killall", "-9", "rosmaster"]
    subprocess.Popen(cmd)


# ========================================================================
# Classes
# ======================================================================== 
class Roslaunch(): 

    def __init__(self, args): 
        """Initializer"""

        self.uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
        roslaunch.configure_logging(self.uuid)
        self.launch = roslaunch.scriptapi.ROSLaunch()
        self.launch_files = []
        self.args = args
        self.FNULL = open(os.devnull, 'w')
        self.output_filename =  generate_PCD_path(args)


    def transform_imu(self):
        rospy.init_node('test')
        msg = rospy.wait_for_message("/imu/data", Imu)                 #Creating a new subscription to the topic, receiving one message, then unsubscribing.

        q0 = msg.orientation.x                                         #Extracting x,y,z,w
        q1 = msg.orientation.y
        q2 = msg.orientation.z 
        q3 = msg.orientation.w

        roll = -math.atan2(2*q1*q2+2*q0*q3, 2*q0**2+2*q1**2-1)         #Calculating roll
        pitch = math.asin(2*q1*q3-2*q0*q2)                             #Calculating pitch
        yaw = -math.atan2(2*q2*q3+2*q0*q1, 2*q0**2+2*q3**2-1)          #Calculating yaw
         
        print("Calc roll: ", roll)
        print("Calc pitch: ", pitch)
        print("Calc yaw: ", yaw)

        rospy.set_param('tf_x', 0)                                     #Setting the parameters to the server
        rospy.set_param('tf_y', 0)
        rospy.set_param('tf_z', 0)
        rospy.set_param('tf_roll', roll)
        rospy.set_param('tf_pitch', pitch)
        rospy.set_param('tf_yaw', yaw)

        cmd = ['roslaunch', 'runtime_manager', 'setup_tf.launch', 'x:=0.0', 'y:=0.0', 'z:=0.0', str(yaw), str(pitch), str(roll), 'frame_id:=/base_link', 'child_frame_id:=/velodyne', 'period_in_ms:=10']
        subprocess.Popen(cmd, stdout=self.FNULL, stderr=self.FNULL) 


    def play_rosbag(self):
        """Play rosbag"""

        cmd = ["rosrun", "topic_tools", "relay", "/velodyne_points", "/points_raw"]
        subprocess.Popen (cmd)

        rosbag_path = self.args.rosbag_dir

        rospy.set_param('use_sim_time', 'true')

        cmd = ["rosbag", "play", str(rosbag_path)]
        
        subprocess.Popen(cmd, stdout=self.FNULL, stderr=self.FNULL)

    def start_ndt(self):


        settings = "{header: {seq: 0, stamp: {secs: 0, nsecs: 0}, frame_id: ''}, resolution: 1.0, step_size: 0.1, trans_epsilon: 0.01, max_iterations: 50, leaf_size: 2.0, min_scan_range: 1.5, max_scan_range: 75.0, min_add_scan_shift: 2.0}"

        cmd = ["rostopic", "pub", "/config/ndt_mapping", "autoware_config_msgs/ConfigNDTMapping", settings]
        subprocess.Popen(cmd)

        rospy.set_param("/ndt_mapping/imu_topic", "/imu/data")
        rospy.set_param("/ndt_mapping/imu_upside_down", True)
        rospy.set_param("/ndt_mapping/incremental_voxel_update", True)
        rospy.set_param("/ndt_mapping/method_type", False)
        rospy.set_param("/ndt_mapping/use_imu", True)
        rospy.set_param("/ndt_mapping/use_odom", False)
        
        if self.args.terminal:

            cmd = ['roslaunch', 'lidar_localizer', 'ndt_mapping.launch', 'method_type:=0', 'incremental_voxel_update:=True', 'use_odom:=False', 'use_imu:=True', 'imu_upside_down:=True', 'imu_topic:=/imu_raw']
            subprocess.Popen(cmd)
        else:
            quer = roslaunch.core.Node('lidar_localizer', 'queue_counter')
            self.launch.launch(quer)
            ndt = roslaunch.core.Node('lidar_localizer', 'ndt_mapping')
            self.launch.launch(ndt)

    def run_rviz(self): 
        """Set rviz node to be launched"""

        node = roslaunch.core.Node("rviz", "rviz")
        self.launch.launch(node)


    def start(self): 
        """Start the launch files"""

        output = "{{header: {{seq: 1, stamp: {{secs: 0, nsecs: 0}}, frame_id: ''}}, filename: {0}, filter_res: 0.0}}".format(self.output_filename)

        self.launch.start()
        
        print("Playing rosbag")
        self.play_rosbag()

        print("Transforming imu")
        self.transform_imu()

        print("Starting ndt-mapping")
        self.start_ndt()

        print(" ndt-mapping")
        #sself.run_rviz()

        
        try: 
            while True:
                self.launch.spin_once()
                rospy.wait_for_message("/ndt_map", PointCloud2, timeout=300) #End process when no new message has been sent on topic for 300 sec.
        except: 
            print(output)
            subprocess.Popen(["rostopic", "pub", "-1" ,"/config/approximate_ndt_mapping_output", "autoware_config_msgs/ConfigNDTMappingOutput", output])
            
            time.sleep(10)

        finally: 
            self.launch.stop()

    
class Roscore(): 
    """roscore wrapped into a subprocess. 
    Singleton implementation prevents from creating more than one instance."""

    __initialized = False
    def __init__(self):
        if Roscore.__initialized:
            raise Exception("You can't create more than 1 instance of Roscore.")
        Roscore.__initialized = True
    def run(self):
        try:
            self.roscore_process = subprocess.Popen(['roscore'])
            #self.roscore_pid = self.roscore_process.pid  # pid of the roscore process (which has child processes)
        except OSError as e:
            sys.stderr.write('roscore could not be run')
            raise e
        
    def stop(self):
        subprocess.call(['killall', '-9', 'rosmaster'])

# ========================================================================
# Main function
# ========================================================================

if __name__ == "__main__":

    force_kill()                                            #Killing active rosmaster
    args = create_parser()                                  #Create parser with user input

    roscore = Roscore()
    files=[]

    for (dirpath, dirnames, filenames) in os.walk(args.rosbag_dir):
        files.extend(filenames)
        print(files)
    rosbag_folder = args.rosbag_dir
    
    i = 1
    for f in files:
        
        args.rosbag_dir =  rosbag_folder +  f 
        print("Starting process rosbag -> pcd with file:  ", f)
        print("File number: ", i,"/", len(files))
        i += 1
        if not os.path.isfile(args.rosbag_dir):                #Error handling if file does not exist 
            raise OSError(2, 'No such file or directory', args.rosbag_dir)
        
        force_kill()
  
        print('Killing all processes..')
        time.sleep(10)
        
        roscore.run()
        rospy.sleep(3)
        
        launcher = Roslaunch(args)

        launcher.start()                                        #Start the making of PCD
        
        roscore.stop()
        time.sleep(10)
