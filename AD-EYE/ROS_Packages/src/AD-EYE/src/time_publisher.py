#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float64
import time

def time_publisher():
    # Add this line if the time is published only one time
    rospy.set_param('/use_sim_time', False)
    
    # ROS node initialization
    rospy.init_node('time_publisher_node', anonymous=True)
    # Creation of the publisher
    pub = rospy.Publisher('time_topic', Float64, queue_size=10)
    # Define the rate 
    rate = rospy.Rate(400)  # Publier une fois par seconde
    
    while not rospy.is_shutdown():
        # Give the current time in seconds (precision = 1 ms)
        current_time_sec = time.time()
        # Print the current time in seconds
        rospy.loginfo("Publication de l'heure en secondes: %f", current_time_sec)
        # Publish the current time in seconds
        pub.publish(current_time_sec)
        # Wait for the next iteration
        rate.sleep()

if __name__ == '__main__':
    try:
        time_publisher()
    except rospy.ROSInterruptException: # This is to avoid error when CTRL+C is pressed
        pass
