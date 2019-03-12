#include "Controller.hpp"
#include "../shared_lib/Shared.hpp"

Controller::Controller(std::string a_setPose_name, std::string a_setCostumPose_name) : setPose_as(setPose_nh, a_setPose_name, boost::bind(&Controller::executePose, this, _1), false),
                                                                                       setPose_name(a_setPose_name),
                                                                                       setCostumPose_as(setCostumPose_nh, a_setCostumPose_name, boost::bind(&Controller::executeCostumPose, this, _1), false),
                                                                                       setCostumPose_name(a_setCostumPose_name)

{
    setPose_as.start();
    setCostumPose_as.start();
}

Controller::~Controller(void)
{
}

void Controller::executePose(const robot_arm_aansturing::setPoseGoalConstPtr &goal)
{
    std::cout << "Executing someting" << std::endl;
    std::cout << goal->g_pos <<std::endl;
    setPose_result.r_finalPose = 1;
    setPose_as.setSucceeded(setPose_result);
}

void Controller::executeCostumPose(const robot_arm_aansturing::setCostumPoseGoalConstPtr &goal)
{
    std::cout << "Executing someting" << std::endl;
    std::cout << goal->g_base        <<std::endl;
    std::cout << goal->g_shoulder    <<std::endl;
    std::cout << goal->g_elbow       <<std::endl;
    std::cout << goal->g_wrist       <<std::endl;
    std::cout << goal->g_gripper     <<std::endl;
    std::cout << goal->g_wristRotate <<std::endl;

    setCostumPose_result.r_finalPose = 1;
    setCostumPose_as.setSucceeded(setCostumPose_result);
}