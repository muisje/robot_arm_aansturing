#include "SSC32U.hpp"
#include "AL5D.hpp"
#include "ArmOffset.hpp"
#include "Ranges.hpp"
#include "MessageHandler.hpp"
#include <ros/ros.h>
#include <memory>

#define BOUTRATE 9600
#define USB_CONNECTION "/dev/ttyUSB0"
#define ROBO_ARM_OFFSET ArmOffset::ROBOT_1
#define ROBO_ARM_RANGES Ranges::AL5DRanges


int main(int argc, char **argv)
{
    ros::init(argc,argv,"robot");
    ros::start();
    
    //If user used a argument for the serial 
    SSC32U servoController(USB_CONNECTION, BOUTRATE);
    AL5D robotArm(servoController, ROBO_ARM_RANGES, ROBO_ARM_OFFSET);
    
    robotArm.gotoPosition(POSITION_PRESET::PARK);

    //Queue q(robotArm);
    std::shared_ptr<Queue> queue = std::make_shared<Queue>(robotArm);

    MessageHandler c("pose_action","costum_pose_action","emergency",queue);

    
    while (ros::ok())
    {
        queue->checkQueue();
        ros::spinOnce();
    }


    return 0;
}