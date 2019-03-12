#include "SSC32U.hpp"
#include "AL5D.hpp"
#include "Controller.hpp"
#include <ros/ros.h>
#include <chrono>
#include <thread>

// Standard C++ entry point
using namespace std::chrono_literals;


int main(int argc, char **argv)
{
    ros::init(argc,argv,"robot");
    ros::start();

    Controller c("robot_arm","test");
    
    //If user used a argument for the serial 
    if(argc > 1)
    {
        SSC32U servoController("/dev/ttyUSB0", std::stoi(argv[1]));

        AL5D robotArm(servoController);

        robotArm.gotoPosition(e_position::PARK);
        std::this_thread::sleep_for(3s);
        
        robotArm.gotoPosition(e_position::READY, 0, 2300);
        std::this_thread::sleep_for(5s);
        
        robotArm.gotoPosition(e_position::STRAIGHT_UP, 0, 500);
        std::this_thread::sleep_for(5s);

        robotArm.gotoPosition(e_position::PARK, 0, 2300);
        std::this_thread::sleep_for(5s);
    }

    

    ROS_INFO_STREAM("Hello, robot arm!");
    ros::spin();// Stop the node's resources

    // Exit tranquillyret
    return 0;
}