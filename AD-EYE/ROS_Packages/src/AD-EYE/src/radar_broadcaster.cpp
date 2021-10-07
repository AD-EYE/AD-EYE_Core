#include <ros/ros.h>

#include <std_msgs/Float32MultiArray.h>
#include <autoware_msgs/DetectedObject.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <geometry_msgs/Point32.h>

/*!
* \brief A node that converts a std_msgs::Float32MultiArray variable into a autoware_msgs::DetectedObject and publishes it
* \details The std_msgs::Float32MultiArray come from the /radarDetections topic.
* The autoware_msgs::DetectedObject is published on /detection/radar_tracker/objects topic
*/
class RadarBroadcaster
{
private:
    // Node, publishers and subscribers
    ros::NodeHandle &nh_;

    ros::Subscriber sub_radar_detections_;

    ros::Publisher pub_radar_objects_;

    // Structures
    struct Detection{
        double x;
        double y;
        double z;
    };

    // variables
    std::vector<Detection> detections;
    bool radar_detection_flag = false;

    /*!
    * \brief Callback of the /radarDetections topic subscriber.
    * \details Converts the float vector received into a vector of Detection (struct with x, y and z)
    */
    void radarDetectionsCallback(const std_msgs::Float32MultiArray::ConstPtr& msg)
    {
        std_msgs::Float32MultiArray radarMsg = *msg;
        Detection d;
        detections.clear();
        for (size_t i = 0; i < radarMsg.data.size()/3; i++) {
            d.x = radarMsg.data.at(3*i);
            d.y = radarMsg.data.at(3*i+1);
            d.z = radarMsg.data.at(3*i+2);
            detections.push_back(d);
        }
        radar_detection_flag = true;
    }

    /*!
    * \brief Generate the autoware_msgs::DetectedObject object, populates it and publishes it
    * \details For each point detected which contain no zero coordinate, set the parameters of object and push it back in the message to publish.
    */
    void publish()
    {
        autoware_msgs::DetectedObject object;
        autoware_msgs::DetectedObjectArray msg;

        msg.header.frame_id = "radar";
        for (size_t i = 0; i < detections.size(); i++) {
            if (detections.at(i).x != 0 || detections.at(i).y != 0 || detections.at(i).z != 0) {
                object.header.frame_id = "radar";
                object.id = i+1;
                object.label = "unknown";
                object.score = 1;
                object.valid = true;
                object.space_frame = "radar";
                object.pose.position.x = detections.at(i).x;
                object.pose.position.y = detections.at(i).y;
                object.pose.position.z = detections.at(i).z;
                object.pose.orientation.x = 0;
                object.pose.orientation.y = 0;
                object.pose.orientation.z = 0;
                object.pose.orientation.w = 1;
                object.dimensions.x = 1;
                object.dimensions.y = 1;
                object.dimensions.z = 1;
                object.pose_reliable = true;
                object.convex_hull.header.frame_id = "radar";
                object.convex_hull.polygon.points.clear();
                geometry_msgs::Point32 p1;
                p1.x = detections.at(i).x;
                p1.y = detections.at(i).y + 1;
                p1.z = detections.at(i).z;
                object.convex_hull.polygon.points.push_back(p1);
                geometry_msgs::Point32 p2;
                p2.x = detections.at(i).x;
                p2.y = detections.at(i).y - 1;
                p2.z = detections.at(i).z;
                object.convex_hull.polygon.points.push_back(p2);
                msg.objects.push_back(object);
            }

        }
        pub_radar_objects_.publish(msg);
    }


public:
    /*!
    * \brief Constructor
    * \param nh A reference to the ros::NodeHandle initialized in the main function.
    * \details The node subscribes to /radarDetections topic and advertise to /detection/radar_tracker/objects topic
    */
    RadarBroadcaster(ros::NodeHandle &nh) : nh_(nh)
    {
        // Initialize the publishers and subscribers
        sub_radar_detections_ = nh_.subscribe<std_msgs::Float32MultiArray>("/radarDetections", 1,
                                                                           &RadarBroadcaster::radarDetectionsCallback, this);
        pub_radar_objects_ = nh_.advertise<autoware_msgs::DetectedObjectArray>("/Detection/radar_tracker/objects", 1, true);
    }

    /*!
    * \brief The main function of the Node. Contains the main loop
    */
    void run()
    {
      ros::Rate rate(20);
      while(nh_.ok())
      {
          ros::spinOnce();
          if(radar_detection_flag)
          {
              radar_detection_flag = false;
              publish();
          }
          rate.sleep();
      }
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "radar_broadcaster");
    ros::NodeHandle nh;
    RadarBroadcaster radar_broadcaster(nh);
    radar_broadcaster.run();
    return 0;
}
