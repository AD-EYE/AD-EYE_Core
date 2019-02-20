#include <planner_utils/costmap_cloner.h>

#include <cpp_utils/ros_comms.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/PolygonStamped.h>

namespace planner_utils {

CostmapCloner::CostmapCloner(const std::vector<geometry_msgs::Point> &footprint,
                             std::string name)
  : costmap_ros_(name,tf_listener_)
{
  ros::NodeHandle private_nh("~/"+name);
  XmlRpc::XmlRpcValue my_list;
  private_nh.getParam("plugins", my_list);
  ROS_INFO_STREAM("xml_input for plugins = "<<my_list.toXml());

  ROS_INFO_STREAM("map_topic = " << private_nh.param("static/map_topic",std::string("")));

  costmap_ros_.setUnpaddedRobotFootprint(footprint);

  ///@todo is this needed?
  //start...
  costmap_ros_.start();
}
void CostmapCloner::tick() {

  costmap_ros_.updateMap(); //this needs to happen before we use the costmap!
}
costmap_2d::Costmap2DROS* CostmapCloner::get_ptr() {

  return &costmap_ros_;
}



struct DerivedDetail {
  DerivedDetail(const std::vector<geometry_msgs::Point> &footprint,
                std::string ns) : cm_cloner_(footprint,ns) {}

protected:
  CostmapCloner cm_cloner_;
};

///Maybe it's really dangerous to call the base constructor
/// after something else!!!
/// Will use "base-from-member idiom"
/// https://stackoverflow.com/questions/5894940/calling-the-constructor-of-the-base-class-after-some-other-instructions-in-c
class ClonedCostmapColChecker : public DerivedDetail, public MoveBaseCostmapChecker {

public:
  ClonedCostmapColChecker(const std::vector<geometry_msgs::Point> &footprint, std::string ns) :
    DerivedDetail(footprint,ns),
    MoveBaseCostmapChecker(cm_cloner_.get_ptr()) {}

  void prepare() {
    cm_cloner_.tick();

  }

  costmap_2d::Costmap2DROS* get_ptr() {
    return costmap_ros_;
  }

