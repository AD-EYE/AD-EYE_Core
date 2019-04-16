#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Int32.h>

//using namespace grid_map;


class safetySupervisor
{
public:

  safetySupervisor(ros::NodeHandle nh)
  {
    // Initialize the node, publishers and subscribers
    nh_ = nh;

    pubSwitch = nh_.advertise<std_msgs::Int32>("/switchCommand", 1, true);

    subGnss = nh_.subscribe<geometry_msgs::PoseStamped>("/gnss_pose", 100, &safetySupervisor::gnss_callback, this);
    subGridmap = nh_.subscribe<grid_map_msgs::GridMap>("/SafetyPlannerGridmap", 1, &safetySupervisor::gridmap_callback, this);

    // Initialize the variables
    state = SAFE;

    // Initialize the flags
    gnss_flag = 0;
    gridmap_flag = 0;
    //rate(float 20);
  }

  void evaluate()
  {
    state = SAFE;
    float current_lane_id = gridmap.atPosition("Lanes", grid_map::Position(pose.position.x, pose.position.y));
    ROS_INFO("%f", current_lane_id);
    if (current_lane_id == 0)
    {
      state = UNSAFE;
    }
  }

  void publish()
  {
    msg.data = state;
    pubSwitch.publish(msg);
  }

  void gnss_callback(const geometry_msgs::PoseStamped::ConstPtr& msg)
  {
    geometry_msgs::PoseStamped gnss = *msg;
    pose = gnss.pose;
    gnss_flag = 1;
  }

  void gridmap_callback(const grid_map_msgs::GridMap::ConstPtr& msg)
  {
    grid_map::GridMapRosConverter::fromMessage(*msg, gridmap);
    //gridmap = *msg;
    gridmap_flag = 1;
  }

  void loop()
  {
    ros::Rate rate(20);
    while(nh_.ok())
    {
      ros::spinOnce();
      if(gnss_flag == 1 && gridmap_flag == 1)
      {
        evaluate();
        publish();
      }
      rate.sleep();
      ROS_INFO("Current state: %d", state);
    }
  }

private:
  // constants
  bool SAFE = 0;
  bool UNSAFE = 1;

  // node, publishers and subscribers
  ros::NodeHandle nh_;
  ros::Publisher pubSwitch;
  ros::Subscriber subGnss;
  ros::Subscriber subGridmap;

  // variables
  geometry_msgs::Pose pose;
  bool state;
  bool gnss_flag;
  bool gridmap_flag;
  std_msgs::Int32 msg;
  //grid_map_msgs::GridMap gridmap;
  grid_map::GridMap gridmap; //({"StaticObjects", "DrivableAreas", "DynamicObjects", "Lanes"});
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "safetySupervisor");
  ros::NodeHandle nh;
  safetySupervisor sS(nh);
  sS.loop();
  return 0;
}
