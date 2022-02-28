#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/TwistStamped.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <vector>
#include <visualization_msgs/Marker.h>

class PedestrainMotionPredictor
{
 private: 
        //Node, publisher and subscribers 
         ros::NodeHandle &n_;
         ros::Subscriber sub1;
         ros::Publisher marker_pub;
        // x, y postions and velocties and time variables  
        double position_x {0};
        double position_y {0};
        double velocity_x{0};
        double velocity_y{0};
        std::vector<double> positions{0,0,0};
        uint32_t shape = visualization_msgs::Marker::SPHERE;

void trackedObj_Callback(const autoware_msgs::DetectedObjectArray::ConstPtr& msg)
{
               
             for (int i = 0; i < msg->objects.size(); i++) {
             if (msg->objects.at(i).label=="pedestrian" && msg-> objects.at(i).pose.position.x != 0) {
                   position_x = msg-> objects.at(i).pose.position.x;
                   position_y = msg-> objects.at(i).pose.position.y;
                   velocity_x = msg-> objects.at(i).velocity.linear.x;
                   velocity_y = msg-> objects.at(i).velocity.linear.y; 
                   calculation(position_x, position_y, velocity_x, velocity_y);
               
             
            }
        }
 
}


public:
       //Constructor of the class 
       PedestrainMotionPredictor(ros::NodeHandle &n): n_(n) {
      sub1 = n_.subscribe("/fusion/objects", 1, &PedestrainMotionPredictor::trackedObj_Callback, this);
      marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
   }

     void calculation(double x, double y, double vx , double vy){
             double secs =ros::Time::now().toSec();
             double time = secs;
             for (int j = 0; j <= 5; j++){
             position_x += (time-secs)*vx ; 
             position_y += (time-secs)*vy ;
             positions[0] = time;
             positions[1] = position_x;
             positions[2] = position_y;
             marking(positions[1], positions[2]);
             ++time;
             std::cout << "@time: " << positions[0] << " " << "x_position: " << positions[1] << " " << "y_position: " << positions[2] << std::endl; 
             }
           std::cout << "-------------------" << std::endl;
    } 

  void marking(double x , double y){
     visualization_msgs::Marker marker;
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
    marker.pose.position.x = positions[1];
    marker.pose.position.y = positions[2];
    
    

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
    marker_pub.publish(marker);
}


void run()
    {
      ros::Rate rate(20);
      while(n_.ok())
      {
          ros::spinOnce();
       }
          rate.sleep();
    }
   


};


int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "PedestrainMotionPredictor");

  
  ros::NodeHandle n;
  PedestrainMotionPredictor Ped(n);
  Ped.run();  
  
  return 0;
}
