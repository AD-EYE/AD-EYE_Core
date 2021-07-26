#include <ros/ros.h> // ROS
#include <grid_map_ros/grid_map_ros.hpp> // for ROS gridmap support
#include <string> // for string support
#include <cmath> // for math functions
#include <cmath> // for math functions
#include <dirent.h> // for directory search

#include <vectormap.h>
#include <prescanmodel.h>

#include <cpp_utils/pose_datatypes.h> // for cpp_utils::extract_yaw

// ROS messages
#include <grid_map_msgs/GridMap.h>
#include <nav_msgs/OccupancyGrid.h>
#include <rcv_common_msgs/SSMP_control.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PolygonStamped.h>
#include <jsk_recognition_msgs/PolygonArray.h>


using namespace grid_map;

#define HALF_PI 1.5708
#define PI 3.1415

/*!
 * \brief The GridMapCreator maintains a grid map used to know where safe places are.
 * \details A submap is sent to the flattening node which build a occupancy grid map
 * for the Safety channel to know where are the safe places (for an emergency stop).
 * The submap is aligned by design with the global axis of the map. So the submap sent to the
 * flatening node is a square that contains the rectangle representing the final occmap.
 */
class GridMapCreator
{
private:
    // publishers and subscribers
    ros::NodeHandle &nh_;
    ros::Publisher pub_grid_map_;
    ros::Publisher pub_footprint_ego_;
    ros::Publisher pub_SSMP_control_;
    ros::Subscriber sub_position_;
    ros::Subscriber sub_dynamic_objects_ground_truth_;
    ros::Subscriber sub_dynamic_objects_;

    //Position
    float x_ego_;
    float y_ego_;
    float yaw_ego_;
    float x_ego_old_;
    float y_ego_old_;

    // for the ego footprint layer
    float last_x_ego_center_;
    float last_y_ego__center_;
    float last_yaw_ego_;
    bool first_position_callback_ = true;



    //Dimensions
    float length_ego_ = 4.6;
    float width_ego_ = 2.2;
    //float height_ego; //Height is not critical for now
    float length_other_;
    float width_other_;
    float heigth_other_;
    //Environments
    geometry_msgs::PoseArray other_actors_;
    geometry_msgs::PoseArray other_actors_old_;
    geometry_msgs::PolygonStamped footprint_ego_;
    jsk_recognition_msgs::PolygonArray detected_objects_;
    jsk_recognition_msgs::PolygonArray detected_objects_old_;
    //Parameters
    bool dynamic_objects_ground_truth_active_ = false;
    bool connection_established_ = false;
    bool dynamic_objects_ground_truth_initialized_ = false;
    bool dynamic_objects_active_ = false;
    bool dynamic_objects_initialized_ = false;

    //GridMap
    GridMap map_;
    float map_resolution_;
    const float occmap_width_;
    const float occmap_height_;
    const float submap_dimensions_;

    //Ros utils
    ros::Rate rate_;
    bool use_pex_file_ = false;
    bool use_ground_truth_dynamic_objects_ = false;

    /*!
     * \brief Creates an empty gridmap with all the layers.
     * \param vector_map The loaded vector map
     */
    void createEmptyGridMap(VectorMap vector_map)
    {
        // Determine the boundaries of the map based on the maximum and minimum values for x and y as saved in the Vector Map
        float lowest_x;
        float lowest_y;
        float maplength_x;
        float maplength_y;
        findGridMapBoundary(vector_map, lowest_x, lowest_y, maplength_x, maplength_y);

        // Create grid map consisting of four layers
        map_ = GridMap({"StaticObjects", "DrivableAreas", "DynamicObjects", "EgoVehicle", "Lanes", "SafeAreas", "SensorSectors"});
        map_.setFrameId("SSMP_map");
        map_.setGeometry(Length(maplength_x, maplength_y), map_resolution_, Position(lowest_x + 0.5 * maplength_x, lowest_y + 0.5 * maplength_y));
        ROS_INFO("Created map with size %f x %f m (%i x %i cells).", map_.getLength().x(), map_.getLength().y(), map_.getSize()(0), map_.getSize()(1));


        // All cells in all layers must first be initialized to 0
        for (GridMapIterator it(map_); !it.isPastEnd(); ++it) {
            map_.at("DrivableAreas", *it) = 0;
            map_.at("StaticObjects", *it) = 0;
            map_.at("DynamicObjects", *it) = 0;
            map_.at("Lanes", *it) = 0;
            map_.at("SafeAreas", *it) = 0;
            map_.at("EgoVehicle", *it) = 0;
            map_.at("SensorSectors", *it) = 0;
        }
    }

