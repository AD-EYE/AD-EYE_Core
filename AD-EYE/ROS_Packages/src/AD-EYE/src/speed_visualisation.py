#!/usr/bin/env python3

import rospy
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from geometry_msgs.msg import TwistStamped
import signal
import sys

data1 = []
time1 = []
data2 = []
time2 = []

def callback1(msg):
    global data1, time1
    data1.append(msg.twist.linear.x)
    time1.append(rospy.Time.now().to_sec())
    if len(data1) > 200: 
        data1.pop(0)
        time1.pop(0)

def callback2(msg):
    global data2, time2
    data2.append(msg.twist.linear.x)
    time2.append(rospy.Time.now().to_sec())
    if len(data2) > 400: 
        data2.pop(0)
        time2.pop(0)

def plot_data(i):
    plt.cla()
    if time1 and time2:
        plt.plot(time1, data1, label='Current speed') 
        plt.plot(time2, data2, label='Desired speed')
    plt.xlabel('Time (s)')
    plt.ylabel('Speed (m/s)')
    plt.legend(loc='upper left')
    plt.tight_layout()

def listener():
    rospy.init_node('data_listener', anonymous=True)
    rospy.Subscriber("/current_velocity", TwistStamped, callback1)
    rospy.Subscriber("/TwistS", TwistStamped, callback2)
    ani = FuncAnimation(plt.gcf(), plot_data, interval=50)
    signal.signal(signal.SIGINT, signal_handler)
    plt.show()


def signal_handler(sig, frame):
    plt.close('all')
    rospy.signal_shutdown("KeyboardInterrupt")
    print("\nPlot closed and program terminated.")
    sys.exit(0)


if __name__ == '__main__':
    listener()
