#include <ros/ros.h>
#include <ros/master.h>
#include <ros/this_node.h>

//#include <std_msgs/Float32MultiArray.h>
//#include <autoware_msgs/DetectedObject.h>
#include <autoware_msgs/DetectedObjectArray.h>
//#include <geometry_msgs/Point32.h>

#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>

class objectsFrameAdapter
{
private:
    // Node, publishers and subscribers
    ros::NodeHandle &nh_;

    ros::Subscriber subObjects;

    ros::Publisher pubObjects;

    tf2_ros::TransformListener tfListener();

public:
    objectsFrameAdapter(ros::NodeHandle &nh, int argc, char **argv) : nh_(nh)
    {
        // Initialize the publishers and subscribers
        subObjects = nh_.subscribe<autoware_msgs::DetectedObjectArray>("/detection/fusion_tools/objects", 1, &objectsFrameAdapter::detectedObjects_callback, this);
        pubObjects = nh_.advertise<autoware_msgs::DetectedObjectArray>("/tracked_objects", 1, true);
    }

    void detectedObjects_callback(autoware_msgs::DetectedObjectArray msg)
    {
        for (size_t i = 0; i < msg.objects; i++) {
            msg.header.frame_id = "/map";

            try{
                transformStamped = tfBuffer.lookupTransform("/map", msg.objects.at(i).header.frame_id, ros::Time(0));
            }
            catch (tf2::TransformException &ex) {
                ROS_WARN("%s",ex.what());
                ros::Duration(1.0).sleep();
                continue;
            }
            msg.objects.at(i).header.frame_id = "/map";
            msg.objects.at(i).pose.position.x = msg.objects.at(i).pose.position.x + transformStamped.transform.translation.x;
            msg.objects.at(i).pose.position.x = msg.objects.at(i).pose.position.y + transformStamped.transform.translation.y;
            msg.objects.at(i).pose.position.x = msg.objects.at(i).pose.position.z + transformStamped.transform.translation.z;
            msg.objects.at(i).pose.orientation. = ;
            msg.objects.at(i).velocity = ;
            msg.objects.at(i).acceleration = ;
            msg.objects.at(i).convex_hull.header.frame_id = "/map";
            for (size_t j = 0; j < msg.objects.at(j).convex_hull.polygon.points.size(); j++) {
                msg.objects.at(i).convex_hull.polygon.points.at(j) =
            }

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

int main(int argc, char** argv)
{
    // Initialize node
    ros::init(argc, argv, "radar_broadcaster");
    ros::NodeHandle nh;
    objectsFrameAdapter rB(nh, argc, argv);
    rB.run();
    return 0;
}