    /*!
     * \brief Finds the boundaries of the gridmap based on the vector map.
     * \param vector_map The loaded vector map
     * \param lowest_x The x value of the bottom left corner position
     * \param lowest_y The y value of the bottom left corner position
     * \param maplength_x The size of the grid map along x axis
     * \param maplength_y The size of the grid map along y axis
     */
    void findGridMapBoundary(VectorMap &vector_map, float &lowest_x, float &lowest_y, float &maplength_x,
                        float &maplength_y) const {
        lowest_x= vector_map.points_x_.at(vector_map.nodes_pid_.at(0) - 1);
        lowest_y= vector_map.points_y_.at(vector_map.nodes_pid_.at(0) - 1);
        float highest_x = vector_map.points_x_.at(vector_map.nodes_pid_.at(0) - 1);
        float highest_y = vector_map.points_y_.at(vector_map.nodes_pid_.at(0) - 1);
        for(int i = 1; i < (int)vector_map.nodes_pid_.size(); i++){
            if(vector_map.points_x_.at(vector_map.nodes_pid_.at(i) - 1) < lowest_x){
                lowest_x = vector_map.points_x_.at(vector_map.nodes_pid_.at(i) - 1);
            }
            if(vector_map.points_x_.at(vector_map.nodes_pid_.at(i) - 1) > highest_x){
                highest_x = vector_map.points_x_.at(vector_map.nodes_pid_.at(i) - 1);
            }
            if(vector_map.points_y_.at(vector_map.nodes_pid_.at(i) - 1) < lowest_y){
                lowest_y = vector_map.points_y_.at(vector_map.nodes_pid_.at(i) - 1);
            }
            if(vector_map.points_y_.at(vector_map.nodes_pid_.at(i) - 1) > highest_y){
                highest_y = vector_map.points_y_.at(vector_map.nodes_pid_.at(i) - 1);
            }
        }
        //Add some margins for when the car drives close to the boundaries
        lowest_x -= submap_dimensions_ * 1.5;
        lowest_y -= submap_dimensions_ * 1.5;
        highest_x += submap_dimensions_ * 1.5;
        highest_y += submap_dimensions_ * 1.5;
        ROS_INFO("X: (%f, %f), Y: (%f, %f)", lowest_x, highest_x, lowest_y, highest_y);

        // Compute the map dimensions
        maplength_x= highest_x - lowest_x;
        maplength_y= highest_y - lowest_y;
    }

