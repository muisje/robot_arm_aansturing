#ifndef RANGES_HPP
#define RANGES_HPP

#include "Joint.hpp"
#include <map>
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 

namespace Ranges
{
std::map<e_joint, Range> AL5DRanges = boost::assign::map_list_of
    (e_joint::BASE, Range{-90, 0}) (e_joint::SHOULDER, Range{-30, 90}) (e_joint::ELBOW, Range{0, 135})
    (e_joint::WRIST, Range{-90, 90}) (e_joint::WRIST_ROTATE, Range{-90, 90});

}

#endif