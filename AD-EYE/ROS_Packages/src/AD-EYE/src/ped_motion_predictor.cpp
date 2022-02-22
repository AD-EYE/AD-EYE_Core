#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/TwistStamped.h>
#include <autoware_msgs/DetectedObjectArray.h>
//adding the markers
#include <visualization_msgs/Marker.h>

///// marker belonging
uint32_t shape = visualization_msgs::Marker::CUBE;
visualization_msgs::Marker marker;
/////////////////////
void pose_Callback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
  //std::cout<<"x_position: " << msg-> pose.position.x << std::endl;
  //std::cout<<"y_position: " << msg-> pose.position.y << std::endl;
  //std::cout<<"z_position: " << msg-> pose.position.z << std::endl;
  //std::cout<< std::endl;
  //std::cout<< "x_orientation: "<< msg->pose.orientation.x << std::endl;
  //std::cout<< "y_orientation: "<< msg->pose.orientation.y << std::endl;
  //std::cout<< "z_orientation: "<< msg->pose.orientation.z << std::endl;
  //std::cout<< "w_orientation: "<< msg->pose.orientation.w << std::endl;
  //std::cout<< std::endl;

 }

void velocity_Callback(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
  //std::cout << "x_linear_velocity: " << msg->twist.linear.x << std::endl;
  //std::cout << "y_linear_velocity: " << msg->twist.linear.y << std::endl;
  //std::cout << "z_linear_velocity: " << msg->twist.linear.z << std::endl;
  //std::cout<< std::endl;
  //std::cout << "x_angular_velocity: " << msg->twist.angular.x << std::endl;
  //std::cout << "y_angular_velocity: " << msg->twist.angular.y << std::endl;
  //std::cout << "z_angular_velocity: " << msg->twist.angular.z << std::endl;
  //std::cout << std::endl;
  
} 

void trackedObj_Callback(const autoware_msgs::DetectedObjectArray::ConstPtr& msg)
{
      
       double x_new {0};
       double y_new {0};
       double secs =ros::Time::now().toSec();
        
             for (int i = 0; i < msg->objects.size(); i++) {
            //if (msg->objects.at(i).label!="unknown" && msg->objects.at(i).label!="") {
              if (msg->objects.at(i).label=="pedestrian" && msg-> objects.at(i).pose.position.x != 0) {
       double x = msg-> objects.at(i).pose.position.x;
       double y = msg-> objects.at(i).pose.position.y;
       double vx = msg-> objects.at(i).velocity.linear.x;
       double vy = msg-> objects.at(i).velocity.linear.y; 
      // double t = msg-> objects.at(i).header.stamp.toSec();
                std::cout<< "Measured informatoin" << std::endl;
                std::cout<< msg->objects.at(i).label<< std::endl ;
                std::cout<< msg->objects.at(i).id << std::endl ;
                std::cout<<"x_position: " << x << std::endl;
                std::cout<<"y_position: " << y << std::endl;
                std::cout<<"x_velocity: " << vx << std::endl;
                std::cout<<"y_velocity: " << vy << std::endl;
                std::cout<<"time: " << secs << std::endl;
                std::cout<<"-----"<<std::endl;
                std::cout<<"-----"<<std::endl;
             double time = secs;
             for (int j = 0; j <= 5; j++){
             x_new = x + (time-secs)*vx ; 
             y_new = y + (time-secs)*vy ;
             std::cout << "Prediction step:" << j << " at time: " << time ;
             std::cout << "\nx_pred_pos:" << "  " << x_new ;
             std::cout << "\ny_pred_pos:" << "  " << y_new ;
             ++time;
             std::cout<<"\n-----"<<std::endl;
               //markers belongings 
              
               //visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/my_frame";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = x_new;
    marker.pose.position.y = y_new;
    

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();
                //markers belongings 
                 }
            }
        }
 
}

void predictedObj_Callback(const autoware_msgs::DetectedObjectArray::ConstPtr& msg)
{
  //std::cout<< "To be continued 2 ;)" << std::endl;
  //std::cout<< std::endl;
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

 // markers belongings
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
 // uint32_t shape = visualization_msgs::Marker::CUBE;
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
  //ros::Subscriber tracked_obj = n.subscribe("/tracked_objects", 1, trackedObj_Callback);
  ros::Subscriber tracked_obj = n.subscribe("/fusion/objects", 1, trackedObj_Callback);
  ros::Subscriber predicted_obj = n.subscribe("/predicted_objects", 1, predictedObj_Callback);
  
   
 ///////////////////////////////////////////////////////////// markers belongings 
 
 while (ros::ok())
  {
    

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    } 
    marker_pub.publish(marker);


    r.sleep();
   
  }

 /////////////////////////////////////////////////////////// markers belongings   
   /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spinOnce();

  return 0;
}
