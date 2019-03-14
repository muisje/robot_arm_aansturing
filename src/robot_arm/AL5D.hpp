/**
 * @file AL5D.hpp
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl)
 * @brief Class for easy use with the AL5D Robot Arm. Class provides functions for going to a specific posiition, giving feedback of current position and stopping all the moving parts.
 * In the constructior the used servo controller can be given to use, the ranges in which the joints need to stay and the offset of those joints all in degrees.
 * @version 0.1
 * @date 2019-03-14
 * 
 */
#ifndef AL5D_HPP
#define AL5D_HPP

#include "SSC32U.hpp"
#include "Position.hpp"
#include "PositionInstruction.hpp"
#include "Joint.hpp"
#include "Range.hpp"
#include <map>

class AL5D
{
private:
    SSC32U servoController;
    std::map<e_joint, Range> jointRanges;
    std::map<e_joint, int16_t> jointOffsets;
    PositionInstruction currentInstruction;

    int16_t getCorrectedJointPosition(e_joint joint, int16_t orginalJointPosition);
    bool validateJointRanges(const std::map<e_joint, int16_t> position); 

public:
    /**
     * @brief Construct a new AL5D object
     * 
     * @param servoController the used servo controller for controlling the robot arm.
     * @param jointRanges the range in which the robot arm needs to stay for each joint in degrees. If an instruction is given that is out of the range it will prevent it from moving.E
     * @param jointOffsets the offset of the robot arm for each joint in degrees.
     */
    AL5D(SSC32U & servoController, const std::map<e_joint, Range> & jointRanges, const std::map<e_joint, int16_t> & jointOffsets);
    ~AL5D();

    /**
     * @brief Instruct the robot arm to go to a position. If it is valid it will move to the given position. 
     * The speed and time can be given to reach the position. 
     * Which ever takes the most time for each joint to reach it's goal will be used. If it is 0 or not specified it will try to go as fast as possible to the given postion.
     * 
     * @param position a map with joints and degrees makes a position. That map is the instruction for which the robot arm will go to if it is valid.
     * @param speed 
     * @param time in miliseconds for how long it needs to take to arive
     * @return true if the given position is valid to go to.
     * @return false if the given position is not valid to go to.
     */
    bool gotoPosition(std::map<e_joint, int16_t> position, uint16_t speed = 0, uint16_t time = 0);
    /**
     * @brief stops all moving parts of the robot arm. Example usage is a emergency stop.
     * 
     */
    void stopAllMotorFunctions();
    /**
     * @brief Get the Current Position of the AL5D robot arm for each joint in degrees returned in a map.
     * 
     * @return std::map<e_joint, int16_t> the current position for each joint in degrees.
     */
    std::map<e_joint, int16_t> getCurrentPosition();
};

#endif