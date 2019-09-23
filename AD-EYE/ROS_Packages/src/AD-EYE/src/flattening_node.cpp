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

/*!
 * \brief This class is used to extract data from the GridMap given by the GridMapCreator
 * \details
 */
class OccMapCreator
{
private:
    // publishers and subscribers
    ros::NodeHandle& nh_;
    ros::Publisher pubOccGrid;
    ros::Subscriber subGridMap;

    nav_msgs::OccupancyGrid occGrid;
    GridMap gridMap;
    float frequency = 30;                 // this value should be alligned with the frequency value used in the GridMapCreator_node
    ros::Rate rate;

public:

    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initializes the node and its components such as publishers and subscribers.
     */
    OccMapCreator(ros::NodeHandle &nh) : nh_(nh), rate(1)
    {
        // Initialize node and publishers
        pubOccGrid = nh_.advertise<nav_msgs::OccupancyGrid>("/SafetyPlannerOccmap",1);
        subGridMap = nh_.subscribe<grid_map_msgs::GridMap>("/SafetyPlannerGridmap", 1, &OccMapCreator::gridMap_callback, this);

        rate = ros::Rate(frequency);
    }

    /*!
     * \brief GridMap Callback : Called when the grid map information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the GridMap information given by the GridMapCreator, then
     * call the flateningProcess.
     */
    void gridMap_callback(const grid_map_msgs::GridMap::ConstPtr& msg)
    {
        // convert received message back to gridmap
        GridMapRosConverter::fromMessage(*msg, gridMap);

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

        flateningProcess();
    }

    /*!
     * \brief The main function of the Node. Contains the main loop
     * \details Basically extract information from gridMap and then
     * publish data extracted from it.
     * Also, checks if the required frequency is met.
     */
    void run() {
        float rostime;

        while (nh_.ok()) {
            rostime = ros::Time::now().toSec();

            ros::spinOnce();
            pubOccGrid.publish(occGrid);

            //Time control
            rostime = ros::Time::now().toSec() - rostime;
            if(rostime > 1/frequency){
                ROS_WARN("Flatening Node : Frequency is not met!");
            }

            rate.sleep();
        }
    }

    /*!
     * \brief The information from the GridMap are translated into an occupancy grid
     * \details Info from all different layers is reduced to either
     * GREEN, YELLOW, or RED, as these values are the only ones that
     * the safety planner can read
     */
    void flateningProcess() {
        size_t nCells = occGrid.data.size();
        float occValue;
        float staticObjectValue;
        float dynamicObjectValue;
        float laneValue;
        size_t index;

        for (GridMapIterator it(gridMap) ; !it.isPastEnd() ; ++it){
            occValue = 0;
            staticObjectValue = (gridMap.at("StaticObjects", *it));
            laneValue = (gridMap.at("DrivableAreas", *it));
            dynamicObjectValue = (gridMap.at("DynamicObjects", *it));
            // 0.20 is just a random value chosen, this value indicates at what height objects become dangerous, so right now this is set to 20 cm
            float dangerous_height = 0.20;
            if(staticObjectValue > dangerous_height || dynamicObjectValue > dangerous_height){
                occValue = RED;
            }
            if(laneValue == 1){
                occValue = YELLOW;
            }
            else if(laneValue == 0 && staticObjectValue <= dangerous_height){
                occValue = GREEN;
            }
            index = getLinearIndexFromIndex(it.getUnwrappedIndex(), gridMap.getSize(), false);
            occGrid.data[nCells - index - 1] = occValue;
        }

        // to test lanes layer
        /*for (GridMapIterator it(gridMap); !it.isPastEnd(); ++it){
          float lanevalue = (gridMap.at("Lanes", *it));
          size_t index = getLinearIndexFromIndex(it.getUnwrappedIndex(), gridMap.getSize(), false);
          occGrid.data[nCells - index - 1] = lanevalue;
          }*/
    }
};

int main(int argc, char** argv)
{
    // Initialize node and publishers
    ros::init(argc, argv, "flattening");
    ros::NodeHandle nh;
    OccMapCreator omc(nh);
    omc.run();
    return 0;
}
