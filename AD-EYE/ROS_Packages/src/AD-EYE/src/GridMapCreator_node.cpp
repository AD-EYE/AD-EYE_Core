#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <limits>

#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <vectormap.h>
#include <prescanmodel.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>
#include <rcv_common_msgs/SSMP_control.h>
#include <cpp_utils/pose_datatypes.h>
#include <geometry_msgs/PoseArray.h>

using namespace grid_map;

#define HALF_PI 1.5708
#define NATURE 0
#define BUILDING 1
#define TRAFFICLIGHT 2

/*!
 * \brief The GridMapCreator maintains a grid map used to know where safe places are
 * \details It is used by the safety channel in order to know where it is better to
 * perform an emergency stop.
 */
class GridMapCreator
{
private:
    // publishers and subscribers
    ros::NodeHandle &nh_;
    ros::Publisher pub_GridMap;
    ros::Publisher pub_footprint_ego;
    ros::Publisher pub_SSMP_control;
    ros::Subscriber sub_Position;
    ros::Subscriber sub_DynamicObjects;

    // variables
    //Position
    float x_ego;
    float y_ego;
    float yaw_ego;
    float x_egoOld;
    float y_egoOld;
    geometry_msgs::Quaternion q_ego;
    //Dimensions
    float length_ego;
    float width_ego;
    //float height_ego; //Height is not critical for now
    float length_other;
    float width_other;
    float heigth_other;
    //Environments
    geometry_msgs::PoseArray otherActors;
    geometry_msgs::PoseArray otherActorsOld;
    geometry_msgs::PolygonStamped footprint_ego;
    //Parameters
    bool DynamicObjectsActive = false;
    bool connection_established = false;
    bool DynamicObjectsInitialized = false;
    //Map
    GridMap map;
    float mapResolution;
    float submap_dimensions;
    //Ros utils
    ros::Rate rate;
    float frequency;

public:

    /*!
     * \brief Constructor
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \details Initializes the node and its components such as publishers and subscribers.
     */
    GridMapCreator(ros::NodeHandle& nh) : nh_(nh), rate(1)
    {
        // Initialize node and publishers
        pub_GridMap = nh.advertise<grid_map_msgs::GridMap>("/SafetyPlannerGridmap", 1, true);
        pub_footprint_ego = nh.advertise<geometry_msgs::PolygonStamped>("/SSMP_ego_footprint", 1, true);
        pub_SSMP_control = nh.advertise<rcv_common_msgs::SSMP_control>("/SSMP_control", 1, true);
        sub_Position = nh.subscribe<nav_msgs::Odometry>("/vehicle/odom", 100, &GridMapCreator::position_callback, this);
        sub_DynamicObjects = nh.subscribe<geometry_msgs::PoseArray>("/pose_otherCar", 1, &GridMapCreator::DynamicObjects_callback, this);

        // these three variables determine the performance of gridmap, the code will warn you whenever the performance becomes to slow to make the frequency
        submap_dimensions = 35;               // Both the length and the width of the submap in meters, increasing this value will cause the flattening node to become slower, 35 is the minimum value
        mapResolution = 0.25;                 // 0.25 or lower number is the desired resolution, load time will significantly increase when increasing mapresolution,
        frequency = 30;                       // 20 Hz is the minimum desired rate to make sure dynamic objects are accurately tracked, remember to allign this value with the flattening_node
        rate = ros::Rate(frequency);

        // for now there is no easy way to send the dimensions of the actors, it is assumed all actors are 5x2x2 meters
        length_ego = 5;
        width_ego = 2;
        //height_ego = 2; //Height is not critical for now
        length_other = length_ego;
        width_other = width_ego;
        heigth_other = 2;

        x_egoOld = 0;
        y_egoOld = 0;

        //Initialize the grid map with static entities provided by the vector map and the pex file.
        initializeGridMap();

        // Create footprint for car
        footprint_ego.header.frame_id = "SSMP_base_link";
        geometry_msgs::Point32 point;
        point.x = -0.5*length_ego;
        point.y = -0.5*width_ego;
        footprint_ego.polygon.points.emplace_back(point);
        point.x = 0.5*length_ego;
        point.y = -0.5*width_ego;
        footprint_ego.polygon.points.emplace_back(point);
        point.x = 0.5*length_ego;
        point.y = 0.5*width_ego;
        footprint_ego.polygon.points.emplace_back(point);
        point.x = -0.5*length_ego;
        point.y = 0.5*width_ego;
        footprint_ego.polygon.points.emplace_back(point);

        // Wait until preScan has been started (connection_established = true), otherwise problems will happen
        while(nh.ok() && connection_established == false){
            ros::spinOnce();
            rate.sleep();
        }

        // Send signal to the safetyplanner that the map has been created, and the safety planner can now start up
        rcv_common_msgs::SSMP_control SSMPcontrol;
        SSMPcontrol.header.stamp = ros::Time::now();
        SSMPcontrol.SSMP_control = 1;
        pub_SSMP_control.publish(SSMPcontrol);

    }

