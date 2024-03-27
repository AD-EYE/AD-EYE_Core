#!/usr/bin/env python

import rospy
from geometry_msgs.msg import PoseStamped
import csv

def parse_pose_line(line):
    # Parse a line of the pose file and extract the values
    values = line.strip().split(',')
    
    # Skip lines that don't have the correct number of values
    if len(values) != 10:
        return None 

    pose_msg = PoseStamped()
    pose_msg.header.frame_id = "world"
    #pose_msg.header.seq = int(values[0])
    pose_msg.pose.position.x = 342.187774658
    pose_msg.pose.position.y = -521.295288086
    pose_msg.pose.position.z = 0
    pose_msg.pose.orientation.x = 0
    pose_msg.pose.orientation.y = 0
    pose_msg.pose.orientation.z = -0.703769872127
    pose_msg.pose.orientation.w = 0.710428016822
    return pose_msg

if __name__ == '__main__':
    rospy.init_node('sample_goal_publisher', anonymous=True)
    rate = rospy.Rate(10.0)
    pub = rospy.Publisher('/adeye/goals', PoseStamped, queue_size=1)

    file_path = '/home/adeye/AD-EYE_Core/AD-EYE/Experiments/KTH_Demo/Vector_Map_Files/VECTORMAP_FILE/point.csv' 

    with open(file_path, 'r') as file:
        csv_reader = csv.reader(file)
        # Skip header since we don't have any headers (based on supposition, we can think that the different components are like defined previously)
        next(csv_reader) 
        for line in csv_reader:
            pose_msg = parse_pose_line(','.join(line))
            if pose_msg:
                while pub.get_num_connections() == 0 and not rospy.is_shutdown():
                    rate.sleep()
                pub.publish(pose_msg)
                rate.sleep()

    rospy.spin()
