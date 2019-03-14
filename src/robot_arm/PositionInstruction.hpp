/**
 * @file PositionInstruction.hpp
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl)
 * @brief a storage struct to have data easily combined of an position instruction.
 * @version 0.1
 * @date 2019-03-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
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


#endif // POSITION_INSTRUCTION_HPP    const int max_pulse = 2500;

