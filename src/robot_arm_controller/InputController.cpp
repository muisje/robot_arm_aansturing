#include "InputController.hpp"
#include <boost/thread.hpp>


#include <chrono>
#include <thread>

InputController::InputController()
{
    
}

InputController::~InputController()
{

}


struct userInput InputController::getUserInput()
{
    userInput returnValue;
    std::string userInput = "";
    std::cout << " Would u like to set a pose(P) or a custom position(C). Type exit to close the executable" << std::endl;
    getline(std::cin, userInput);

    if (userInput == "c" || userInput == "C")
    {
        returnValue.prefrence = COSTUM_POSE;

        std::cout << " Costum pose selected \n Use the next format to set the costum position: <Base degree>,<Shoulder degree>,<Elbow degree>,<Wrist degree>,<Gripper degree>,<Gripper rotate degree>," << std::endl;
        getline(std::cin, returnValue.stringInput);
    }
    else if (userInput == "p" || userInput == "P")
    {
        returnValue.prefrence = PRE_SET_POSE;

        std::cout << " Pre set pose selected \n Choose on of the next poses Park(P), Ready(R) or Straight-up(S)" << std::endl;
        getline(std::cin, returnValue.stringInput);

    }
    else if (userInput == "exit" || userInput == "Exit")
    {
        returnValue.appStatus = false;
    }
    else
    {
        std::cout << "User input not supported" << std::endl;
        //TODO ROS IMPELENT ROS ERROR
    }
    return returnValue;
}

void InputController::sendRequest(struct userInput input)
{
    


    if (input.prefrence == PRE_SET_POSE)
    {
        actionlib::SimpleActionClient<robot_arm_aansturing::setPoseAction> ac("pose_action", true);

        ros::start();
        ac.waitForServer();

        robot_arm_aansturing::setPoseGoal goal;

        if (input.stringInput == "p" || input.stringInput == "P")
        {
            goal.g_pos = e_poses::PARK;
        }
        else if (input.stringInput == "r" || input.stringInput == "R")
        {
            goal.g_pos = e_poses::READY;
        }
        else if ((input.stringInput == "s" || input.stringInput == "S"))
        {
            goal.g_pos = e_poses::STRAIGHT_UP;
        }
        else
        {
            std::cout << "User input not supported" << std::endl;
            //TODO ROS IMPELENT ROS ERROR
        }
        std::cout << "Sending goal" << std::endl;

        ac.sendGoal(goal);
        ac.waitForResult(ros::Duration(30.0));
    }
    else if (input.prefrence == COSTUM_POSE)
    {
        actionlib::SimpleActionClient<robot_arm_aansturing::setCostumPoseAction> ac("costum_pose_action", true);

        ros::start();
        ac.waitForServer();

        robot_arm_aansturing::setCostumPoseGoal goal;

        struct parsString messageValues(input.stringInput);

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
