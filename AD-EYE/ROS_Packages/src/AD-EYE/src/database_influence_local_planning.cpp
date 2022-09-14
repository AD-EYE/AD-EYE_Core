// ------------------- Database influence local planning --------------------- //
/* 
 * This c++ code aims to influence the local planner when a pothole is detected
 * The potholes coordinates come from a SQL database
 * 
 * Coded by Nicolas Pelissier on summer 2021
 * Changed by Zacharie Baeumlin on September 2022
 * 
 * Lastly edited on September 14, 2022
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

// #include <iomanip> // to print float numbers with a chosen precision

// ---------------- Parameters concerning the SQL database ------------------- //
#define DATABASE_NAME "adeye_database"              // before: adeye
#define DATABASE_HOSTNAME "tcp://127.0.0.1:3306"    // before: tcp://130.237.59.134:3306
#define DATABASE_USERNAME "root"                    // before: adeye
#define DATABASE_PASSWORD "adeye"                   // before: AdeyeSQL05

// --------------- Parameters concerning the car behaviour ------------------- //
#define DISTANCE_PARAMETER 20.0   // below this distance, if the lane collides with the pothole, the lane is set to "blocked"


// --------------------------------------------------------------------------- //
class databaseInfluenceLocalPlanning
{
private:
    // ROS: Node, publishers, subscribers, msg
    ros::NodeHandle &nh_;           // ROS node
    ros::Publisher pub_traj;        // publisher for the trajectory
    ros::Publisher pub_potholes;    // publisher for the obstacles
    ros::Subscriber sub;

    autoware_msgs::LaneArray msg1;  // message for the trajectory influencer
    visualization_msgs::MarkerArray markers_potholes; // message for the potholes markers

    //MySQL
    sql::Driver *driver_;
    sql::Connection* conn_;

    //MySQL data
    std::vector<float> pothole_x = {};
    std::vector<float> pothole_y = {};
    std::vector<float> pothole_size = {};

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

                pothole_x.push_back(_x_);
                pothole_y.push_back(_y_);
                pothole_size.push_back(_size_);

                std::cout << "GET DATA FROM DATABASE -- pothole " << i << ": " << _x_ << " " << _y_ << " " << _size_ << std::endl; // print the pothole

                visualization_msgs::Marker marker_;
                marker_.header.frame_id = "world";                  // name of the frame, found with the command rosrun tf view_frames
                marker_.header.stamp = ros::Time::now();
                marker_.id = markers_potholes.markers.size();
                marker_.type = visualization_msgs::Marker::SPHERE;  // type of marker, can be ARROW, CUBE, SPHERE, ...
                marker_.scale.x = _size_;                           // the marker size is equal to the pothole size
                marker_.scale.y = _size_;
                marker_.scale.z = _size_;
                marker_.pose.position.x = pothole_x[i];             // link the marker position to the pothole position
                marker_.pose.position.y = pothole_y[i];
                marker_.pose.position.z = 0.0;                      // show the marker on the ground
                marker_.color.a = 1.0;                              // opacity to maximum
                marker_.color.r = 1.0;                              // set the red color (0 to 1)
                marker_.color.g = 0.0;                              // set the green color (0 to 1)
                marker_.color.b = 0.0;                              // set the blue color (0 to 1)

                markers_potholes.markers.push_back(marker_);        // add the marker to the marker array

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
        pub_potholes = nh.advertise<visualization_msgs::MarkerArray>("/adeye/pothole_visualisation",1); // publisher for potholes markers
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

        // go accross all potholes and show them
        for(int k=0; k<pothole_x.size(); k++) {
            std::cout << "obstacle " << k << ":  x: " << pothole_x[k] << "  y: " << pothole_y[k] << "  size: " << pothole_size[k] << std::endl; }

        pub_potholes.publish(markers_potholes); // publish the marker array to visualise the potholes
        
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

                float pothole_distance = 0;
                float car_distance = std::sqrt(std::pow(std::abs(car_x-x),2.0)+std::pow(std::abs(car_y-y),2.0)); // calculate the distance between the car and the waypoint j of lane i
                
                // go accross all potholes
                for(int k=0; k<pothole_x.size(); k++)
                {
                    float pothole_distance = std::sqrt(std::pow(std::abs(pothole_x[k]-x),2.0)+std::pow(std::abs(pothole_y[k]-y),2.0)); // calculate the distance between the pothole and the waypoint j of lane i
                    if(pothole_distance < pothole_size[k] && car_distance < DISTANCE_PARAMETER)
                    {
                        // std::cout << "Distance " << pothole_distance << "  " << car_distance << std::endl;
                        distance_text += "  -  distance to pothole " + std::to_string(k) + ": " + std::to_string(pothole_distance).substr(0,4) + "  distance to car: " + std::to_string(car_distance).substr(0,4); // print distances with 2 decimales
                        // lane_v.lanes[i].cost = 0.9;             // change the cost of the lane
                        lane_v.lanes[i].is_blocked = 1;         // set the lane to "blocked"
                        is_change = true;                       // retain that a change has been made
                        j=lane_v.lanes[i].waypoints.size();     // exit the loop which goes accross all waypoints
                    }
                }
            }
            std::string is_blocked_text;  // text to show the status of the lane
            if (lane_v.lanes[i].is_blocked == 0) { is_blocked_text = "not blocked"; }
            else { is_blocked_text = "BLOCKED"; }

            std::string lane_cost_text = std::to_string(lane_v.lanes[i].cost);  // text to show the cost of the lane
            lane_cost_text = lane_cost_text.substr(0,5);                        // keep only 3 decimals of the cost

            // std::cout << "Lane " << i << " : " << lane_v.lanes[i].cost << "  " << std::to_string(lane_v.lanes[i].is_blocked) << std::endl;
            std::cout << "Lane " << i << ":  cost: " << lane_cost_text << "   (" << is_blocked_text << ")" << distance_text << std::endl;  // print the data of the lane
        }
        
        if(!is_change) { lane_v.lanes.clear(); }  
        else { std::cout << "-- LOCAL PLANNING CHANGED --" << std::endl; }  // make awre the user that the code changes the lanes parameters

        // std::cout << "Size : " << lane_v.lanes.size() << std::endl;  // print the size of lane_v.lanes
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
