#include "SSC32U.hpp"
#include "AL5D.hpp"
#include "ArmOffset.hpp"
#include "Ranges.hpp"
#include "MessageHandler.hpp"
#include <ros/ros.h>
#include <memory>

#define BOUTRATE 9600
#define USB_CONNECTION "/dev/ttyUSB0"
#define ROBO_ARM_OFFSET ArmOffset::ROBOT_3
#define ROBO_ARM_RANGES Ranges::AL5DRanges


int main(int argc, char **argv)
{
    ros::init(argc,argv,"robot");
    ros::start();
    
    //Setting up the connection with the controller board
    SSC32U servoController(USB_CONNECTION, BOUTRATE);
    AL5D robotArm(servoController, ROBO_ARM_RANGES, ROBO_ARM_OFFSET);

    //Starting the robotic arm in the default position  
    robotArm.gotoPosition(POSITION_PRESET::PARK);

    //Creating a sharedPointer for the message handler
    std::shared_ptr<Queue> queue = std::make_shared<Queue>(robotArm);
    MessageHandler c("pose_action","costum_pose_action","emergency",queue);

    
    while (ros::ok())
    {
        ros::spinOnce();
        queue->checkQueue();  
    }

    return 0;
}