# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "project_ros_python: 2 messages, 0 services")

set(MSG_I_FLAGS "-Iproject_ros_python:/home/jetbot/project_black/src/project_ros_python/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(project_ros_python_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/jetbot/project_black/src/project_ros_python/msg/nano_control.msg" NAME_WE)
add_custom_target(_project_ros_python_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "project_ros_python" "/home/jetbot/project_black/src/project_ros_python/msg/nano_control.msg" ""
)

get_filename_component(_filename "/home/jetbot/project_black/src/project_ros_python/msg/get_degree.msg" NAME_WE)
add_custom_target(_project_ros_python_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "project_ros_python" "/home/jetbot/project_black/src/project_ros_python/msg/get_degree.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(project_ros_python
  "/home/jetbot/project_black/src/project_ros_python/msg/nano_control.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/project_ros_python
)
_generate_msg_cpp(project_ros_python
  "/home/jetbot/project_black/src/project_ros_python/msg/get_degree.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/project_ros_python
)

### Generating Services

### Generating Module File
_generate_module_cpp(project_ros_python
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/project_ros_python
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(project_ros_python_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(project_ros_python_generate_messages project_ros_python_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jetbot/project_black/src/project_ros_python/msg/nano_control.msg" NAME_WE)
add_dependencies(project_ros_python_generate_messages_cpp _project_ros_python_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jetbot/project_black/src/project_ros_python/msg/get_degree.msg" NAME_WE)
add_dependencies(project_ros_python_generate_messages_cpp _project_ros_python_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(project_ros_python_gencpp)
add_dependencies(project_ros_python_gencpp project_ros_python_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS project_ros_python_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(project_ros_python
  "/home/jetbot/project_black/src/project_ros_python/msg/nano_control.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/project_ros_python
)
_generate_msg_eus(project_ros_python
  "/home/jetbot/project_black/src/project_ros_python/msg/get_degree.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/project_ros_python
)

### Generating Services

### Generating Module File
_generate_module_eus(project_ros_python
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/project_ros_python
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(project_ros_python_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(project_ros_python_generate_messages project_ros_python_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jetbot/project_black/src/project_ros_python/msg/nano_control.msg" NAME_WE)
add_dependencies(project_ros_python_generate_messages_eus _project_ros_python_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jetbot/project_black/src/project_ros_python/msg/get_degree.msg" NAME_WE)
add_dependencies(project_ros_python_generate_messages_eus _project_ros_python_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(project_ros_python_geneus)
add_dependencies(project_ros_python_geneus project_ros_python_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS project_ros_python_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(project_ros_python
  "/home/jetbot/project_black/src/project_ros_python/msg/nano_control.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/project_ros_python
)
_generate_msg_lisp(project_ros_python
  "/home/jetbot/project_black/src/project_ros_python/msg/get_degree.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/project_ros_python
)

### Generating Services

### Generating Module File
_generate_module_lisp(project_ros_python
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/project_ros_python
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(project_ros_python_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(project_ros_python_generate_messages project_ros_python_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jetbot/project_black/src/project_ros_python/msg/nano_control.msg" NAME_WE)
add_dependencies(project_ros_python_generate_messages_lisp _project_ros_python_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jetbot/project_black/src/project_ros_python/msg/get_degree.msg" NAME_WE)
add_dependencies(project_ros_python_generate_messages_lisp _project_ros_python_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(project_ros_python_genlisp)
add_dependencies(project_ros_python_genlisp project_ros_python_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS project_ros_python_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(project_ros_python
  "/home/jetbot/project_black/src/project_ros_python/msg/nano_control.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/project_ros_python
)
_generate_msg_nodejs(project_ros_python
  "/home/jetbot/project_black/src/project_ros_python/msg/get_degree.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/project_ros_python
)

### Generating Services

### Generating Module File
_generate_module_nodejs(project_ros_python
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/project_ros_python
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(project_ros_python_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(project_ros_python_generate_messages project_ros_python_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jetbot/project_black/src/project_ros_python/msg/nano_control.msg" NAME_WE)
add_dependencies(project_ros_python_generate_messages_nodejs _project_ros_python_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jetbot/project_black/src/project_ros_python/msg/get_degree.msg" NAME_WE)
add_dependencies(project_ros_python_generate_messages_nodejs _project_ros_python_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(project_ros_python_gennodejs)
add_dependencies(project_ros_python_gennodejs project_ros_python_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS project_ros_python_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(project_ros_python
  "/home/jetbot/project_black/src/project_ros_python/msg/nano_control.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/project_ros_python
)
_generate_msg_py(project_ros_python
  "/home/jetbot/project_black/src/project_ros_python/msg/get_degree.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/project_ros_python
)

### Generating Services

### Generating Module File
_generate_module_py(project_ros_python
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/project_ros_python
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(project_ros_python_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(project_ros_python_generate_messages project_ros_python_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jetbot/project_black/src/project_ros_python/msg/nano_control.msg" NAME_WE)
add_dependencies(project_ros_python_generate_messages_py _project_ros_python_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/jetbot/project_black/src/project_ros_python/msg/get_degree.msg" NAME_WE)
add_dependencies(project_ros_python_generate_messages_py _project_ros_python_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(project_ros_python_genpy)
add_dependencies(project_ros_python_genpy project_ros_python_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS project_ros_python_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/project_ros_python)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/project_ros_python
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(project_ros_python_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/project_ros_python)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/project_ros_python
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(project_ros_python_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/project_ros_python)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/project_ros_python
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(project_ros_python_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/project_ros_python)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/project_ros_python
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(project_ros_python_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/project_ros_python)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/project_ros_python\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/project_ros_python
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(project_ros_python_generate_messages_py std_msgs_generate_messages_py)
endif()
