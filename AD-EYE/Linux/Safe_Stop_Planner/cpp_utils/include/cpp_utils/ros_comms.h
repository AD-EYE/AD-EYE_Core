#include <ros/ros.h>

namespace cpp_utils {

template <typename T, typename T_ptr>
class MsgBuffer {
public:
  bool have_msg;
  T last_msg;
  ros::Subscriber sub;

  void cb(T_ptr const & msg) {
    last_msg = *msg;
    have_msg = true;
  }

  MsgBuffer(std::string topic) {
    ros::NodeHandle nh;
    have_msg = false;
    sub = nh.subscribe(topic,1,&MsgBuffer::cb,this);
  }
};
}
