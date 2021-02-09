#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <nav_msgs/OccupancyGrid.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>



class PointsToOccupancyGrid {
    private:
        ros::Subscriber points_sub_;
        ros::Publisher costmap_pub_;
        double map_resolution_;
        int map_width_;
        int map_height_;
        double map_offset_x_;
        double map_offset_y_;
        double map_offset_z_;
        nav_msgs::OccupancyGrid occupancy_grid_;


        void updateCostMap(const pcl::PointCloud<pcl::PointXYZ> &scan)
        {
            double map_center_x = (map_width_ / 2.0) * map_resolution_ - map_offset_x_;
            double map_center_y = (map_height_ / 2.0) * map_resolution_ - map_offset_y_;
            for (const auto &p : scan.points)
            {
                // Compute grid index
                int grid_x = (p.x + map_center_x) / map_resolution_;
                int grid_y = (p.y + map_center_y) / map_resolution_;
                if (!(grid_x < 0 || grid_x >= map_width_ || grid_y < 0 || grid_y >= map_height_)) { // if index is in the grid
                    int index = map_width_ * grid_y + grid_x;
                    occupancy_grid_.data[index] += 1;
                    if (occupancy_grid_.data[index] > 100) // saturate at 100
                        occupancy_grid_.data[index] = 100;
                }
            }
        }

        void setOccupancyGrid(nav_msgs::OccupancyGrid *occupancy_grid)
        {
            occupancy_grid->info.width = map_width_;
            occupancy_grid->info.height = map_height_;
            occupancy_grid->info.resolution = map_resolution_;
            occupancy_grid->info.origin.position.x = - map_width_ * map_resolution_ / 2.0  + map_offset_x_;
            occupancy_grid->info.origin.position.y = - map_height_ * map_resolution_ / 2.0  + map_offset_y_;
            occupancy_grid->info.origin.position.z = map_offset_z_;
            occupancy_grid->info.origin.orientation.x = 0.0;
            occupancy_grid->info.origin.orientation.y = 0.0;
            occupancy_grid->info.origin.orientation.z = 0.0;
            occupancy_grid->info.origin.orientation.w = 1.0;
            std::vector<int8_t> cost_map(map_width_ * map_height_, 0);
            occupancy_grid->data.insert(occupancy_grid_.data.end(), cost_map.begin(), cost_map.end());
        }

        void pointsCallback(const sensor_msgs::PointCloud2::ConstPtr &input_scan)
        {
            pcl::PointCloud<pcl::PointXYZ> scan;
            pcl::fromROSMsg(*input_scan, scan);
            if(input_scan->header.frame_id != "")
            {
                occupancy_grid_.header = input_scan->header;        
                updateCostMap(scan);
                costmap_pub_.publish(occupancy_grid_);
            }
        }


    public:

        PointsToOccupancyGrid(ros::NodeHandle nh)
        {
            nh.param<double>("map_resolution_", map_resolution_, 1.0);
            nh.param<int>("map_width_", map_width_, 1000);
            nh.param<int>("map_height_", map_height_, 1000);
            nh.param<double>("map_offset_x_", map_offset_x_, 130.0);
            nh.param<double>("map_offset_y_", map_offset_y_, 150.0);
            nh.param<double>("map_offset_z_", map_offset_z_, -2.0);

            std::string points_topic;
            std::string cost_map_topic;
            nh.param<std::string>("points_topic", points_topic, "/points_world_frame");
            // nh.param<std::string>("points_topic", points_topic, "/points_accumulated");
            nh.param<std::string>("cost_map_topic", cost_map_topic, "/cost_map");

            costmap_pub_ = nh.advertise<nav_msgs::OccupancyGrid>(cost_map_topic, 10);
            points_sub_ = nh.subscribe(points_topic, 10, &PointsToOccupancyGrid::pointsCallback, this);
            setOccupancyGrid(&occupancy_grid_);
            
        }

        void run()
        {
            ros::spin();
        }
        
};





int main(int argc, char **argv)
{
    ros::init(argc, argv, "points2costmap");
    ros::NodeHandle private_nh("~");
    PointsToOccupancyGrid points_to_occupancy_grid(private_nh);
    points_to_occupancy_grid.run();
}
