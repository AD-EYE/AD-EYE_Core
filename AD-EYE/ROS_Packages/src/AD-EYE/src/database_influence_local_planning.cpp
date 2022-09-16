// ------------------- Database influence local planning --------------------- //
/* 
 * This c++ code aims to influence the local planner when a obstacle is detected
 * The obstacles coordinates come from a SQL database
 * 
 * Coded by Nicolas Pelissier on summer 2021
 * Changed by Zacharie Baeumlin on September 2022
 * 
 * Lastly edited on September 16, 2022
*/
// -------------------------------- Libraries -------------------------------- //
#include <ros/ros.h>

#include <autoware_msgs/LaneArray.h>
#include <autoware_msgs/ObjPose.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <visualization_msgs/Marker.h>  
#include <visualization_msgs/MarkerArray.h>

#include <math.h>

// ---------------- Parameters concerning the SQL database ------------------- //
#define DATABASE_NAME "adeye_database"              // before: adeye
#define DATABASE_HOSTNAME "tcp://127.0.0.1:3306"    // before: tcp://130.237.59.134:3306
#define DATABASE_USERNAME "root"                    // before: adeye
#define DATABASE_PASSWORD "adeye"                   // before: AdeyeSQL05

// --------------- Parameters concerning the car behaviour ------------------- //
#define DISTANCE_PARAMETER 20.0   // below this distance, if the lane collides with the obstacle, the lane is blocked


// --------------------------------------------------------------------------- //
class databaseInfluenceLocalPlanning
{
private:
    // ROS: Node, publishers, subscribers, msg
    ros::NodeHandle &nh_;           // ROS node
    ros::Publisher pub_traj;        // publisher for the trajectory
    ros::Publisher pub_obstacles;    // publisher for the obstacles
    ros::Subscriber sub;

    autoware_msgs::LaneArray msg1;  // message for the trajectory influencer
    visualization_msgs::MarkerArray markers_obstacles; // message for the obstacles markers

    //MySQL
    sql::Driver *driver_;
    sql::Connection* conn_;

    //MySQL data
    std::vector<float> obstacle_x = {};
    std::vector<float> obstacle_y = {};
    std::vector<float> obstacle_size = {};

    void readDatabase()
    {
        /* Send the query to mysql */
        sql::Statement *stmt;
        sql::ResultSet *res;
        stmt = conn_->createStatement();
        std::string query = "SELECT ST_X(coordinate), ST_Y(coordinate), obstacle_size  FROM test";
        try
        {
            res = stmt->executeQuery(query);
            int i = 0;
            while (res->next())
            {
                float _x_ = res->getDouble(1);
                float _y_ = res->getDouble(2);
                float _size_ = res->getDouble(3);

                obstacle_x.push_back(_x_);
                obstacle_y.push_back(_y_);
                obstacle_size.push_back(_size_);

                std::cout << "GET DATA FROM DATABASE -- obstacle " << i << ": " << _x_ << " " << _y_ << " " << _size_ << std::endl; // print the obstacle

                visualization_msgs::Marker marker_;
                marker_.header.frame_id = "world";                  // name of the frame, found with the command rosrun tf view_frames
                marker_.header.stamp = ros::Time::now();
                marker_.id = markers_obstacles.markers.size();
                marker_.type = visualization_msgs::Marker::SPHERE;  // type of marker, can be ARROW, CUBE, SPHERE, ...
                marker_.scale.x = _size_;                           // the marker size is equal to the obstacle size
                marker_.scale.y = _size_;
                marker_.scale.z = _size_;
                marker_.pose.position.x = obstacle_x[i];             // link the marker position to the obstacle position
                marker_.pose.position.y = obstacle_y[i];
                marker_.pose.position.z = 0.0;                      // show the marker on the ground
                marker_.color.a = 1.0;                              // opacity to maximum
                marker_.color.r = 1.0;                              // set the red color (0 to 1)
                marker_.color.g = 0.0;                              // set the green color (0 to 1)
                marker_.color.b = 0.0;                              // set the blue color (0 to 1)

                markers_obstacles.markers.push_back(marker_);        // add the marker to the marker array

                i += 1;
            }
        }
        catch(sql::SQLException sql_exception)
        {
            if (sql_exception.getErrorCode()!=1062)
            {
                    std::cerr << std::endl << "ERROR, failed to send the query: " << query << std::endl
                            << "MySQL ERROR: " << sql_exception.what() << std::endl 
                            << "MySQL ERROR code: " << sql_exception.getErrorCode() << std::endl
                            << "SQLSate: " << sql_exception.getSQLState() << std::endl;
            }    
        }
        delete stmt;
    }

public:
    /*!
     * \brief Constructor of the class
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     */
    databaseInfluenceLocalPlanning(ros::NodeHandle &nh) : nh_(nh)
    {
        // Initialize the publishers and subscribers
        pub_traj = nh_.advertise<autoware_msgs::LaneArray>("/adeye/overwrite_trajectory_eval", 1);      // publisher for trajectory changes
        pub_obstacles = nh.advertise<visualization_msgs::MarkerArray>("/adeye/obstacle_visualisation",1); // publisher for obstacles markers
        sub = nh_.subscribe<autoware_msgs::LaneArray>("/local_weighted_trajectories", 1, &databaseInfluenceLocalPlanning::callbackLocalTrajectoryCost, this);
    
        //Connection to the MYSQL database
        try{
            driver_ = get_driver_instance();
            conn_ = driver_->connect(DATABASE_HOSTNAME, DATABASE_USERNAME, DATABASE_PASSWORD);
            conn_->setSchema(DATABASE_NAME); // name of the database to connect to
        }
        catch(sql::SQLException sql_exception)
        {
            std::cerr << "ERROR, failed to connect to the server" << std::endl 
                        << "MySQL ERROR: " << sql_exception.what() << std::endl 
                        << "MySQL ERROR code: " << sql_exception.getErrorCode() << std::endl
                        << "SQLSate: " << sql_exception.getSQLState() << std::endl;
        }
        readDatabase();
    }

