#include "SSC32U.hpp"
#include "AL5D.hpp"
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

    // CODE HENDRIK
    Controller c("robot_arm","test");
    

        std::map<e_joint, Range> jointRanges = boost::assign::map_list_of
    (e_joint::BASE, Range{-90, 0}) (e_joint::SHOULDER, Range{-30, 90}) (e_joint::ELBOW, Range{0, 90})
    (e_joint::WRIST, Range{-90, 90}) (e_joint::WRIST_ROTATE, Range{-90, 90});


    //If user used a argument for the serial 
    if(argc > 1)
    {
        SSC32U servoController("/dev/ttyUSB0", std::stoi(argv[1]));

        AL5D robotArm(servoController, jointRanges);

        robotArm.gotoPosition(e_position::PARK);
        std::this_thread::sleep_for(3s);
        
        robotArm.gotoPosition(e_position::READY, 0, 2300);
        std::this_thread::sleep_for(5s);
        
        robotArm.gotoPosition(e_position::STRAIGHT_UP, 0, 500);
        std::this_thread::sleep_for(5s);

        robotArm.gotoPosition(e_position::PARK, 0, 2300);
        std::this_thread::sleep_for(5s);
    }



    //      CODE MOURITS
    /*
    // SSC32U servoController("/dev/ttyUSB0");
    SSC32U servoController("/dev/ttyUSB1", 115200);

    // servoController.setPositionOffset(e_joint::ELBOW, 100);


    std::map<e_joint, Range> jointRanges = boost::assign::map_list_of
    (e_joint::BASE, Range{-90, 0}) (e_joint::SHOULDER, Range{-30, 90}) (e_joint::ELBOW, Range{0, 90})
    (e_joint::WRIST, Range{-90, 90}) (e_joint::WRIST_ROTATE, Range{-90, 90});


    AL5D robotArm(servoController, jointRanges);

    

    std::cout << "PARK" << std::endl;
    std::cout << robotArm.gotoPosition(e_position::PARK) << std::endl;
    std::this_thread::sleep_for(3s);
    
    std::cout << "READY" << std::endl;
    robotArm.gotoPosition(e_position::READY, 0, 2300);
    std::this_thread::sleep_for(5s);
    
    std::cout << "STRAIGHT_UP" << std::endl;
    robotArm.gotoPosition(e_position::STRAIGHT_UP, 0, 1000);
    std::this_thread::sleep_for(5s);
    
    std::cout << "IMPOSSIBLE" << std::endl;
    std::cout << robotArm.gotoPosition(POSITION_PRESET::IMPOSSIBLE, 0, 1000) << std::endl;
    std::this_thread::sleep_for(5s);
    
    std::cout << "POSSIBLE" << std::endl;
    std::cout << robotArm.gotoPosition(POSITION_PRESET::POSSIBLE, 0, 1000) << std::endl;
    std::this_thread::sleep_for(5s);

    std::cout << "PARK" << std::endl;
    robotArm.gotoPosition(e_position::PARK, 0, 2300);
    std::this_thread::sleep_for(5s);
    
    
    */

    ROS_INFO_STREAM("Hello, robot arm!");
    ros::spin();// Stop the node's resources

    // Exit tranquillyret
    return 0;
}