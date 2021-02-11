#ifndef POINT_CLOUD_TO_OCCUPANCY_GRID_H
#define POINT_CLOUD_TO_OCCUPANCY_GRID_H

#include "ros/ros.h"
#include <sensor_msgs/PointCloud2.h>
#include <nav_msgs/OccupancyGrid.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>



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
        std::string points_topic_;
        std::string cost_map_topic_;
        double scan_z_min_ = 0.1;

        /*!
        * \brief Updates the occupancy grid
        * \details This method sends a ROS message that once received by Simulink should stop the simulation
        */
        void updateCostMap(const pcl::PointCloud<pcl::PointXYZ> &scan);

        /*!
        * \brief Configures the occupancy grid fields
        */
        void setOccupancyGrid(nav_msgs::OccupancyGrid *occupancy_grid);

        /*!
        * \brief Callback for the point cloud topic
        * \details The messages with an empty frame_id are ignored
        */
        void pointsCallback(const sensor_msgs::PointCloud2::ConstPtr &input_scan);


    public:
        /*!
        * \brief Constructor
        * \param nh A NodeHandle to retrieve ROS parameters, subscribe and publish
        * \param delayed_start If false, the node listens immediately to the poibt cloud topic. If true the method start() needs to be called.
        */
        PointsToOccupancyGrid(ros::NodeHandle nh, bool delayed_start = false);

        /*!
        * \brief Defines the subscriber
        * \param nh A NodeHandle to retrieve ROS parameters, subscribe and publish
        * \details To be used in conjunction with the delayed start to decide when the node needs to become active
        */
        void startSubsciber(ros::NodeHandle nh);

        /*!
        * \brief Pubishes the occupancy grid
        */
        void publishOccupancyGrid();

        /*!
        * \brief Loop waiting for callbacks
        */
        void run();
        
};


#endif