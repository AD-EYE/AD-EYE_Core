#pragma once

//Idea is to use the "static layer" costmap together
//with costmap2d_ros

#include <costmap_2d/costmap_2d_ros.h>
#include <planner_utils/collision_checking.h>
#include <planner_utils/collision_checking_move_base_impl.hpp>

namespace planner_utils {

class CostmapCloner {
private:
  tf::TransformListener tf_listener_;

  costmap_2d::Costmap2DROS costmap_ros_;
public:

  CostmapCloner(std::vector<geometry_msgs::Point> const & footprint,
                std::string name=std::string("map_cloner"));

  void tick();

  costmap_2d::Costmap2DROS* get_ptr();

};



/**
 * @brief get_collision_checker_from_topic Wait for data on costmap_base_topic/costmap
 * and costmap_base_topic/footprint (calls ros::spin()) then sets up a costmap
 * that clones data from the costmap topic.
 *
 * @param robot_frame        This is not given as output from costmap2d so we need it as input
 * @param costmap_base_topic namespace where topics costmap and footprint are
 * @param publish_freq       publish frequency of the cloned costmap (default = 0)
 * @param cm_data_type       Should we interpret the data as comming from move_base (default val) or just use "raw_data"
 * @return a ptr to a collision checker
 */
planner_utils::TwoDCollisionCheckerI *get_collision_checker_from_topic(std::string robot_frame,
                                                                       std::string costmap_base_topic,
                                                                       double publish_freq = 0.0,
                                                                       std::string cm_data_type = "move_base");

}//end namespace

