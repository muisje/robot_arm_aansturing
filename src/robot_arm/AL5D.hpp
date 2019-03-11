#ifndef AL5D_HPP
#define AL5D_HPP

#include "SSC32U.hpp"
#include "Position.hpp"
#include "Joint.hpp"
#include <map>

class AL5D
{
private:
    /* data */
    SSC32U servoController;

public:
    AL5D(SSC32U & servoController);
    ~AL5D();

    void gotoPosition(enum::e_position position, uint16_t speed = 0, uint16_t time = 0);
    void gotoPosition(std::map<e_joint, int16_t> position, uint16_t speed = 0, uint16_t time = 0);
    void stopAllMotorFunctions();
};

#endif