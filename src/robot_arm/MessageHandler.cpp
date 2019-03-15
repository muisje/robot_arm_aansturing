#include "MessageHandler.hpp"
#include "../shared_lib/Shared.hpp"

MessageHandler::MessageHandler(std::string a_setPose_name, std::string a_setCostumPose_name, std::shared_ptr<Queue> a_queue) : 
                                                                                    setPose_as(setPose_nh, a_setPose_name, boost::bind(&MessageHandler::executePose, this, _1), false),
                                                                                    setPose_name(a_setPose_name),
                                                                                    setCostumPose_as(setCostumPose_nh, a_setCostumPose_name, boost::bind(&MessageHandler::executeCostumPose, this, _1), false),
                                                                                    setCostumPose_name(a_setCostumPose_name),
                                                                                    queue(a_queue)
                                                                                    //,robotArm(a_robotArm)
                                                                                       

{
    setPose_as.start();
    setCostumPose_as.start();
    
}

MessageHandler::~MessageHandler(void)
{
}

void MessageHandler::executePose(const robot_arm_aansturing::setPoseGoalConstPtr &goal)
{
    
    std::cout << "Executing pose" <<std::endl;

    if (goal->g_pos == e_poses::PARK)
    {
        std::cout << "MOVING TO PARK" <<std::endl;
        //robotArm.gotoPosition(POSITION_PRESET::PARK);

        queue->addToQueue(POSITION_PRESET::PARK, 0, 2300);
    }
    else if (goal->g_pos == e_poses::READY)
    {
        std::cout << "MOVING TO READY" <<std::endl;
        //robotArm.gotoPosition(POSITION_PRESET::READY, 0, 2300);
        queue->addToQueue(POSITION_PRESET::READY, 0, 2300);

    }
    else if (goal->g_pos == e_poses::STRAIGHT_UP)
    {
        std::cout << "MOVING TO STRAIGTUP" <<std::endl;
        //robotArm.gotoPosition(POSITION_PRESET::STRAIGHT_UP, 0, 500);
        queue->addToQueue(POSITION_PRESET::STRAIGHT_UP, 0, 2300);

    }
    else
    {
        //ERRROR GOOIEN
    }

   // int test = 0;
    

    // while(test < 1000)
    // {
    //     std::cout << test << std::endl;
    //     setPose_feedback.f_procesStatus = test;
    //     setPose_as.publishFeedback(setPose_feedback);
    //     ++test;
    // }
    setPose_result.r_finalPose = 1;
    setPose_as.setSucceeded(setPose_result);


}

void MessageHandler::executeCostumPose(const robot_arm_aansturing::setCostumPoseGoalConstPtr &goal)
{
    std::cout << "Executing someting" << std::endl;

    //TODO MOVE ARE TO POSITION BELOW
    std::cout << goal->g_base << std::endl;
    std::cout << goal->g_shoulder << std::endl;
    std::cout << goal->g_elbow << std::endl;
    std::cout << goal->g_wrist << std::endl;
    std::cout << goal->g_gripper << std::endl;
    std::cout << goal->g_wristRotate << std::endl;

    //TODO SET FINAL POSITION
    setCostumPose_result.r_finalPose = 1;
    setCostumPose_as.setSucceeded(setCostumPose_result);
}