#!/usr/bin/env python

import tf
import math
import rospy
from autoware_config_msgs.msg import ConfigNDTMapping
from autoware_config_msgs.msg import ConfigApproximateNDTMapping
import subprocess
from sensor_msgs.msg import Imu, PointCloud2
import argparse
from datetime import datetime
import os
import roslaunch
import time


root_dir = os.path.dirname(os.path.abspath(__file__))


def create_parser(): 
    """Create a parser object"""
    parser = argparse.ArgumentParser(description='Description goes here')
    parser.add_argument('-r', '--rosbag', type=bool, default=True, help="Run with rosbag <True|False>")
    parser.add_argument("--rosbag-folder", type=str, default="/home/adeye/Downloads/KTH_map/Rosbags/Splitted_bags/", help="Path to rosbag files")
    parser.add_argument("--output-dir", type=str, default="/home/adeye/Downloads/KTH_map/Rosbags/Generated_pcd", help="Path to PCD output dir")
    parser.add_argument("-rviz","--rviz", type=bool, default=False, help="Runs rviz")
    my_args = parser.parse_args()
    return my_args

def generate_PCD_path(args): 
    """Geneate a timestamp for the PCD"""
    output_filename = os.path.basename(os.path.abspath(args.rosbag_folder)).split(".bag")[0] + ".pcd"
    output_path = os.path.join(args.output_dir, output_filename)
    output_path = "'{0}'".format(output_path)
    return output_path
    
def force_kill_ros():
    subprocess.Popen(["rosnode", "kill", "-a"])
    time.sleep(10)
    subprocess.Popen(["killall", "-9", "rosmaster"])


