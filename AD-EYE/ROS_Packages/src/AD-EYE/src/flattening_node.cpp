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
#include <nav_msgs/Odometry.h>

#include <tf/transform_broadcaster.h>

#include <cpp_utils/pose_datatypes.h>

using namespace grid_map;

#define WHITE 1
#define GREEN 30
#define YELLOW 50
#define RED 99

const float SQRT_2 = sqrt(2);
#define PI 3.141592654

/*!
 * \brief This class is used to extract data from the GridMap given by the GridMapCreator
 * \details This node produce two OccupancyGrid : One, aligned with the global axis, which is used by
 * the Safe_Stop_Planner ; one smaller, aligned with the car which is used by the safety supervisor.
 */
class OccMapCreator
{
private:
    // publishers and subscribers
    ros::NodeHandle& nh_;
    ros::Publisher pubOccGrid;
    ros::Publisher pubOccGrid_aligned;
    ros::Subscriber subGridMap;
    ros::Subscriber subPosition_ego;

    //Car informations
    float x_ego = 0;
    float y_ego = 0;
    float yaw_ego = 0;

    // 0.20 is just a random value chosen, this value indicates at what height objects become dangerous, so right now this is set to 20 cm
    float dangerous_height = 0.20;
    nav_msgs::OccupancyGrid occGrid;
    nav_msgs::OccupancyGrid occGrid_aligned;
    float submap_width;  // We are using width and height, but don't worry,
    float submap_height; // it will NEVER work if the gridMap is not a SQUARRE
    GridMap gridMap;
    float frequency = 30; // this value should be alligned with the frequency value used in the GridMapCreator_node
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
        pubOccGrid = nh_.advertise<nav_msgs::OccupancyGrid>("/SafetyPlannerOccmap", 1);
        pubOccGrid_aligned = nh_.advertise<nav_msgs::OccupancyGrid>("/SafetyPlannerOccmap_aligned", 1);
        subGridMap = nh_.subscribe<grid_map_msgs::GridMap>("/SafetyPlannerGridmap", 1, &OccMapCreator::gridMap_callback, this);
        subPosition_ego = nh.subscribe<nav_msgs::Odometry>("/vehicle/odom", 100, &OccMapCreator::positionEgo_callback, this);

        rate = ros::Rate(frequency);

        //Constants values
        occGrid.info.origin.position.z = 0;
        occGrid.info.origin.orientation.x = 0.0;
        occGrid.info.origin.orientation.y = 0.0;
        occGrid.info.origin.orientation.z = 0.0;
        occGrid.info.origin.orientation.w = 1.0;

        occGrid_aligned.info.origin.position.z = 0;
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
        size_t nCells = gridMap.getSize().prod();
        occGrid.data.resize(nCells);

        // initialize occupancy map ALIGNED with gridmap data
        occGrid_aligned.header.frame_id = gridMap.getFrameId();
        occGrid_aligned.header.stamp.fromNSec(gridMap.getTimestamp());
        occGrid_aligned.info.map_load_time = occGrid_aligned.header.stamp;
        occGrid_aligned.info.resolution = gridMap.getResolution();
        occGrid_aligned.info.width = gridMap.getSize()(0) / SQRT_2;
        occGrid_aligned.info.height = gridMap.getSize()(1) / SQRT_2;
        submap_width = occGrid_aligned.info.width * occGrid_aligned.info.resolution;
        submap_height = occGrid_aligned.info.height * occGrid_aligned.info.resolution;
        origin = gridMap.getPosition(); //Center of the gridmap
        //The occupancyGrid origin is its top left corner and it rotates around it (and not around the center)
        origin[0] += sin(PI/4 - yaw_ego) * submap_width/SQRT_2; // So we have to move it at the right place
        origin[1] += cos(PI/4 - yaw_ego) * submap_width/SQRT_2;
        // (To understand every calculation, just take a paper, draw squares, lines and angles,
        //   make trigonometry calculation, scream, start again from the begining and you will get it)
        occGrid_aligned.info.origin.position.x = origin.x();
        occGrid_aligned.info.origin.position.y = origin.y();
        geometry_msgs::Quaternion q = cpp_utils::tf_quat_to_quat(cpp_utils::get_tf_quat(yaw_ego - PI)); // Don't know why, but '- pi' is needed
        occGrid_aligned.info.origin.orientation.x = q.x;
        occGrid_aligned.info.origin.orientation.y = q.y;
        occGrid_aligned.info.origin.orientation.z = q.z;
        occGrid_aligned.info.origin.orientation.w = q.w;
        nCells = occGrid_aligned.info.width * occGrid_aligned.info.height;
        occGrid_aligned.data.resize(nCells);

