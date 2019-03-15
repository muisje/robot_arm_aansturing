/**
 * @file ArmOffset.hpp
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl)
 * @brief Predefined offsets used for using robots that have a different base position for one or more joints
 * @version 0.1
 * @date 2019-03-14
 * 
 */
#ifndef ARM_OFFSET
#define ARM_OFFSET

#include "Joint.hpp"
#include <map>
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 
#include <inttypes.h>

namespace ArmOffset
{
    const std::map<e_joint, int16_t> ROBOT_1 = boost::assign::map_list_of
    (e_joint::BASE, 0) (e_joint::SHOULDER, -6) (e_joint::ELBOW, -80)
    (e_joint::WRIST, 5) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);
    
    const std::map<e_joint, int16_t> ROBOT_2 = boost::assign::map_list_of
    (e_joint::BASE, 0) (e_joint::SHOULDER, 0) (e_joint::ELBOW, -70)
    (e_joint::WRIST, 0) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);
    
    const std::map<e_joint, int16_t> ROBOT_3 = boost::assign::map_list_of
    (e_joint::BASE, 0) (e_joint::SHOULDER, 5) (e_joint::ELBOW, -70)
    (e_joint::WRIST, 10) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);
    
    //? robot 4 is broken

    const std::map<e_joint, int16_t> ROBOT_5 = boost::assign::map_list_of
    (e_joint::BASE, 0) (e_joint::SHOULDER, -5) (e_joint::ELBOW, -80)
    (e_joint::WRIST, 0) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);
    
    const std::map<e_joint, int16_t> ROBOT_6 = boost::assign::map_list_of
    (e_joint::BASE, 0) (e_joint::SHOULDER, 2) (e_joint::ELBOW, -60)
    (e_joint::WRIST, 2) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);
    
    const std::map<e_joint, int16_t> ROBOT_7 = boost::assign::map_list_of
    (e_joint::BASE, 0) (e_joint::SHOULDER, 0) (e_joint::ELBOW, -75)
    (e_joint::WRIST, 10) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);
    
    //? 8 is broken
}

#endif // ARM_OFFSET