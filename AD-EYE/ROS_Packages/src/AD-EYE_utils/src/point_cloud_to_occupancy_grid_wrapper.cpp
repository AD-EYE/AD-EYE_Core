#include "ros/ros.h"
#include <adeye_utils/point_cloud_to_occupancy_grid.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "points2costmap");
    ros::NodeHandle private_nh("~");
    PointsToOccupancyGrid points_to_occupancy_grid(private_nh);
    points_to_occupancy_grid.run();
}
