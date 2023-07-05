#ifndef ROS_LISTEN
#define ROS_LISTEN

#include "ros/ros.h"
#include "std_msgs/String.h"


void chatterCallback(const std_msgs::String::ConstPtr& msg);
int rosMain(int argc, char **argv, int s, struct sockaddr_in si_other);

#endif
