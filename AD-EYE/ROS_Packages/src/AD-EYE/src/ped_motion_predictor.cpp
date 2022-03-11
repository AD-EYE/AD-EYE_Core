#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/TwistStamped.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <vector>
#include <visualization_msgs/Marker.h>

// The node is predicting the position of a detected pedestrain within the next 5 steps.
// Also, it visualizes the positions with sphere markers.
// Details,the node reads the detected pedestrain from /fusion/objects topic, calculates the positons after 5 stpes, then publishs the markers on that positions
class PedestrainMotionPredictor
{
 private: 
        //Node, publisher and subscribers 
         ros::NodeHandle &n_;
         ros::Subscriber sub1;
         ros::Publisher marker_pub;
        // x, y postions and velocties, time and marking variables  
        double position_x {0};
        double position_y {0};
        double velocity_x{0};
        double velocity_y{0};
        std::vector<double> positions{0,0,0}; // {time,position_x,position_y}
        uint32_t shape = visualization_msgs::Marker::SPHERE;
        double count_id {0};
        //visualization_msgs::Marker marker;

//Callback function receives the published pedestrain info from /fusion/objects topic, then it calls 
// calculation function in order to calculate the next 5 steps positions.
void trackedObj_Callback(const autoware_msgs::DetectedObjectArray::ConstPtr& msg)
{
             
             for (int i = 0; i < msg->objects.size(); i++) {
             if (msg->objects.at(i).label!="unknown" && msg-> objects.at(i).pose.position.x != 0) {
                   position_x = msg-> objects.at(i).pose.position.x;
                   position_y = msg-> objects.at(i).pose.position.y;
                   velocity_x = msg-> objects.at(i).velocity.linear.x;
                   velocity_y = msg-> objects.at(i).velocity.linear.y; 
                   std::cout << "label : " << msg->objects.at(i).label << std::endl; 
                   removeMarkers();
                   count_id = 0; 
                   calculation(position_x, position_y, velocity_x, velocity_y); // call calculation function 
                  //marker.action = visualization_msgs::Marker::DELETEALL;
             
            }
        }
 
}


public:
       //Constructor of the class 
       PedestrainMotionPredictor(ros::NodeHandle &n): n_(n) {
      sub1 = n_.subscribe("/fusion/objects", 1, &PedestrainMotionPredictor::trackedObj_Callback, this);
      marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
   }
     // Calculation function accepts x & y positions and velocities as parameters from the callback function.
     // In each calculation step, it calls the marking function as well. 
     void calculation(double x, double y, double vx , double vy){
             double secs =ros::Time::now().toSec();
             double time  = secs;
             for (int j = 0; j <= 5; j++){
             x += (time-secs)*vx ; 
             y += (time-secs)*vy ;
             positions[0] = time;
             positions[1] = x;
             positions[2] = y;
             marking(positions[1], positions[2]);// call marking function for each the new calculated x & y positions
             ++time;
             std::cout << "@time: " << positions[0] << " " << "x_position: " << positions[1] << " " << "y_position: " << positions[2] << std::endl; 
             ++count_id;
             }
            std::cout << "-------------------" << std::endl;
            //marker.action = visualization_msgs::Marker::DELETEALL;
    } 

  // marking function, initiates the marker info, then publishes a marker based on the calculated x & y positions 
  // it publishes the markers on visualization_marker topic 
  void marking(double x , double y){
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/velodyne"; 
    marker.header.stamp = ros::Time::now();
    

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = count_id ;

    std::cout << "id : " << marker.id << std::endl; 

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
    marker_pub.publish(marker); // publishing the markers 
     
}

//remove markers function , is removing what marking function was pubishing 
 void removeMarkers(){
  visualization_msgs::Marker marker;
marker.header.frame_id = "/velodyne";
marker.header.stamp = ros::Time::now();
marker.action = visualization_msgs::Marker::DELETEALL;
marker_pub.publish(marker);
}

void run()
    {
      ros::Rate rate(5);
      while(n_.ok())
      {
          ros::spinOnce();
       }
          rate.sleep();
    }
   


};

// the main function 
int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "PedestrainMotionPredictor");

  
  ros::NodeHandle n;
  PedestrainMotionPredictor Ped(n); // define an object called Ped 
  Ped.run();  // call the run function 
  
  return 0;
}
