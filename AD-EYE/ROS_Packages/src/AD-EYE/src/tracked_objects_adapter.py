#!/usr/bin/env python
# license removed for brevity
import rospy
import math as m
from autoware_msgs.msg import DetectedObjectArray
from std_msgs.msg import UInt32
from geometry_msgs.msg import PoseStamped
from tf import transformations
import tf

pos_flag = False
current_pose = PoseStamped()
trans = list()
rot = list()


def mycallback1(data):
    global pos_flag
    global trans
    global rot

    if pos_flag == True:
        pub = rospy.Publisher('tracked_objects', DetectedObjectArray, queue_size=1)

        # tflistener = tf.TransformListener()

        # xf = current_pose.pose.position.x
        # yf = current_pose.pose.position.y
        # zf = current_pose.pose.position.z
        # angles = transformations.euler_from_quaternion([current_pose.pose.orientation.x, current_pose.pose.orientation.y, current_pose.pose.orientation.z, current_pose.pose.orientation.w])
        # theta = angles [2]
        xf = trans[0]
        yf = trans[1]
        zf = trans[2]
        angles = transformations.euler_from_quaternion([rot[0], rot[1], rot[2], rot[3]])
        theta = angles[2]
        # rospy.loginfo(len(data.objects))

        for i in range(len(data.objects)):
            # Fix the ID:
            data.objects[i].id = data.objects[i].id + 1
            # rospy.loginfo(data.objects[i].label)

            # Position:
            xp = data.objects[i].pose.position.x
            yp = data.objects[i].pose.position.y
            zp = data.objects[i].pose.position.z

            data.objects[i].pose.position.x = xf + xp * m.cos(theta) - yp * m.sin(theta)
            data.objects[i].pose.position.y = yf + xp * m.sin(theta) + yp * m.cos(theta)
            data.objects[i].pose.position.z = zf + zp

            # rospy.loginfo(data.objects[i].pose.position.x)
            # rospy.loginfo(data.objects[i].pose.position.y)
            # rospy.loginfo(data.objects[i].pose.position.z)

            # Orientation:
            anglesp = transformations.euler_from_quaternion(
                [data.objects[i].pose.orientation.x, data.objects[i].pose.orientation.y,
                 data.objects[i].pose.orientation.z, data.objects[i].pose.orientation.w])
            titap = anglesp[2]
            titat = theta + titap
            rotp = transformations.quaternion_from_euler(0.0, 0.0, titat)
            data.objects[i].pose.orientation.z = rotp[2]
            data.objects[i].pose.orientation.w = rotp[3]

            for j in range(len(data.objects[i].convex_hull.polygon.points)):
                xp = data.objects[i].convex_hull.polygon.points[j].x  # += current_pose.pose.position.x
                yp = data.objects[i].convex_hull.polygon.points[j].y
                zp = data.objects[i].convex_hull.polygon.points[j].z

                data.objects[i].convex_hull.polygon.points[j].x = xf + xp * m.cos(theta) - yp * m.sin(theta)
                data.objects[i].convex_hull.polygon.points[j].y = yf + xp * m.sin(theta) + yp * m.cos(theta)
                data.objects[i].convex_hull.polygon.points[j].z = zf + zp

        pub.publish(data)


# def mycallback2(data):
#    global pos_flag
#    global current_pose
#    pos_flag = True
#    current_pose = data


if __name__ == '__main__':
    # global trans
    # global rot
    # global pos_flag
    rospy.init_node('tracked_objects_adapter', anonymous=True)
    tflistener = tf.TransformListener()
    rospy.Subscriber("tracked_objects_pre", DetectedObjectArray, mycallback1)
    # rospy.Subscriber("current_pose", PoseStamped, mycallback2)
    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():
        try:
            (trans, rot) = tflistener.lookupTransform('/world', '/velodyne', rospy.Time(0))
            pos_flag = True
        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            continue
        rate.sleep()
    # rospy.spin()
