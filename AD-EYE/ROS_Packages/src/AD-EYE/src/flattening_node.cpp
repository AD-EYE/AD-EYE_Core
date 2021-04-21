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
    ros::Publisher puboccGrid;
    ros::Subscriber subGridMap;
    ros::Subscriber subPosition_ego;

    //Car informations
    float x_ego = 0;
    float y_ego = 0;
    float yaw_ego = 0;

    // 0.20 is just a random value chosen, this value indicates at what height objects become dangerous, so right now this is set to 20 cm
    const float dangerous_height = 0.20;
    nav_msgs::OccupancyGrid occGrid;
    const float occmap_width;
    const float occmap_height;
    float submap_dimensions;
    float submap_dimensions_x;
    float submap_dimensions_y;
    GridMap grid_map_;
    float frequency_ = 20; // this value should be aligned with the frequency value used in the GridMapCreator_node
    ros::Rate rate_;


    /*!
     * \brief GridMap Callback : Called when the grid map information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the GridMap information given by the GridMapCreator, then
     * call the flateningProcess.
     */
    void gridMapCallback(const grid_map_msgs::GridMap::ConstPtr& msg)
    {
        // convert received message back to gridmap
        GridMapRosConverter::fromMessage(*msg, grid_map_);

        occGrid.header.frame_id = grid_map_.getFrameId();
        occGrid.header.stamp.fromNSec(grid_map_.getTimestamp());
        occGrid.info.map_load_time = occGrid.header.stamp;
        occGrid.info.resolution = grid_map_.getResolution();
        occGrid.info.width = grid_map_.getSize().x();
        occGrid.info.height = grid_map_.getSize().y();
        submap_dimensions = grid_map_.getLength().x();    // Also, length of the diagonal of the area
        // The occGrid origin is on its corner
        Position origin = grid_map_.getPosition() - grid_map_.getLength().matrix() / 2;
        occGrid.info.origin.position.x = origin.x();
        occGrid.info.origin.position.y = origin.y();
        std::size_t nCells = occGrid.info.width * occGrid.info.height;
        occGrid.data.resize(nCells);

        flateningProcess();
    }

    /*!
     * \brief Ego Position Callback : Called when the ego position information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the position information as read from simulink of the controlled car
     */
    void positionEgoCallback(const nav_msgs::Odometry::ConstPtr& msg) {
        x_ego = msg->pose.pose.position.x;
        y_ego = msg->pose.pose.position.y;
        yaw_ego = cpp_utils::extract_yaw(msg->pose.pose.orientation);
    }


    /*!
     * \brief The information from the GridMap are translated into an occupancy grid
     * \details Info from all different layers is reduced to either
     * GREEN, YELLOW, or RED, as these values are the only ones that
     * the safety planner can read.
     * The safety planner do not consider the orientation of the grid, so the Occupancy Grid
     * has the same size than the Grid Map (which is aligned with global axis by design).
     * Then, every cells in the grid that are not in the considered area (aligned with the car),
     * will be hidden (filled with the RED value).
     */
    void flateningProcess() {
        size_t nCells = occGrid.data.size();
        size_t index;
        float occValue;
        float staticObjectValue;
        float dynamicObjectValue;
        float laneValue;
        float safeAreaValue;
        Position pos;

        grid_map::Polygon area;
        float alpha = yaw_ego + std::atan(occmap_width / occmap_height); // Angle between the horizontal and the diagonal of the area
        Position point1 = grid_map_.getPosition();
        point1.x() += cos(alpha) * submap_dimensions/2;
        point1.y() += sin(alpha) * submap_dimensions/2;
        Position point2 = {point1.x() + occmap_width * sin(yaw_ego), point1.y() - occmap_width * cos(yaw_ego)};
        Position point3 = {point2.x() - occmap_height * cos(yaw_ego), point2.y() - occmap_height * sin(yaw_ego)};
        Position point4 = {point3.x() - occmap_width * sin(yaw_ego), point3.y() + occmap_width * cos(yaw_ego)};
        area.addVertex(point1);
        area.addVertex(point2);
        area.addVertex(point3);
        area.addVertex(point4);

        for(GridMapIterator it(grid_map_) ; !it.isPastEnd() ; ++it) {
            if(!grid_map_.getPosition(*it, pos)) {
                ROS_ERROR("Flattening : Error when retrieving position of a grid_map_ cell");
                continue;
            }

            //Getting values
            if(area.isInside(pos)) { //If we are inside the area
                staticObjectValue = grid_map_.atPosition("StaticObjects", pos);
                dynamicObjectValue = grid_map_.atPosition("DynamicObjects", pos);
                laneValue = grid_map_.atPosition("DrivableAreas", pos);
                safeAreaValue = grid_map_.atPosition("SafeAreas", pos);

                //Calculation the occupancy value
                occValue = calculateOccValue(staticObjectValue, dynamicObjectValue, laneValue, safeAreaValue);
            } else { //Hide if not inside the area
                occValue = RED;
            }

            index = it.getLinearIndex();
            occGrid.data[nCells - index - 1] = occValue;
        }
    }

    /*!
     * \brief This function is used to calculate the occupancy value of a cell according to the layer of the grid map
     * \param staticObjectValue The value of the cell in the StaticObjects layer of the GridMap
     * \param dynamicObjectValue The value of the cell in the DynamicObjects layer of the GridMap
     * \param laneValue The value of the cell in the DrivableAreas layer of the GridMap
     * \return The occupancy value calculated
     */
    float calculateOccValue(float staticObjectValue, float dynamicObjectValue, float laneValue, float safeAreaValue) {
        float occValue = GREEN;

        
        if(safeAreaValue > 0) {
            if (safeAreaValue <= 64) {
                occValue = RED;
            } else if (safeAreaValue <= 128) {
                occValue = YELLOW;
            } else if (safeAreaValue <= 192){
                occValue = GREEN;
            } else {
                occValue = WHITE;
            }
        }
        if(laneValue == 1) {
            occValue = YELLOW;
        }
        if(staticObjectValue > dangerous_height) {
            occValue = RED;
        }
        if(dynamicObjectValue > dangerous_height) { // Dynamic objects overwrite everything
            occValue = RED;
        }
        return occValue;
    }

