#ifndef POSITION_INSTRUCTION_HPP
#define POSITION_INSTRUCTION_HPP

#include "Joint.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <map>

struct PositionInstruction
{
    std::map<e_joint, int16_t> positionStart;
    std::map<e_joint, int16_t> positionGoal;
    boost::posix_time::ptime startTime;
    boost::posix_time::time_duration duration;
};


#endif // POSITION_INSTRUCTION_HPP