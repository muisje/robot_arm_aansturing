#include "SSC32U.hpp"
#include "AL5D.hpp"
#include "ArmOffset.hpp"
#include "MessageHandler.hpp"
#include <ros/ros.h>
#include <memory>

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 
#include "Queue.hpp"

#include <boost/thread/thread.hpp>


int main(int argc, char **argv)
{
    ros::init(argc,argv,"robot");
    ros::start();

    std::map<e_joint, Range> jointRanges = boost::assign::map_list_of
    (e_joint::BASE, Range{-90, 0}) (e_joint::SHOULDER, Range{-30, 90}) (e_joint::ELBOW, Range{0, 90})
    (e_joint::WRIST, Range{-90, 90}) (e_joint::WRIST_ROTATE, Range{-90, 90});

    if(argc =! 1)
    {
        //TODO ROS ERROR GOOIEN
    }
    
    
    //If user used a argument for the serial 
    SSC32U servoController("/dev/ttyUSB0", std::stoi(argv[1]));
    AL5D robotArm(servoController, jointRanges, ArmOffset::ROBOT_2);
    
    //Queue q(robotArm);
    std::shared_ptr<Queue> q = std::make_shared<Queue>(robotArm);

    MessageHandler c("pose_action","costum_pose_action",q);

    
    while (ros::ok())
    {
        q->checkQueue();
        ros::spinOnce();
    }


    return 0;
}