public:

    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \param area_width The width in meter of the ssmp occupancy area
     * \param area_height_front The distance in meter in front of the base_link point that remains in the ssmp occmap area
     * \param area_height_back The distance in meter behind the base_link point that remains in the ssmp occmap area
     * \details Initializes the node and its components such as publishers and subscribers.
     * The area related parameters needs to be given as command line arguments to the node (order : width, height_front, height_back)
     */
    OccMapCreator(ros::NodeHandle &nh, const float area_width, const float area_height_front, const float area_height_back) : nh_(nh), rate_(1),
                                                                                                                              occmap_width(area_width),                               // The width in meter...
        occmap_height(area_height_front + area_height_back)     // ... and the height in meter of the occupancy grid map that will be produced by the flattening node.
    {
        // Initialize node and publishers
        pubOccGrid = nh_.advertise<nav_msgs::OccupancyGrid>("/SafetyPlannerOccmap", 1);
        subGridMap = nh_.subscribe<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, &OccMapCreator::gridMapCallback, this);
        subPosition_ego = nh.subscribe<nav_msgs::Odometry>("/vehicle/odom", 100, &OccMapCreator::positionEgoCallback, this);

        rate_ = ros::Rate(frequency_);

        //Constants values
        occGrid.info.origin.position.z = 0;
        occGrid.info.origin.orientation.x = 0.0;
        occGrid.info.origin.orientation.y = 0.0;
        occGrid.info.origin.orientation.z = 0.0;
        occGrid.info.origin.orientation.w = 1.0;
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
            if(rostime > 1 / frequency_){
                ROS_WARN("Flatening Node : Frequency is not met!");
            }

            rate_.sleep();
        }
    }

};

void usage(std::string binName) {
    ROS_FATAL_STREAM("\n" << "Usage : " << binName <<
                     " <area_width> <area_height_front> <area_height_back>");
}

int main(int argc, char** argv)
{
    if(argc < 4) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    //Convert cli args into float (with error handling)
    float area_width, area_height_front, area_height_back;
    try {
        area_width = std::atof(argv[1]);
        area_height_front = std::atof(argv[2]);
        area_height_back = std::atof(argv[3]);
    } catch (const std::exception& e) {
        ROS_FATAL_STREAM("GridMapCreator:\n Error when parsing arguments : " << e.what());
        exit(EXIT_FAILURE);
    } catch (...) {
        ROS_FATAL("GridMapCreator:\nUndefined error when parsing arguments..\n");
        exit(EXIT_FAILURE);
    }

    // Initialize node
    ros::init(argc, argv, "flattening");
    ros::NodeHandle nh;
    OccMapCreator omc(nh, area_width, area_height_front, area_height_back);
    omc.run();
    return 0;
}
