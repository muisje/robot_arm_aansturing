/**
 * @file Position.hpp
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl)
 * @brief Preset positions like park, ready and straight up.
 * @version 0.1
 * @date 2019-03-14
 * 
 */
#ifndef POSITION_HPP
#define POSITION_HPP

#include "Joint.hpp"
#include <map>
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 

namespace POSITION_PRESET
{
    const std::map<e_joint, int16_t> PARK = boost::assign::map_list_of
        (e_joint::BASE, 00) (e_joint::SHOULDER, 45) (e_joint::ELBOW, 115)
        (e_joint::WRIST, -80) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);

    const std::map<e_joint, int16_t> READY = boost::assign::map_list_of
        (e_joint::BASE, 00) (e_joint::SHOULDER, 30) (e_joint::ELBOW, 70)
        (e_joint::WRIST, -80) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);

    const std::map<e_joint, int16_t> STRAIGHT_UP = boost::assign::map_list_of
        (e_joint::BASE, 0) (e_joint::SHOULDER, 0) (e_joint::ELBOW, 0)
        (e_joint::WRIST, -60) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);
    
    const std::map<e_joint, int16_t> IMPOSSIBLE = boost::assign::map_list_of
        (e_joint::BASE, 180) (e_joint::SHOULDER, 0) (e_joint::ELBOW, 0)
        (e_joint::WRIST, 0) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);

    const std::map<e_joint, int16_t> POSSIBLE = boost::assign::map_list_of
        (e_joint::BASE, 0) (e_joint::SHOULDER, 0) (e_joint::ELBOW, 0)
        (e_joint::WRIST, 0) (e_joint::GRIPPER, 180) (e_joint::WRIST_ROTATE, 0);
}


#endif