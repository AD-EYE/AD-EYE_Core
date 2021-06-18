#include <ros/ros.h>

#include <autoware_msgs/DetectedObjectArray.h>
#include <geometry_msgs/Point.h>

#define RADAR_LIDAR_MAX_DISTANCE 1

/*!
 * \brief This node fuse the object detected by lidar and radar in one message
 * \details At 20 hz, the node read the objects detected by lidar and radar, and publish it into one message.
 * Every object have a personal id.
 */
class lidarRadarFuse
{
private:
    // Node, publishers and subscribers
    ros::NodeHandle &nh_;

    ros::Subscriber sub1;
    ros::Subscriber sub2;

    ros::Publisher pub;

    autoware_msgs::DetectedObjectArray lidar_msg;
    autoware_msgs::DetectedObjectArray radar_msg;
    autoware_msgs::DetectedObjectArray fused_msg;

    bool lidar_msg_flag = false;
    bool radar_msg_flag = false;

    /*!
    * \brief Callback of the lidar topic
    * \param msg The msg received by the topic
    * \details Put the message received into a private variable
    */
    void lidar_msg_callback(autoware_msgs::DetectedObjectArray msg)
    {
        lidar_msg = msg;
        lidar_msg_flag = true;
    }

    /*!
    * \brief Callback of the radar topic
    * \param msg The msg received by the topic
    * \details Put the message received into a private variable
    */
    void radar_msg_callback(autoware_msgs::DetectedObjectArray msg)
    {
        radar_msg = msg;
        radar_msg_flag = true;
    }

    /*!
    * \brief Calculate the distance bewteen tow points
    * \param P1 First point.
    * \param P2 Second point.
    * \result The distance between the two points given.
    */
    double distance(geometry_msgs::Point P1, geometry_msgs::Point P2)
    {
        double x = P1.x - P2.x;
        double y = P1.y - P2.y;
        double z = P1.z - P2.z;
        return sqrt(x*x + y*y + z*z);
    }

    /*!
    * \brief Fuse the objects detected by lidar and radar and publish it
    * \details Give an personal id on each differente detected object and put it in a msg, then publish it. 
    * If the distance between one lidar object and one radar object is lower than RADAR_LIDAR_MAX_DISTANCE, 
    * it means that they have detected the same object.
    */
    void publish()
    {
        bool objectAssigned;
        fused_msg = lidar_msg;

        // Here we indicate that all these objects have been detected by lidar and
        // we add the unique "id" that will be used when merging the output from the
        // different range_vision_fusion nodes for the different cameras
        size_t i;
        for (i = 0; i < fused_msg.objects.size(); i++) {
            fused_msg.objects.at(i).user_defined_info.push_back(std::to_string(i));
            fused_msg.objects.at(i).user_defined_info.push_back("lidar");
        }

        for (size_t j = 0; j < radar_msg.objects.size(); j++) {
            objectAssigned = false;
            for (size_t k = 0; k < fused_msg.objects.size(); k++) {
                if (distance(fused_msg.objects.at(k).pose.position, radar_msg.objects.at(j).pose.position) < RADAR_LIDAR_MAX_DISTANCE) {
                    fused_msg.objects.at(k).user_defined_info.push_back("radar"); // This object has been detected by the lidar. Now, we indicate that it has also been detected by radar
                    objectAssigned = true;
                    break;
                }
            }
            if (!objectAssigned) {
                radar_msg.objects.at(j).user_defined_info.push_back(std::to_string(i));
                i++;
                radar_msg.objects.at(j).user_defined_info.push_back("radar"); // This object has been detected only by radar
                fused_msg.objects.push_back(radar_msg.objects.at(j));
            }
        }

        // Here we give a unique "id" that will be used when merging the output from the diferent range_vision_fusion nodes for the different cameras
        //for (size_t k = 0; k < fused_msg.objects.size(); k++) {
        //    fused_msg.objects.at(k).user_defined_info.push_back(std::to_string(k)); //std::to_string(fused_msg.objects.at(k).id)
        //}

        // Publish the message
        pub.publish(fused_msg);
    }


public:
    /*!
     * \brief Constructor of the class
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \param lidar_topic Name of the topic that connect the lidar node
     * \param radar_topic Name of the topic that connect the radar node
     * \param fused_topic Name of the topic where the output list will be published
     * \details Initialize the node and its components such as publishers and subscribers. It call lidar_msg_callback and radar_msg_callback
     */
    lidarRadarFuse(ros::NodeHandle &nh, std::string lidar_topic, std::string radar_topic, std::string fused_topic) : nh_(nh)
    {
        // Initialize the publishers and subscribers
        sub1 = nh_.subscribe<autoware_msgs::DetectedObjectArray>(lidar_topic, 1, &lidarRadarFuse::lidar_msg_callback, this);
        sub2 = nh_.subscribe<autoware_msgs::DetectedObjectArray>(radar_topic, 1, &lidarRadarFuse::radar_msg_callback, this);
        pub = nh_.advertise<autoware_msgs::DetectedObjectArray>(fused_topic, 1, true);
    }

    /*!
     * \brief The main loop of the Node
     * \details Set the rate at 20Hz.
     */
    void run()
    {
      ros::Rate rate(20);
      while(nh_.ok())
      {
          ros::spinOnce();
          if (lidar_msg_flag == true || radar_msg_flag == true) {
              publish();
          }
          rate.sleep();
      }
    }
};

/*!
* \brief Exception
* \details Exception raise if names of topics weren't given
*/
void usage(std::string binName) {
    ROS_FATAL_STREAM("\n" << "Usage : " << binName <<
                     " <lidar_topic> <radar_topic> <fused_topic>");
}

/*!
* \brief Main function
*/
int main(int argc, char** argv)
{
    if (argc < 4) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string lidar_topic, radar_topic, fused_topic;
    lidar_topic = argv[1];
    radar_topic = argv[2];
    fused_topic = argv[3];

    ros::init(argc, argv, "lidarRadarFuse");
    ros::NodeHandle nh;
    lidarRadarFuse lRF(nh, lidar_topic, radar_topic, fused_topic);
    lRF.run();
    return 0;
}
