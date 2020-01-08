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

#include <dirent.h>

using namespace grid_map;

#define HALF_PI 1.5708

/*!
 * \brief The GridMapCreator maintains a grid map used to know where safe places are
 * \details A submap is sent to the flattening node which build a occupancy grid map
 * for the Safety channel to know where are the safe places (for an emergency stop).
 * The submap is aligned by design with the global axis of the map. So the submap sent to the
 * flatening node is a square that contains the rectangle representing the final occmap
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
    const float occmap_width;
    const float occmap_height;
    const float car_offset;
    const float submap_dimensions;
    //Ros utils
    ros::Rate rate;
    float frequency;

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
    GridMapCreator(ros::NodeHandle& nh, const float area_width, const float area_height_front, const float area_height_back) : nh_(nh), rate(1),
        occmap_width(area_width),                               // The width in meter...
        occmap_height(area_height_front + area_height_back),    // ... and the height in meter of the occupancy grid map that will be produced by the flattening node.
        car_offset(area_height_front - occmap_height/2),        // relative distance between the center of the grid map and the center of the car (logitudinal axis...
                                                                // ... positive towards the front of the car

        submap_dimensions(sqrt(std::pow(occmap_width, 2) +      // The submap that will be extracted is aligned with the global grid_map and contains the occmap.
                               std::pow(occmap_height, 2)))
    {
        // Initialize node and publishers
        pub_GridMap = nh.advertise<grid_map_msgs::GridMap>("/SafetyPlannerGridmap", 1, true);
        pub_footprint_ego = nh.advertise<geometry_msgs::PolygonStamped>("/SSMP_ego_footprint", 1, true);
        pub_SSMP_control = nh.advertise<rcv_common_msgs::SSMP_control>("/SSMP_control", 1, true);
        sub_Position = nh.subscribe<nav_msgs::Odometry>("/vehicle/odom", 100, &GridMapCreator::position_callback, this);
        sub_DynamicObjects = nh.subscribe<geometry_msgs::PoseArray>("/pose_otherCar", 1, &GridMapCreator::DynamicObjects_callback, this);

        // these three variables determine the performance of gridmap, the code will warn you whenever the performance becomes to slow to make the frequency
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

        Position subMap_center;
        const Length subMap_size(submap_dimensions, submap_dimensions);
        bool subsucces;
        GridMap subMap;

        grid_map_msgs::GridMap message;

        float rostime;

        //Main loop
        while (nh_.ok()) {
            rostime = ros::Time::now().toSec();
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
                        if(x_other-x_egoOld < submap_dimensions && x_other-x_egoOld > -submap_dimensions && y_other-y_egoOld < submap_dimensions && y_other-y_egoOld > -submap_dimensions){
                            otherCarOld = rectangle_creator(x_other, y_other, length_other, width_other, yaw_other);
                            for(grid_map::PolygonIterator iterator(map, otherCarOld); !iterator.isPastEnd(); ++iterator){
                                map.at("DynamicObjects", *iterator) = 0;
                            }
                        }
                    }
                    //add new location of other actors by looking at the new position as send by prescan
                    x_other = otherActors.poses.at(i).position.x;
                    y_other = otherActors.poses.at(i).position.y;
                    yaw_other = cpp_utils::extract_yaw(otherActors.poses.at(i).orientation);
                    if(x_other-x_ego < submap_dimensions && x_other-x_ego > -submap_dimensions && y_other-y_ego < submap_dimensions && y_other-y_ego > -submap_dimensions){
                        otherCar = rectangle_creator(x_other, y_other, length_other, width_other, yaw_other);
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
            subMap_center.x() = x_ego + car_offset*cos(yaw_ego);
            subMap_center.y() = y_ego + car_offset*sin(yaw_ego);
            map.setTimestamp(ros::Time::now().toNSec());
            subMap = map.getSubmap(subMap_center, subMap_size, subsucces);
            if(subsucces == false){
                ROS_ERROR("GridMapCreator : Error when creating the submap");
                continue;
            }

            GridMapRosConverter::toMessage(subMap, message);
            pub_GridMap.publish(message);

            footprint_ego.header.stamp = ros::Time::now();
            pub_footprint_ego.publish(footprint_ego);

            rostime = ros::Time::now().toSec() - rostime;
            if(rostime > 1/frequency){
                ROS_WARN("GridMapCreator : frequency is not met!");
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
        //Add some margins for when the car drives close to the boundaries
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

        if(pexObjects.ULElementFound) { // If a User Library Element is present
            // A .csv file containing its footprint as an occupancy map should be present
            ROS_INFO("User Library Element found in Prescan Experiment !");
            std::string file = checkFile(mapResolution, filePex);
            if(file.empty()) {
                ROS_ERROR_STREAM("No .csv files describing the UserLibrary Element has been found for resolution " << mapResolution);
            } else {
                ROS_INFO_STREAM("staticObjects map found : " << file);
            }
            readFile(file);
        }

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
            else if(pexObjects.type.at(i) == TRAFFICLIGHT){
                Position center(pexObjects.posX.at(i), pexObjects.posY.at(i));
                float radius = mapResolution;
                for (grid_map::CircleIterator iterator(map, center, radius); !iterator.isPastEnd(); ++iterator) {
                    map.at("StaticObjects", *iterator) = pexObjects.sizeZ.at(i);
                }
            }
            // Nature is created using the circleIterator, as trees and bushes do not really have a definite shape, a circle describes their shape the best
            else if(pexObjects.type.at(i) == NATURE){
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
            if(pexObjects.type.at(i) == SAFEAREA) {
                grid_map::Polygon polygon = rectangle_creator(pexObjects.posX.at(i), pexObjects.posY.at(i), pexObjects.sizeX.at(i), pexObjects.sizeY.at(i), 0.01745*pexObjects.yaw.at(i));
                for(grid_map::PolygonIterator it(map, polygon) ; !it.isPastEnd() ; ++it) {
                    map.at("StaticObjects", *it) = -1;
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
     * \brief This method checks if a .csv file is provided for the given resolution
     * \param resolution The resolution the file should match
     * \param pexFileLocation The location of the .pexFile
     * \return The filePath of the right file (empty if not found)
     * \details In the case a UserLibrary Element is found on the map, this
     * function will be called in order to check if a .csv file describing the
     * Elements footprint is given. The file name should contain the resolution without
     * decimal mark preceded by an underscore (e.g. Map_025.csv for a resolution of 0.25 m/cell).
     * Then, it uses the pex file location to go to the right folder (which is hardcoded as
     * <ExperimentFolder>/staticObjects)
     */
    std::string checkFile(float resolution, std::string pexFileLocation) {
        // Finds the right folder from the pex file location
        //   Ignores the .pex file and goes 1 folder back
        std::size_t pos = pexFileLocation.find_last_of("/");
        pos = pexFileLocation.find_last_of("/", pos-1);
        std::string folder = pexFileLocation.substr(0, pos);
        //   Going 1 folder back
        folder.append("/staticObjects/");

        // Creating the search pattern: '_<resolution>' (resolution without the '.': '0.25' -> '025')
        std::stringstream s;
        s << '_' << resolution;
        std::string pattern = s.str();
        pattern.replace(pattern.find('.'), 1, "");

        // Searching for the right file
        std::string filePath;

        // Old C method for searching in the directory
        // Because it seems that c++17 standard isn't supported
        DIR *dpdf;
        struct dirent *epdf;

        dpdf = opendir(folder.c_str());
        if (dpdf != NULL){
            std::string fileName;
            while ( (epdf = readdir(dpdf)) ){
                fileName = epdf->d_name;
                if(fileName.find(pattern) != std::string::npos) {
                    filePath = folder + fileName;
                    break;
                }
            }
        } else {
            ROS_ERROR_STREAM("Cannot open folder" << folder);
        }
        closedir(dpdf);

        return filePath;
    }

    //TODO:
    //      Sanity checks ! (resolution, size, etc...)
    /*!
     * \brief This function read a .csv containing the staticObjects layer values and
     * build this layer with these.
     * \param filePath The path to the file to read
     * \details It extracts the data from the file and put it first in an occupandyGrid.
     * Then, it converts the occupancyGrid to a GridMap and finally, add the data from
     * the GridMap newly created inside the world GridMap.
     */
    void readFile(std::string filePath){
        ROS_INFO("Opening file");
        std::ifstream mapStream(filePath);
        if(!mapStream.is_open()) {
            ROS_FATAL_STREAM("Map file can't be opened:\n(File path: '" << filePath << "' )\n");
            exit(EXIT_FAILURE);
        }

        ROS_INFO("Reading metadatas");
        grid_map::Length Xlimits, Ylimits;
        float resolution;
        unsigned int width, height;
        std::string line;
        std::string value_str;

        // Reading Xlimits
        std::getline(mapStream, line); //line == "#<XLimit1>,<XLimit2>"
        std::stringstream s(line);
        s.get(); // Ignores the '#'
        std::getline(s, value_str, ','); // Gets the first limit
        Xlimits[0] = std::atof(value_str.c_str()); // Converts it to number
        std::getline(s, value_str);
        Xlimits[1] = std::atof(value_str.c_str());

        // Reading Ylimits
        std::getline(mapStream, line); //line == "#<YLimit1>,<YLimit2>"
        s.str(line);
        s.seekg(1); // Reset the cursor position to the beginning of the string (after the '#')
        std::getline(s, value_str, ','); // Gets the first limit
        Ylimits[0] = std::atof(value_str.c_str()); // Converts it to number
        std::getline(s, value_str);
        Ylimits[1] = std::atof(value_str.c_str());

        // Reading number of cells
        std::getline(mapStream, line); //line == "#<width>,<height>"
        s.str(line);
        s.seekg(1);
        std::getline(s, value_str, ',');
        width = std::atoi(value_str.c_str());
        std::getline(s, value_str);
        height = std::atoi(value_str.c_str());

        // Reading resolution
        std::getline(mapStream, line); //line == "#<resolution>"
        s.str(line);
        s.seekg(1);
        std::getline(s, value_str);
        resolution = std::atof(value_str.c_str());

        ROS_INFO("Retrieving occupancy Values");
        nav_msgs::OccupancyGrid occGrid;
        occGrid.header.frame_id = "SSMP_map";
        occGrid.info.origin.orientation.w = 1;
        occGrid.info.resolution = resolution; //0.25;
        occGrid.info.width = width; //2890;
        occGrid.info.height = height; //3085;
        occGrid.info.origin.position.x = Xlimits[0]; //-160.2371; // [-160.2371 562.0715] (XLimits (from Matlab))
        occGrid.info.origin.position.y = Ylimits[0]; //-712.9244;  // [-712.9244 58.1797] (YLimits (from Matlab))
        occGrid.data.resize(occGrid.info.width * occGrid.info.height);

        std::size_t i = 0;
        float value;
        while(std::getline(mapStream, line)) {
            std::stringstream is(line);
            /*s.str(line);
            s.seekg(0);*/ // Reseting the output cursor position to the beginning of the stream
            while(std::getline(is, value_str, ',')) {
                value = std::atoi(value_str.c_str());
                if(i >= occGrid.data.size()) {
                    ROS_FATAL("Index bigger than occGrid size...");
                    exit(EXIT_FAILURE);
                }
                occGrid.data[i] = value;
                i++;
            }
        }

        mapStream.close();
        ROS_INFO("Creating occupancyMap");
        grid_map::GridMap newMap;
        if(!grid_map::GridMapRosConverter::fromOccupancyGrid(occGrid, "StaticObjects", newMap)) {
            ROS_FATAL("GridMap from occGrid didn't worked...");
            exit(EXIT_FAILURE);
        }

        ROS_INFO("Filling the Grid_Map");
        if(!map.addDataFrom(newMap, false, true, false, {"StaticObjects"})) {
            ROS_FATAL("GridMap data addition didn't worked");
            exit(EXIT_FAILURE);
        }
        ROS_INFO("Everything happened fine ! :)");
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

/*!
 * \brief Print a help message on how to use the node.
 * \details Specify arguments needed
 */
void usage(std::string binName) {
    ROS_FATAL_STREAM("\n" << "Usage : " << binName <<
                     " <area_width> <area_height_front> <area_height_back>");
}

int main(int argc, char **argv)
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

    // init node
    ros::init(argc, argv, "GridMapCreator");
    ros::NodeHandle nh;
    GridMapCreator gmc(nh, area_width, area_height_front, area_height_back);
    gmc.run();
    return 0;
}
