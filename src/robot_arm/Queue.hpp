#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <queue> 
#include <map>
#include "Joint.hpp"
#include "AL5D.hpp"
#include <list>

struct armTask
{
  std::map<e_joint, int16_t> s_position;
  uint16_t s_speed = 0;
  uint16_t s_time = 0;
};

class Queue
{
    public:

        Queue(AL5D &a_robotArm);
        ~Queue();

        void addToQueue(const std::map<e_joint, int16_t>& s_position, const uint16_t s_speed, const uint16_t s_time);
        void checkQueue();
        void emptyQueue();

    private:
        std::list<armTask> queue; 
        AL5D robotArm;
};

#endif
