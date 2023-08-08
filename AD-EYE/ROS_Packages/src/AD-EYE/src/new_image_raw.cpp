#include "new_image_raw.h"

VisualizeRaw::VisualizeRaw()
{
  ros::NodeHandle private_nh_("~");

  ros::NodeHandle nh;

  std::string image_src_topic;
  std::string image_out_topic;

  private_nh_.param<std::string>("image_src", image_src_topic, "/sim_image_raw");
  private_nh_.param<std::string>("image_out", image_out_topic, "/image_raw");

  //get namespace from topic
  std::string ros_namespace = image_src_topic;
  std::size_t found_pos = ros_namespace.rfind("/"); //find last / from topic name to extract namespace
  std::cout << ros_namespace << std::endl;
  if (found_pos!=std::string::npos)
    ros_namespace.erase(found_pos, ros_namespace.length()-found_pos);
  std::cout << ros_namespace << std::endl;
  image_out_topic = ros_namespace + image_out_topic;

  image_subscriber_ = new message_filters::Subscriber<sensor_msgs::Image>(private_nh_, image_src_topic, 1);
  ROS_INFO("[%s] image_src: %s", __APP_NAME__, image_src_topic.c_str());
  
  image_subscriber_->registerCallback(boost::bind(&VisualizeRaw::ImageCallback, this, _1));

  publisher_image_ = node_handle_.advertise<sensor_msgs::Image>(image_out_topic, 1);
  ROS_INFO("[%s] image_out: %s", __APP_NAME__, image_out_topic.c_str());
}

void VisualizeRaw::ImageCallback(const sensor_msgs::Image::ConstPtr &in_image_msg)
{
  publisher_image_.publish(in_image_msg);
}