;; Auto-generated. Do not edit!


(when (boundp 'project_ros_python::nano_control)
  (if (not (find-package "PROJECT_ROS_PYTHON"))
    (make-package "PROJECT_ROS_PYTHON"))
  (shadow 'nano_control (find-package "PROJECT_ROS_PYTHON")))
(unless (find-package "PROJECT_ROS_PYTHON::NANO_CONTROL")
  (make-package "PROJECT_ROS_PYTHON::NANO_CONTROL"))

(in-package "ROS")
;;//! \htmlinclude nano_control.msg.html


(defclass project_ros_python::nano_control
  :super ros::object
  :slots (_move_message ))

(defmethod project_ros_python::nano_control
  (:init
   (&key
    ((:move_message __move_message) 0)
    )
   (send-super :init)
   (setq _move_message (round __move_message))
   self)
  (:move_message
   (&optional __move_message)
   (if __move_message (setq _move_message __move_message)) _move_message)
  (:serialization-length
   ()
   (+
    ;; int32 _move_message
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _move_message
       (write-long _move_message s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _move_message
     (setq _move_message (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get project_ros_python::nano_control :md5sum-) "09377968f5a8b50b28685fd8aea01579")
(setf (get project_ros_python::nano_control :datatype-) "project_ros_python/nano_control")
(setf (get project_ros_python::nano_control :definition-)
      "int32 move_message

")



(provide :project_ros_python/nano_control "09377968f5a8b50b28685fd8aea01579")


