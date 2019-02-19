#include "SSC32U.hpp"
#include <ros/ros.h>

#include "Controller.hpp"

enum joint {BASE = 0, SHOULDER = 1, ELBOW = 2, WRIST = 3, GRIPPER = 4, WRIST_ROTATE = 5};

// Standard C++ entry point

int main(int argc,char**argv)
{   

    
    // Announce this program to the ROS master as a "node" called "hello_world_node"
    ros::init(argc,argv,"robot_arm");
    // Start the node resource managers (communication, time, etc)

    Controller c("robot_arm");
    

   // ros::start();

    // SSC32U servoController("/dev/ttyUSB0");

    // //Set position ofset with pulse -100 to 100 is around 15 degrees
    // servoController.setPositionOffset(joint::SHOULDER, -100);

    // //Should go straight up with this
    // servoController.move(joint::BASE, 90);
    // servoController.move(joint::SHOULDER, 0);
    // servoController.move(joint::ELBOW, 0);
    // servoController.move(joint::WRIST, 0);
    // servoController.move(joint::GRIPPER, 0, 10);
    // servoController.move(joint::WRIST_ROTATE, 0, 0, 200);


    ROS_INFO_STREAM("Hello, robot arm!");
    // Process ROS callbacks until receiving a SIGINT (ctrl-c)
    ros::spin();// Stop the node's resources

   //ros::shutdown();

    // Exit tranquillyret
    return 0;
}