    /*!
     * \brief Position Callback : Called when the position information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the position information as read from simulink of the controlled car
     */
    void position_callback(const nav_msgs::Odometry::ConstPtr& msg){
        x_ego = msg->pose.pose.position.x;
        y_ego = msg->pose.pose.position.y;
        q_ego = msg->pose.pose.orientation;
        yaw_ego = cpp_utils::extract_yaw(msg->pose.pose.orientation);
        connection_established = true;
    }

    /*!
     * \brief Dynamic Objects Callback : Called when the position of the dynamic objects has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the array of poses as read out from simulink of all the non controlled actors.
     */
    void DynamicObjects_callback(const geometry_msgs::PoseArray::ConstPtr& msg) {
        otherActors = *msg;
        DynamicObjectsActive = true;
    }

    /*!
     * \brief The main function of the Node. Contains the main loop
     * \brief Basically, updates the gridmap with the position of the
     * dynamic objects, and then, publish.
     */
    void run() {
        static tf::TransformBroadcaster br;
        tf::Transform carTF;
        static tf::TransformBroadcaster br2;
        tf::Transform mapTF;

        size_t N_actors;
        float x_other;
        float y_other;
        float yaw_other;

        grid_map::Polygon otherCarOld;
        grid_map::Polygon otherCar;

        bool subsucces;
        GridMap subMap;

        grid_map_msgs::GridMap message;

        //Main loop
        while (nh_.ok()) {
            float rostime = ros::Time::now().toSec();
            ros::spinOnce();

            // Transform between gridmap frame and ego frame
            carTF.setOrigin( tf::Vector3(x_ego, y_ego, 0) );
            tf::Quaternion q = cpp_utils::quat_to_tf_quat(q_ego);
            carTF.setRotation(q);
            br.sendTransform(tf::StampedTransform(carTF, ros::Time::now(), map.getFrameId(), "SSMP_base_link"));

            mapTF.setOrigin( tf::Vector3(0, 0, 0) );
            //tf::Quaternion map_q = cpp_utils::quat_to_tf_quat(q_ego);
            mapTF.setRotation(tf::createQuaternionFromRPY(0, 0, 0));
            br2.sendTransform(tf::StampedTransform(mapTF, ros::Time::now(), "map", "SSMP_map"));

            // Dynamic map updates, information of which is delivered by prescan
            if(DynamicObjectsActive == true){
                N_actors = otherActors.poses.size();
                for(int i = 0; i < (int)N_actors; i++){
                    //remove old location of other actors by looking at the position of the previous iteration
                    if(DynamicObjectsInitialized == true){
                        x_other = otherActorsOld.poses.at(i).position.x;
                        y_other = otherActorsOld.poses.at(i).position.y;
                        yaw_other = cpp_utils::extract_yaw(otherActorsOld.poses.at(i).orientation);
                        otherCarOld = rectangle_creator(x_other, y_other, length_other, width_other, yaw_other);
                        if(x_other-x_egoOld < submap_dimensions && x_other-x_egoOld > -submap_dimensions && y_other-y_egoOld < submap_dimensions && y_other-y_egoOld > -submap_dimensions){
                            for(grid_map::PolygonIterator iterator(map, otherCarOld); !iterator.isPastEnd(); ++iterator){
                                map.at("DynamicObjects", *iterator) = 0;
                            }
                        }
                    }
                    //add new location of other actors by looking at the new position as send by prescan
                    x_other = otherActors.poses.at(i).position.x;
                    y_other = otherActors.poses.at(i).position.y;
                    yaw_other = cpp_utils::extract_yaw(otherActors.poses.at(i).orientation);
                    otherCar = rectangle_creator(x_other, y_other, length_other, width_other, yaw_other);
                    if(x_other-x_ego < submap_dimensions && x_other-x_ego > -submap_dimensions && y_other-y_ego < submap_dimensions && y_other-y_ego > -submap_dimensions){
                        for(grid_map::PolygonIterator iterator(map, otherCar); !iterator.isPastEnd(); ++iterator){
                            map.at("DynamicObjects", *iterator) = heigth_other;
                        }
                    }
                }
                x_egoOld = x_ego;
                y_egoOld = y_ego;
                otherActorsOld = otherActors;
                DynamicObjectsInitialized = true;
                DynamicObjectsActive = false;
            }

            // publish stuff
            // a submap of the gridmap is created based on the location and the orientation of the controlled ego actor, this submap will be send to the flattening node
            map.setTimestamp(ros::Time::now().toNSec());
            subMap = map.getSubmap(Position(x_ego+(0.5*submap_dimensions-length_ego)*cos(yaw_ego), y_ego+(0.5*submap_dimensions-length_ego)*sin(yaw_ego)), Length(submap_dimensions, submap_dimensions), subsucces);
            if(subsucces == false){
                ROS_INFO("Error");
            }

            GridMapRosConverter::toMessage(subMap, message);
            pub_GridMap.publish(message);

            footprint_ego.header.stamp = ros::Time::now();
            pub_footprint_ego.publish(footprint_ego);

            rostime = ros::Time::now().toSec() - rostime;
            if(rostime > 1/frequency){
                ROS_INFO("frequency is not met!");
            }
            rate.sleep();
        }
    }

