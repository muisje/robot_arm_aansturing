#include "ImputController.hpp"

ImputController::ImputController()
{

}

ImputController::~ImputController()
{

}

struct userImput ImputController::getUserImput()
{
    userImput returnValue;

    std::string userImput = "";
    std::cout << " Would u like to set a pose(P) or a custom position(C)" << std::endl;
    getline(std::cin, userImput);

    if (userImput == "c" || userImput == "C")
    {
        returnValue.prefrence = COSTUM_POSE;

        std::cout << " Costum pose selected \n Use the next format to set the costum position: <Base degree>,<Shoulder degree>,<Elbow degree>,<Wrist degree>,<Gripper degree>,<Gripper rotate degree>," << std::endl;
        getline(std::cin, returnValue.stringImput);
    }
    else if (userImput == "p" || userImput == "P")
    {
        returnValue.prefrence = PRE_SET_POSE;

        std::cout << " Pre set pose selected \n Choose on of the next poses Park(P), Ready(R) or Straight-up(S)" << std::endl;
        getline(std::cin, returnValue.stringImput);
    }
    else
    {
        std::cout << "User imput not supported" << std::endl;
        //TODO ROS IMPELENT ROS ERROR
    }

    return returnValue;
}

void ImputController::sendRequest(struct userImput imput)
{
    if (imput.prefrence == PRE_SET_POSE)
    {
        actionlib::SimpleActionClient<robot_arm_aansturing::setPoseAction> ac("robot_arm", true);

        ros::start();
        ac.waitForServer();

        robot_arm_aansturing::setPoseGoal goal;

        if (imput.stringImput == "p" || imput.stringImput == "P")
        {
            goal.g_pos = e_poses::PARK;
        }
        else if (imput.stringImput == "r" || imput.stringImput == "R")
        {
            goal.g_pos = e_poses::READY;
        }
        else if ((imput.stringImput == "s" || imput.stringImput == "S"))
        {
            goal.g_pos = e_poses::STRAIGHT_UP;
        }
        else
        {
            std::cout << "User imput not supported" << std::endl;
            //TODO ROS IMPELENT ROS ERROR
        }
        ac.sendGoal(goal);

        ac.waitForResult(ros::Duration(30.0));
    }
    else if (imput.prefrence == COSTUM_POSE)
    {
        actionlib::SimpleActionClient<robot_arm_aansturing::setCostumPoseAction> ac("test", true);

        ros::start();
        ac.waitForServer();

        robot_arm_aansturing::setCostumPoseGoal goal;

        struct parsString messageValues(imput.stringImput);

        goal.g_base = messageValues.base;
        goal.g_shoulder = messageValues.shoulder;
        goal.g_elbow = messageValues.elbow;
        goal.g_wrist = messageValues.wrist;
        goal.g_gripper = messageValues.gripper;
        goal.g_wristRotate = messageValues.wristRotate;

        ac.sendGoal(goal);

        ac.waitForResult(ros::Duration(30.0));
    }
}
