#include "Queue.hpp"
#include <ros/console.h>

Queue::Queue(AL5D &a_robotArm) :robotArm(a_robotArm)
{
}

Queue::~Queue()
{
}

void Queue::addToQueue(const std::map<e_joint, int16_t>& s_position, const uint16_t s_speed, const uint16_t s_time)
{
    ROS_DEBUG("EVENT: adding position instruction");
    queue.push_back(armTask{s_position, s_speed, s_time});
}

void Queue::checkQueue()
{
    setMovingState();

    while(queue.size() > 0 && robotArm.isAtDestination())
    {
        ROS_DEBUG("EVENT: executing position instruction");
        if(robotArm.gotoPosition(queue.front().s_position, queue.front().s_speed, queue.front().s_time))
        {
            queue.pop_front();
        }
        else
        {
            ROS_WARN("QoS-Warning: not able to move to position.");
            queue.pop_front();
        }
    }
}
 
void Queue::emptyQueue()
{
    ROS_DEBUG("EVENT: emptying queue");
    while (!queue.empty())
    {
        queue.pop_front();
    }
    robotArm.stopAllMotorFunctions();
}

void Queue::setMovingState()
{
    ROS_DEBUG("EVENT: setting moving state");
    bool status = robotArm.isAtDestination();

    if(standby != status)
    {
        standby = status;
        
        if(!status)
        {
            ROS_INFO("STATE: MOVING");
        }
        else
        {
            ROS_INFO("STATE: NOT_MOVING");
        }
    }
}