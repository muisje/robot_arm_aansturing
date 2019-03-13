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

    Controller c("robot_arm","test");
    

    std::map<e_joint, Range> jointRanges = boost::assign::map_list_of
    (e_joint::BASE, Range{-90, 0}) (e_joint::SHOULDER, Range{-30, 90}) (e_joint::ELBOW, Range{0, 90})
    (e_joint::WRIST, Range{-90, 90}) (e_joint::WRIST_ROTATE, Range{-90, 90});

    //If user used a argument for the serial 
    
    
    SSC32U servoController("/dev/ttyUSB0", std::stoi(argv[1]));
    AL5D robotArm(servoController, jointRanges, ArmOffset::ROBOT_2);
    
    std::cout << "begin" << std::endl;
    robotArm.gotoPosition(POSITION_PRESET::PARK);
    std::this_thread::sleep_for(2s);
    
    std::cout << "ready" << std::endl;
    robotArm.gotoPosition(POSITION_PRESET::READY, 0, 2300);
    std::this_thread::sleep_for(5s);
    
    std::cout << "straight" << std::endl;
    robotArm.gotoPosition(POSITION_PRESET::STRAIGHT_UP, 0, 5000);
    std::this_thread::sleep_for(2s);

    std::cout << "stop" << std::endl;
    robotArm.stopAllMotorFunctions();
    std::this_thread::sleep_for(5s);

    std::cout << "straight" << std::endl;
    robotArm.gotoPosition(POSITION_PRESET::STRAIGHT_UP, 0, 1000);
    std::this_thread::sleep_for(2s);


    std::cout << "end" << std::endl;
    robotArm.gotoPosition(POSITION_PRESET::PARK, 0, 2300);
    std::this_thread::sleep_for(3s);
    

    ROS_INFO_STREAM("Hello, robot arm!");
    ros::spin();// Stop the node's resources

    // Exit tranquillyret
    return 0;
}