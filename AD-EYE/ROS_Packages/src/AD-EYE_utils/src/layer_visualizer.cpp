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
#include <geometry_msgs/PoseStamped.h>

#include <tf/transform_broadcaster.h>

#include <cpp_utils/pose_datatypes.h>


using namespace grid_map;

#define WHITE 1
#define GREEN 30
#define YELLOW 50
#define RED 99
#define LANE_VALUE 25
#define OBSTRUCTED_VALUE 100
#define CROSSING_ROAD_MALUS 50

#define PI 3.14159265 

/*!
 * \brief This class is used to extract data from the GridMap given by the GridMapCreator
 * \details This node produce one OccupancyGrid with one layer from the GridMap.
 */
class OccMapCreator
{
private:
    // publishers and subscribers
    ros::NodeHandle& nh_;
    ros::Publisher pub_occ_grid_;
    ros::Subscriber sub_grid_map_;
    ros::Subscriber sub_position_ego_;

    //Car informations
    float x_ego_ = 0;
    float y_ego_ = 0;
    float yaw_ego_ = 0;

    // 0.20 is just a random value chosen, this value indicates at what height objects become dangerous, so right now this is set to 20 cm
    const float DANGEROUS_HEIGHT_ = 0.20;
    nav_msgs::OccupancyGrid occ_grid_;
    const float occmap_width_;
    const float occmap_height_;
    float submap_dimensions_;
    GridMap grid_map_;
    float frequency_ = 20; // this value should be aligned with the frequency value used in the GridMapCreator_node
    ros::Rate rate_;
    float car_offset_;

    float width_ego_ = 2.2;


    void extractsSubmap(const GridMap &full_grid_map) {
        bool is_submap_extracted;
        submap_dimensions_ = sqrt(std::pow(occmap_width_, 2) +      // The submap that will be extracted is aligned with the global grid_map and contains the occmap.
                                      std::pow(occmap_height_, 2));
        const Length subMap_size(submap_dimensions_, submap_dimensions_);
        Position subMap_center;
        subMap_center.x() = x_ego_ + car_offset_ * cos(yaw_ego_);
        subMap_center.y() = y_ego_ + car_offset_ * sin(yaw_ego_);

        grid_map_.setTimestamp(full_grid_map.getTimestamp());
        grid_map_ = full_grid_map.getSubmap(subMap_center, subMap_size, is_submap_extracted);
        if(!is_submap_extracted)
            ROS_ERROR("GridMapCreator : Error when creating the submap in flattening");
    }

    /*!
     * \brief GridMap Callback : Called when the grid map information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the GridMap information given by the GridMapCreator, then
     * call the flateningProcess.
     */
    void gridMapCallback(const grid_map_msgs::GridMap::ConstPtr& msg)
    {
        GridMap full_grid_map;
        // convert received message back to gridmap
        GridMapRosConverter::fromMessage(*msg, full_grid_map);


        extractsSubmap(full_grid_map);

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

        flateningProcess();
    }

