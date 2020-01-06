;; Auto-generated. Do not edit!


(when (boundp 'project_ros_cpp::step_one_flag)
  (if (not (find-package "PROJECT_ROS_CPP"))
    (make-package "PROJECT_ROS_CPP"))
  (shadow 'step_one_flag (find-package "PROJECT_ROS_CPP")))
(unless (find-package "PROJECT_ROS_CPP::STEP_ONE_FLAG")
  (make-package "PROJECT_ROS_CPP::STEP_ONE_FLAG"))

(in-package "ROS")
;;//! \htmlinclude step_one_flag.msg.html


(defclass project_ros_cpp::step_one_flag
  :super ros::object
  :slots (_done_flag ))

(defmethod project_ros_cpp::step_one_flag
  (:init
   (&key
    ((:done_flag __done_flag) 0)
    )
   (send-super :init)
   (setq _done_flag (round __done_flag))
   self)
  (:done_flag
   (&optional __done_flag)
   (if __done_flag (setq _done_flag __done_flag)) _done_flag)
  (:serialization-length
   ()
   (+
    ;; int32 _done_flag
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _done_flag
       (write-long _done_flag s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _done_flag
     (setq _done_flag (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get project_ros_cpp::step_one_flag :md5sum-) "17baec0563bbecdba8661f601b44ff3e")
(setf (get project_ros_cpp::step_one_flag :datatype-) "project_ros_cpp/step_one_flag")
(setf (get project_ros_cpp::step_one_flag :definition-)
      "int32 done_flag
")



(provide :project_ros_cpp/step_one_flag "17baec0563bbecdba8661f601b44ff3e")


