// ROS
#include <ros/ros.h>
// used for the gridmap
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <grid_map_ros/GridMapRosConverter.hpp>

// basic libraries used in the node
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <limits>

// used for the occupancy grid
#include <nav_msgs/OccupancyGrid.h>

using namespace grid_map;

/*!
 * \brief This class is used to extract data from the GridMap
 * \details This node produces one OccupancyGrid with one layer from the GridMap.
 */
class OccMapCreator
{
  private:
    // publishers and subscribers
    ros::NodeHandle& nh_;
    ros::Publisher pub_occ_grid_;
    ros::Subscriber sub_grid_map_;

    nav_msgs::OccupancyGrid occ_grid_;
    GridMap grid_map_;
    float frequency_ = 20;  // this value should be aligned with the frequency value used in the GridMapCreator_node
    ros::Rate rate_;
    std::string visualized_layer_;  // class member that will contain the name of the layer we want to visualize

    /*!
     * \brief GridMap Callback : Called when the grid map information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the GridMap information given by the GridMapCreator, then
     * call the visualizationProcess.
     */
    void gridMapCallback(const grid_map_msgs::GridMap::ConstPtr& msg)
    {
        GridMap full_grid_map;
        // convert received message back to gridmap
        GridMapRosConverter::fromMessage(*msg, full_grid_map);
        // update the gridmap
        grid_map_ = full_grid_map;

        // some informations needed to create the Occupancy Grid
        occ_grid_.header.frame_id = grid_map_.getFrameId();
        occ_grid_.header.stamp.fromNSec(grid_map_.getTimestamp());
        occ_grid_.info.map_load_time = occ_grid_.header.stamp;
        occ_grid_.info.resolution = grid_map_.getResolution();
        occ_grid_.info.width = grid_map_.getSize().x();
        occ_grid_.info.height = grid_map_.getSize().y();

        // The occ_grid_ origin is on its corner
        Position origin = grid_map_.getPosition() - grid_map_.getLength().matrix() / 2;
        occ_grid_.info.origin.position.x = origin.x();
        occ_grid_.info.origin.position.y = origin.y();
        std::size_t nCells = occ_grid_.info.width * occ_grid_.info.height;
        occ_grid_.data.resize(nCells);

        visualizationProcess();
    }

    /*!
     * \brief The information of one layer from the GridMap are translated into an occupancy grid
     * \details Info from one layer is reduced to the value corresponding to the layer selected
     * as these values are the only ones that the safety planner can read.
     */
    void visualizationProcess()
    {
        size_t nCells = occ_grid_.data.size();
        size_t index;
        float occValue;
        Position pos;

        for (GridMapIterator it(grid_map_); !it.isPastEnd(); ++it)
        {
            if (!grid_map_.getPosition(*it, pos))
            {
                ROS_ERROR("Visualizing : Error when retrieving position of a grid_map_ cell");
                continue;
            }

            // Getting values
            occValue = grid_map_.atPosition(visualized_layer_, pos);

            index = it.getLinearIndex();
            occ_grid_.data[nCells - index - 1] = occValue;
        }
    }

  public:
    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \param topic_name The topic on which to find informations on GridMap.
     * \param layer_name The layer we want to visualize.
     * \details Initializes the node and its components such as publishers and subscribers.
     */
    OccMapCreator(ros::NodeHandle& nh, std::string topic_name, std::string layer_name)
      : nh_(nh), rate_(1), visualized_layer_(layer_name)
    {
        // Initialize node and publishers/subscribers
        pub_occ_grid_ = nh_.advertise<nav_msgs::OccupancyGrid>("/occmap_one_layer", 1);
        sub_grid_map_ = nh_.subscribe<grid_map_msgs::GridMap>(topic_name, 1, &OccMapCreator::gridMapCallback, this);

        rate_ = ros::Rate(frequency_);

        // Constants values
        occ_grid_.info.origin.position.z = 0;
        occ_grid_.info.origin.orientation.x = 0.0;
        occ_grid_.info.origin.orientation.y = 0.0;
        occ_grid_.info.origin.orientation.z = 0.0;
        occ_grid_.info.origin.orientation.w = 1.0;
    }

    /*!
     * \brief The main function of the Node. Contains the main loop
     * \details Basically extract information from gridMap and then
     * publish data extracted from it.
     * Also, checks if the required frequency is met.
     */
    void run()
    {
        float rostime;

        while (nh_.ok())
        {
            rostime = ros::Time::now().toSec();

            ros::spinOnce();
            pub_occ_grid_.publish(occ_grid_);

            // Time control
            rostime = ros::Time::now().toSec() - rostime;
            if (rostime > 1 / frequency_)
            {
                ROS_WARN("Layer Visualizer Node : Frequency is not met!");
            }

            rate_.sleep();
        }
    }
};

/*!
* \brief Print a help message on how to use the node.
* \details Specify arguments needed
*/
void usage(std::string binName)
{
    ROS_FATAL_STREAM("\n"
                     << "Usage : " << binName << " <topic_name> <layer_name>");
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    std::string topic_name;
    std::string layer_name;

    topic_name = argv[1];
    layer_name = argv[2];

    // Initialize node
    ros::init(argc, argv, "visualization");
    ros::NodeHandle nh;
    OccMapCreator omc(nh, topic_name, layer_name);

    omc.run();
    return 0;
}
