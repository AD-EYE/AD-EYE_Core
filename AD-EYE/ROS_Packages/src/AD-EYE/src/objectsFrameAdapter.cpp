#include <ros/ros.h>
#include <ros/master.h>
#include <ros/this_node.h>

//#include <std_msgs/Float32MultiArray.h>
//#include <autoware_msgs/DetectedObject.h>
#include <autoware_msgs/DetectedObjectArray.h>
//#include <geometry_msgs/Point32.h>

#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PointStamped.h>
//#include <geometry_msgs/PolygonStamped.h>
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

class objectsFrameAdapter
{
private:
    // Node, publishers and subscribers
    ros::NodeHandle &nh_;

    ros::Subscriber subObjects;

    ros::Publisher pubObjects;


    std::string target_frame = "map";

    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener;

public:
    objectsFrameAdapter(ros::NodeHandle &nh, std::string inputTopic, std::string outputTopic) : nh_(nh), tfListener(tfBuffer)
    {
        // Initialize the publishers and subscribers
        subObjects = nh_.subscribe<autoware_msgs::DetectedObjectArray>(inputTopic, 1, &objectsFrameAdapter::detectedObjects_callback, this);
        pubObjects = nh_.advertise<autoware_msgs::DetectedObjectArray>(outputTopic, 1, true);
        // Initialize the transform listener
    }

    void detectedObjects_callback(autoware_msgs::DetectedObjectArray msg)
    {
        geometry_msgs::PoseStamped poseStampedIn;
        geometry_msgs::PoseStamped poseStampedOut;
        //geometry_msgs::PolygonStamped PolygonStampedIn;
        //geometry_msgs::PolygonStamped PolygonStampedOut;
        geometry_msgs::PointStamped pointStampedIn;
        geometry_msgs::PointStamped pointStampedOut;

        for (size_t i = 0; i < msg.objects.size(); i++) {
            msg.header.frame_id = target_frame;

            //geometry_msgs::TransformStamped transformStamped;

            try{
                //transformStamped = tfListener.lookupTransform("/map", msg.objects.at(i).header.frame_id, ros::Time(0));
                //tfBuffer::transform()
                msg.objects.at(i).space_frame = target_frame;

                poseStampedIn.header = msg.objects.at(i).header;
                poseStampedIn.pose = msg.objects.at(i).pose;
                //std::cout << "Frame in: " << poseStampedIn.header.frame_id << '\n';
                //poseStampedOut =
                tfBuffer.transform(poseStampedIn, poseStampedOut, target_frame, ros::Duration(0));
                msg.objects.at(i).header = poseStampedOut.header;
                msg.objects.at(i).pose = poseStampedOut.pose;
                //std::cout << "Frame out: " << poseStampedOut.header.frame_id << '\n';

                //msg.objects.at(i).convex_hull =
                //tfBuffer.transform(msg.objects.at(i).convex_hull, msg.objects.at(i).convex_hull, target_frame, ros::Duration(0));
                //PolygonStampedIn = msg.objects.at(i).convex_hull;
                //tfBuffer.transform(PolygonStampedIn, PolygonStampedOut, target_frame, ros::Duration(0));
                //msg.objects.at(i).convex_hull = PolygonStampedOut;

                for (size_t j = 0; j < msg.objects.at(i).convex_hull.polygon.points.size(); j++) {
                    pointStampedIn.point.x = msg.objects.at(i).convex_hull.polygon.points[j].x;
                    pointStampedIn.point.y = msg.objects.at(i).convex_hull.polygon.points[j].y;
                    pointStampedIn.point.z = msg.objects.at(i).convex_hull.polygon.points[j].z;
                    pointStampedIn.header = msg.objects.at(i).convex_hull.header;
                    tfBuffer.transform(pointStampedIn, pointStampedOut, target_frame, ros::Duration(0));
                    msg.objects.at(i).convex_hull.polygon.points[j].x = pointStampedOut.point.x;
                    msg.objects.at(i).convex_hull.polygon.points[j].y = pointStampedOut.point.y;
                    msg.objects.at(i).convex_hull.polygon.points[j].z = pointStampedOut.point.z;
                }
                msg.objects.at(i).convex_hull.header.frame_id = target_frame;

            }
            catch (tf2::TransformException &ex) {
                ROS_WARN("%s",ex.what());
                ros::Duration(1.0).sleep();
                continue;
            }
            //msg.objects.at(i).header.frame_id = "/map";
            //msg.objects.at(i).pose.position.x = msg.objects.at(i).pose.position.x + transformStamped.transform.translation.x;
            //msg.objects.at(i).pose.position.x = msg.objects.at(i).pose.position.y + transformStamped.transform.translation.y;
            //msg.objects.at(i).pose.position.x = msg.objects.at(i).pose.position.z + transformStamped.transform.translation.z;
            //msg.objects.at(i).pose.orientation. = ;
            //msg.objects.at(i).velocity = ;
            //msg.objects.at(i).acceleration = ;
            //msg.objects.at(i).convex_hull.header.frame_id = "/map";
            //for (size_t j = 0; j < msg.objects.at(j).convex_hull.polygon.points.size(); j++) {
            //    msg.objects.at(i).convex_hull.polygon.points.at(j) =
            //}

        }

        pubObjects.publish(msg);
    }

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

void usage(std::string binName) {
    ROS_FATAL_STREAM("\n" << "Usage : " << binName <<
                     " <input_topic_1> <input_topic_2> <output_topic>");
}

int main(int argc, char** argv)
{
    if (argc < 4) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string inputTopic, outputTopic;
    inputTopic = argv[1];
    outputTopic = argv[2];

    // Initialize node
    ros::init(argc, argv, "objectsFrameAdapter");
    ros::NodeHandle nh;
    objectsFrameAdapter oFA(nh, inputTopic, outputTopic);
    oFA.run();
    return 0;
}