    void callbackLocalTrajectoryCost(autoware_msgs::LaneArray lane_v)
    {
        std::cout << "car position:  x: " <<  lane_v.lanes[0].waypoints[0].pose.pose.position.x << "  y: " << lane_v.lanes[0].waypoints[0].pose.pose.position.y << std::endl;
        
        bool is_change = false;

        // go accross all obstacles and show them
        for(int k=0; k<obstacle_x.size(); k++) {
            std::cout << "obstacle " << k << ":  x: " << obstacle_x[k] << "  y: " << obstacle_y[k] << "  size: " << obstacle_size[k] << std::endl; }
        std::cout << std::endl;

        pub_obstacles.publish(markers_obstacles); // publish the marker array to visualise the obstacles
        
        // go accross all lanes
        for (int i=0; i<lane_v.lanes.size(); i++)
        {
            std::string distance_text = "";
            int car_x = lane_v.lanes[i].waypoints[0].pose.pose.position.x; // get the x position of the car on lane i
            int car_y = lane_v.lanes[i].waypoints[0].pose.pose.position.y; // get the y position of the car on lane i
            
            // go accross all waypoints of lane i
            for (int j=0; j<lane_v.lanes[i].waypoints.size(); j++) 
            {
                int x = lane_v.lanes[i].waypoints[j].pose.pose.position.x; // get the x position of the waypoint j of lane i
                int y = lane_v.lanes[i].waypoints[j].pose.pose.position.y; // get the y position of the waypoint j of lane i

                float obstacle_distance = 0;
                float car_distance = std::sqrt(std::pow(std::abs(car_x-x),2.0)+std::pow(std::abs(car_y-y),2.0)); // calculate the distance between the car and the waypoint j of lane i
                
                // go accross all obstacles
                for(int k=0; k<obstacle_x.size(); k++)
                {
                    float obstacle_distance = std::sqrt(std::pow(std::abs(obstacle_x[k]-x),2.0)+std::pow(std::abs(obstacle_y[k]-y),2.0)); // calculate the distance between the obstacle and the waypoint j of lane i
                    if(obstacle_distance < obstacle_size[k] && car_distance < DISTANCE_PARAMETER)
                    {
                        distance_text += "  -  distance to obstacle " + std::to_string(k) + ": " + std::to_string(obstacle_distance).substr(0,4) + "  distance to car: " + std::to_string(car_distance).substr(0,4); // print distances with 2 decimales
                        lane_v.lanes[i].is_blocked = 1;         // set the lane to "blocked"
                        is_change = true;                       // retain that a change has been made
                        j=lane_v.lanes[i].waypoints.size();     // exit the loop which goes accross all waypoints
                    }
                }
            }
            std::string is_blocked_text;  // text to show the status of the lane
            if (lane_v.lanes[i].is_blocked == 0) { is_blocked_text = "\033[32mnot blocked\033[0m"; } // print the text in green
            else { is_blocked_text = "\033[1;31mBLOCKED\033[0m"; }  // print the text in bold red
            std::cout << "Lane " << i << ":  " << is_blocked_text << distance_text << std::endl;  // print the data of the lane
        }
        
        if(!is_change) { 
            std::cout << "-- LOCAL PLANNING UNCHANGED --" << std::endl;
            lane_v.lanes.clear(); }  
        else { std::cout << "-- \033[1mLOCAL PLANNING CHANGED\033[0m --" << std::endl; }  // make the user aware that the code changed the parameters of lanes (prints in bold white)

        std::cout << std::endl;
        pub_traj.publish(lane_v);   // publish on the topic
    }

    /*!
     * \brief The main loop of the Node
     */
    void run()
    {
      ros::Rate rate(20);
      while(nh_.ok())
      {
          ros::spinOnce();
          rate.sleep();
      }
    }
};

/*!
* \brief Main function
* \details 
*/
int main(int argc, char** argv)
{
    ros::init(argc, argv, "databaseInfluenceLocalPlanning");
    ros::NodeHandle nh;
    databaseInfluenceLocalPlanning database_influence_local_planning(nh);
    database_influence_local_planning.run();
    return 0;
}
