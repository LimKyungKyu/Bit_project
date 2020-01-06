// Generated by gencpp from file project_ros_python/nano_control.msg
// DO NOT EDIT!


#ifndef PROJECT_ROS_PYTHON_MESSAGE_NANO_CONTROL_H
#define PROJECT_ROS_PYTHON_MESSAGE_NANO_CONTROL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace project_ros_python
{
template <class ContainerAllocator>
struct nano_control_
{
  typedef nano_control_<ContainerAllocator> Type;

  nano_control_()
    : move_message(0)  {
    }
  nano_control_(const ContainerAllocator& _alloc)
    : move_message(0)  {
  (void)_alloc;
    }



   typedef int32_t _move_message_type;
  _move_message_type move_message;





  typedef boost::shared_ptr< ::project_ros_python::nano_control_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::project_ros_python::nano_control_<ContainerAllocator> const> ConstPtr;

}; // struct nano_control_

typedef ::project_ros_python::nano_control_<std::allocator<void> > nano_control;

typedef boost::shared_ptr< ::project_ros_python::nano_control > nano_controlPtr;
typedef boost::shared_ptr< ::project_ros_python::nano_control const> nano_controlConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::project_ros_python::nano_control_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::project_ros_python::nano_control_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace project_ros_python

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg'], 'project_ros_python': ['/home/jetbot/project_black/src/project_ros_python/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::project_ros_python::nano_control_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::project_ros_python::nano_control_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::project_ros_python::nano_control_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::project_ros_python::nano_control_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::project_ros_python::nano_control_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::project_ros_python::nano_control_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::project_ros_python::nano_control_<ContainerAllocator> >
{
  static const char* value()
  {
    return "09377968f5a8b50b28685fd8aea01579";
  }

  static const char* value(const ::project_ros_python::nano_control_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x09377968f5a8b50bULL;
  static const uint64_t static_value2 = 0x28685fd8aea01579ULL;
};

template<class ContainerAllocator>
struct DataType< ::project_ros_python::nano_control_<ContainerAllocator> >
{
  static const char* value()
  {
    return "project_ros_python/nano_control";
  }

  static const char* value(const ::project_ros_python::nano_control_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::project_ros_python::nano_control_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 move_message\n"
;
  }

  static const char* value(const ::project_ros_python::nano_control_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::project_ros_python::nano_control_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.move_message);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct nano_control_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::project_ros_python::nano_control_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::project_ros_python::nano_control_<ContainerAllocator>& v)
  {
    s << indent << "move_message: ";
    Printer<int32_t>::stream(s, indent + "  ", v.move_message);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PROJECT_ROS_PYTHON_MESSAGE_NANO_CONTROL_H