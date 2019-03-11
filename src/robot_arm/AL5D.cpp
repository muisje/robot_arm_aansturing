#include "AL5D.hpp"

AL5D::AL5D(SSC32U & servoController) 
    : servoController(servoController)
{
}

AL5D::~AL5D()
{
}

void AL5D::gotoPosition(std::map<e_joint, int16_t> position, uint16_t speed, uint16_t time)
{
    servoController.move(e_joint::BASE, position[e_joint::BASE], speed, time);
    servoController.move(e_joint::SHOULDER, position[e_joint::SHOULDER], speed, time);
    servoController.move(e_joint::ELBOW, position[e_joint::ELBOW], speed, time);
    servoController.move(e_joint::WRIST, position[e_joint::WRIST], speed, time);
    servoController.move(e_joint::GRIPPER, position[e_joint::GRIPPER], speed, time);
    servoController.move(e_joint::WRIST_ROTATE, position[e_joint::WRIST_ROTATE], speed, time);
}
    
void AL5D::gotoPosition(enum::e_position position, uint16_t speed, uint16_t time)
{
    switch (position)
    {
        case e_position::PARK:
            this->gotoPosition(POSITION_PRESET::PARK, speed, time);
            break;
        
        case e_position::READY:
            this->gotoPosition(POSITION_PRESET::READY, speed, time);
            break;
        
        case e_position::STRAIGHT_UP:
            this->gotoPosition(POSITION_PRESET::STRAIGHT_UP, speed, time);
            break;
    
        default:
            break;
    }
}