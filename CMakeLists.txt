cmake_minimum_required(VERSION 2.8.3)
project(robot_arm_aansturing)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES beginner_tutorials
CATKIN_DEPENDS roscpp rospy
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(robot_arm src/robot_arm/main.cpp)
target_link_libraries(robot_arm ${catkin_LIBRARIES})

add_executable(robot_arm_controller src/robot_arm_controller/main.cpp)
target_link_libraries(robot_arm_controller ${catkin_LIBRARIES})
