/* Implementation of TwoDCollisionCheckerI based
 * on move base.
 *
 * Author: Erik Ward
 * Licence: MIT
 */

///@todo hide this implementation, only expose a Factory that can create this type of object!

#pragma once

#include <planner_utils/collision_checking.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <base_local_planner/world_model.h>

namespace planner_utils {

class MoveBaseColCheckShape : public ConvexPolygonRobotShapeI {
public:
  std::vector<geometry_msgs::Point> get_vertices_transformed(geometry_msgs::PoseStamped const & pose) const;
  std::vector<geometry_msgs::Point> get_vertices() const;

  MoveBaseColCheckShape(std::vector<geometry_msgs::Point> footprint);
private:
  std::vector<geometry_msgs::Point> footprint_;
};

/**
 * @brief The MoveBaseCostmapChecker class
 * Maintain a pointer to a ros costmap and supply collision checking
 */
class MoveBaseCostmapChecker : public TwoDCollisionCheckerI {
public:

  MoveBaseCostmapChecker(costmap_2d::Costmap2DROS* costmap_ros);

  MoveBaseCostmapChecker(MoveBaseCostmapChecker const & other);

  MoveBaseCostmapChecker& operator= (const MoveBaseCostmapChecker& other);

  std::vector<COLLISION_CHECK_TYPE> get_supported_types() const;

  ConvexPolygonRobotShapeI const & get_polygon_shape() const;
  CircleCoverRobotShapeI const & get_circle_shape() const;

  void set_outside_region_behavior(bool do_collision_check);

  bool in_collision( geometry_msgs::PoseStamped const & pose );
  double max_val_for_footprint( geometry_msgs::PoseStamped const & pose );

  double distance_to_closest_obstacle( geometry_msgs::PoseStamped const & pose);



  ~MoveBaseCostmapChecker();

  void swap_pointers();

  virtual void prepare();

protected:
  costmap_2d::Costmap2DROS* costmap_ros_;

  costmap_2d::Costmap2D* costmap_;
  base_local_planner::WorldModel* world_model_;
  MoveBaseColCheckShape* col_check_shape_;
  std::vector<geometry_msgs::Point> footprint_;
};
}
