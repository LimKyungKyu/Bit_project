; Auto-generated. Do not edit!


(cl:in-package project_ros_python-msg)


;//! \htmlinclude nano_control.msg.html

(cl:defclass <nano_control> (roslisp-msg-protocol:ros-message)
  ((move_message
    :reader move_message
    :initarg :move_message
    :type cl:integer
    :initform 0))
)

(cl:defclass nano_control (<nano_control>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <nano_control>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'nano_control)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name project_ros_python-msg:<nano_control> is deprecated: use project_ros_python-msg:nano_control instead.")))

(cl:ensure-generic-function 'move_message-val :lambda-list '(m))
(cl:defmethod move_message-val ((m <nano_control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader project_ros_python-msg:move_message-val is deprecated.  Use project_ros_python-msg:move_message instead.")
  (move_message m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <nano_control>) ostream)
  "Serializes a message object of type '<nano_control>"
  (cl:let* ((signed (cl:slot-value msg 'move_message)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <nano_control>) istream)
  "Deserializes a message object of type '<nano_control>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'move_message) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<nano_control>)))
  "Returns string type for a message object of type '<nano_control>"
  "project_ros_python/nano_control")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'nano_control)))
  "Returns string type for a message object of type 'nano_control"
  "project_ros_python/nano_control")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<nano_control>)))
  "Returns md5sum for a message object of type '<nano_control>"
  "09377968f5a8b50b28685fd8aea01579")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'nano_control)))
  "Returns md5sum for a message object of type 'nano_control"
  "09377968f5a8b50b28685fd8aea01579")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<nano_control>)))
  "Returns full string definition for message of type '<nano_control>"
  (cl:format cl:nil "int32 move_message~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'nano_control)))
  "Returns full string definition for message of type 'nano_control"
  (cl:format cl:nil "int32 move_message~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <nano_control>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <nano_control>))
  "Converts a ROS message object to a list"
  (cl:list 'nano_control
    (cl:cons ':move_message (move_message msg))
))
