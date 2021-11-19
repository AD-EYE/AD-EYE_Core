#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <autoware_msgs/CloudClusterArray.h>
#include <geometry_msgs/PolygonStamped.h>
#include <jsk_recognition_msgs/PolygonArray.h>

 /*!
* \brief Uses Euclidean clustering output and makes something usable by GridMapCreator
*/
class SafetyChannelPerception {

    private:
        ros::NodeHandle &nh_;
        ros::Subscriber sub_lidar_;
        ros::Publisher pub_polygons_;
        ros::Rate rate_;
        std::string polygon_frame_ = "SSMP_map";
        tf::TransformListener& tf_listener_;
        

        /*!
        * \brief Cluster Callback : Called when the Euclidean clustering of the safety channel publishes.
        * \param msg A smart pointer to the message from the topic.
        * \details Gets the Point Cloud clusters and transform each point of their convex hull footprints into the frame used for the GridMap
        * \todo Move the processing to another function
        */
        void clusterCallback(const autoware_msgs::CloudClusterArray::ConstPtr& msg) {
            jsk_recognition_msgs::PolygonArray poly_array;
            for(auto cluster: msg->clusters)
            {
                poly_array.header.frame_id = cluster.convex_hull.header.frame_id;
                geometry_msgs::PolygonStamped poly_in_gridmap_frame;
                poly_in_gridmap_frame.header.frame_id = polygon_frame_;
                float z = cluster.convex_hull.polygon.points.front().z;
                for(auto pt: cluster.convex_hull.polygon.points)
                {
                    if(pt.z == z) { // to get only the footprint, autoware's cluster hulls are composed of two layers: the footprint and the same shape but above the cluster
                        geometry_msgs::PointStamped pt_stamped_sensor_frame, pt_stamped_gridmap_frame;
                        pt_stamped_sensor_frame.header.frame_id = cluster.convex_hull.header.frame_id;
                        pt_stamped_sensor_frame.point.x = pt.x;
                        pt_stamped_sensor_frame.point.y = pt.y;
                        pt_stamped_sensor_frame.point.z = pt.z;
                        try {
                            tf_listener_.transformPoint(polygon_frame_, pt_stamped_sensor_frame,
                                                        pt_stamped_gridmap_frame);
                        }
                        catch (tf::TransformException &ex) {
                            ROS_ERROR("Received an exception trying to transform a point: %s", ex.what());
                        }
                        geometry_msgs::Point32 pt32__gridmap_frame;
                        pt32__gridmap_frame.x = pt_stamped_gridmap_frame.point.x;
                        pt32__gridmap_frame.y = pt_stamped_gridmap_frame.point.y;
                        pt32__gridmap_frame.z = pt_stamped_gridmap_frame.point.z;
                        poly_in_gridmap_frame.polygon.points.push_back(pt32__gridmap_frame);
                    }
                }
                poly_array.polygons.push_back(poly_in_gridmap_frame);
            }
            pub_polygons_.publish(poly_array);
        }

    public:
        /*!
        * \brief Constructor
        * \param nh ROS node handler
        * \param listener tf transform listener
        */
        SafetyChannelPerception(ros::NodeHandle& nh, tf::TransformListener& listener): nh_(nh), rate_(10), tf_listener_(listener)
        {
            sub_lidar_ = nh.subscribe<autoware_msgs::CloudClusterArray>("detection/lidar_detector/cloud_clusters", 1,
                                                                        &SafetyChannelPerception::clusterCallback, this);
            pub_polygons_ = nh.advertise<jsk_recognition_msgs::PolygonArray>("safetyChannelPerception/detection/polygons", 1, true);
        }

        /*!
        * \brief Main loop of the node
        */
        void run() {
            while (nh_.ok()) {
                ros::spinOnce();
                
                rate_.sleep();
            }
        }

};



int main(int argc, char** argv)
{
    ros::init(argc, argv, "SafetyChannelPerception");
    ros::NodeHandle nh;
    tf::TransformListener listener;
    SafetyChannelPerception scp = SafetyChannelPerception(nh,listener);
    scp.run();
}