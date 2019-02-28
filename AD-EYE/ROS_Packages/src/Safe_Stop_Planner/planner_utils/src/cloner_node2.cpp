#include <planner_utils/costmap_cloner.h>
#include <planner_utils/collision_checking_move_base_impl.hpp>
#include <tf/transform_listener.h>


int main(int argc, char** argv) {
  ros::init(argc, argv, "costmap_cloner_node");

  ros::NodeHandle p_nh("~");
  std::string r_frame  = p_nh.param("robot_frame",std::string("base_link"));
  std::string cm_base  = p_nh.param("costmap_base_topic",std::string("costmap_base"));
  double     pub_freq  = p_nh.param("publish_frequency",0.0);

  planner_utils::TwoDCollisionCheckerI * col_checker =
      planner_utils::get_collision_checker_from_topic(r_frame,
                                                      cm_base,
                                                      pub_freq);

  ros::Rate r_outer(50.0);
  ros::Rate r_inner(100.0);
  while(ros::ok()) {
    ros::spinOnce();

    //mock planning
    col_checker->prepare();
    //col_checker->print_info();

    {

      geometry_msgs::PoseStamped pose;
      pose.header.frame_id = r_frame;
      pose.header.stamp = ros::Time::now();
      pose.pose.position.x = 20.0;
      pose.pose.orientation.w = 1.0;
      for(int i=0; i<100; ++i)
        col_checker->in_collision(pose);

    }
    r_inner.sleep(); //simulate planning taking some time

    r_outer.sleep();
  }


  return 0;
}
