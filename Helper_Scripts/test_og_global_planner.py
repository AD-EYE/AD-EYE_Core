import roslaunch
import rospy


##Main function that initizalize node and corresponding launch file.
def main():
    rospy.init_node('op_global_planner', anonymous=True) #Initializing ROS Node given nodename. 
    uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
    roslaunch.configure_logging(uuid)
    roslaunch_file = ["/home/adeye/AD-EYE_Core/AD-EYE/ROS_Packages/src/AD-EYE/launch/my_mission_planning.launch"]
    launch = roslaunch.parent.ROSLaunchParent(uuid, roslaunch_file)

    
    launch.start()

    try:
        launch.spin()
    finally:
        # After Ctrl+C, stop all nodes from running
        launch.shutdown()

if __name__ == "__main__":
    main()
