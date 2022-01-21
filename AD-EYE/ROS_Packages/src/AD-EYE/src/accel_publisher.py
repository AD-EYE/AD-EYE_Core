#!/usr/bin/env python

import rospy
from geometry_msgs.msg import TwistStamped
from rosgraph_msgs.msg import Clock
from std_msgs.msg import Float32
from autoware_msgs.msg import ControlCommandStamped


class ExperimentARecorder:
    ego_speed_received = False
    ego_cmd_received = False
    counter = 0
    


    def __init__(self):
        rospy.Subscriber("/current_velocity", TwistStamped, self.egoSpeedCallback)
        rospy.Subscriber("/TwistS", TwistStamped, self.egoCmdCallback)
        rospy.Subscriber("/clock", Clock, self.clockCallback)
        # rospy.Subscriber("/ctrl_cmd", ControlCommandStamped, self.ctrlCmdCallback)
        self.accel_pub = rospy.Publisher("/simulink_accel_cmd",Float32, queue_size = 1)

    def egoSpeedCallback(self, data):
        print("in egoSpeedCallback ")
        self.current_ego_speed = data.twist.linear.x
        self.ego_speed_received = True
        self.sendIfbothReceived()

    def egoCmdCallback(self, data):
        print("in egoCmdCallback ")
        self.current_cmd = data.twist.linear.x
        self.ego_cmd_received = True
        self.sendIfbothReceived()

    def ctrlCmdCallback(self, data):
        
        msg_to_send = Float32()
        msg_to_send = data.cmd.linear_acceleration
        self.accel_pub.publish(msg_to_send)

    def clockCallback(self, data):
        self.ego_speed_received = False
        self.ego_cmd_received = False


    def sendIfbothReceived(self):
        # print("in function")
        if(self.ego_cmd_received and self.ego_speed_received):
            print("in if")
            msg_to_send = Float32()
            msg_to_send = (self.current_cmd - self.current_ego_speed) * 20
            self.accel_pub.publish(msg_to_send)
            
      


#listens to the topics
if __name__ == '__main__':
    rospy.init_node('ExperimentA_recorder')
    exp_A_recorder = ExperimentARecorder()
    rospy.spin()
