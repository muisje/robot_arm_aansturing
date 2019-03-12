cmake_minimum_required(VERSION 2.8.3)
project(robot_arm_aansturing)

find_package(catkin REQUIRED COMPONENTS
  genmsg
  actionlib
  actionlib_msgs
  roscpp
  rospy
)

add_action_files(
  DIRECTORY action
  FILES setPose.action
)

add_action_files(
  DIRECTORY action
  FILES setCostumPose.action
)

generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp rospy actionlib_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

AUX_SOURCE_DIRECTORY(src/robot_arm SOURCE_ROBOT_ARM)
add_executable(robot_arm ${SOURCE_ROBOT_ARM})
target_link_libraries(robot_arm ${catkin_LIBRARIES})

add_dependencies(
  robot_arm
  ${robot_arm_aansturing_EXPORTED_TARGETS}
)

AUX_SOURCE_DIRECTORY(src/robot_arm_controller SOURCE_ROBOT_ARM_CONTROLLER)
add_executable(robot_arm_controller ${SOURCE_ROBOT_ARM_CONTROLLER})
target_link_libraries(robot_arm_controller ${catkin_LIBRARIES})

add_dependencies(
  robot_arm_controller
  ${robot_arm_aansturing_EXPORTED_TARGETS}
)