#include <ros/ros.h>

#include <autoware_msgs/DetectedObjectArray.h>

#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PointStamped.h>
//#include <geometry_msgs/PolygonStamped.h>
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

/*!
* \brief A node that calculate the position of an object in an other frame
*/
class ObjectsFrameAdapter
{
private:
    // Node, publishers and subscribers
    ros::NodeHandle &nh_;
    ros::Subscriber sub_objects_;
    ros::Publisher pub_objects_;
    std::string target_frame_;
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;

    /*!
    * \brief Calculate the new position of every objects in the message
    * \param msg The message receive in the subscriber
    * \details There is an exception : If it can't calculate the new position, it seends a ROS_WARN
    */
    void detectedObjects_callback(autoware_msgs::DetectedObjectArray msg)
    {
        geometry_msgs::PoseStamped pose_stamped_in;
        geometry_msgs::PoseStamped pose_stamped_out;
        geometry_msgs::PointStamped point_stamped_in;
        geometry_msgs::PointStamped point_stamped_out;

        for (size_t i = 0; i < msg.objects.size(); i++) {
            msg.header.frame_id = target_frame_;

            try{
                msg.objects.at(i).space_frame = target_frame_;

                pose_stamped_in.header = msg.objects.at(i).header;
                pose_stamped_in.pose = msg.objects.at(i).pose;
                //std::cout << "Frame in: " << pose_stamped_in.header.frame_id << '\n';
                tf_buffer_.transform(pose_stamped_in, pose_stamped_out, target_frame_, ros::Duration(0));
                msg.objects.at(i).header = pose_stamped_out.header;
                msg.objects.at(i).pose = pose_stamped_out.pose;
                //std::cout << "Frame out: " << pose_stamped_out.header.frame_id << '\n';


                for (size_t j = 0; j < msg.objects.at(i).convex_hull.polygon.points.size(); j++) {
                    point_stamped_in.point.x = msg.objects.at(i).convex_hull.polygon.points[j].x;
                    point_stamped_in.point.y = msg.objects.at(i).convex_hull.polygon.points[j].y;
                    point_stamped_in.point.z = msg.objects.at(i).convex_hull.polygon.points[j].z;
                    point_stamped_in.header = msg.objects.at(i).convex_hull.header;
                    tf_buffer_.transform(point_stamped_in, point_stamped_out, target_frame_, ros::Duration(0));
                    msg.objects.at(i).convex_hull.polygon.points[j].x = point_stamped_out.point.x;
                    msg.objects.at(i).convex_hull.polygon.points[j].y = point_stamped_out.point.y;
                    msg.objects.at(i).convex_hull.polygon.points[j].z = point_stamped_out.point.z;
                }
                msg.objects.at(i).convex_hull.header.frame_id = target_frame_;

            }
            catch (tf2::TransformException &ex) {
                ROS_WARN("%s",ex.what());
                ros::Duration(1.0).sleep();
                continue;
            }

        }

        pub_objects_.publish(msg);
    }

public:
    /*!
     * \brief Constructor of the class
     * \param nh A reference to the ros::NodeHandle initialized in the main function.
     * \param inputTopic1 Name of the topic where our object will be receive.
     * \param outputTopic Name of the topic where the output message will be published
     * \param targetFrame The new frame
     * \details Initialize the node and its components such as publishers and subscribers.
     */
    ObjectsFrameAdapter(ros::NodeHandle &nh, std::string inputTopic, std::string outputTopic, std::string targetFrame) : nh_(nh), tf_listener_(tf_buffer_)
    {
        target_frame_ = targetFrame;
        sub_objects_ = nh_.subscribe<autoware_msgs::DetectedObjectArray>(inputTopic, 1, &ObjectsFrameAdapter::detectedObjects_callback, this);
        pub_objects_ = nh_.advertise<autoware_msgs::DetectedObjectArray>(outputTopic, 1, true);
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
* \brief This function prints how the node should be called.
*/
void usage(std::string bin_name) {
    ROS_FATAL_STREAM("\n" << "Usage : " << bin_name <<
                          " <input_topic> <output_topic> <target_frame_>");
}

/*!
* \brief Main function
* \details Requires the command line arguments inputTopic, outputTopic and target frame
*/
int main(int argc, char** argv)
{
    if (argc < 4) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string input_topic, output_topic, target_frame;
    input_topic = argv[1];
    output_topic = argv[2];
    target_frame = argv[3];

    // Initialize node
    ros::init(argc, argv, "ObjectsFrameAdapter");
    ros::NodeHandle nh;
    ObjectsFrameAdapter objects_frame_adapter(nh, input_topic, output_topic, target_frame);
    objects_frame_adapter.run();
    return 0;
}
