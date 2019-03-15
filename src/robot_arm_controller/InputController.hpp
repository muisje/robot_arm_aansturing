#ifndef INPUTCONTROLLER_HPP
#define INPUTCONTROLLER_HPP

#include <iostream>
#include <vector>

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <robot_arm_aansturing/setPoseAction.h>
#include <robot_arm_aansturing/setCostumPoseAction.h>
#include "../shared_lib/Shared.hpp"

enum e_userPrefrences
{
    COSTUM_POSE,
    PRE_SET_POSE,
    DEFAULT
};

struct userInput
{
    e_userPrefrences prefrence = e_userPrefrences::DEFAULT;
    std::string stringInput;
    bool appStatus = true;
};

struct parsString
{
    int base;
    int shoulder;
    int elbow;
    int wrist;
    int gripper;
    int wristRotate;

    parsString(std::string &input)
    {
        std::vector<int> values;
        std::string subString;
        unsigned int previousIdx = 0;

        for (unsigned int idx = 0; idx < input.size(); ++idx)
        {
            if (input[idx] == ',')
            {
                std::string substr = input.substr(previousIdx, idx - previousIdx);
                values.push_back(std::stoi(substr));
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

class InputController
{
  public:
    InputController();
    ~InputController();

    /**
     * @brief Get the user Input by terminal input
     * 
     * @return - Return a struct with the input string and a preference for a costume pose or pre set pose
     */
    struct userInput getUserInput();

    /**
     * @brief Send a action message tot the published node
     * 
     * @param input - A struct with the user input info
     */
    void sendRequest(struct userInput input);

};

#endif