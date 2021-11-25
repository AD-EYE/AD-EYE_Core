#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/TwistStamped.h>
#include <autoware_msgs/DetectedObjectArray.h>


void pose_Callback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
  std::cout<<"x_position: " << msg-> pose.position.x << std::endl;
  std::cout<<"y_position: " << msg-> pose.position.y << std::endl;
  std::cout<<"z_position: " << msg-> pose.position.z << std::endl;
  std::cout<< std::endl;
  std::cout<< "x_orientation: "<< msg->pose.orientation.x << std::endl;
  std::cout<< "y_orientation: "<< msg->pose.orientation.y << std::endl;
  std::cout<< "z_orientation: "<< msg->pose.orientation.z << std::endl;
  std::cout<< "w_orientation: "<< msg->pose.orientation.w << std::endl;
  std::cout<< std::endl;

 }

void velocity_Callback(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
  std::cout << "x_linear_velocity: " << msg->twist.linear.x << std::endl;
  std::cout << "y_linear_velocity: " << msg->twist.linear.y << std::endl;
  std::cout << "z_linear_velocity: " << msg->twist.linear.z << std::endl;
  std::cout<< std::endl;
  std::cout << "x_angular_velocity: " << msg->twist.angular.x << std::endl;
  std::cout << "y_angular_velocity: " << msg->twist.angular.y << std::endl;
  std::cout << "z_angular_velocity: " << msg->twist.angular.z << std::endl;
  std::cout << std::endl;
  
} 

void trackedObj_Callback(const autoware_msgs::DetectedObjectArray::ConstPtr& msg)
{
  std::cout<< "To be continued :)" << std::endl;
  std::cout<< std::endl;
}

void predictedOb_Callback(const autoware_msgs::DetectedObjectArray::ConstPtr& msg)
{
}


int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "ped_motion_predictor");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  ros::Subscriber pos = n.subscribe("/current_pose", 10, pose_Callback);
  ros::Subscriber vel = n.subscribe("/current_velocity", 10, velocity_Callback);
  ros::Subscriber tracked_obj = n.subscribe("/tracked_objects", 1, trackedObj_Callback);
  ros::subscriber predicted_obj = n.subscribe("/predicted_objects", 1, predictedOb_Callback);
 

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  return 0;
}