    /*!
     * \brief Adds objects from the pex file.
     * \param nh A reference to a ros::NodeHandle.
     */
    void addPrescanObjects(ros::NodeHandle& p_nh)
    {
        // read out prescanmap from the pex file and store all information in 'pexObjects'
        std::string filePex = p_nh.param<std::string>("filePex","");
        PrescanModel pexObjects;
        pexObjects.load_pexmap(filePex);

        //if(pexObjects.ULElementFound) { // If a User Library Element is present
            // A .csv file containing its footprint as an occupancy map should be present
            ROS_INFO("User Library Element found in Prescan Experiment !");
            std::string file = checkFile(map_resolution_, filePex);
            if(file.empty()) {
                ROS_ERROR_STREAM("No .csv files describing the UserLibrary Element has been found for resolution " << map_resolution_);
            } else {
                ROS_INFO_STREAM("staticObjects map found : " << file);
                readFile(file);
            }
        //}

        // pex file data is used to built the staticObjects layer (stuff like buildings, nature, traffic lights), the value given to the cells is the height of the static object

        // building objects are always considered to be rectangles, and as such, a rectangle is created and the PolygonIterator is used. The number 0.01745 is a conversion from degrees to radians
        for(int i = 0; i < (int)pexObjects.buildingObjects.size(); i++){
            grid_map::Polygon polygon = rectangle_creator(pexObjects.buildingObjects.at(i).posX, pexObjects.buildingObjects.at(i).posY, pexObjects.buildingObjects.at(i).sizeX, pexObjects.buildingObjects.at(i).sizeY, 0.01745*pexObjects.buildingObjects.at(i).yaw);
            for (grid_map::PolygonIterator iterator(map_, polygon); !iterator.isPastEnd(); ++iterator) {
                map_.at("StaticObjects", *iterator) = pexObjects.buildingObjects.at(i).sizeZ;
            }
        }

        // Traffic lights are created by filling in just one or two cells, as traffic lights are usually very small
        for(int i = 0; i < (int)pexObjects.trafficlightObjects.size(); i++){
            Position center(pexObjects.trafficlightObjects.at(i).posX, pexObjects.trafficlightObjects.at(i).posY);
            float radius = map_resolution_;
            for (grid_map::CircleIterator iterator(map_, center, radius); !iterator.isPastEnd(); ++iterator) {
                map_.at("StaticObjects", *iterator) = pexObjects.trafficlightObjects.at(i).sizeZ;
            }
        }

        // Nature is created using the circleIterator, as trees and bushes do not really have a definite shape, a circle describes their shape the best
        for(int i = 0; i < (int)pexObjects.natureObjects.size(); i++){
            Position center(pexObjects.natureObjects.at(i).posX, pexObjects.natureObjects.at(i).posY);
            float radius;
            if(pexObjects.natureObjects.at(i).sizeX > pexObjects.natureObjects.at(i).sizeY){
                radius = 0.5*pexObjects.natureObjects.at(i).sizeX;
            }
            else{
                radius = 0.5*pexObjects.natureObjects.at(i).sizeY;
            }
            for (grid_map::CircleIterator iterator(map_, center, radius); !iterator.isPastEnd(); ++iterator) {
                map_.at("StaticObjects", *iterator) = pexObjects.natureObjects.at(i).sizeZ;
            }
        }

        // Safe Area objects are always considered to be rectangles
        for(int i = 0; i < (int)pexObjects.safeAreaObjects.size(); i++){
            grid_map::Polygon polygon = rectangle_creator(pexObjects.safeAreaObjects.at(i).posX, pexObjects.safeAreaObjects.at(i).posY, pexObjects.safeAreaObjects.at(i).sizeX, pexObjects.safeAreaObjects.at(i).sizeY, 0.01745*pexObjects.safeAreaObjects.at(i).yaw);
            for(grid_map::PolygonIterator it(map_, polygon) ; !it.isPastEnd() ; ++it) {
                map_.at("SafeAreas", *it) = pexObjects.safeAreaObjects.at(i).safetyAreaValue;
            }
        }

        // Static Car objects are always considered to be rectangles
		for(int i = 0; i < (int)pexObjects.staticCarsObjects.size(); i++){
            grid_map::Polygon polygon = rectangle_creator(pexObjects.staticCarsObjects.at(i).posX, pexObjects.staticCarsObjects.at(i).posY, pexObjects.staticCarsObjects.at(i).sizeX, pexObjects.staticCarsObjects.at(i).sizeY, 0.01745*pexObjects.staticCarsObjects.at(i).yaw);
            for(grid_map::PolygonIterator it(map_, polygon) ; !it.isPastEnd() ; ++it) {
                map_.at("StaticObjects", *it) = pexObjects.staticCarsObjects.at(i).sizeZ;
                //ROS_INFO_STREAM("staticCarsObjects : " << pexObjects.staticCarsObjects.at(i).ID);
            }
        }
    }
    /*!
     * \brief Adds zones from the vector map.
     * \param vector_map The loaded vector map
     */
    void addVectorMapObjects(VectorMap vector_map)
    {
        //Map Road with the data from the vector map
        grid_map::Polygon polygon;
        polygon.setFrameId(map_.getFrameId());
        Position point1;
        Position point2;
        float dx;
        float dy;
        float angle;
        float lanewidth;
        float laneID;
        for(int i = 0 ; i < static_cast<int>(vector_map.lanes_startpoint_.size()) ; i++) { //For every lane
            if(!nh_.ok()) { break; }
            polygon.removeVertices();
            point1.x() = vector_map.points_x_.at(vector_map.nodes_pid_.at(vector_map.lanes_startpoint_.at(i) - 1 ) - 1); //Get the first
            point1.y() = vector_map.points_y_.at(vector_map.nodes_pid_.at(vector_map.lanes_startpoint_.at(i) - 1 ) - 1);
            point2.x() = vector_map.points_x_.at(vector_map.nodes_pid_.at(vector_map.lanes_endpoint_.at(i) - 1 ) - 1); // and the second point
            point2.y() = vector_map.points_y_.at(vector_map.nodes_pid_.at(vector_map.lanes_endpoint_.at(i) - 1 ) - 1);
            angle = atan2(point2.y()-point1.y(), point2.x()-point1.x()); //Calculate the angle
            angle += HALF_PI;
            lanewidth = vector_map.dtlanes_leftwidth_.at(vector_map.lanes_did_.at(i) - 1);
            dx = lanewidth * cos(angle);
            dy = lanewidth * sin(angle);
            polygon.addVertex(Position(point2.x() + dx, point2.y() + dy)); //Draw the rectangle around
            polygon.addVertex(Position(point1.x() + dx, point1.y() + dy));
            polygon.addVertex(Position(point1.x() - dx, point1.y() - dy));
            polygon.addVertex(Position(point2.x() - dx, point2.y() - dy));
            laneID = vector_map.lanes_id_.at(i);
            for(grid_map::PolygonIterator iterator(map_, polygon) ; !iterator.isPastEnd() ; ++iterator) {
                map_.at("DrivableAreas", *iterator) = 1;
                map_.at("Lanes", *iterator) = laneID;
            }
            //Add a half-circle at the end to help filling when road turns
            for(grid_map::CircleIterator iterator(map_, point2, lanewidth) ; !iterator.isPastEnd() ; ++iterator) {
                map_.at("DrivableAreas", *iterator) = 1;
                map_.at("Lanes", *iterator) = laneID;
            }
        }
    }
    /*!
     * \brief Update the dynamic layer using the information sent by PreScan
     */
    void dynamicActorsUpdateGroundTruth()
    {
        size_t N_actors = other_actors_.poses.size();
        for(int i = 0; i < (int)N_actors; i++){
            float x_other;
            float y_other;
            float yaw_other;
            //remove old location of other actors by looking at the position of the previous iteration
            if(dynamic_objects_ground_truth_initialized_){
                x_other = other_actors_old_.poses.at(i).position.x;
                y_other = other_actors_old_.poses.at(i).position.y;
                yaw_other = cpp_utils::extract_yaw(other_actors_old_.poses.at(i).orientation);
                if(x_other - x_ego_old_ < submap_dimensions_ && x_other - x_ego_old_ > -submap_dimensions_ && y_other - y_ego_old_ < submap_dimensions_ && y_other - y_ego_old_ > -submap_dimensions_){
                    grid_map::Polygon otherCarOld = rectangle_creator(x_other, y_other, length_other_, width_other_, yaw_other);
                    for(grid_map::PolygonIterator iterator(map_, otherCarOld); !iterator.isPastEnd(); ++iterator){
                        map_.at("DynamicObjects", *iterator) = 0;
                    }
                }
            }
            //add new location of other actors by looking at the new position as sent by Prescan
            x_other = other_actors_.poses.at(i).position.x;
            y_other = other_actors_.poses.at(i).position.y;
            yaw_other = cpp_utils::extract_yaw(other_actors_.poses.at(i).orientation);
            if(x_other - x_ego_ < submap_dimensions_ && x_other - x_ego_ > -submap_dimensions_ && y_other - y_ego_ < submap_dimensions_ && y_other - y_ego_ > -submap_dimensions_){
                grid_map::Polygon otherCar = rectangle_creator(x_other, y_other, length_other_, width_other_, yaw_other);
                for(grid_map::PolygonIterator iterator(map_, otherCar); !iterator.isPastEnd(); ++iterator){
                    map_.at("DynamicObjects", *iterator) = heigth_other_;
                }
            }
        }
    }
    /*!
     * \brief Update the dynamic layer using the information published by the Euclidean clustering
     */
    void dynamicActorsUpdate()
    {
        size_t N_actors = detected_objects_.polygons.size();
        for(int i = 0; i < (int)N_actors; i++){
            if(dynamic_objects_initialized_){
                for(auto poly: detected_objects_old_.polygons)
                {
                    bool first_point = true;
                    Position previous_point;
                    grid_map::Polygon polygon;
                    polygon.setFrameId("SSMP_map");
                    for(auto pt: poly.polygon.points)
                    {
                        polygon.addVertex(Position(pt.x, pt.y));
                        if(!first_point)
                        {
                            for (grid_map::LineIterator iterator(map_, previous_point, Position(pt.x, pt.y)); !iterator.isPastEnd(); ++iterator) {
                                map_.at("StaticObjects", *iterator) = 0;
                            }
                        }
                        first_point = false;
                        previous_point = Position(pt.x, pt.y);
                    }
                    for(grid_map::PolygonIterator iterator(map_, polygon); !iterator.isPastEnd(); ++iterator){
                        map_.at("DynamicObjects", *iterator) = 0;
                    }
                }
            }


            for(auto poly: detected_objects_.polygons)
            {
                bool first_point = true;
                float z = poly.polygon.points.front().z;
                Position previous_point;
                grid_map::Polygon polygon;
                polygon.setFrameId("SSMP_map");
                for(auto pt: poly.polygon.points)
                {
                    polygon.addVertex(Position(pt.x, pt.y));
                    if(!first_point)
                    {
                        for (grid_map::LineIterator iterator(map_, previous_point, Position(pt.x, pt.y)); !iterator.isPastEnd(); ++iterator) {
                            map_.at("StaticObjects", *iterator) = heigth_other_;
                        }
                    }
                    first_point = false;
                    previous_point = Position(pt.x, pt.y);
                }
                for(grid_map::PolygonIterator iterator(map_, polygon); !iterator.isPastEnd(); ++iterator){
                    map_.at("DynamicObjects", *iterator) = heigth_other_;
                }
            }
            detected_objects_old_ = detected_objects_;
        }
    }

