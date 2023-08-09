#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <grid_map_ros/GridMapRosConverter.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <limits>
#include <vector_map_msgs/PointArray.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <tf/transform_broadcaster.h>

#include <cpp_utils/pose_datatypes.h>

using namespace grid_map;

class VisualizationMap
{
  private:
    ros::NodeHandle& nh_;
    ros::Subscriber sub_map_;
    ros::Publisher pub_map_image_;

    ros::Rate rate_;

    GridMap grid_map_;
    sensor_msgs::Image image_;

    bool created_image_= false;

    void MapCallback(const grid_map_msgs::GridMap::ConstPtr& msg)
    {
        GridMapRosConverter::fromMessage(*msg, grid_map_);
        created_image_ = GridMapRosConverter::toImage(grid_map_, "Lanes", sensor_msgs::image_encodings::RGB8, image_);
   }

  public:
    VisualizationMap(ros::NodeHandle& nh) : nh_(nh), rate_(1)
    {
        sub_map_ = nh_.subscribe<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, &VisualizationMap::MapCallback, this);
    }
    
    void run() {
        cv_bridge::CvImagePtr cv_ptr;
        bool sent = false;
        ros::NodeHandle private_nh_("~");
        std::string image_path_;
        private_nh_.param<std::string>("path", image_path_, "/home/adeye/WorldImage.png");
        while (nh_.ok()) {
            ros::spinOnce();
            if (created_image_ && !sent) {
                cv_ptr = cv_bridge::toCvCopy(image_, sensor_msgs::image_encodings::BGR8);
                cv::imwrite(image_path_, cv_ptr->image);
                sent = true;
            }
            rate_.sleep();
        }
    }
};

int main(int argc, char** argv)
{
    // Initialize node
    ros::init(argc, argv, "fullmap");
    ros::NodeHandle nh;
    VisualizationMap VM(nh);
    VM.run();
    return 0;
}
