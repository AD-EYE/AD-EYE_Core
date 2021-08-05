#include <ros/ros.h>

#include <autoware_msgs/LaneArray.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class databaseInfluenceLocalPlanning
{
private:
    // ROS: Node, publishers, subscribers, msg
    ros::NodeHandle &nh_;
    ros::Publisher pub;
    autoware_msgs::LaneArray msg1;

    //MySQL
    sql::Driver *driver_;
    sql::Connection* conn_;

    bool msg1_flag = false;

public:
    /*!
     * \brief Constructor of the class
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     */
    databaseInfluenceLocalPlanning(ros::NodeHandle &nh) : nh_(nh)
    {
        // Initialize the publishers and subscribers
        pub = nh_.advertise<autoware_msgs::LaneArray>("/adeye/overwrite_trajectory_eval", 1);
    
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
    
    }

    /*!
     * \brief 
     * \details 
     */
    void publish()
    {
        bool objectAssigned = false;
        // std::cout << "Size of msg1: " << msg1.objects.size() << '\n';

        pub.publish(msg1);
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