    /*!
     * \brief Position Callback : Called when the position information has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the position information as read from simulink of the controlled car
     */
    void positionCallback(const geometry_msgs::PoseStamped::ConstPtr& msg){
        x_ego_ = msg->pose.position.x;
        y_ego_ = msg->pose.position.y;
        yaw_ego_ = cpp_utils::extract_yaw(msg->pose.orientation);
        float x_ego_center = x_ego_ + cos(yaw_ego_) * 0.3 * length_ego_; // center of the car's rectangular footprint
        float y_ego_center = y_ego_ + sin(yaw_ego_) * 0.3 * length_ego_; // center of the car's rectangular footprint
        connection_established_ = true;
        //Creating footprint for Ego vehicle
        if(x_ego_center != last_x_ego_center_ || x_ego_center != last_y_ego__center_)
        {
            grid_map::Polygon egoCar = rectangle_creator(last_x_ego_center_, last_y_ego__center_, length_ego_, width_ego_, last_yaw_ego_);
            for(grid_map::PolygonIterator iterator(map_, egoCar); !iterator.isPastEnd(); ++iterator){
                map_.at("EgoVehicle", *iterator) = 0;
            }
        }
        if(first_position_callback_ || (!first_position_callback_ && (x_ego_center != last_x_ego_center_ || y_ego_center != last_y_ego__center_ || yaw_ego_ != last_yaw_ego_)))
        {
            if(first_position_callback_)
            {
                last_x_ego_center_ = x_ego_center;
                last_x_ego_center_ = y_ego_center;
                first_position_callback_ = false;
            }
            grid_map::Polygon egoCar = rectangle_creator(x_ego_center, y_ego_center, length_ego_, width_ego_, yaw_ego_);
            for(grid_map::PolygonIterator iterator(map_, egoCar); !iterator.isPastEnd(); ++iterator){
                map_.at("EgoVehicle", *iterator) = heigth_other_;
            }
            last_x_ego_center_ = x_ego_center;
            last_y_ego__center_ = y_ego_center;
            last_yaw_ego_ = yaw_ego_;
        }
    }

