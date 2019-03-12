#ifndef IMPUTCONTROLLER_HPP
#define IMPUTCONTROLLER_HPP

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

class ImputController
{
  public:
    ImputController();
    ~ImputController();
    struct userImput getUserImput();
    void sendRequest(struct userImput imput);

};

#endif