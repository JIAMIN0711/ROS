# Install script for directory: /home/lianchuang/catkin_ws/src/tf2_web_republisher-develop

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/lianchuang/catkin_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tf2_web_republisher/action" TYPE FILE FILES "/home/lianchuang/catkin_ws/src/tf2_web_republisher-develop/action/TFSubscription.action")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tf2_web_republisher/msg" TYPE FILE FILES
    "/home/lianchuang/catkin_ws/devel/share/tf2_web_republisher/msg/TFSubscriptionAction.msg"
    "/home/lianchuang/catkin_ws/devel/share/tf2_web_republisher/msg/TFSubscriptionActionGoal.msg"
    "/home/lianchuang/catkin_ws/devel/share/tf2_web_republisher/msg/TFSubscriptionActionResult.msg"
    "/home/lianchuang/catkin_ws/devel/share/tf2_web_republisher/msg/TFSubscriptionActionFeedback.msg"
    "/home/lianchuang/catkin_ws/devel/share/tf2_web_republisher/msg/TFSubscriptionGoal.msg"
    "/home/lianchuang/catkin_ws/devel/share/tf2_web_republisher/msg/TFSubscriptionResult.msg"
    "/home/lianchuang/catkin_ws/devel/share/tf2_web_republisher/msg/TFSubscriptionFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tf2_web_republisher/services" TYPE FILE FILES "/home/lianchuang/catkin_ws/src/tf2_web_republisher-develop/services/RepublishTFs.srv")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tf2_web_republisher/msg" TYPE FILE FILES "/home/lianchuang/catkin_ws/src/tf2_web_republisher-develop/msg/TFArray.msg")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tf2_web_republisher/cmake" TYPE FILE FILES "/home/lianchuang/catkin_ws/build/tf2_web_republisher-develop/catkin_generated/installspace/tf2_web_republisher-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/lianchuang/catkin_ws/devel/include/tf2_web_republisher")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/lianchuang/catkin_ws/devel/share/roseus/ros/tf2_web_republisher")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/lianchuang/catkin_ws/devel/share/common-lisp/ros/tf2_web_republisher")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/lianchuang/catkin_ws/devel/share/gennodejs/ros/tf2_web_republisher")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/lianchuang/catkin_ws/devel/lib/python2.7/dist-packages/tf2_web_republisher")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/lianchuang/catkin_ws/devel/lib/python2.7/dist-packages/tf2_web_republisher")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/lianchuang/catkin_ws/build/tf2_web_republisher-develop/catkin_generated/installspace/tf2_web_republisher.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tf2_web_republisher/cmake" TYPE FILE FILES "/home/lianchuang/catkin_ws/build/tf2_web_republisher-develop/catkin_generated/installspace/tf2_web_republisher-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tf2_web_republisher/cmake" TYPE FILE FILES
    "/home/lianchuang/catkin_ws/build/tf2_web_republisher-develop/catkin_generated/installspace/tf2_web_republisherConfig.cmake"
    "/home/lianchuang/catkin_ws/build/tf2_web_republisher-develop/catkin_generated/installspace/tf2_web_republisherConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tf2_web_republisher" TYPE FILE FILES "/home/lianchuang/catkin_ws/src/tf2_web_republisher-develop/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/tf2_web_republisher/tf2_web_republisher" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/tf2_web_republisher/tf2_web_republisher")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/tf2_web_republisher/tf2_web_republisher"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/tf2_web_republisher" TYPE EXECUTABLE FILES "/home/lianchuang/catkin_ws/devel/lib/tf2_web_republisher/tf2_web_republisher")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/tf2_web_republisher/tf2_web_republisher" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/tf2_web_republisher/tf2_web_republisher")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/tf2_web_republisher/tf2_web_republisher"
         OLD_RPATH "/opt/ros/kinetic/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/tf2_web_republisher/tf2_web_republisher")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tf2_web_republisher" TYPE DIRECTORY FILES "/home/lianchuang/catkin_ws/src/tf2_web_republisher-develop/include/" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.hpp$")
endif()

