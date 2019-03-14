#include "Controller.hpp"
#include "../shared_lib/Shared.hpp"
#include <ros/console.h>

Controller::Controller(std::string a_setPose_name, std::string a_setCostumPose_name, SSC32U& board, std::map<e_joint, Range> ranges, const std::map<e_joint, int16_t> & jointOffsets) : 
                                                                                    setPose_as(setPose_nh, a_setPose_name, boost::bind(&Controller::executePose, this, _1), false),
                                                                                    setPose_name(a_setPose_name),
                                                                                    setCostumPose_as(setCostumPose_nh, a_setCostumPose_name, boost::bind(&Controller::executeCostumPose, this, _1), false),
                                                                                    setCostumPose_name(a_setCostumPose_name),
                                                                                    robotArm(board, ranges, jointOffsets)
                                                                                       

{
    setPose_as.start();
    setCostumPose_as.start();
}

Controller::~Controller(void)
{
}

void Controller::executePose(const robot_arm_aansturing::setPoseGoalConstPtr &goal)
{
    if (goal->g_pos == e_poses::PARK)
    {
        if(robotArm.gotoPosition(POSITION_PRESET::PARK))
        {
            ROS_INFO("STATE: MOVING");
        }
        else
        {
            ROS_WARN("QoS-Warning: not able to move to park preset position");
        }
        
    }
    else if (goal->g_pos == e_poses::READY)
    {
        if (robotArm.gotoPosition(POSITION_PRESET::READY, 0, 2300))
        {
            ROS_INFO("STATE: MOVING");
        }
        else
        {
            ROS_WARN("QoS-Warning: not able to move to ready preset position");
        }
        
    }
    else if (goal->g_pos == e_poses::STRAIGHT_UP)
    {
        if(robotArm.gotoPosition(POSITION_PRESET::STRAIGHT_UP, 0, 500))
        {
            ROS_INFO("STATE: MOVING");
        }
        else
        {
            ROS_WARN("QoS-Warning: not able to move to straight up preset position");
        }
    }
    else
    {
        ROS_WARN("QoS-Warning: not able to move to unsuported preset position");
    }

    //TODO GIVE FEEDBACK
    //TODO SET FINAL POSITION WHEN FINISHED
    ROS_INFO("STATE: FINISHED_MOVING");
    setPose_result.r_finalPose = 1;
    setPose_as.setSucceeded(setPose_result);
}

void Controller::executeCostumPose(const robot_arm_aansturing::setCostumPoseGoalConstPtr &goal)
{
    std::cout << "Executing custom pose" << std::endl;

    std::map<e_joint, int16_t> customPosition;
    customPosition.insert(std::pair<e_joint, int16_t>(e_joint::BASE, goal->g_base));
    customPosition.insert(std::pair<e_joint, int16_t>(e_joint::SHOULDER, goal->g_shoulder));
    customPosition.insert(std::pair<e_joint, int16_t>(e_joint::ELBOW, goal->g_elbow));
    customPosition.insert(std::pair<e_joint, int16_t>(e_joint::WRIST, goal->g_wrist));
    customPosition.insert(std::pair<e_joint, int16_t>(e_joint::GRIPPER, goal->g_gripper));
    customPosition.insert(std::pair<e_joint, int16_t>(e_joint::WRIST_ROTATE, goal->g_wristRotate));
    if(robotArm.gotoPosition(customPosition, 0, 500))
    {
        ROS_INFO("STATE: MOVING");
    }
    else
    {
        ROS_WARN("QoS-Warning: not able to move to unsuported custom position");
    }
    
    //TODO GIVE FEEDBACK
    //TODO SET FINAL POSITION WHEN FINISHED
    ROS_INFO("STATE: FINISHED_MOVING");
    setCostumPose_result.r_finalPose = 1;
    setCostumPose_as.setSucceeded(setCostumPose_result);
}