    /*!
     * \brief Ego Position Callback : Called when the ego position information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the position information as read from simulink of the controlled car
     */
    void positionEgoCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
        x_ego_ = msg->pose.position.x;
        y_ego_ = msg->pose.position.y;
        yaw_ego_ = cpp_utils::extract_yaw(msg->pose.orientation);
    }


    /*!
     * \brief The information from the GridMap are translated into an occupancy grid
     * \details Info from one layer is reduced to either
     * GREEN, YELLOW, or RED, as these values are the only ones that
     * the safety planner can read.
     * The safety planner do not consider the orientation of the grid, so the Occupancy Grid
     * has the same size than the Grid Map (which is aligned with global axis by design).
     * Then, every cells in the grid that are not in the considered area (aligned with the car),
     * will be hidden (filled with the RED value).
     */

     void flateningProcess() {
        size_t nCells = occ_grid_.data.size();
        size_t index;
        float occValue;
        float laneValue;
        Position pos;

        grid_map::Polygon area;
        float alpha = yaw_ego_ + std::atan(occmap_width_ / occmap_height_); // Angle between the horizontal and the diagonal of the area
        Position point1 = grid_map_.getPosition();
        point1.x() += cos(alpha) * submap_dimensions_ / 2;
        point1.y() += sin(alpha) * submap_dimensions_ / 2;
        Position point2 = {point1.x() + occmap_width_ * sin(yaw_ego_), point1.y() - occmap_width_ * cos(yaw_ego_)};
        Position point3 = {point2.x() - occmap_height_ * cos(yaw_ego_), point2.y() - occmap_height_ * sin(yaw_ego_)};
        Position point4 = {point3.x() - occmap_width_ * sin(yaw_ego_), point3.y() + occmap_width_ * cos(yaw_ego_)};
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
                laneValue = grid_map_.atPosition("DrivableAreas", pos);

                float angleToPosition = 0; // angle between the the heading of the ego placed on the left side of the footprint and the vector from the ego position to the grid map cell position
                angleToPosition = atan2(pos[1] - (y_ego_ + cos(yaw_ego_) * width_ego_ / 2), pos[0] - (x_ego_ - sin(yaw_ego_) * width_ego_ / 2)) - yaw_ego_;
                if(angleToPosition > PI)
                    angleToPosition -= 2 *PI;
                else if(angleToPosition < -PI)
                    angleToPosition += 2 *PI;

                //Calculation the occupancy value
                occValue = calculateOccValue(laneValue, angleToPosition);
            } else { //Hide if not inside the area
                occValue = RED;
            }

            index = it.getLinearIndex();
            occ_grid_.data[nCells - index - 1] = occValue;

        }
    }

    /*!
     * \brief This function is used to calculate the occupancy value of a cell according to the layer of the grid map
     * \param laneValue The value of the cell in the DrivableAreas layer of the GridMap
     * \return The occupancy value calculated
     */
    float calculateOccValue(float laneValue, float angleToPosition) {
        float occValue = 0;

        if(laneValue == 1) {
            occValue = LANE_VALUE;
        }

        if(angleToPosition>0) // applying a malus for positions that are on the left side of the ego vehicle
            occValue += CROSSING_ROAD_MALUS;

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
                                                                                                                              occmap_width_(area_width),                               // The width in meter...
        occmap_height_(area_height_front + area_height_back), // ... and the height in meter of the occupancy grid map that will be produced by the flattening node.
        car_offset_(area_height_front - occmap_height_ / 2) // relative distance between the center of the grid map and the center of the car (longitudinal axis positive towards the front of the car
    {
        // Initialize node and publishers
        pub_occ_grid_ = nh_.advertise<nav_msgs::OccupancyGrid>("/safety_planner_occmap", 1);
        sub_grid_map_ = nh_.subscribe<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, &OccMapCreator::gridMapCallback, this);
        sub_position_ego_ = nh.subscribe<geometry_msgs::PoseStamped>("/ground_truth_pose", 10, &OccMapCreator::positionEgoCallback, this);

        rate_ = ros::Rate(frequency_);

        //Constants values
        occ_grid_.info.origin.position.z = 0;
        occ_grid_.info.origin.orientation.x = 0.0;
        occ_grid_.info.origin.orientation.y = 0.0;
        occ_grid_.info.origin.orientation.z = 0.0;
        occ_grid_.info.origin.orientation.w = 1.0;

        if(nh.hasParam("car_width"))
            nh.getParam("car_width", width_ego_);
        else
            ROS_WARN_STREAM( "Could not get parameter car_length will use default value of " << width_ego_ );
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
            pub_occ_grid_.publish(occ_grid_);

            //Time control
            rostime = ros::Time::now().toSec() - rostime;
            if(rostime > 1 / frequency_){
                ROS_WARN("Flatening Node : Frequency is not met!");
            }

            rate_.sleep();
        }
    }

};

/*!
* \brief Exception
* \details Exception raise if area parameters aren't given
*/
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
