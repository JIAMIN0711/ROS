execute_process(COMMAND "/home/lianchuang/catkin_ws/build/arbotix/arbotix_python/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/lianchuang/catkin_ws/build/arbotix/arbotix_python/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