    /*!
     * \brief Dynamic Objects Ground TruthCallback : Called when the position of the dynamic objects sent by Simulink has changed.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the array of poses as read out from simulink of all the non controlled actors.
     */
    void dynamicObjectsGroundTruthCallback(const geometry_msgs::PoseArray::ConstPtr& msg) {
        other_actors_ = *msg;
        dynamic_objects_ground_truth_active_ = true;
    }

    /*!
     * \brief Dynamic Objects Callback : Called when a new clustering has been done.
     * \param msg A smart pointer to the message from the topic.
     * \details Stores the array of poses as read out from simulink of all the non controlled actors.
     */
    void dynamicObjectsCallback(const jsk_recognition_msgs::PolygonArray::ConstPtr& msg) {
        detected_objects_ = *msg;
        dynamic_objects_active_ = true;
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

        createEmptyGridMap(veclane);
        if(use_pex_file_)
            addPrescanObjects(p_nh);
        addVectorMapObjects(veclane);

        

        
    }

    /*!
     * \brief This method checks if a .csv file is provided for the given resolution
     * \param resolution The resolution the file should match
     * \param pex_file_location The location of the .pexFile
     * \return The filePath of the right file (empty if not found)
     * \details In the case a UserLibrary Element is found on the map, this
     * function will be called in order to check if a .csv file describing the
     * Elements footprint is given. The file name should contain the resolution without
     * decimal mark preceded by an underscore (e.g. Map_025.csv for a resolution of 0.25 m/cell).
     * Then, it uses the pex file location to go to the right folder (which is hardcoded as
     * <ExperimentFolder>/staticObjects)
     */
    std::string checkFile(float resolution, std::string pex_file_location) {
        // Finds the right folder from the pex file location
        //   Ignores the .pex file and goes 1 folder back
        std::size_t pos = pex_file_location.find_last_of("/");
        pos = pex_file_location.find_last_of("/", pos - 1);
        std::string folder = pex_file_location.substr(0, pos);
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


    /*!
     * \brief This function read a .csv containing the staticObjects layer values and
     * build this layer with these.
     * \param filePath The path to the file to read
     * \details It extracts the data from the file and put it first in an occupandyGrid.
     * Then, it converts the occupancyGrid to a GridMap and finally, add the data from
     * the GridMap newly created inside the world GridMap.
     * \todo Sanity checks ! (resolution, size, etc...)
     */
    void readFile(const std::string& filePath){
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
                    ROS_FATAL("Index bigger than occ_grid_ size...");
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
            ROS_FATAL("GridMap from occ_grid_ didn't worked...");
            exit(EXIT_FAILURE);
        }

        ROS_INFO("Filling the Grid_Map");
        if(!map_.addDataFrom(newMap, false, true, false, {"StaticObjects"})) {
            ROS_FATAL("GridMap data addition didn't worked");
            exit(EXIT_FAILURE);
        }
        ROS_INFO("Everything happened fine ! :)");
    }

