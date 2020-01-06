; Auto-generated. Do not edit!


(cl:in-package project_ros_cpp-msg)


;//! \htmlinclude clean_point.msg.html

(cl:defclass <clean_point> (roslisp-msg-protocol:ros-message)
  ((clean_data
    :reader clean_data
    :initarg :clean_data
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0))
   (max_gird_point
    :reader max_gird_point
    :initarg :max_gird_point
    :type cl:integer
    :initform 0))
)

(cl:defclass clean_point (<clean_point>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <clean_point>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'clean_point)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name project_ros_cpp-msg:<clean_point> is deprecated: use project_ros_cpp-msg:clean_point instead.")))

(cl:ensure-generic-function 'clean_data-val :lambda-list '(m))
(cl:defmethod clean_data-val ((m <clean_point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader project_ros_cpp-msg:clean_data-val is deprecated.  Use project_ros_cpp-msg:clean_data instead.")
  (clean_data m))

(cl:ensure-generic-function 'max_gird_point-val :lambda-list '(m))
(cl:defmethod max_gird_point-val ((m <clean_point>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader project_ros_cpp-msg:max_gird_point-val is deprecated.  Use project_ros_cpp-msg:max_gird_point instead.")
  (max_gird_point m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <clean_point>) ostream)
  "Serializes a message object of type '<clean_point>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'clean_data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'clean_data))
  (cl:let* ((signed (cl:slot-value msg 'max_gird_point)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <clean_point>) istream)
  "Deserializes a message object of type '<clean_point>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'clean_data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'clean_data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296)))))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'max_gird_point) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<clean_point>)))
  "Returns string type for a message object of type '<clean_point>"
  "project_ros_cpp/clean_point")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'clean_point)))
  "Returns string type for a message object of type 'clean_point"
  "project_ros_cpp/clean_point")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<clean_point>)))
  "Returns md5sum for a message object of type '<clean_point>"
  "fc3d368272e33463cb6bcfa0567b445f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'clean_point)))
  "Returns md5sum for a message object of type 'clean_point"
  "fc3d368272e33463cb6bcfa0567b445f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<clean_point>)))
  "Returns full string definition for message of type '<clean_point>"
  (cl:format cl:nil "int32[] clean_data~%int32 max_gird_point~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'clean_point)))
  "Returns full string definition for message of type 'clean_point"
  (cl:format cl:nil "int32[] clean_data~%int32 max_gird_point~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <clean_point>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'clean_data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <clean_point>))
  "Converts a ROS message object to a list"
  (cl:list 'clean_point
    (cl:cons ':clean_data (clean_data msg))
    (cl:cons ':max_gird_point (max_gird_point msg))
))
