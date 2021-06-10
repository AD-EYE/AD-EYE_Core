package adeye_msgs;

public interface categorized_pose extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "adeye_msgs/categorized_pose";
  static final java.lang.String _DEFINITION = "Header header\r\nint64 category\r\ngeometry_msgs/Pose pose";
  static final boolean _IS_SERVICE = false;
  static final boolean _IS_ACTION = false;
  std_msgs.Header getHeader();
  void setHeader(std_msgs.Header value);
  long getCategory();
  void setCategory(long value);
  geometry_msgs.Pose getPose();
  void setPose(geometry_msgs.Pose value);
}
