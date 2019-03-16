#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <robot_arm_aansturing/setPoseAction.h>
#include <robot_arm_aansturing/setCostumPoseAction.h>
#include "../shared_lib/Shared.hpp"
#include "InputController.hpp"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_arm_controller");

    InputController controller;
    struct userInput input;

    while(input.appStatus)
    {
        input = controller.getUserInput();

        if(input.appStatus)
        {
            ROS_DEBUG("EVENT: Handling user input");

            controller.sendRequest(input);
            input.prefrence = e_userPrefrences::DEFAULT;
        }
    }
    return 0;
}
