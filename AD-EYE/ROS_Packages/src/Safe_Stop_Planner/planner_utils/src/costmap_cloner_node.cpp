#include <planner_utils/costmap_cloner.h>
#include <planner_utils/collision_checking_move_base_impl.hpp>
#include <tf/transform_listener.h>


//should be intra-process publishing...
//http://wiki.ros.org/roscpp/Overview/Publishers%20and%20Subscribers
///@todo, this should be started with move-base?
class FootprintStampedConverter {
public:
  ros::Publisher pub;
  ros::Subscriber sub;

  bool got_msg;

  geometry_msgs::PolygonStamped last_footprint;

  FootprintStampedConverter(std::string footprint_stamped_topic) {
    ros::NodeHandle n;
    pub = n.advertise<geometry_msgs::Polygon>("/map_cloner/footprint_to_costmap_input",100);
    sub = n.subscribe(footprint_stamped_topic,100,&FootprintStampedConverter::footprint_cb,this);
    got_msg = false;
  }
  void footprint_cb(geometry_msgs::PolygonStampedConstPtr const & msg) {
    last_footprint = *msg;
    geometry_msgs::PolygonPtr poly_ptr(new geometry_msgs::Polygon);
    poly_ptr->points = msg->polygon.points;

    //let's not do this
    //pub.publish(poly_ptr);
    got_msg = true;
  }
};

///@todo, we need to make our OWN plugin that doesn't change
/// values as static costmap does. I think change of
/// unsigned char StaticLayer::interpretValue(unsigned char value) is enough

///@todo, figure out how this should work...
/// probably want a "factory" that creates the map...
/// this should set the name for the private node_handle for each map
/// use private_nh.setParam();

int main(int argc, char** argv) {
  ros::init(argc, argv, "costmap_cloner_node");

  ros::NodeHandle private_nh("~/map_cloner");


  //There is a bug with ros-logging: https://github.com/ros/ros_comm/issues/688
  //It counts the node handles, and if there was more than 0 and these
  //go out of scope logging is shut down. Since get_collision_checker_from_topic() creates a temporary node
  //handle, this can close down the whole logging system, unless we already have a node handle in scope!
  //planner_utils::get_collision_checker_from_topic("lel");


  tf::TransformListener tf_listen;

  std::string footprint_stamped_topic =
      private_nh.param<std::string>("footprint_stamped_topic","/footprint_stamped");

  FootprintStampedConverter footprint_converter(footprint_stamped_topic);


  //make sure we convert some data before we start the costmap cloner...
  ros::Rate r(20.0);
  ROS_INFO_STREAM("Waiting for footprint from " << footprint_stamped_topic);
  while( !footprint_converter.got_msg && ros::ok()) {
    ros::spinOnce();
    r.sleep();
  }
  ROS_INFO_STREAM("Got footprint!");

  std::string robot_frame, global_frame;
  private_nh.param("robot_base_frame", robot_frame, std::string("base_link"));
  private_nh.param("global_frame", global_frame, std::string("/map"));

  //Let's set the footprint
  //We assume that the footprint should be expressed in the robot frame
  std::vector<geometry_msgs::Point> footprint;
  std::string footprint_frame = footprint_converter.last_footprint.header.frame_id;

  tf::StampedTransform transform;
  tf_listen.lookupTransform(robot_frame,footprint_frame,ros::Time(0),transform);

  ROS_INFO_STREAM("transforming footprint from frame: "<<footprint_frame<< " to "<<robot_frame);


  for(auto const & p_fp : footprint_converter.last_footprint.polygon.points) {
    std::stringstream ss;


    geometry_msgs::Point p;
    p.x = p_fp.x;
    p.y = p_fp.y;
    p.z = p_fp.z;

    ss << "before: (" << p.x << ", " << p.y << ", " << p.z << ") ";
    //transform to robot frame
    tf::Point tf_p;
    tf::pointMsgToTF(p,tf_p);
    tf_p = transform*tf_p;
    tf::pointTFToMsg(tf_p,p);
    ss << " after: (" << p.x << ", " << p.y << ", " << p.z << ") ";
    ROS_INFO_STREAM(ss.str());
    footprint.push_back(p);
  }


  planner_utils::CostmapCloner cloner(footprint);



  //USE the costmap...
  planner_utils::TwoDCollisionCheckerI * col_checker =
      new planner_utils::MoveBaseCostmapChecker(cloner.get_ptr());


  ros::Rate r_outer(50.0);
  ros::Rate r_inner(100.0);
  while(ros::ok()) {

    ros::spinOnce();

    cloner.tick();


    {

      //boost::unique_lock<costmap_2d::Costmap2D::mutex_t> lock(*(cloner.get_ptr()->getCostmap()->getMutex()));


      //col_checker->in_collision()
      costmap_2d::NO_INFORMATION;

      bool all_clear = true;
      unsigned char max_val = 0;
      //Check if the map is empty (this would be really bad)
      for(unsigned int i=0; i<cloner.get_ptr()->getCostmap()->getSizeInCellsX(); ++i) {
        for(unsigned int j=0; j<cloner.get_ptr()->getCostmap()->getSizeInCellsY(); ++j) {
          unsigned int  index = cloner.get_ptr()->getCostmap()->getIndex(i,j);
          all_clear &=
              cloner.get_ptr()->getCostmap()->getCharMap()[index] < 128;
          if(cloner.get_ptr()->getCostmap()->getCharMap()[index] > max_val)
            max_val = cloner.get_ptr()->getCostmap()->getCharMap()[index];
        }
      }
      if(all_clear) {
        ROS_WARN_STREAM("Costmap ( sz = " << cloner.get_ptr()->getCostmap()->getSizeInCellsX()
                        << " X " << cloner.get_ptr()->getCostmap()->getSizeInCellsY() << " ) completely clear! Max val = " << (int)max_val);
      }

      geometry_msgs::PoseStamped pose;
      pose.header.frame_id = "/base_link";
      pose.header.stamp = ros::Time::now();
      pose.pose.position.x = 20.0;
      pose.pose.orientation.w = 1.0;
      for(int i=0; i<100; ++i)
        col_checker->in_collision(pose);

      r_inner.sleep(); //simulate planning taking some time
    }
    r_outer.sleep();
  }
  //ros::spin();

  delete col_checker;

  return 0;
}

