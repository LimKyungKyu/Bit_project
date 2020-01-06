;; Auto-generated. Do not edit!


(when (boundp 'project_ros_cpp::clean_point)
  (if (not (find-package "PROJECT_ROS_CPP"))
    (make-package "PROJECT_ROS_CPP"))
  (shadow 'clean_point (find-package "PROJECT_ROS_CPP")))
(unless (find-package "PROJECT_ROS_CPP::CLEAN_POINT")
  (make-package "PROJECT_ROS_CPP::CLEAN_POINT"))

(in-package "ROS")
;;//! \htmlinclude clean_point.msg.html


(defclass project_ros_cpp::clean_point
  :super ros::object
  :slots (_clean_data _max_gird_point ))

(defmethod project_ros_cpp::clean_point
  (:init
   (&key
    ((:clean_data __clean_data) (make-array 0 :initial-element 0 :element-type :integer))
    ((:max_gird_point __max_gird_point) 0)
    )
   (send-super :init)
   (setq _clean_data __clean_data)
   (setq _max_gird_point (round __max_gird_point))
   self)
  (:clean_data
   (&optional __clean_data)
   (if __clean_data (setq _clean_data __clean_data)) _clean_data)
  (:max_gird_point
   (&optional __max_gird_point)
   (if __max_gird_point (setq _max_gird_point __max_gird_point)) _max_gird_point)
  (:serialization-length
   ()
   (+
    ;; int32[] _clean_data
    (* 4    (length _clean_data)) 4
    ;; int32 _max_gird_point
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32[] _clean_data
     (write-long (length _clean_data) s)
     (dotimes (i (length _clean_data))
       (write-long (elt _clean_data i) s)
       )
     ;; int32 _max_gird_point
       (write-long _max_gird_point s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32[] _clean_data
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _clean_data (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _clean_data i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;; int32 _max_gird_point
     (setq _max_gird_point (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get project_ros_cpp::clean_point :md5sum-) "fc3d368272e33463cb6bcfa0567b445f")
(setf (get project_ros_cpp::clean_point :datatype-) "project_ros_cpp/clean_point")
(setf (get project_ros_cpp::clean_point :definition-)
      "int32[] clean_data
int32 max_gird_point

")



(provide :project_ros_cpp/clean_point "fc3d368272e33463cb6bcfa0567b445f")


