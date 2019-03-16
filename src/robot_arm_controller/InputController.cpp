#include "InputController.hpp"
#include <ros/console.h>

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
    std::cout << " Would u like to set a pose(P) or a custom position(C). Type exit to close the executable or S for a emergency stop" << std::endl;
    getline(std::cin, userInput);

    if (userInput == "c" || userInput == "C")
    {
        returnValue.prefrence = COSTUM_POSE;

        std::cout << " Costum pose selected \n Use the next format to set the costum position: <Base degree>,<Shoulder degree>,<Elbow degree>,<Wrist degree>,<Gripper degree>,<Gripper rotate degree>,<Execute time>," << std::endl;
        getline(std::cin, returnValue.stringInput);
    }
    else if (userInput == "p" || userInput == "P")
    {
        returnValue.prefrence = PRE_SET_POSE;

        std::cout << " Pre set pose selected \n Choose on of the next poses Park(P),<Execute time>, | Ready(R),<Execute time>, | Straight-up(S),<Execute time>," << std::endl;
        getline(std::cin, returnValue.stringInput);
    }
    else if (userInput == "s" || userInput == "S")
    {
        returnValue.prefrence = STOP;
    }
    else if (userInput == "exit" || userInput == "Exit")
    {
        returnValue.appStatus = false;
    }
    else
    {
        ROS_WARN("QoS-Warning: User input not supported");
    }
    return returnValue;
}

void InputController::sendRequest(struct userInput& input)
{
    if (input.prefrence == PRE_SET_POSE)
    {
        ROS_DEBUG("EVENT: sending request[preset pose]");
        actionlib::SimpleActionClient<robot_arm_aansturing::setPoseAction> ac("pose_action", true);

        ros::start();
        ac.waitForServer();
        robot_arm_aansturing::setPoseGoal goal;

        struct parsStringPose messageValues(input.stringInput);

        //! maybe check if messages values are correctly parsed?

        goal.g_time = messageValues.time;
        goal.g_pos = messageValues.pose;

        ac.sendGoal(goal);
        ac.waitForResult();
    }
    else if (input.prefrence == COSTUM_POSE)
    {
        ROS_DEBUG("EVENT: sending request[custom pose]");
        actionlib::SimpleActionClient<robot_arm_aansturing::setCostumPoseAction> ac("costum_pose_action", true);

        ros::start();
        ac.waitForServer();

        robot_arm_aansturing::setCostumPoseGoal goal;

        struct parsStringCostumPose messageValues(input.stringInput);

        //! maybe check if messages values are correctly parsed?

        goal.g_base = messageValues.base;
        goal.g_shoulder = messageValues.shoulder;
        goal.g_elbow = messageValues.elbow;
        goal.g_wrist = messageValues.wrist;
        goal.g_gripper = messageValues.gripper;
        goal.g_wristRotate = messageValues.wristRotate;
        goal.g_time = messageValues.time;

        ac.sendGoal(goal);
        ac.waitForResult();
    }
    else if (input.prefrence == STOP)
    {
        ROS_DEBUG("EVENT: sending request[emergency stop]");
        actionlib::SimpleActionClient<robot_arm_aansturing::emergencyAction> ac("emergency", true);

        ros::start();
        ac.waitForServer();

        robot_arm_aansturing::emergencyGoal goal;
        goal.emergency = true;

        ac.sendGoal(goal);
        ac.waitForResult();
    }
    else if (input.prefrence == DEFAULT)
    {
        ROS_WARN("QoS-Warning: default input; no request send.");
    }
    else
    {
        ROS_WARN("QoS-Warning: unkown input; no request send.");
    }
}
