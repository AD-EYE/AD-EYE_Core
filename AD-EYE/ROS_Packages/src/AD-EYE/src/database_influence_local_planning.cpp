#include <ros/ros.h>

#include <autoware_msgs/LaneArray.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <math.h>
//#include <vector.h>

class databaseInfluenceLocalPlanning
{
private:
    // ROS: Node, publishers, subscribers, msg
    ros::NodeHandle &nh_;
    ros::Publisher pub;
    ros::Subscriber sub;

    autoware_msgs::LaneArray msg1;

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
            while (res->next())
            {
                obstacle_x.push_back(res->getDouble(1));
                obstacle_y.push_back(res->getDouble(2));
                obstacle_size.push_back(res->getDouble(3));
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
        pub = nh_.advertise<autoware_msgs::LaneArray>("/adeye/overwrite_trajectory_eval", 1);
        sub = nh_.subscribe<autoware_msgs::LaneArray>("/local_weighted_trajectories", 1, &databaseInfluenceLocalPlanning::callbackLocalTrajectoryCost, this);
    
        //Connection to the mysql database
        try{
            driver_ = get_driver_instance();
            conn_ = driver_->connect("tcp://130.237.59.134:3306", "adeye", "AdeyeSQL05");
            conn_->setSchema("adeye");
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
        bool is_change = false;

        std::cout << "Obstacle " << obstacle_x[0] << " " << obstacle_y[0] << " " << obstacle_size[0] << std::endl;
        for (int i=0; i<lane_v.lanes.size(); i++)
        {
            int car_x = lane_v.lanes[i].waypoints[0].pose.pose.position.x;
            int car_y = lane_v.lanes[i].waypoints[0].pose.pose.position.y;
            for (int j=0; j<lane_v.lanes[i].waypoints.size(); j++)
            {
                int x = lane_v.lanes[i].waypoints[j].pose.pose.position.x;
                int y = lane_v.lanes[i].waypoints[j].pose.pose.position.y;

                float distance_obstacle = 0;
                float distance_voiture = std::sqrt(std::pow(std::abs(car_x-x),2.0)+std::pow(std::abs(car_y-y),2.0));
                
                for(int k=0; k<obstacle_x.size(); k++)
                {
                    float distance_obstacle = std::sqrt(std::pow(std::abs(obstacle_x[k]-x),2.0)+std::pow(std::abs(obstacle_y[k]-y),2.0));
                    if(distance_obstacle < obstacle_size[k] && distance_voiture < 20)
                    {
                        std::cout << "Distance " << distance_obstacle << "  " << distance_voiture << std::endl;
                        lane_v.lanes[i].cost = 0.9;
                        is_change = true;
                        j=lane_v.lanes[i].waypoints.size();
                    }
                }
            }
            std::cout << "Lane " << i << " : " << lane_v.lanes[i].cost << "  " << std::to_string(lane_v.lanes[i].is_blocked) << std::endl;
        }
        std::cout << "x: " <<  lane_v.lanes[0].waypoints[0].pose.pose.position.x << " y: " << lane_v.lanes[0].waypoints[0].pose.pose.position.y << std::endl;

        if(!is_change)
            lane_v.lanes.clear();  
        std::cout << "Size : " << lane_v.lanes.size() << std::endl;  
        std::cout << std::endl;
        pub.publish(lane_v);
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
