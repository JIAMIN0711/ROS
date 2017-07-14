// Generated by gencpp from file arbotix_msgs/SetSpeed.msg
// DO NOT EDIT!


#ifndef ARBOTIX_MSGS_MESSAGE_SETSPEED_H
#define ARBOTIX_MSGS_MESSAGE_SETSPEED_H

#include <ros/service_traits.h>


#include <arbotix_msgs/SetSpeedRequest.h>
#include <arbotix_msgs/SetSpeedResponse.h>


namespace arbotix_msgs
{

struct SetSpeed
{

typedef SetSpeedRequest Request;
typedef SetSpeedResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct SetSpeed
} // namespace arbotix_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::arbotix_msgs::SetSpeed > {
  static const char* value()
  {
    return "4641bb0523a3557209606d9bd91ce33a";
  }

  static const char* value(const ::arbotix_msgs::SetSpeed&) { return value(); }
};

template<>
struct DataType< ::arbotix_msgs::SetSpeed > {
  static const char* value()
  {
    return "arbotix_msgs/SetSpeed";
  }

  static const char* value(const ::arbotix_msgs::SetSpeed&) { return value(); }
};


// service_traits::MD5Sum< ::arbotix_msgs::SetSpeedRequest> should match 
// service_traits::MD5Sum< ::arbotix_msgs::SetSpeed > 
template<>
struct MD5Sum< ::arbotix_msgs::SetSpeedRequest>
{
  static const char* value()
  {
    return MD5Sum< ::arbotix_msgs::SetSpeed >::value();
  }
  static const char* value(const ::arbotix_msgs::SetSpeedRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::arbotix_msgs::SetSpeedRequest> should match 
// service_traits::DataType< ::arbotix_msgs::SetSpeed > 
template<>
struct DataType< ::arbotix_msgs::SetSpeedRequest>
{
  static const char* value()
  {
    return DataType< ::arbotix_msgs::SetSpeed >::value();
  }
  static const char* value(const ::arbotix_msgs::SetSpeedRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::arbotix_msgs::SetSpeedResponse> should match 
// service_traits::MD5Sum< ::arbotix_msgs::SetSpeed > 
template<>
struct MD5Sum< ::arbotix_msgs::SetSpeedResponse>
{
  static const char* value()
  {
    return MD5Sum< ::arbotix_msgs::SetSpeed >::value();
  }
  static const char* value(const ::arbotix_msgs::SetSpeedResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::arbotix_msgs::SetSpeedResponse> should match 
// service_traits::DataType< ::arbotix_msgs::SetSpeed > 
template<>
struct DataType< ::arbotix_msgs::SetSpeedResponse>
{
  static const char* value()
  {
    return DataType< ::arbotix_msgs::SetSpeed >::value();
  }
  static const char* value(const ::arbotix_msgs::SetSpeedResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // ARBOTIX_MSGS_MESSAGE_SETSPEED_H
