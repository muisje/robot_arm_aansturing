#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <robot_arm_aansturing/setPoseAction.h>
#include <robot_arm_aansturing/setCostumPoseAction.h>
#include "../shared_lib/Shared.hpp"
#include "InputController.hpp"

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

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_arm_controller");

    InputController controller;

    while(1)
    {
        auto userInput = controller.getUserInput();
        controller.sendRequest(userInput);
    }
    return 0;
}
