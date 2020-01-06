; Auto-generated. Do not edit!


(cl:in-package project_ros_cpp-msg)


;//! \htmlinclude step_one_flag.msg.html

(cl:defclass <step_one_flag> (roslisp-msg-protocol:ros-message)
  ((done_flag
    :reader done_flag
    :initarg :done_flag
    :type cl:integer
    :initform 0))
)

(cl:defclass step_one_flag (<step_one_flag>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <step_one_flag>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'step_one_flag)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name project_ros_cpp-msg:<step_one_flag> is deprecated: use project_ros_cpp-msg:step_one_flag instead.")))

(cl:ensure-generic-function 'done_flag-val :lambda-list '(m))
(cl:defmethod done_flag-val ((m <step_one_flag>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader project_ros_cpp-msg:done_flag-val is deprecated.  Use project_ros_cpp-msg:done_flag instead.")
  (done_flag m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <step_one_flag>) ostream)
  "Serializes a message object of type '<step_one_flag>"
  (cl:let* ((signed (cl:slot-value msg 'done_flag)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <step_one_flag>) istream)
  "Deserializes a message object of type '<step_one_flag>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'done_flag) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<step_one_flag>)))
  "Returns string type for a message object of type '<step_one_flag>"
  "project_ros_cpp/step_one_flag")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'step_one_flag)))
  "Returns string type for a message object of type 'step_one_flag"
  "project_ros_cpp/step_one_flag")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<step_one_flag>)))
  "Returns md5sum for a message object of type '<step_one_flag>"
  "17baec0563bbecdba8661f601b44ff3e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'step_one_flag)))
  "Returns md5sum for a message object of type 'step_one_flag"
  "17baec0563bbecdba8661f601b44ff3e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<step_one_flag>)))
  "Returns full string definition for message of type '<step_one_flag>"
  (cl:format cl:nil "int32 done_flag~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'step_one_flag)))
  "Returns full string definition for message of type 'step_one_flag"
  (cl:format cl:nil "int32 done_flag~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <step_one_flag>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <step_one_flag>))
  "Converts a ROS message object to a list"
  (cl:list 'step_one_flag
    (cl:cons ':done_flag (done_flag msg))
))
