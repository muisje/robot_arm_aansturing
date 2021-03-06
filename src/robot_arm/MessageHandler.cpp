#include "MessageHandler.hpp"
#include "../shared_lib/Shared.hpp"
#include <ros/console.h>

MessageHandler::MessageHandler(std::string a_setPose_name, std::string a_setCostumPose_name, std::string a_emergency_name, std::shared_ptr<Queue> a_queue) : 
                                                                                    setPose_as(setPose_nh, a_setPose_name, boost::bind(&MessageHandler::executePose, this, _1), false),
                                                                                    setPose_name(a_setPose_name),
                                                                                    setCostumPose_as(setCostumPose_nh, a_setCostumPose_name, boost::bind(&MessageHandler::executeCostumPose, this, _1), false),
                                                                                    setCostumPose_name(a_setCostumPose_name),
                                                                                    emergency_as(emergency_nh, a_emergency_name, boost::bind(&MessageHandler::executeEmergency, this, _1), false),
                                                                                    emergency_name(a_emergency_name),
                                                                                    queue(a_queue)
{
    setPose_as.start();
    setCostumPose_as.start();
    emergency_as.start();
    
}

MessageHandler::~MessageHandler(void)
{
}

void MessageHandler::executePose(const robot_arm_aansturing::setPoseGoalConstPtr &goal)
{
    if (goal->g_pos == e_poses::PARK)
    {
       queue->addToQueue(POSITION_PRESET::PARK, 0, goal->g_time);
    }
    else if (goal->g_pos == e_poses::READY)
    {
        queue->addToQueue(POSITION_PRESET::READY, 0, goal->g_time);
    }
    else if (goal->g_pos == e_poses::STRAIGHT_UP)
    {
        queue->addToQueue(POSITION_PRESET::STRAIGHT_UP, 0, goal->g_time);
    }
    else
    {
        ROS_WARN("QoS-Warning: not able to move to unsuported preset position");
    }

    setPose_result.r_finalPose = 1;
    setPose_as.setSucceeded(setPose_result);
}

void MessageHandler::executeCostumPose(const robot_arm_aansturing::setCostumPoseGoalConstPtr &goal)
{
    std::map<e_joint, int16_t> customPosition;
    customPosition.insert(std::pair<e_joint, int16_t>(e_joint::BASE, goal->g_base));
    customPosition.insert(std::pair<e_joint, int16_t>(e_joint::SHOULDER, goal->g_shoulder));
    customPosition.insert(std::pair<e_joint, int16_t>(e_joint::ELBOW, goal->g_elbow));
    customPosition.insert(std::pair<e_joint, int16_t>(e_joint::WRIST, goal->g_wrist));
    customPosition.insert(std::pair<e_joint, int16_t>(e_joint::GRIPPER, goal->g_gripper));
    customPosition.insert(std::pair<e_joint, int16_t>(e_joint::WRIST_ROTATE, goal->g_wristRotate));
    
    queue->addToQueue(customPosition, 0, goal->g_time);

    setCostumPose_result.r_finalPose = 1;
    setCostumPose_as.setSucceeded(setCostumPose_result);
}

void MessageHandler::executeEmergency(const robot_arm_aansturing::emergencyGoalConstPtr &goal)
{
    queue->emptyQueue();
    emergency_result.succes = true;
    emergency_as.setSucceeded(emergency_result);
}