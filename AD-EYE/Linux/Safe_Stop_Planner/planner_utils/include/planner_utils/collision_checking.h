/* Collision checking iterface where
 * we support different implentations.
 * The idea is that we specify the shape of
 * our vehicle in 2D as a convex polygon + an origin.
 * Then we can check for collisions for different
 * angles and positions.
 *
 * We want to hide the implementation of
 * this operation.
 *
 * Author: Erik Ward
 * Licence: MIT
 */

#pragma once

#include <tf/transform_datatypes.h>
#include <geometry_msgs/PoseStamped.h>


namespace planner_utils {
class ConvexPolygonRobotShapeI {
  virtual std::vector<geometry_msgs::Point> get_vertices_transformed(geometry_msgs::PoseStamped const & pose) const = 0;
  virtual std::vector<geometry_msgs::Point> get_vertices() const = 0;
};

class CircleCoverRobotShapeI {
public:
  virtual std::vector<geometry_msgs::Point> get_circle_centers_transformed(geometry_msgs::PoseStamped const & pose) const = 0;
  virtual std::vector<geometry_msgs::Point> get_circle_centers() const = 0;
  virtual double get_radius() const = 0;
};

class TwoDCollisionCheckerI {
protected:
  bool do_collision_check_outside_region_ = false;
public:
  enum COLLISION_CHECK_TYPE {CIRCLE_APPROX,CONVEX_POLY};

  virtual std::vector<COLLISION_CHECK_TYPE> get_supported_types() const = 0;

  virtual ConvexPolygonRobotShapeI const & get_polygon_shape() const = 0;
  virtual CircleCoverRobotShapeI const & get_circle_shape() const = 0;

  void set_outside_region_behavior(bool do_collision_check) {
    do_collision_check_outside_region_ = do_collision_check;
  }

  bool get_outside_region_behavior() const {
    return do_collision_check_outside_region_;
  }

  virtual bool in_collision( geometry_msgs::PoseStamped const & pose ) = 0;
  virtual double max_val_for_footprint( geometry_msgs::PoseStamped const & pose ) = 0;

  virtual double distance_to_closest_obstacle( geometry_msgs::PoseStamped const & pose) = 0;

  virtual void prepare() = 0;

  virtual ~TwoDCollisionCheckerI() {}
};
}

