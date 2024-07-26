#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float64
import time

def time_publisher():
    # Add this line if the time is published only one time
    rospy.set_param('/use_sim_time', False)
    
    rospy.init_node('time_publisher_node', anonymous=True)
    pub = rospy.Publisher('time_topic', Float64, queue_size=10) # Creation of the time topic
    rate = rospy.Rate(400)
    
    while not rospy.is_shutdown():
        current_time_sec = time.time() # Give the current time in seconds (precision = 1 ms)
        #rospy.loginfo("Publication de l'heure en secondes: %f", current_time_sec)
        pub.publish(current_time_sec)
        rate.sleep()

if __name__ == '__main__':
    try:
        time_publisher()
    except rospy.ROSInterruptException: # This is to avoid error when CTRL+C is pressed
        pass