    /*!
     * \brief This function initialize the GridMap with the static entities.
     * \details First, the vector map is read from the .csv found within the parameters
     * Then, the size of the map is extracted and the map can be initialized.
     * The .pex file is read in order to parse environment and infrastructure elements.
     * And the map is completed after with the roads read from the vector map.
     */
    void initializeGridMap() {
        // read out the vectormap files and store all information in 'veclane'
        ros::NodeHandle p_nh("~");
        std::string filePoint = p_nh.param<std::string>("filePoint","");
        std::string fileLane = p_nh.param<std::string>("fileLane","");
        std::string fileNode = p_nh.param<std::string>("fileNode","");
        std::string fileDtlane = p_nh.param<std::string>("fileDtlane","");
        VectorMap veclane;
        veclane.load_vectormap(filePoint, fileLane, fileNode, fileDtlane);

        // Determine the boundaries of the map based on the maximum and minimum values for x and y as saved in the vectormap
        float lowest_x = veclane.point_x.at(veclane.node_pid.at(0)-1);
        float highest_x = veclane.point_x.at(veclane.node_pid.at(0)-1);
        float lowest_y = veclane.point_y.at(veclane.node_pid.at(0)-1);
        float highest_y = veclane.point_y.at(veclane.node_pid.at(0)-1);
        for(int i = 1; i < (int)veclane.node_pid.size(); i++){
            if(veclane.point_x.at(veclane.node_pid.at(i)-1) < lowest_x){
                lowest_x = veclane.point_x.at(veclane.node_pid.at(i)-1);
            }
            if(veclane.point_x.at(veclane.node_pid.at(i)-1) > highest_x){
                highest_x = veclane.point_x.at(veclane.node_pid.at(i)-1);
            }
            if(veclane.point_y.at(veclane.node_pid.at(i)-1) < lowest_y){
                lowest_y = veclane.point_y.at(veclane.node_pid.at(i)-1);
            }
            if(veclane.point_y.at(veclane.node_pid.at(i)-1) > highest_y){
                highest_y = veclane.point_y.at(veclane.node_pid.at(i)-1);
            }
        }
        lowest_x -= submap_dimensions * 1.5;
        lowest_y -= submap_dimensions * 1.5;
        highest_x += submap_dimensions * 1.5;
        highest_y += submap_dimensions * 1.5;
        ROS_INFO("X: (%f, %f), Y: (%f, %f)", lowest_x, highest_x, lowest_y, highest_y);

        // Create grid map consisting of four layers
        map = GridMap({"StaticObjects", "DrivableAreas", "DynamicObjects", "Lanes"});
        map.setFrameId("SSMP_map");
        float maplength_x = highest_x-lowest_x;
        float maplength_y = highest_y-lowest_y;
        map.setGeometry(Length(maplength_x, maplength_y), mapResolution, Position(lowest_x+0.5*maplength_x, lowest_y+0.5*maplength_y));
        ROS_INFO("Created map with size %f x %f m (%i x %i cells).", map.getLength().x(), map.getLength().y(), map.getSize()(0), map.getSize()(1));

        // All cells in all layers must first be initialized to 0
        for (GridMapIterator it(map); !it.isPastEnd(); ++it) {
            map.at("DrivableAreas", *it) = 0;
            map.at("StaticObjects", *it) = 0;
            map.at("DynamicObjects", *it) = 0;
            map.at("Lanes", *it) = 0;
        }

        // read out prescanmap from the pex file and store all information in 'pexObjects'
        std::string filePex = p_nh.param<std::string>("filePex","");
        PrescanModel pexObjects;
        pexObjects.load_pexmap(filePex);

        // pex file data is used to built the staticObjects layer (stuff like buildings, nature, traffic lights), the value given to the cells is the height of the static object
        for(int i = 0; i < (int)pexObjects.ID.size(); i++){
            // building objects are always considered to be rectangles, and as such, a rectangle is created and the PolygonIterator is used. The number 0.01745 is a conversion from degrees to radians
            if(pexObjects.type.at(i) == BUILDING){
                grid_map::Polygon polygon = rectangle_creator(pexObjects.posX.at(i), pexObjects.posY.at(i), pexObjects.sizeX.at(i), pexObjects.sizeY.at(i), 0.01745*pexObjects.yaw.at(i));
                for (grid_map::PolygonIterator iterator(map, polygon); !iterator.isPastEnd(); ++iterator) {
                    map.at("StaticObjects", *iterator) = pexObjects.sizeZ.at(i);
                }
            }
            // Traffic lights are created by filling in just one or two cells, as traffic lights are usually very small
            if(pexObjects.type.at(i) == TRAFFICLIGHT){
                Position center(pexObjects.posX.at(i), pexObjects.posY.at(i));
                float radius = mapResolution;
                for (grid_map::CircleIterator iterator(map, center, radius); !iterator.isPastEnd(); ++iterator) {
                    map.at("StaticObjects", *iterator) = pexObjects.sizeZ.at(i);
                }
            }
            // Nature is created using the circleIterator, as trees and bushes do not really have a definite shape, a circle describes their shape the best
            if(pexObjects.type.at(i) == NATURE){
                Position center(pexObjects.posX.at(i), pexObjects.posY.at(i));
                float radius;
                if(pexObjects.sizeX.at(i) > pexObjects.sizeY.at(i)){
                    radius = 0.5*pexObjects.sizeX.at(i);
                }
                else{
                    radius = 0.5*pexObjects.sizeY.at(i);
                }
                for (grid_map::CircleIterator iterator(map, center, radius); !iterator.isPastEnd(); ++iterator) {
                    map.at("StaticObjects", *iterator) = pexObjects.sizeZ.at(i);
                }
            }
        }

        //Map Road with the data from the vector map
        grid_map::Polygon polygon;
        polygon.setFrameId(map.getFrameId());
        Position point1;
        Position point2;
        float dx;
        float dy;
        float angle;
        float lanewidth;
        float laneID;
        for(int i = 0 ; i < static_cast<int>(veclane.lane_startpoint.size()) ; i++) { //For every lane
            if(!nh_.ok()) { break; }
            polygon.removeVertices();
            point1.x() = veclane.point_x.at(veclane.node_pid.at(veclane.lane_startpoint.at(i) - 1 ) - 1); //Get the first
            point1.y() = veclane.point_y.at(veclane.node_pid.at(veclane.lane_startpoint.at(i) - 1 ) - 1);
            point2.x() = veclane.point_x.at(veclane.node_pid.at(veclane.lane_endpoint.at(i) - 1 ) - 1); // and the second point
            point2.y() = veclane.point_y.at(veclane.node_pid.at(veclane.lane_endpoint.at(i) - 1 ) - 1);
            angle = atan2(point2.y()-point1.y(), point2.x()-point1.x()); //Calculate the angle
            angle += HALF_PI;
            lanewidth = veclane.dtlane_leftwidth.at(veclane.lane_did.at(i)-1);
            dx = lanewidth*cos(angle);
            dy = lanewidth*sin(angle);
            polygon.addVertex(Position(point2.x() + dx, point2.y() + dy)); //Draw the rectangle around
            polygon.addVertex(Position(point1.x() + dx, point1.y() + dy));
            polygon.addVertex(Position(point1.x() - dx, point1.y() - dy));
            polygon.addVertex(Position(point2.x() - dx, point2.y() - dy));
            laneID = veclane.lane_id.at(i);
            for(grid_map::PolygonIterator iterator(map, polygon) ; !iterator.isPastEnd() ; ++iterator) {
                map.at("DrivableAreas", *iterator) = 1;
                map.at("Lanes", *iterator) = laneID;
            }
            //Add a half-circle at the end to help filling when road turns
            for(grid_map::CircleIterator iterator(map, point2, lanewidth) ; !iterator.isPastEnd() ; ++iterator) {
                map.at("DrivableAreas", *iterator) = 1;
                map.at("Lanes", *iterator) = laneID;
            }
        }
    }

