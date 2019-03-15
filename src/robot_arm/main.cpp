#include "SSC32U.hpp"
#include "AL5D.hpp"
#include "ArmOffset.hpp"
#include "Controller.hpp"
#include <ros/ros.h>
#include <chrono>
#include <thread>
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 

// Standard C++ entry point
using namespace std::chrono_literals;


int main(int argc, char **argv)
{
    ros::init(argc,argv,"robot");
    ros::start();

    std::map<e_joint, Range> jointRanges = boost::assign::map_list_of
    (e_joint::BASE, Range{-90, 0}) (e_joint::SHOULDER, Range{-30, 90}) (e_joint::ELBOW, Range{0, 135})
    (e_joint::WRIST, Range{-90, 90}) (e_joint::WRIST_ROTATE, Range{-90, 90});


    //If user used a argument for the serial 
    SSC32U servoController("/dev/ttyUSB0", std::stoi(argv[1]));
    Controller c("pose_action","costum_pose_action",servoController,jointRanges, ArmOffset::ROBOT_2);
  
    ROS_INFO_STREAM("Hello, robot arm!");
    ros::spin();// Stop the node's resources

    // Exit tranquillyret
    return 0;
}