        flateningProcess();
    }

    /*!
     * \brief Ego Position Callback : Called when the ego position information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the position information as read from simulink of the controlled car
     */
    void positionEgo_callback(const nav_msgs::Odometry::ConstPtr& msg) {
        x_ego = msg->pose.pose.position.x;
        y_ego = msg->pose.pose.position.y;
        yaw_ego = cpp_utils::extract_yaw(msg->pose.pose.orientation);
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
            pubOccGrid_aligned.publish(occGrid_aligned);

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
        size_t index;
        float occValue;
        float staticObjectValue;
        float dynamicObjectValue;
        float laneValue;

        for (GridMapIterator it(gridMap) ; !it.isPastEnd() ; ++it) {
            staticObjectValue = (gridMap.at("StaticObjects", *it));
            dynamicObjectValue = (gridMap.at("DynamicObjects", *it));
            laneValue = (gridMap.at("DrivableAreas", *it));

            //Calculation the occupancy value
            occValue = calculateOccValue(staticObjectValue, dynamicObjectValue, laneValue);

            index = getLinearIndexFromIndex(it.getUnwrappedIndex(), gridMap.getSize(), false);
            occGrid.data[nCells - index - 1] = occValue;
        }


        // Flatening the ALIGNED occupancy map
        Position origin = {occGrid_aligned.info.origin.position.x, occGrid_aligned.info.origin.position.y};
        Position pos = origin; //Position of each cell during the loop
        double dx;
        double dy;
        for(index = 0 ; index < occGrid_aligned.data.size() ; index++) {
            // Distances between the actual cell and the origin (in the LOCAL coordinates)
            dx = (index % occGrid_aligned.info.width) * occGrid_aligned.info.resolution;
            dy = (index / occGrid_aligned.info.width) * occGrid_aligned.info.resolution;
            //Position of the cell (top left corner of the cell)
            pos.x() = origin.x() - dx * cos(yaw_ego) + dy * sin(yaw_ego);
            pos.y() = origin.y() - dx * sin(yaw_ego) - dy * cos(yaw_ego);
            //Finding the center of the cell
            pos.x() += 0.5 * occGrid_aligned.info.resolution * (-cos(yaw_ego) + sin(yaw_ego));
            pos.y() += 0.5 * occGrid_aligned.info.resolution * (-sin(yaw_ego) - cos(yaw_ego));

            //Getting values
            staticObjectValue = gridMap.atPosition("StaticObjects", pos);
            dynamicObjectValue = gridMap.atPosition("DynamicObjects", pos);
            laneValue = gridMap.atPosition("DrivableAreas", pos);

            //Calculation the occupancy value
            occValue = calculateOccValue(staticObjectValue, dynamicObjectValue, laneValue);

            occGrid_aligned.data[index] = occValue;
        }

        // to test lanes layer
        /*for (GridMapIterator it(gridMap); !it.isPastEnd(); ++it){
          float lanevalue = (gridMap.at("Lanes", *it));
          size_t index = getLinearIndexFromIndex(it.getUnwrappedIndex(), gridMap.getSize(), false);
          occGrid.data[nCells - index - 1] = lanevalue;
          }*/
    }

    /*!
     * \brief This function is used to calculate the occupancy value of a cell according to the layer of the grid map
     * \param staticObjectValue The value of the cell in the StaticObjects layer of the GridMap
     * \param dynamicObjectValue The value of the cell in the DynamicObjects layer of the GridMap
     * \param laneValue The value of the cell in the DrivableAreas layer of the GridMap
     * \return The occupancy value calculated
     */
    float calculateOccValue(float staticObjectValue, float dynamicObjectValue, float laneValue) {
        float occValue = 0;

        if(staticObjectValue > dangerous_height) {
            occValue = RED;
        }
        if(laneValue == 1) { // Lanes overwrite static objects
            occValue = YELLOW;
        }
        else if(laneValue == 0 && staticObjectValue <= dangerous_height) {
            occValue = GREEN;
        }
        if(staticObjectValue == -1) {
            occValue = WHITE;
        }
        if(dynamicObjectValue > dangerous_height) { // Dynamic objects overwrite lanes
            occValue = RED;
        }
        return occValue;
    }
};

int main(int argc, char** argv)
{
    // Initialize node
    ros::init(argc, argv, "flattening");
    ros::NodeHandle nh;
    OccMapCreator omc(nh);
    omc.run();
    return 0;
}
