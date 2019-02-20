#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <grid_map_ros/GridMapRosConverter.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <limits>

#include <nav_msgs/OccupancyGrid.h>
using namespace grid_map;

#define GREEN 10
#define YELLOW 50
#define RED 99

class OccMapCreator
{
public:

  void gridMap_callback(const grid_map_msgs::GridMap::ConstPtr& msg)
  {
    float rostime = ros::Time::now().toSec();

    // convert received message back to gridmap
    grid_map_msgs::GridMap message = *msg;
    grid_map::GridMap gridMap;
    grid_map::GridMapRosConverter::fromMessage(message, gridMap);

    // initialize occupancy map with gridmap data
    occGrid.header.frame_id = gridMap.getFrameId();
    occGrid.header.stamp.fromNSec(gridMap.getTimestamp());
    occGrid.info.map_load_time = occGrid.header.stamp;
    occGrid.info.resolution = gridMap.getResolution();
    occGrid.info.width = gridMap.getSize()(0);
    occGrid.info.height = gridMap.getSize()(1);
    Position origin = gridMap.getPosition() - 0.5 * gridMap.getLength().matrix();;
    occGrid.info.origin.position.x = origin.x();
    occGrid.info.origin.position.y = origin.y();
    occGrid.info.origin.position.z = 0;
    occGrid.info.origin.orientation.x = 0.0;
    occGrid.info.origin.orientation.y = 0.0;
    occGrid.info.origin.orientation.z = 0.0;
    occGrid.info.origin.orientation.w = 1.0;
    size_t nCells = gridMap.getSize().prod();
    occGrid.data.resize(nCells);

    // the actual flattening process happens here, info from all different layers is reduced to either GREEN, YELLOW, or RED, as these values are the only ones that the safety planner can read
    for (GridMapIterator it(gridMap); !it.isPastEnd(); ++it){
      float occValue = 0;
      float staticobjectvalue = (gridMap.at("StaticObjects", *it));
      float lanevalue = (gridMap.at("DrivableAreas", *it));
      float dynamicobjectvalue = (gridMap.at("DynamicObjects", *it));
      // 0.20 is just a random value chosen, this value indicates at what height objects become dangerous, so right now this is set to 20 cm
      float dangerous_height = 0.20;
      if(staticobjectvalue > dangerous_height){
        occValue = RED;
      }
      if(lanevalue == 1){
        occValue = YELLOW;
      } 
      if(lanevalue == 0 && staticobjectvalue <= dangerous_height){
        occValue = GREEN;
      }   
      if(dynamicobjectvalue > dangerous_height){
        occValue = RED;
      }
      size_t index = getLinearIndexFromIndex(it.getUnwrappedIndex(), gridMap.getSize(), false);
      occGrid.data[nCells - index - 1] = occValue;
    }

    // to test lanes layer
    /*for (GridMapIterator it(gridMap); !it.isPastEnd(); ++it){
      float lanevalue = (gridMap.at("Lanes", *it));
      size_t index = getLinearIndexFromIndex(it.getUnwrappedIndex(), gridMap.getSize(), false);
      occGrid.data[nCells - index - 1] = lanevalue;
    }*/
    rostime = ros::Time::now().toSec() - rostime;
    if(rostime > 1/frequency){
      ROS_INFO("frequency is not met!");
    }   
  }

  OccMapCreator(ros::NodeHandle nh)
  {
    // Initialize node and publishers
    nh_ = nh;
    pubOccGrid = nh.advertise<nav_msgs::OccupancyGrid>("/SafetyPlannerOccmap",1);
    subGridMap = nh.subscribe<grid_map_msgs::GridMap>("/SafetyPlannerGridmap", 1, &OccMapCreator::gridMap_callback, this);    
    ros::Rate rate(frequency);
    while (nh.ok()) {
      ros::spinOnce();  
      pubOccGrid.publish(occGrid);
      rate.sleep();
    }
  }

private:
  // publishers and subscribers
  ros::NodeHandle nh_;
  ros::Publisher pubOccGrid;
  ros::Subscriber subGridMap;

  // global var
  nav_msgs::OccupancyGrid occGrid;
  float frequency = 30;                 // this value should be alligned with the frequency value used in the GridMapCreator_node
};

int main(int argc, char** argv)
{
  // Initialize node and publishers
  ros::init(argc, argv, "flattening");
  ros::NodeHandle nh;
  OccMapCreator omc(nh);
  return 0;
}