    /*!
     * \brief This function creates a rectangle in a gridmap.
     * \param X X coordinate of the center location in the gridmap.
     * \param Y Y coordinate of the center location in the gridmap.
     * \param length Length of the rectangle.
     * \param width Width of the rectangle.
     * \param angle The amount of tilt.
     * \return A rectangle created corresponding to the given parameters
     * \details This function is especially used to creates car footprint.
     */
    grid_map::Polygon rectangle_creator(float X, float Y, float length, float width, float angle) {
        length = 0.5*length;
        width = 0.5*width;
        grid_map::Polygon polygon;
        polygon.setFrameId("SSMP_map");
        polygon.addVertex(Position(X+length*cos(angle)-width*sin(angle), Y+width*cos(angle)+length*sin(angle)));
        polygon.addVertex(Position(X+length*cos(angle)+width*sin(angle), Y-width*cos(angle)+length*sin(angle)));
        polygon.addVertex(Position(X-length*cos(angle)+width*sin(angle), Y-width*cos(angle)-length*sin(angle)));
        polygon.addVertex(Position(X-length*cos(angle)-width*sin(angle), Y+width*cos(angle)-length*sin(angle)));
        return polygon;
    }

};

int main(int argc, char **argv)
{
    // init node
    ros::init(argc, argv, "GridMapCreator");
    ros::NodeHandle nh;
    GridMapCreator gmc(nh);
    gmc.run();
    return 0;
}
