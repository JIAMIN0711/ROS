// Generated by gencpp from file rosapi/GetParamNamesResponse.msg
// DO NOT EDIT!


#ifndef ROSAPI_MESSAGE_GETPARAMNAMESRESPONSE_H
#define ROSAPI_MESSAGE_GETPARAMNAMESRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace rosapi
{
template <class ContainerAllocator>
struct GetParamNamesResponse_
{
  typedef GetParamNamesResponse_<ContainerAllocator> Type;

  GetParamNamesResponse_()
    : names()  {
    }
  GetParamNamesResponse_(const ContainerAllocator& _alloc)
    : names(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  _names_type;
  _names_type names;




  typedef boost::shared_ptr< ::rosapi::GetParamNamesResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rosapi::GetParamNamesResponse_<ContainerAllocator> const> ConstPtr;

}; // struct GetParamNamesResponse_

typedef ::rosapi::GetParamNamesResponse_<std::allocator<void> > GetParamNamesResponse;

typedef boost::shared_ptr< ::rosapi::GetParamNamesResponse > GetParamNamesResponsePtr;
typedef boost::shared_ptr< ::rosapi::GetParamNamesResponse const> GetParamNamesResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::rosapi::GetParamNamesResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::rosapi::GetParamNamesResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace rosapi

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'rosapi': ['/home/lianchuang/catkin_ws/src/rosbridge_suite/rosapi/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::rosapi::GetParamNamesResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::rosapi::GetParamNamesResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rosapi::GetParamNamesResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rosapi::GetParamNamesResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rosapi::GetParamNamesResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rosapi::GetParamNamesResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::rosapi::GetParamNamesResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dc7ae3609524b18034e49294a4ce670e";
  }

  static const char* value(const ::rosapi::GetParamNamesResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xdc7ae3609524b180ULL;
  static const uint64_t static_value2 = 0x34e49294a4ce670eULL;
};

template<class ContainerAllocator>
struct DataType< ::rosapi::GetParamNamesResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "rosapi/GetParamNamesResponse";
  }

  static const char* value(const ::rosapi::GetParamNamesResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::rosapi::GetParamNamesResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string[] names\n\
";
  }

  static const char* value(const ::rosapi::GetParamNamesResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::rosapi::GetParamNamesResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.names);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetParamNamesResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::rosapi::GetParamNamesResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::rosapi::GetParamNamesResponse_<ContainerAllocator>& v)
  {
    s << indent << "names[]" << std::endl;
    for (size_t i = 0; i < v.names.size(); ++i)
    {
      s << indent << "  names[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.names[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROSAPI_MESSAGE_GETPARAMNAMESRESPONSE_H
