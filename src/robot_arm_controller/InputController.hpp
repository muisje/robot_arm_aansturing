#ifndef INPUTCONTROLLER_HPP
#define INPUTCONTROLLER_HPP

#include <iostream>
#include <vector>

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <robot_arm_aansturing/setPoseAction.h>
#include <robot_arm_aansturing/setCostumPoseAction.h>
#include <robot_arm_aansturing/emergencyAction.h>
#include "../shared_lib/Shared.hpp"

enum e_userPrefrences
{
    COSTUM_POSE,
    PRE_SET_POSE,
    STOP,
    DEFAULT
};

struct userInput
{
    e_userPrefrences prefrence = e_userPrefrences::DEFAULT;
    std::string stringInput;
    bool appStatus = true;
};

struct parsStringCostumPose
{
    int base;
    int shoulder;
    int elbow;
    int wrist;
    int gripper;
    int wristRotate;
    unsigned int time;

    parsStringCostumPose(const std::string &input)
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

        if (values.size() == 7)
        {
            base = values.at(0);
            shoulder = values.at(1);
            elbow = values.at(2);
            wrist = values.at(3);
            gripper = values.at(4);
            wristRotate = values.at(5);
            time = values.at(6);
            
        }
        else
        {
            ROS_WARN("User input not supported");
        }
    }
};

struct parsStringPose
{
    short pose;
    unsigned int time;

    parsStringPose(const std::string &input)
    {
        std::vector<int> values;
        std::string subString;
        unsigned int previousIdx = 0;

        for (unsigned int idx = 0; idx < input.size(); ++idx)
        {
            if (input[idx] == ',')
            {
                std::string substr = input.substr(previousIdx, idx - previousIdx);

                if (substr == "p" || substr == "P")
                {
                    pose = e_poses::PARK;
                }
                else if (substr == "r" || substr == "R")
                {
                    pose = e_poses::READY;
                }
                else if ((substr == "s" || substr == "S"))
                {
                    pose = e_poses::STRAIGHT_UP;
                }
                else
                {
                    std::cout << "substr" << substr <<std::endl;
                    time = std::stoi(substr);
                }
                previousIdx = idx + 1;
            }
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
    void sendRequest(struct userInput& input);

};

#endif