    /*!
     * \brief This function creates a rectangle in a gridmap.
     * \param x x coordinate of the center location in the gridmap.
     * \param y y coordinate of the center location in the gridmap.
     * \param length Length of the rectangle.
     * \param width Width of the rectangle.
     * \param angle The amount of tilt.
     * \return A rectangle created corresponding to the given parameters
     * \details This function is especially used to creates car footprint.
     */
    grid_map::Polygon rectangle_creator(float x, float y, float length, float width, float angle) {
        length = 0.5 * length;
        width = 0.5 * width;
        grid_map::Polygon polygon;
        polygon.setFrameId("SSMP_map");
        polygon.addVertex(Position(x + length * cos(angle) - width * sin(angle), y + width * cos(angle) + length * sin(angle)));
        polygon.addVertex(Position(x + length * cos(angle) + width * sin(angle), y - width * cos(angle) + length * sin(angle)));
        polygon.addVertex(Position(x - length * cos(angle) + width * sin(angle), y - width * cos(angle) - length * sin(angle)));
        polygon.addVertex(Position(x - length * cos(angle) - width * sin(angle), y + width * cos(angle) - length * sin(angle)));
        return polygon;
    }

    /*!
     * \brief This function creates a circle section in the gridmap.
     * \param x x coordinate of the center location in the gridmap.
     * \param y y coordinate of the center location in the gridmap.
     * \param radius Sensor beam range in meter.
     * \param orientation Orientation of the section, seen from above.
     * \param angle Openning angle of the section.
     * \return A circle section created corresponding to the given parameters.
     * \details This function is especially used to create sensor sectors arround the car.
     * The circle section will be approximate by a succession of points close enought.
     */
    grid_map::Polygon circle_section_creator(float x, float y, float radius, float orientation, float angle) {
        grid_map::Polygon polygon;
        float dangle = 0.1; //the angle step for the succession of points
        polygon.setFrameId("SSMP_map");
        polygon.addVertex(Position(x, y));
        
        for (float i = (orientation - (angle / 2)); i <= (orientation + (angle / 2)); i=i+dangle){ //approximate circle section by a succession of points
                polygon.addVertex(Position(x + radius * cos(i * PI / 180), y + radius * sin(i * PI / 180)));
        } 

        if (fmodf(angle, dangle) != 0) { //if the discretion of the circle section by step doesn't fall right, we add the last point
            polygon.addVertex(Position(x + radius * cos((orientation + (angle / 2)) * PI / 180), y + radius * sin((orientation + (angle / 2)) * PI / 180)));
        }

        return polygon;
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
    GridMapCreator(ros::NodeHandle& nh, const float area_width, const float area_height_front, const float area_height_back) : nh_(nh), rate_(1),
                                                                                                                               occmap_width_(area_width),                               // The width in meter...
        occmap_height_(area_height_front + area_height_back),    // ... and the height in meter of the occupancy grid map that will be produced by the flattening node.

        submap_dimensions_(sqrt(std::pow(occmap_width_, 2) +      // The submap that will be extracted is aligned with the global grid_map and contains the occmap.
                               std::pow(occmap_height_, 2)))
    {
        nh.getParam("use_pex_file", use_pex_file_);
        nh.getParam("use_ground_truth_dynamic_objects", use_ground_truth_dynamic_objects_);
        if (nh.hasParam("car_length"))
            nh.getParam("car_length", length_ego_);
        else
            ROS_WARN_STREAM( "Could not get parameter car_length will use default value of " << length_ego_ );

        if(nh.hasParam("car_width"))
            nh.getParam("car_width", width_ego_);
        else
            ROS_WARN_STREAM( "Could not get parameter car_length will use default value of " << width_ego_ );



        // Initialize node and publishers
        pub_grid_map_ = nh.advertise<grid_map_msgs::GridMap>("/safety_planner_gridmap", 1, true);
        pub_footprint_ego_ = nh.advertise<geometry_msgs::PolygonStamped>("/SSMP_ego_footprint", 1, true);
        pub_SSMP_control_ = nh.advertise<rcv_common_msgs::SSMP_control>("/SSMP_control", 1, true);
        sub_position_ = nh.subscribe<geometry_msgs::PoseStamped>("/ground_truth_pose", 10, &GridMapCreator::positionCallback, this);
        
        if(use_ground_truth_dynamic_objects_)
            sub_dynamic_objects_ground_truth_ = nh.subscribe<geometry_msgs::PoseArray>("/pose_otherCar", 1, &GridMapCreator::dynamicObjectsGroundTruthCallback, this);
        else
            sub_dynamic_objects_ = nh.subscribe<jsk_recognition_msgs::PolygonArray>("/safetyChannelPerception/safetyChannelPerception/detection/polygons", 1, &GridMapCreator::dynamicObjectsCallback, this);

        // these three variables determine the performance of gridmap, the code will warn you whenever the performance becomes to slow to make the frequency
        map_resolution_ = 0.5;                 // 0.25 or lower number is the desired resolution, load time will significantly increase when increasing mapresolution,
        rate_ = ros::Rate(20);         // 20 Hz is the minimum desired rate_ to make sure dynamic objects are accurately tracked, remember to allign this value with the flattening_node


        //height_ego = 2; //Height is not critical for now
        length_other_ = length_ego_;
        width_other_ = width_ego_;
        heigth_other_ = 2;

        x_ego_old_ = 0;
        y_ego_old_ = 0;

        //Initialize the grid map with static entities provided by the vector map and the pex file.
        initializeGridMap();

        // Create footprint for car
        footprint_ego_.header.frame_id = "SSMP_base_link";
        geometry_msgs::Point32 point;
        point.x = -0.2 * length_ego_;
        point.y = -0.5 * width_ego_;
        footprint_ego_.polygon.points.emplace_back(point);
        point.x = 0.8 * length_ego_;
        point.y = -0.5 * width_ego_;
        footprint_ego_.polygon.points.emplace_back(point);
        point.x = 0.8 * length_ego_;
        point.y = 0.5 * width_ego_;
        footprint_ego_.polygon.points.emplace_back(point);
        point.x = -0.2 * length_ego_;
        point.y = 0.5 * width_ego_;
        footprint_ego_.polygon.points.emplace_back(point);

        // Wait until preScan has been started (connection_established_ = true), otherwise problems will happen
        while(nh.ok() && !connection_established_){
            ros::spinOnce();
            rate_.sleep();
        }

        // Send signal to the safetyplanner that the map has been created, and the safety planner can now start up
        rcv_common_msgs::SSMP_control SSMPcontrol;
        SSMPcontrol.header.stamp = ros::Time::now();
        SSMPcontrol.SSMP_control = 1;
        pub_SSMP_control_.publish(SSMPcontrol);

    }

    /*!
     * \brief The main function of the Node. Contains the main loop
     * \brief Basically, updates the gridmap with the position of the
     * dynamic objects, and then, publish.
     */
    void run() {


        grid_map_msgs::GridMap message;

        //Main loop
        while (nh_.ok()) {
            ros::Time rostime = ros::Time::now();
            ros::spinOnce();

            if(use_ground_truth_dynamic_objects_)
            {
                // Dynamic map updates, information of which is delivered by Prescan
                if(dynamic_objects_ground_truth_active_){
                    dynamicActorsUpdateGroundTruth();

                    x_ego_old_ = x_ego_;
                    y_ego_old_ = y_ego_;
                    other_actors_old_ = other_actors_;
                    dynamic_objects_ground_truth_initialized_ = true;
                    dynamic_objects_ground_truth_active_ = false;
                }
            }
            else
            {
                if(dynamic_objects_active_)
                {
                    dynamicActorsUpdate();
                    dynamic_objects_initialized_ = true;
                    dynamic_objects_active_ = false;
                }
            }
            
            

            // publish
            map_.setTimestamp(ros::Time::now().toNSec());
            GridMapRosConverter::toMessage(map_, message);
            pub_grid_map_.publish(message);

            footprint_ego_.header.stamp = ros::Time::now();
            pub_footprint_ego_.publish(footprint_ego_);

            ros::Duration rostime_elapsed = ros::Time::now() - rostime;
            if(rostime_elapsed > rate_.expectedCycleTime()){
                ROS_WARN("GridMapCreator : frequency is not met!");
            }

            rate_.sleep();
        }
    }

};

/*!
 * \brief Print a help message on how to use the node.
 * \details Specify arguments needed
 */
void usage(const std::string& binName) {
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