#include "SSC32U.hpp"
#include <ros/ros.h>

#include <chrono>
#include <thread>

enum joint {BASE = 0, SHOULDER = 1, ELBOW = 2, WRIST = 3, GRIPPER = 4, WRIST_ROTATE = 5};

// Standard C++ entry point

int main(int argc,char**argv)
{   
    using namespace std::chrono_literals;

    // Announce this program to the ROS master as a "node" called "hello_world_node"
    ros::init(argc,argv,"hello_robot_arm_node");
    // Start the node resource managers (communication, time, etc)
    ros::start();

    SSC32U servoController("/dev/ttyUSB0");

    //Set position ofset with pulse -100 to 100 is around 15 degrees
    // servoController.setPositionOffset(joint::SHOULDER, -100);


    servoController.move(joint::BASE, 0);
    servoController.move(joint::SHOULDER, 45);
    servoController.move(joint::ELBOW, 70);
    servoController.move(joint::WRIST, -60);
    servoController.move(joint::GRIPPER, 0, 0);
    servoController.move(joint::WRIST_ROTATE, 0, 0);

    std::this_thread::sleep_for(2s);
    
    servoController.move(joint::BASE, 0, 0, 2000);
    servoController.move(joint::SHOULDER, 30, 0, 2000);
    servoController.move(joint::ELBOW, 30, 0, 2000);
    servoController.move(joint::WRIST, -30, 0, 2000);
    servoController.move(joint::GRIPPER, 0, 0, 2000);
    servoController.move(joint::WRIST_ROTATE, 0, 2000);

    std::this_thread::sleep_for(8s);
    //Should go straight up with this
    servoController.move(joint::BASE, 0, 0, 2000);
    servoController.move(joint::SHOULDER, 0, 0, 2000);
    servoController.move(joint::ELBOW, -60, 0, 2000);
    servoController.move(joint::WRIST, 0, 0, 2000);
    servoController.move(joint::GRIPPER, 0, 0, 2000);
    servoController.move(joint::WRIST_ROTATE, 0, 0, 2000);

    std::this_thread::sleep_for(10s);

    servoController.move(joint::BASE, 0, 0, 2000);
    servoController.move(joint::SHOULDER, 45, 0, 2000);
    servoController.move(joint::ELBOW, 70, 0, 2000);
    servoController.move(joint::WRIST, -60, 0, 2000);
    servoController.move(joint::GRIPPER, 0, 0, 2000);
    servoController.move(joint::WRIST_ROTATE, 0, 0, 2000);


    ROS_INFO_STREAM("Hello, robot arm!");
    // Process ROS callbacks until receiving a SIGINT (ctrl-c)
    ros::spin();// Stop the node's resources

    ros::shutdown();

    // Exit tranquillyret
    return 0;
}