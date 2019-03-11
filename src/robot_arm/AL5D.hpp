#ifndef AL5D_HPP
#define AL5D_HPP

#include "SSC32U.hpp"
#include "Position.hpp"
#include "Joint.hpp"
#include "Range.hpp"
#include <map>

class AL5D
{
private:
    SSC32U servoController;
    std::map<e_joint, Range> jointRanges;

    bool validateJointRanges(const std::map<e_joint, int16_t> position); 

public:
    AL5D(SSC32U & servoController, const std::map<e_joint, Range> & jointRanges);
    ~AL5D();

    bool gotoPosition(enum::e_position position, uint16_t speed = 0, uint16_t time = 0);
    bool gotoPosition(std::map<e_joint, int16_t> position, uint16_t speed = 0, uint16_t time = 0);
    void stopAllMotorFunctions();
};

#endif