  void print_info() {
    swap_pointers();

    bool all_clear = true;
    unsigned char max_val = 0;
    //Check if the map is empty (this would be really bad)
    for(unsigned int i=0; i<costmap_ros_->getCostmap()->getSizeInCellsX(); ++i) {
      for(unsigned int j=0; j<costmap_ros_->getCostmap()->getSizeInCellsY(); ++j) {
        unsigned int  index = costmap_ros_->getCostmap()->getIndex(i,j);
        all_clear &=
            costmap_ros_->getCostmap()->getCharMap()[index] < 128;
        if(costmap_ros_->getCostmap()->getCharMap()[index] > max_val)
          max_val = costmap_ros_->getCostmap()->getCharMap()[index];
      }
    }
    if(all_clear) {
      ROS_WARN_STREAM("Costmap ( sz = " << costmap_ros_->getCostmap()->getSizeInCellsX()
                      << " X " << costmap_ros_->getCostmap()->getSizeInCellsY() << " ) completely clear! Max val = " << (int)max_val);
    }

    std::stringstream ss;
    ss << "sz in meters X = " <<
          cm_cloner_.get_ptr()->getCostmap()->getSizeInMetersX();
    ss << " sz in meters Y = " <<
          cm_cloner_.get_ptr()->getCostmap()->getSizeInMetersY();
    ss << "cm_cloner_.ptr = " << std::hex << cm_cloner_.get_ptr();
    ss << " own_ptr = " << std::hex << costmap_ros_;
    ROS_INFO_STREAM(ss.str());
  }

};


TwoDCollisionCheckerI * get_collision_checker_from_topic(std::string robot_frame,
                                                         std::string costmap_base_topic,
                                                         double publish_freq,
                                                         std::string cm_data_type) {

  //Wait for costmap to figure out frame
  //Wait for footprint
  std::string cm_topic = costmap_base_topic + "/costmap";
  std::string fp_topic = costmap_base_topic + "/footprint";

  cpp_utils::MsgBuffer<nav_msgs::OccupancyGrid,nav_msgs::OccupancyGridConstPtr>
      cm_buffer(cm_topic);

  cpp_utils::MsgBuffer<geometry_msgs::PolygonStamped,geometry_msgs::PolygonStampedConstPtr>
      fp_buffer(fp_topic);

  //ROS_INFO_STREAM("Waiting for data on " << cm_topic << " and " << fp_topic);
  
  tf::TransformListener tf_listen;

  ros::Rate r(20.0);
  while(ros::ok() && !(cm_buffer.have_msg && fp_buffer.have_msg) ) {
    ros::spinOnce();
    r.sleep();
  }
  if(!ros::ok()) {
    return NULL;
  }

  //important to do this, otherwise the costmap will not get a new map when requesting..
  cm_buffer.sub.shutdown();
  fp_buffer.sub.shutdown();

  //get a more or less random name
  std::stringstream ss;
  ss << "cm_" << (long int)(10*ros::Time::now().toSec());
  std::string ns = ss.str();

  //Set parameters
  ros::NodeHandle cm_nh("~/"+ns);
  cm_nh.setParam("publish_frequency",publish_freq);
  cm_nh.setParam("global_frame",    cm_buffer.last_msg.header.frame_id);
  cm_nh.setParam("robot_base_frame",robot_frame);
  cm_nh.setParam("width", (int) cm_buffer.last_msg.info.width);
  cm_nh.setParam("height", (int) cm_buffer.last_msg.info.height);
  cm_nh.setParam("resolution", cm_buffer.last_msg.info.resolution);
  cm_nh.setParam("footprint_topic", "/dummy/topic/"+ns);

  //In more readable format: [{'name':'static','type':'planner_utils::CloneLayer'}]
  std::string xml_for_plugins("<value><array><data><value><struct><member><name>name</name><value>static</value></member><member><name>type</name><value>planner_utils::CloneLayer</value></member></struct></value></data></array></value>");

  XmlRpc::XmlRpcValue plugin_list;

  //This is the hardest part...
  //how the hell do you populate this shit...

  int dummy_offset=0;
  plugin_list.fromXml(xml_for_plugins,&dummy_offset);


  //ROS_INFO_STREAM("plugin_list.xml = " << plugin_list.toXml());

  cm_nh.setParam("plugins",plugin_list);


  //get it again and try...
  XmlRpc::XmlRpcValue plugin_list_from_param;
  cm_nh.getParam("plugins", plugin_list_from_param);

  //ROS_INFO_STREAM("plugin_list_from_param.xml = " << plugin_list_from_param.toXml());

  cm_nh.setParam("static/map_topic",cm_topic);
  cm_nh.setParam("static/subscribe_to_updates",true);
  cm_nh.setParam("static/use_maximum",true);
  cm_nh.setParam("static/costmap_interpretation",cm_data_type);

  //Let's set the footprint
  //We assume that the footprint should be expressed in the robot frame
  std::vector<geometry_msgs::Point> footprint;
  std::string footprint_frame = fp_buffer.last_msg.header.frame_id;
 
  tf::StampedTransform transform;
  tf_listen.waitForTransform(robot_frame,footprint_frame,ros::Time(0),ros::Duration(10.0));
  tf_listen.lookupTransform(robot_frame,footprint_frame,ros::Time(0),transform);

  for(auto const & p_fp : fp_buffer.last_msg.polygon.points) {
    geometry_msgs::Point p;
    p.x = p_fp.x;
    p.y = p_fp.y;
    p.z = p_fp.z;

    //transform to robot frame
    tf::Point tf_p;
    tf::pointMsgToTF(p,tf_p);
    tf_p = transform*tf_p;
    tf::pointTFToMsg(tf_p,p);

    footprint.push_back(p);
  }

  //ROS_INFO("Have data, starting cloning...");

  planner_utils::ClonedCostmapColChecker * col_checker =
      new planner_utils::ClonedCostmapColChecker(footprint,ns);



  ///@todo think about deleting these params when the object is destroyed...
  return col_checker;
}

}//end namespace
