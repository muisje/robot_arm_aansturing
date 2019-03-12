#include "AL5D.hpp"

#include <iostream>

AL5D::AL5D(SSC32U & servoController, const std::map<e_joint, Range> & jointRanges) 
    : servoController(servoController), jointRanges(jointRanges)
{
}

AL5D::~AL5D()
{
}

bool AL5D::validateJointRanges( const std::map<e_joint, int16_t> position)
{
    for (auto const & value : position)
    {
        std::map<e_joint, Range>::iterator jointRange = jointRanges.find(value.first);
        if (jointRange != jointRanges.end())
        {
            if ( value.second < jointRange->second.min || value.second > jointRange->second.max )
            {
                return false;
            }
        }
    }
    return true;
}

void AL5D::stopAllMotorFunctions()
{
    this->gotoPosition(this->getCurrentPosition());
}

std::map<e_joint, int16_t> AL5D::getCurrentPosition()
{
    if (currentInstruction.duration == boost::posix_time::time_duration(0,0,0,0))
    {
        return currentInstruction.positionGoal;
    }

    boost::posix_time::time_duration diff = currentInstruction.startTime - boost::posix_time::microsec_clock::local_time();

    if (diff >= currentInstruction.duration)
    {
        return currentInstruction.positionGoal;
    }
    else
    {
        double progress = currentInstruction.duration.fractional_seconds() / diff.fractional_seconds();
        
        std::map<e_joint, int16_t> currentPosition;
        for (auto const & jointStart : currentInstruction.positionStart)
        {
            uint16_t currentJointPosition = round((currentInstruction.positionGoal[jointStart.first] - jointStart.second) * progress + jointStart.second);
            currentPosition.insert(std::pair<e_joint, int16_t>(jointStart.first, currentJointPosition));
        }
        return currentPosition;
    }
}

bool AL5D::gotoPosition(std::map<e_joint, int16_t> position, uint16_t speed, uint16_t time)
{
    if(!this->validateJointRanges(position))
    {
        return false;
    }
    this->currentInstruction.positionStart = this->currentInstruction.positionGoal;
    this->currentInstruction.positionGoal = position;
    this->currentInstruction.startTime = boost::posix_time::microsec_clock::local_time();
    this->currentInstruction.duration = boost::posix_time::milliseconds(time);
    
    servoController.move(e_joint::BASE, position[e_joint::BASE], speed, time);
    servoController.move(e_joint::SHOULDER, position[e_joint::SHOULDER], speed, time);
    servoController.move(e_joint::ELBOW, position[e_joint::ELBOW], speed, time);
    servoController.move(e_joint::WRIST, position[e_joint::WRIST], speed, time);
    servoController.move(e_joint::GRIPPER, position[e_joint::GRIPPER], speed, time);
    servoController.move(e_joint::WRIST_ROTATE, position[e_joint::WRIST_ROTATE], speed, time);
    return true;
}