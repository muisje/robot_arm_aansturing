#ifndef ARM_OFFSET
#define ARM_OFFSET

#include "Joint.hpp"
#include <map>
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 
#include <inttypes.h>

namespace ArmOffset
{
    const std::map<e_joint, int16_t> ROBOT_2 = boost::assign::map_list_of
    (e_joint::BASE, 0) (e_joint::SHOULDER, 0) (e_joint::ELBOW, -70)
    (e_joint::WRIST, 0) (e_joint::GRIPPER, 0) (e_joint::WRIST_ROTATE, 0);
}

#endif // ARM_OFFSET