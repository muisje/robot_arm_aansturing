// #define TIMING

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <robot_arm_aansturing/setPoseAction.h>
#include <robot_arm_aansturing/setCostumPoseAction.h>
#include "../shared_lib/Shared.hpp"
#include "InputController.hpp"

#ifdef TIMING
#include <iostream>
#include <chrono>
#include <thread>
#endif // TIMING

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_arm_controller");

    InputController controller;
    struct userInput input;

    while(input.appStatus)
    {
        input = controller.getUserInput();

        if(input.appStatus && input.prefrence != e_userPrefrences::DEFAULT)
        {
            ROS_DEBUG("EVENT: Handling user input");
            
            #ifdef TIMING
            auto start = std::chrono::high_resolution_clock::now();
            #endif //timing
            controller.sendRequest(input);
            #ifdef TIMING
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "controller.sendRequest(input) took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
              << " milliseconds\n";
            #endif

            input.prefrence = e_userPrefrences::DEFAULT;
        }
    }
    return 0;
}
