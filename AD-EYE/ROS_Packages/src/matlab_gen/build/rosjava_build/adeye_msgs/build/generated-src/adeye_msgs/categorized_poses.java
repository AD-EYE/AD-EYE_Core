package adeye_msgs;

public interface categorized_poses extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "adeye_msgs/categorized_poses";
  static final java.lang.String _DEFINITION = "categorized_pose[] poses";
  static final boolean _IS_SERVICE = false;
  static final boolean _IS_ACTION = false;
  java.util.List<adeye_msgs.categorized_pose> getPoses();
  void setPoses(java.util.List<adeye_msgs.categorized_pose> value);
}
