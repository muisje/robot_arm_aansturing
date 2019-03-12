#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <robot_arm_aansturing/setPoseAction.h>
#include <robot_arm_aansturing/setCostumPoseAction.h>
#include "../shared_lib/Shared.hpp"

// Called once when the goal completes
// void doneCb(const actionlib::SimpleClientGoalState& state,
//             const FibonacciResultConstPtr& result)
// {
//   ROS_INFO("Finished in state [%s]", state.toString().c_str());
//   ROS_INFO("Answer: %i", result->finalLocation);
//   ros::shutdown();
// }

// // Called once when the goal becomes active
// void activeCb()
// {
//   ROS_INFO("Goal just went active");
// }

// void feedbackCb(const FibonacciFeedbackConstPtr& feedback)
// {
//   ROS_INFO("Got Feedback of length %lu", feedback->currentLocation);
// }
enum e_userPrefrences
{
    COSTUM_POSE,
    PRE_SET_POSE
};

struct userImput
{
    e_userPrefrences prefrence;
    std::string stringImput;
};

struct parsString
{
    int base;
    int shoulder;
    int elbow;
    int wrist;
    int gripper;
    int wristRotate;

    parsString(std::string &imput)
    {
        std::vector<int> values;
        std::string subString;
        unsigned int previousIdx = 0;

        for (unsigned int idx = 0; idx < imput.size(); ++idx)
        {
            if (imput[idx] == ',')
            {
                std::string substr = imput.substr(previousIdx, idx - previousIdx);
                int test = std::stoi(substr);
                values.push_back(test);
                previousIdx = idx + 1;
            }
        }

        if (values.size() == 6)
        {
            base = values.at(0);
            shoulder = values.at(1);
            elbow = values.at(2);
            wrist = values.at(3);
            gripper = values.at(4);
            wristRotate = values.at(5);
        }
        else
        {
            std::cout << "Value amound not right" << std::endl;
        }
    }
};

struct userImput getUserImput()
{
    userImput returnValue;

    std::string userImput = "";
    std::cout << " Would u like to set a pose(P) or a custom position(C)" << std::endl;
    getline(std::cin, userImput);

    if (userImput == "c" || userImput == "C")
    {
        returnValue.prefrence = COSTUM_POSE;

        std::cout << " Costum pose selected \n Use the next format to set the costum position: <Base degree>,<Shoulder degree>,<Elbow degree>,<Wrist degree>,<Gripper degree>,<Gripper rotate degree>" << std::endl;
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

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_arm_controller");

    auto Imput = getUserImput();

    if (Imput.prefrence == PRE_SET_POSE)
    {
        actionlib::SimpleActionClient<robot_arm_aansturing::setPoseAction> ac("robot_arm", true);

        ros::start();
        ac.waitForServer();

        robot_arm_aansturing::setPoseGoal goal;

        if (Imput.stringImput == "p" || Imput.stringImput == "P")
        {
            goal.g_pos = e_poses::PARK;
        }
        else if (Imput.stringImput == "r" || Imput.stringImput == "R")
        {
            goal.g_pos = e_poses::READY;
        }
        else if ((Imput.stringImput == "s" || Imput.stringImput == "S"))
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
    else if (Imput.prefrence == COSTUM_POSE)
    {
        actionlib::SimpleActionClient<robot_arm_aansturing::setCostumPoseAction> ac("test", true);

        ros::start();
        ac.waitForServer();

        robot_arm_aansturing::setCostumPoseGoal goal;

        struct parsString messageValues(Imput.stringImput);

        goal.g_base = messageValues.base;
        goal.g_shoulder = messageValues.shoulder;
        goal.g_elbow = messageValues.elbow;
        goal.g_wrist = messageValues.wrist;
        goal.g_gripper = messageValues.gripper;
        goal.g_wristRotate = messageValues.wristRotate;

        ac.sendGoal(goal);

        ac.waitForResult(ros::Duration(30.0));
    }

    return 0;
}
