#!/usr/bin/env python

import rospy
from geometry_msgs.msg import TwistStamped
from rosgraph_msgs.msg import Clock


class ExperimentARecorder:

    counter = 0
    


    def __init__(self):
        rospy.Subscriber("/current_velocity", TwistStamped, self.egoSpeedCallback)
        # rospy.Subscriber("/clock", Clock, self.clockCallback)
        self.twist_pub = rospy.Publisher("/TwistS",TwistStamped, queue_size = 1)
        # self.twist_pub = rospy.Publisher("/autowareTwist",TwistStamped, queue_size = 1)

        
    # def clockCallback(self, data):
    #     msg_to_send = TwistStamped()
    #     msg_to_send.twist.linear.x = rospy.get_rostime().to_sec()#self.current_ego_speed + 0.1
    #     msg_to_send.header.stamp = rospy.get_rostime()
    #     self.twist_pub.publish(msg_to_send)

    # def egoSpeedCallback(self, data):
    #     self.counter += 1
    #     self.current_ego_speed = data.twist.linear.x
    #     msg_to_send = TwistStamped()
    #     msg_to_send.twist.linear.x = self.counter
    #     msg_to_send.header.stamp = rospy.get_rostime()
    #     self.twist_pub.publish(msg_to_send)
    def egoSpeedCallback(self, data):
        self.current_ego_speed = data.twist.linear.x + 0.1
        msg_to_send = TwistStamped()
        msg_to_send.twist.linear.x = self.current_ego_speed
        msg_to_send.header.stamp = rospy.get_rostime()
        self.twist_pub.publish(msg_to_send)
      


#listens to the topics
if __name__ == '__main__':
    rospy.init_node('ExperimentA_recorder')
    exp_A_recorder = ExperimentARecorder()
    rospy.spin()
