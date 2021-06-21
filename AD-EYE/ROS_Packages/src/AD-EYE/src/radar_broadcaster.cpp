#include <ros/ros.h>

#include <std_msgs/Float32MultiArray.h>
#include <autoware_msgs/DetectedObject.h>
#include <autoware_msgs/DetectedObjectArray.h>
#include <geometry_msgs/Point32.h>

/*!
* \brief A node that convert a std_msgs::Float32MultiArray variable into a autoware_msgs::DetectedObject and publish it
* \details Rate at 20Hz. The std_msgs::Float32MultiArray come from the /radarDetections topic.
* The autoware_msgs::DetectedObject is publish on /detection/radar_tracker/objects topic
*/
class radarBroadcaster
{
private:
    // Node, publishers and subscribers
    ros::NodeHandle &nh_;

    ros::Subscriber subRadarDetections;

    ros::Publisher pubRadarObjects;

    // Structures
    struct detection{
        double x;
        double y;
        double z;
    };

    // variables
    std::vector<detection> detections;
    bool radarDetection_flag = false;

    /*!
    * \brief Callback of the /radarDetections topic sucriber.
    * \details Take position of every point on the message into a detection variable.
    */
    void radarDetections_callback(const std_msgs::Float32MultiArray::ConstPtr& msg)
    {
        std_msgs::Float32MultiArray radarMsg = *msg;
        detection d;
        detections.clear();
        for (size_t i = 0; i < radarMsg.data.size()/3; i++) {
            d.x = radarMsg.data.at(3*i);
            d.y = radarMsg.data.at(3*i+1);
            d.z = radarMsg.data.at(3*i+2);
            detections.push_back(d);
        }
        radarDetection_flag = true;
    }

    /*!
    * \brief Generate the autoware_msgs::DetectedObject object and publish it
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
        pubRadarObjects.publish(msg);


    }


public:
    /*!
    * \brief Constructor of the node.
    * \param nh A reference to the ros::NodeHandle initialized in the main function.
    * \details Subscribe the node to /radarDetections topic and advertise to /detection/radar_tracker/objects topic
    */
    radarBroadcaster(ros::NodeHandle &nh) : nh_(nh)
    {
        // Initialize the publishers and subscribers
        subRadarDetections = nh_.subscribe<std_msgs::Float32MultiArray>("/radarDetections", 1, &radarBroadcaster::radarDetections_callback, this);
        pubRadarObjects = nh_.advertise<autoware_msgs::DetectedObjectArray>("/detection/radar_tracker/objects", 1, true);
    }

    /*!
    * \brief The main function of the Node. Contains the main loop
    * \details Rate at 20Hz
    */
    void run()
    {
      ros::Rate rate(20);
      while(nh_.ok())
      {
          ros::spinOnce();
          if(radarDetection_flag == true)
          {
              radarDetection_flag = false;
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
    radarBroadcaster rB(nh);
    rB.run();
    return 0;
}
