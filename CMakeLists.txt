cmake_minimum_required(VERSION 2.8.3)
project(robot_arm_aansturing)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  roscpp
  rospy
)


add_action_files(
  DIRECTORY action
  FILES setPose.action
)

generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs  # Or other packages containing msgs
)

catkin_package(
  CATKIN_DEPENDS actionlib_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES beginner_tutorials
CATKIN_DEPENDS roscpp rospy actionlib_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(robot_arm src/robot_arm/main.cpp src/robot_arm/SSC32U.cpp)
target_link_libraries(robot_arm ${catkin_LIBRARIES})

add_dependencies(
  robot_arm
  ${robot_arm_aansturing_EXPORTED_TARGETS}
)

add_executable(robot_arm_controller src/robot_arm_controller/main.cpp)
target_link_libraries(robot_arm_controller ${catkin_LIBRARIES})

add_dependencies(
  robot_arm_controller
  ${robot_arm_aansturing_EXPORTED_TARGETS}
)