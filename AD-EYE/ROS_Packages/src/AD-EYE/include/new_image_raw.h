#ifndef _VISUALIZERAW_H
#define _VISUALIZERAW_H

#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

#include <ros/ros.h>

#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>

#include <message_filters/subscriber.h>

#define __APP_NAME__ "visualize_raw"

class VisualizeRaw
{
private:
  std::string input_topic_;

  ros::NodeHandle node_handle_;
  image_transport::Subscriber subscriber_image_;

  message_filters::Subscriber<sensor_msgs::Image> *image_subscriber_;
  ros::Publisher publisher_image_;
  
  void ImageCallback(const sensor_msgs::Image::ConstPtr &in_image_msg);

public:
  VisualizeRaw();
};

#endif
