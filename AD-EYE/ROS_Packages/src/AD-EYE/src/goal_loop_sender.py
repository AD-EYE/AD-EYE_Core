#!/usr/bin/env python  
import roslib
import rospy
import tf
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped

class loop:
    def __inif__(self):
        rospy.Subscriber("/gnss_pose", PoseStamped)

    def goal1(self):
        pub = rospy.Publisher("/move_base_simple/goal", PoseStamped,, queue_size=1)





if __name__ == '__main__':
    rospy.init_node('sender', anonymous=True)
    if len(sys.argv) < 3:
        Sender(True)
    else:
        if sys.argv[1]=="false":
            Sender(False)
        else:
            Sender(True)
    rospy.spin()
