;; Auto-generated. Do not edit!


(when (boundp 'autoware_config_msgs::ConfigDecisionMaker)
  (if (not (find-package "AUTOWARE_CONFIG_MSGS"))
    (make-package "AUTOWARE_CONFIG_MSGS"))
  (shadow 'ConfigDecisionMaker (find-package "AUTOWARE_CONFIG_MSGS")))
(unless (find-package "AUTOWARE_CONFIG_MSGS::CONFIGDECISIONMAKER")
  (make-package "AUTOWARE_CONFIG_MSGS::CONFIGDECISIONMAKER"))

(in-package "ROS")
;;//! \htmlinclude ConfigDecisionMaker.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass autoware_config_msgs::ConfigDecisionMaker
  :super ros::object
  :slots (_header _auto_mission_reload _auto_engage _auto_mission_change _use_fms _disuse_vector_map _num_of_steer_behind _change_threshold_dist _change_threshold_angle _goal_threshold_dist _goal_threshold_vel _stopped_vel ))

(defmethod autoware_config_msgs::ConfigDecisionMaker
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:auto_mission_reload __auto_mission_reload) nil)
    ((:auto_engage __auto_engage) nil)
    ((:auto_mission_change __auto_mission_change) nil)
    ((:use_fms __use_fms) nil)
    ((:disuse_vector_map __disuse_vector_map) nil)
    ((:num_of_steer_behind __num_of_steer_behind) 0)
    ((:change_threshold_dist __change_threshold_dist) 0.0)
    ((:change_threshold_angle __change_threshold_angle) 0.0)
    ((:goal_threshold_dist __goal_threshold_dist) 0.0)
    ((:goal_threshold_vel __goal_threshold_vel) 0.0)
    ((:stopped_vel __stopped_vel) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _auto_mission_reload __auto_mission_reload)
   (setq _auto_engage __auto_engage)
   (setq _auto_mission_change __auto_mission_change)
   (setq _use_fms __use_fms)
   (setq _disuse_vector_map __disuse_vector_map)
   (setq _num_of_steer_behind (round __num_of_steer_behind))
   (setq _change_threshold_dist (float __change_threshold_dist))
   (setq _change_threshold_angle (float __change_threshold_angle))
   (setq _goal_threshold_dist (float __goal_threshold_dist))
   (setq _goal_threshold_vel (float __goal_threshold_vel))
   (setq _stopped_vel (float __stopped_vel))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:auto_mission_reload
   (&optional __auto_mission_reload)
   (if __auto_mission_reload (setq _auto_mission_reload __auto_mission_reload)) _auto_mission_reload)
  (:auto_engage
   (&optional __auto_engage)
   (if __auto_engage (setq _auto_engage __auto_engage)) _auto_engage)
  (:auto_mission_change
   (&optional __auto_mission_change)
   (if __auto_mission_change (setq _auto_mission_change __auto_mission_change)) _auto_mission_change)
  (:use_fms
   (&optional __use_fms)
   (if __use_fms (setq _use_fms __use_fms)) _use_fms)
  (:disuse_vector_map
   (&optional __disuse_vector_map)
   (if __disuse_vector_map (setq _disuse_vector_map __disuse_vector_map)) _disuse_vector_map)
  (:num_of_steer_behind
   (&optional __num_of_steer_behind)
   (if __num_of_steer_behind (setq _num_of_steer_behind __num_of_steer_behind)) _num_of_steer_behind)
  (:change_threshold_dist
   (&optional __change_threshold_dist)
   (if __change_threshold_dist (setq _change_threshold_dist __change_threshold_dist)) _change_threshold_dist)
  (:change_threshold_angle
   (&optional __change_threshold_angle)
   (if __change_threshold_angle (setq _change_threshold_angle __change_threshold_angle)) _change_threshold_angle)
  (:goal_threshold_dist
   (&optional __goal_threshold_dist)
   (if __goal_threshold_dist (setq _goal_threshold_dist __goal_threshold_dist)) _goal_threshold_dist)
  (:goal_threshold_vel
   (&optional __goal_threshold_vel)
   (if __goal_threshold_vel (setq _goal_threshold_vel __goal_threshold_vel)) _goal_threshold_vel)
  (:stopped_vel
   (&optional __stopped_vel)
   (if __stopped_vel (setq _stopped_vel __stopped_vel)) _stopped_vel)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; bool _auto_mission_reload
    1
    ;; bool _auto_engage
    1
    ;; bool _auto_mission_change
    1
    ;; bool _use_fms
    1
    ;; bool _disuse_vector_map
    1
    ;; uint32 _num_of_steer_behind
    4
    ;; float64 _change_threshold_dist
    8
    ;; float64 _change_threshold_angle
    8
    ;; float64 _goal_threshold_dist
    8
    ;; float64 _goal_threshold_vel
    8
    ;; float64 _stopped_vel
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; bool _auto_mission_reload
       (if _auto_mission_reload (write-byte -1 s) (write-byte 0 s))
     ;; bool _auto_engage
       (if _auto_engage (write-byte -1 s) (write-byte 0 s))
     ;; bool _auto_mission_change
       (if _auto_mission_change (write-byte -1 s) (write-byte 0 s))
     ;; bool _use_fms
       (if _use_fms (write-byte -1 s) (write-byte 0 s))
     ;; bool _disuse_vector_map
       (if _disuse_vector_map (write-byte -1 s) (write-byte 0 s))
     ;; uint32 _num_of_steer_behind
       (write-long _num_of_steer_behind s)
     ;; float64 _change_threshold_dist
       (sys::poke _change_threshold_dist (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _change_threshold_angle
       (sys::poke _change_threshold_angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _goal_threshold_dist
       (sys::poke _goal_threshold_dist (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _goal_threshold_vel
       (sys::poke _goal_threshold_vel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _stopped_vel
       (sys::poke _stopped_vel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; bool _auto_mission_reload
     (setq _auto_mission_reload (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _auto_engage
     (setq _auto_engage (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _auto_mission_change
     (setq _auto_mission_change (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _use_fms
     (setq _use_fms (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _disuse_vector_map
     (setq _disuse_vector_map (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; uint32 _num_of_steer_behind
     (setq _num_of_steer_behind (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _change_threshold_dist
     (setq _change_threshold_dist (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _change_threshold_angle
     (setq _change_threshold_angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _goal_threshold_dist
     (setq _goal_threshold_dist (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _goal_threshold_vel
     (setq _goal_threshold_vel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _stopped_vel
     (setq _stopped_vel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get autoware_config_msgs::ConfigDecisionMaker :md5sum-) "adfaf802f5ca35bf03b4eb5191ba9782")
(setf (get autoware_config_msgs::ConfigDecisionMaker :datatype-) "autoware_config_msgs/ConfigDecisionMaker")
(setf (get autoware_config_msgs::ConfigDecisionMaker :definition-)
      "Header header
bool auto_mission_reload
bool auto_engage
bool auto_mission_change
bool use_fms
bool disuse_vector_map
uint32 num_of_steer_behind
float64 change_threshold_dist
float64 change_threshold_angle
float64 goal_threshold_dist
float64 goal_threshold_vel
float64 stopped_vel

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

")



(provide :autoware_config_msgs/ConfigDecisionMaker "adfaf802f5ca35bf03b4eb5191ba9782")


