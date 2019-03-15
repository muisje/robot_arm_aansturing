#include "Queue.hpp"

Queue::Queue(AL5D &a_robotArm) :robotArm(a_robotArm)
{

}


Queue::~Queue()
{
    
}

void Queue::addToQueue(const std::map<e_joint, int16_t>& s_position, const uint16_t s_speed, const uint16_t s_time)
{
    queue.push(armTask{ s_position ,s_speed ,s_time });
}


void Queue::checkQueue()
{
    while(queue.size() > 0)
    {
        robotArm.gotoPosition(queue.front().s_position, queue.front().s_time, queue.front().s_speed);

        queue.pop();
    }
}