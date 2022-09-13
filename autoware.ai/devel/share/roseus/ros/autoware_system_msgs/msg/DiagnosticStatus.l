;; Auto-generated. Do not edit!


(when (boundp 'autoware_system_msgs::DiagnosticStatus)
  (if (not (find-package "AUTOWARE_SYSTEM_MSGS"))
    (make-package "AUTOWARE_SYSTEM_MSGS"))
  (shadow 'DiagnosticStatus (find-package "AUTOWARE_SYSTEM_MSGS")))
(unless (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS")
  (make-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))

(in-package "ROS")
;;//! \htmlinclude DiagnosticStatus.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(intern "*UNDEFINED*" (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(shadow '*UNDEFINED* (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(defconstant autoware_system_msgs::DiagnosticStatus::*UNDEFINED* 0)
(intern "*OUT_OF_RANGE*" (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(shadow '*OUT_OF_RANGE* (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(defconstant autoware_system_msgs::DiagnosticStatus::*OUT_OF_RANGE* 1)
(intern "*RATE_IS_SLOW*" (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(shadow '*RATE_IS_SLOW* (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(defconstant autoware_system_msgs::DiagnosticStatus::*RATE_IS_SLOW* 2)
(intern "*HARDWARE*" (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(shadow '*HARDWARE* (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(defconstant autoware_system_msgs::DiagnosticStatus::*HARDWARE* 255)
(intern "*OK*" (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(shadow '*OK* (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(defconstant autoware_system_msgs::DiagnosticStatus::*OK* 1)
(intern "*WARN*" (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(shadow '*WARN* (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(defconstant autoware_system_msgs::DiagnosticStatus::*WARN* 2)
(intern "*ERROR*" (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(shadow '*ERROR* (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(defconstant autoware_system_msgs::DiagnosticStatus::*ERROR* 3)
(intern "*FATAL*" (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(shadow '*FATAL* (find-package "AUTOWARE_SYSTEM_MSGS::DIAGNOSTICSTATUS"))
(defconstant autoware_system_msgs::DiagnosticStatus::*FATAL* 4)
(defclass autoware_system_msgs::DiagnosticStatus
  :super ros::object
  :slots (_header _key _value _description _type _level ))

(defmethod autoware_system_msgs::DiagnosticStatus
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:key __key) "")
    ((:value __value) "")
    ((:description __description) "")
    ((:type __type) 0)
    ((:level __level) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _key (string __key))
   (setq _value (string __value))
   (setq _description (string __description))
   (setq _type (round __type))
   (setq _level (round __level))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:key
   (&optional __key)
   (if __key (setq _key __key)) _key)
  (:value
   (&optional __value)
   (if __value (setq _value __value)) _value)
  (:description
   (&optional __description)
   (if __description (setq _description __description)) _description)
  (:type
   (&optional __type)
   (if __type (setq _type __type)) _type)
  (:level
   (&optional __level)
   (if __level (setq _level __level)) _level)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string _key
    4 (length _key)
    ;; string _value
    4 (length _value)
    ;; string _description
    4 (length _description)
    ;; uint8 _type
    1
    ;; uint8 _level
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string _key
       (write-long (length _key) s) (princ _key s)
     ;; string _value
       (write-long (length _value) s) (princ _value s)
     ;; string _description
       (write-long (length _description) s) (princ _description s)
     ;; uint8 _type
       (write-byte _type s)
     ;; uint8 _level
       (write-byte _level s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string _key
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _key (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _value
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _value (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _description
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _description (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; uint8 _type
     (setq _type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _level
     (setq _level (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get autoware_system_msgs::DiagnosticStatus :md5sum-) "6c3db7fb4a3aac47a2b0c51e9b4e3539")
(setf (get autoware_system_msgs::DiagnosticStatus :datatype-) "autoware_system_msgs/DiagnosticStatus")
(setf (get autoware_system_msgs::DiagnosticStatus :definition-)
      "Header header

string key

string value

string description

uint8 UNDEFINED = 0

uint8 type
uint8 OUT_OF_RANGE = 1
uint8 RATE_IS_SLOW = 2
uint8 HARDWARE = 255

uint8 level
uint8 OK = 1
uint8 WARN = 2
uint8 ERROR = 3
uint8 FATAL = 4
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



(provide :autoware_system_msgs/DiagnosticStatus "6c3db7fb4a3aac47a2b0c51e9b4e3539")


