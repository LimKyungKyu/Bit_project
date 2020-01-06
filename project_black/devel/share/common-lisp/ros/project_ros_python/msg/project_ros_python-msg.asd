
(cl:in-package :asdf)

(defsystem "project_ros_python-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "get_degree" :depends-on ("_package_get_degree"))
    (:file "_package_get_degree" :depends-on ("_package"))
    (:file "nano_control" :depends-on ("_package_nano_control"))
    (:file "_package_nano_control" :depends-on ("_package"))
  ))