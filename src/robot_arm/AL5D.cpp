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

bool AL5D::gotoPosition(std::map<e_joint, int16_t> position, uint16_t speed, uint16_t time)
{
    if(!this->validateJointRanges(position))
    {
        return false;
    }
    servoController.move(e_joint::BASE, position[e_joint::BASE], speed, time);
    servoController.move(e_joint::SHOULDER, position[e_joint::SHOULDER], speed, time);
    servoController.move(e_joint::ELBOW, position[e_joint::ELBOW], speed, time);
    servoController.move(e_joint::WRIST, position[e_joint::WRIST], speed, time);
    servoController.move(e_joint::GRIPPER, position[e_joint::GRIPPER], speed, time);
    servoController.move(e_joint::WRIST_ROTATE, position[e_joint::WRIST_ROTATE], speed, time);
    return true;
}
    
bool AL5D::gotoPosition(enum::e_position position, uint16_t speed, uint16_t time)
{
    switch (position)
    {
        case e_position::PARK:
            return this->gotoPosition(POSITION_PRESET::PARK, speed, time);
            break;
        
        case e_position::READY:
            return this->gotoPosition(POSITION_PRESET::READY, speed, time);
            break;
        
        case e_position::STRAIGHT_UP:
            return this->gotoPosition(POSITION_PRESET::STRAIGHT_UP, speed, time);
            break;
    
        default:
            return false;
            break;
    }
}