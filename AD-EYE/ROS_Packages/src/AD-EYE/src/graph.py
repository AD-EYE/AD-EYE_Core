# import rospy
# import matplotlib.pyplot as plt
# from matplotlib.animation import FuncAnimation
# from geometry_msgs.msg import TwistStamped

# # Global variables to store velocities
# linear_velocities_topic1 = []
# linear_velocities_topic2 = []

# def callback_topic1(data):
#     global linear_velocities_topic1
#     linear_velocities_topic1.append(data.twist.linear.x)

# def callback_topic2(data):
#     global linear_velocities_topic2
#     linear_velocities_topic2.append(data.twist.linear.x)

# def plot_data():
#     rospy.init_node('plotter', anonymous=True)
    
#     rospy.Subscriber("/current_velocity", TwistStamped, callback_topic1)
#     rospy.Subscriber("/TwistS", TwistStamped, callback_topic2)
    
#     plt.ion()
#     fig, ax = plt.subplots()
#     ax.set_title('ROS Topics Linear Velocity Comparison')
#     ax.set_xlabel('Time')
#     ax.set_ylabel('Linear Velocity')

#     def update_plot(event):
#         ax.clear()
#         ax.plot(linear_velocities_topic1, label='Topic 1')
#         ax.plot(linear_velocities_topic2, label='Topic 2')
#         ax.legend()
#         plt.draw()

#     # Use ROS timer to call update_plot function periodically
#     rospy.Timer(rospy.Duration(0.1), update_plot)

#     # Keep matplotlib's main loop running
#     plt.show(block=True)

#     rospy.spin()

# if __name__ == '__main__':
#     plot_data()



#!/usr/bin/env python3

# import rospy
# import matplotlib.pyplot as plt
# from matplotlib.animation import FuncAnimation
# from geometry_msgs.msg import TwistStamped

# data = []

# def callback(msg):
#     global data
#     data.append(msg.twist.linear.x)
#     if len(data) > 100: 
#         data.pop(0)

# def plot_data(i):
#     plt.cla()
#     plt.plot(data, label='Data')
#     plt.legend(loc='upper left')
#     plt.tight_layout()

# def listener():
#     rospy.init_node('data_listener', anonymous=True)
#     rospy.Subscriber("/current_velocity", TwistStamped, callback)
#     #rospy.Subscriber("/TwistS", TwistStamped, callback)   
#     ani = FuncAnimation(plt.gcf(), plot_data, interval=1000)
#     plt.show()

# if __name__ == '__main__':
#     listener()





#!/usr/bin/env python3
import rospy
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from geometry_msgs.msg import TwistStamped

data1 = []
data2 = []

def callback1(msg):
    global data1
    data1.append(msg.twist.linear.x)
    if len(data1) > 100: 
        data1.pop(0)

def callback2(msg):
    global data2
    data2.append(msg.twist.linear.x)
    if len(data2) > 100: 
        data2.pop(0)

def plot_data(i):
    plt.cla()
    plt.plot(data1, label='Current speed') 
    plt.plot(data2, label='Desired speed')  
    plt.legend(loc='upper left')
    plt.tight_layout()

def listener():
    rospy.init_node('data_listener', anonymous=True)
    rospy.Subscriber("/current_velocity", TwistStamped, callback1)
    rospy.Subscriber("/TwistS", TwistStamped, callback2) 
    ani = FuncAnimation(plt.gcf(), plot_data, interval=1000)
    plt.show()

if __name__ == '__main__':
    listener()
