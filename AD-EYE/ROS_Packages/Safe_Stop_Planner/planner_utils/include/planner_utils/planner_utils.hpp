#pragma once

#include <vector>
#include <geometry_msgs/PoseStamped.h>
#include <ros/publisher.h>
#include <ros/node_handle.h>


#include <base_local_planner/world_model.h>
#include <base_local_planner/costmap_model.h>
#include <eigen3/Eigen/Dense>

namespace planner_utils {


class PlanStatusSingleton
{
    public:
        static PlanStatusSingleton& getInstance()
        {
            static PlanStatusSingleton    instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
            return instance;
        }

        double traveled_s;

    private:

        PlanStatusSingleton() : traveled_s(0.0) {} // Constructor? (the {} brackets) are needed here.

        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
    public:
        PlanStatusSingleton(PlanStatusSingleton const&)               = delete;
        void operator=(PlanStatusSingleton const&)  = delete;

        // Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status
};

/**
 * @brief The PathFixer class, state machine that locks a path that we have
 * found a few meters ahead and makes us re-plan from the last pose of the
 * locked path instead of our closed path.
 *
 * If we for some reason cannot find a path, a user can re-set the
 * state machine to the inital state. (e.g. when we have been standing still for
 * too long)
 */
class PathFixer {
private:
  enum STATE {NO_PATH,PATH_LOCKED};
  enum STATE state_;

   std::vector<geometry_msgs::PoseStamped> path_;

   geometry_msgs::PoseStamped fixed_pose_;

   double s_start_;
   double s_total_;

   geometry_msgs::PoseStamped current_pose_;

   ros::NodeHandle node_handle_;
   ros::Publisher fixed_pose_publisher_;

   int fixed_path_id_ = 0;

   ros::Publisher path_point_pub_;

   void publish_current_path_points(const std::vector<geometry_msgs::PoseStamped> &path_to_pub, double r, double g, double b,
                                    double lat_offset=0.0);

public:

   ///@todo this should depend on speed and replan freq.
   double const PATH_LOCK_DISTANCE = 10.0;
   std::vector<geometry_msgs::PoseStamped> update_path(std::vector<geometry_msgs::PoseStamped> const & plan,
                                                       bool estimate_theta=false);
   void reset_state( geometry_msgs::PoseStamped const & start_pose);
   geometry_msgs::PoseStamped get_start_pose(const geometry_msgs::PoseStamped& start_input);

   PathFixer( );

   bool initialized() const;

};

bool collision_check(costmap_2d::Costmap2D* costmap,
                     std::vector<geometry_msgs::Point> & footprint,
                     base_local_planner::WorldModel *world_model,
                     Eigen::Vector3d const & state);




}
