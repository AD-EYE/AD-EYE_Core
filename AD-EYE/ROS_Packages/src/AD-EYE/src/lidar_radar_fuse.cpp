#include <ros/ros.h>

#include <autoware_msgs/DetectedObjectArray.h>
#include <geometry_msgs/Point.h>

#define RADAR_LIDAR_MAX_DISTANCE 1

/*!
 * \brief This node fuse the object detected by lidar and radar in one message
 * \details The node read the objects detected by lidar and radar, and publish it into one message.
 * Every object have a personal id.
 */
class LidarRadarFuser
{
  private:
    // Node, publishers and subscribers
    ros::NodeHandle& nh_;

    ros::Subscriber sub1_;
    ros::Subscriber sub2_;

    ros::Publisher pub_;

    autoware_msgs::DetectedObjectArray lidar_msg_;
    autoware_msgs::DetectedObjectArray radar_msg_;
    autoware_msgs::DetectedObjectArray fused_msg_;

    bool lidar_msg_flag_ = false;
    bool radar_msg_flag_ = false;

    /*!
    * \brief Callback of the lidar topic
    * \param msg The msg received by the topic
    * \details Put the message received into a private variable
    */
    void lidarMsgCallback(autoware_msgs::DetectedObjectArray msg)
    {
        lidar_msg_ = msg;
        lidar_msg_flag_ = true;
    }

    /*!
    * \brief Callback of the radar topic
    * \param msg The msg received by the topic
    * \details Put the message received into a private variable
    */
    /* void radarMsgCallback(autoware_msgs::DetectedObjectArray msg)
    {
        radar_msg_ = msg;
        radar_msg_flag_ = true;
    } */

    /*!
    * \brief Calculate the distance bewteen tow points
    * \param P1 First point.
    * \param P2 Second point.
    * \result The distance between the two points given.
    */
    static double distance(geometry_msgs::Point P1, geometry_msgs::Point P2)
    {
        double dx = P1.x - P2.x;
        double dy = P1.y - P2.y;
        double dz = P1.z - P2.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }

    /*!
    * \brief Fuse the objects detected by lidar and radar and publish it
    * \details Give a personal id for each detected object, put it in a msg and then publish it.
    * If the distance between one lidar object and one radar object is lower than RADAR_LIDAR_MAX_DISTANCE,
    * it means that they have detected the same object.
    */
    void publish()
    {
        bool is_object_assigned;
        fused_msg_ = lidar_msg_;

       /*  // Here we indicate that all these objects have been detected by lidar and
        // we add the unique "id" that will be used when merging the output from the
        // different range_vision_fusion nodes for the different cameras
        size_t i;
        for (i = 0; i < fused_msg_.objects.size(); i++)
        {
            fused_msg_.objects.at(i).user_defined_info.push_back(std::to_string(i));
            fused_msg_.objects.at(i).user_defined_info.push_back("lidar");
        }

        for (size_t j = 0; j < radar_msg_.objects.size(); j++)
        {
            is_object_assigned = false;
            for (size_t k = 0; k < fused_msg_.objects.size(); k++)
            {
                if (distance(fused_msg_.objects.at(k).pose.position, radar_msg_.objects.at(j).pose.position) <
                    RADAR_LIDAR_MAX_DISTANCE)
                {
                    fused_msg_.objects.at(k).user_defined_info.push_back("radar");  // This object has been detected by
                                                                                    // the lidar. Now, we indicate that
                                                                                    // it has also been detected by
                                                                                    // radar
                    is_object_assigned = true;
                    break;
                }
            }
            if (!is_object_assigned)
            {
                radar_msg_.objects.at(j).user_defined_info.push_back(std::to_string(i));
                i++;
                radar_msg_.objects.at(j).user_defined_info.push_back(
                    "radar");  // This object has been detected only by radar
                fused_msg_.objects.push_back(radar_msg_.objects.at(j));
            }
        } */

        // Here we give a unique "id" that will be used when merging the output from the diferent range_vision_fusion
        // nodes for the different cameras
        // for (size_t k = 0; k < fused_msg_.objects.size(); k++) {
        //    fused_msg_.objects.at(k).user_defined_info.push_back(std::to_string(k));
        //    //std::to_string(fused_msg_.objects.at(k).id)
        //}

        // Publish the message
        pub_.publish(fused_msg_);
    }

  public:
    /*!
     * \brief Constructor of the class
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \param lidar_topic Name of the topic that connect the lidar node
     * \param radar_topic Name of the topic that connect the radar node
     * \param fused_topic Name of the topic where the output list will be published
     * \details Initialize the node and its components such as publishers and subscribers. It call lidarMsgCallback and
     * radarMsgCallback
     */
    LidarRadarFuser(ros::NodeHandle& nh, std::string lidar_topic, std::string fused_topic)
      : nh_(nh)
    {
        // Initialize the publishers and subscribers
        sub1_ =
            nh_.subscribe<autoware_msgs::DetectedObjectArray>(lidar_topic, 1, &LidarRadarFuser::lidarMsgCallback, this);
/*         sub2_ =
            nh_.subscribe<autoware_msgs::DetectedObjectArray>(radar_topic, 1, &LidarRadarFuser::radarMsgCallback, this); */
        pub_ = nh_.advertise<autoware_msgs::DetectedObjectArray>(fused_topic, 1, true);
    }

    /*!
     * \brief The main loop of the Node
     */
    void run()
    {
        ros::Rate rate(20);
        while (nh_.ok())
        {
            ros::spinOnce();
            if (lidar_msg_flag_)
            {
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
void usage(std::string bin_name)
{
    ROS_FATAL_STREAM("\n"
                     << "Usage : " << bin_name << " <lidar_topic> <radar_topic> <fused_topic>");
}

/*!
* \brief Main function
*/
int main(int argc, char** argv)
{
    if (argc < 4)
    {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string lidar_topic, fused_topic;
    lidar_topic = argv[1];
    fused_topic = argv[3];

    ros::init(argc, argv, "LidarRadarFuser");
    ros::NodeHandle nh;
    LidarRadarFuser Lidar_radar_fuser(nh, lidar_topic, fused_topic);
    Lidar_radar_fuser.run();
    return 0;
}
