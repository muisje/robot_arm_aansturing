#ifndef POSITION_HPP
#define POSITION_HPP

#include "Joint.hpp"
#include <map>
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 

enum e_position {PARK, READY, STRAIGHT_UP};

namespace POSITION_PRESET
{
    const std::map<e_joint, int16_t> PARK = boost::assign::map_list_of
        (e_joint::BASE, 0) (e_joint::SHOULDER, 45) (e_joint::ELBOW, 70)
        (e_joint::WRIST, -60) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);

    const std::map<e_joint, int16_t> READY = boost::assign::map_list_of
        (e_joint::BASE, 0) (e_joint::SHOULDER, 30) (e_joint::ELBOW, 30)
        (e_joint::WRIST, -30) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);

    const std::map<e_joint, int16_t> STRAIGHT_UP = boost::assign::map_list_of
        (e_joint::BASE, 0) (e_joint::SHOULDER, 0) (e_joint::ELBOW, 0)
        (e_joint::WRIST, -60) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);
}


#endif