class ProcessManager(): 

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
        print("Transforming imu")
        rospy.init_node('imu_transformer')
        msg = rospy.wait_for_message("/imu/data", Imu) #This will create a new subscription to the topic, receive one message, then unsubscribe.
        q0 = msg.orientation.x
        q1 = msg.orientation.y
        q2 = msg.orientation.z 
        q3 = msg.orientation.w
        roll = -math.atan2(2*q1*q2+2*q0*q3, 2*q0**2+2*q1**2-1)
        pitch = math.asin(2*q1*q3-2*q0*q2)
        yaw = -math.atan2(2*q2*q3+2*q0*q1, 2*q0**2+2*q3**2-1)
        print("Calc roll: ", roll)
        print("Calc pitch: ", pitch)
        print("Calc yaw: ", yaw)
        #set parameter to server
        rospy.set_param('tf_x', 0)
        rospy.set_param('tf_y', 0)
        rospy.set_param('tf_z', 0)
        rospy.set_param('tf_roll', roll)
        rospy.set_param('tf_pitch', pitch)
        rospy.set_param('tf_yaw', yaw)
        cmd = ['roslaunch', 'runtime_manager', 'setup_tf.launch', 'x:=0.0', 'y:=0.0', 'z:=0.0', str(yaw), str(pitch), str(roll), 'frame_id:=/base_link', 'child_frame_id:=/velodyne', 'period_in_ms:=10']
        subprocess.Popen(cmd, stdout=self.FNULL, stderr=self.FNULL) #TODO: Output stderr


    def play_rosbag(self):
        """Play rosbag"""
        print("Playing rosbag")
        cmd = ["rosrun", "topic_tools", "relay", "/velodyne_points", "/points_raw"]
        subprocess.Popen (cmd)
        rosbag_path = self.args.rosbag_folder
        rospy.set_param('use_sim_time', 'true')
        cmd = ["rosbag", "play", str(rosbag_path)]
        subprocess.Popen(cmd, stdout=self.FNULL, stderr=self.FNULL)

    def start_ndt_mapping(self):
        print("Starting ndt-mapping")

        settings = "{header: {seq: 0, stamp: {secs: 0, nsecs: 0}, frame_id: ''}, resolution: 0.5, step_size: 0.1, trans_epsilon: 0.01, max_iterations: 50, leaf_size: 0.1, min_scan_range: 0.2, max_scan_range: 20.0, min_add_scan_shift: 2.0}"

        # settings = "{header: {seq: 0, stamp: {secs: 0, nsecs: 0}, frame_id: ''}, resolution: 1.0, step_size: 0.1, trans_epsilon: 0.01, max_iterations: 50, leaf_size: 2.0, min_scan_range: 1.5, max_scan_range: 75.0, min_add_scan_shift: 2.0}"

        cmd = ["rostopic", "pub", "/config/ndt_mapping", "autoware_config_msgs/ConfigNDTMapping", settings]
        subprocess.Popen(cmd)

        rospy.set_param("/ndt_mapping/imu_topic", "/imu/data")
        rospy.set_param("/ndt_mapping/imu_upside_down", True)
        rospy.set_param("/ndt_mapping/incremental_voxel_update", True)
        rospy.set_param("/ndt_mapping/method_type", False)
        rospy.set_param("/ndt_mapping/use_imu", True)
        rospy.set_param("/ndt_mapping/use_odom", False)

        quer = roslaunch.core.Node('lidar_localizer', 'queue_counter')
        self.launch.launch(quer)
        ndt = roslaunch.core.Node('lidar_localizer', 'ndt_mapping')
        self.launch.launch(ndt)

    def start_approximate_ndt_mapping(self):
        print("Starting approximate-ndt-mapping")

        settings = "{header: {seq: 0, stamp: {secs: 0, nsecs: 0}, frame_id: ''}, resolution: 0.5, step_size: 0.1, trans_epsilon: 0.01, max_iterations: 50, leaf_size: 0.1, min_scan_range: 0.2, max_scan_range: 20.0, min_add_scan_shift: 2.0}"
        # settings = "{header: {seq: 0, stamp: {secs: 0, nsecs: 0}, frame_id: ''}, resolution: 1.0, step_size: 0.1, trans_epsilon: 0.01, max_iterations: 50, leaf_size: 2.0, min_scan_range: 1.5, max_scan_range: 75.0, min_add_scan_shift: 2.0}"

        cmd = ["rostopic", "pub", "/config/approximate_ndt_mapping", "autoware_config_msgs/ConfigApproximateNDTMapping", settings]
        subprocess.Popen(cmd)

        rospy.set_param("/approximate_ndt_mapping/imu_topic", "/imu/data")
        rospy.set_param("/approximate_ndt_mapping/imu_upside_down", True)
        rospy.set_param("/approximate_ndt_mapping/incremental_voxel_update", True)
        rospy.set_param("/approximate_ndt_mapping/method_type", False)
        rospy.set_param("/approximate_ndt_mapping/use_imu", True)
        rospy.set_param("/approximate_ndt_mapping/use_odom", False)

        
        quer = roslaunch.core.Node('lidar_localizer', 'queue_counter')
        self.launch.launch(quer)
        ndt = roslaunch.core.Node('lidar_localizer', 'approximate_ndt_mapping')
        self.launch.launch(ndt)


    def run_rviz(self): 
        """Set all nodes that should be launched"""
        subprocess.Popen(["rosrun", "rviz", "rviz", "-d" , "/home/adeye/AD-EYE_Core/Helper_Scripts/Mapping/mapping_config.rviz"])



    def start(self): 
        """Start the launch files"""

        output = "{{header: {{seq: 1, stamp: {{secs: 0, nsecs: 0}}, frame_id: ''}}, filename: {0}, filter_res: 0.0}}".format(self.output_filename)

        self.launch.start()
        
        self.play_rosbag()

        self.transform_imu()

        self.start_ndt_mapping()

        self.run_rviz()

        # the mapping process is finished when no new message is published on the topic /ndt_map
        try: 
            while True:
                self.launch.spin_once()
                rospy.wait_for_message("/ndt_map", PointCloud2, timeout=5)
                print("Waiting for the mapping to be finished")
        except:
            print("Saving the map as a pcd file")
            # subprocess.Popen(["rostopic", "pub", "-1" ,"/config/approximate_ndt_mapping_output", "autoware_config_msgs/ConfigApproximateNDTMappingOutput", output])
            subprocess.Popen(["rostopic", "pub", "-1" ,"/config/ndt_mapping_output", "autoware_config_msgs/ConfigNDTMappingOutput", output])
            time.sleep(10)
        finally: 
            self.launch.stop()




if __name__ == "__main__":

    force_kill_ros()
    args = create_parser()
    print(args)
    files=[]

    for (dirpath, dirnames, filenames) in os.walk(args.rosbag_folder):
        files.extend(filenames)
        print(files)
    rosbag_folder = args.rosbag_folder
    
    print('Killing all processes..')
    force_kill_ros()

    i = 1
    for f in files:
        
        args.rosbag_folder =  rosbag_folder +  f 
        print("Starting process rosbag -> pcd with file:  ", f)
        print("File number: ", i,"/", len(files))
        i += 1
        if not os.path.isfile(args.rosbag_folder): 
            raise OSError(2, 'No such file or directory', args.rosbag_folder)
        
        subprocess.Popen(['roscore'])
        process_manager = ProcessManager(args)
        process_manager.start()

        print('Killing all processes..')
        force_kill_ros()
