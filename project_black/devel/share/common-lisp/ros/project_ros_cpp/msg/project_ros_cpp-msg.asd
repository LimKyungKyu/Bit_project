
(cl:in-package :asdf)

(defsystem "project_ros_cpp-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "clean_point" :depends-on ("_package_clean_point"))
    (:file "_package_clean_point" :depends-on ("_package"))
    (:file "get_degree" :depends-on ("_package_get_degree"))
    (:file "_package_get_degree" :depends-on ("_package"))
    (:file "nano_control" :depends-on ("_package_nano_control"))
    (:file "_package_nano_control" :depends-on ("_package"))
    (:file "step_one_flag" :depends-on ("_package_step_one_flag"))
    (:file "_package_step_one_flag" :depends-on ("_package"))
  ))