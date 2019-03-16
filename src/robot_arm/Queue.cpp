#define TIMING

#include "Queue.hpp"
#include <ros/console.h>

#ifdef TIMING
#include <iostream>
#include <chrono>
#include <thread>
#endif // TIMING

Queue::Queue(AL5D &a_robotArm) :robotArm(a_robotArm)
{
}

Queue::~Queue()
{
}

void Queue::addToQueue(const std::map<e_joint, int16_t>& s_position, const uint16_t s_speed, const uint16_t s_time)
{
    ROS_DEBUG("EVENT: adding position instruction");
    #ifdef TIMING
        auto start = std::chrono::high_resolution_clock::now();
    #endif //timing
    queue.push_back(armTask{s_position, s_speed, s_time});
    #ifdef TIMING
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "queue.push_back took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
              << " milliseconds\n";
    #endif
}

void Queue::checkQueue()
{
    setMovingState();

    while(queue.size() > 0 && robotArm.isAtDestination())
    {
        ROS_DEBUG("EVENT: executing position instruction");
        #ifdef TIMING
            auto start = std::chrono::high_resolution_clock::now();
        #endif //timing
        if(robotArm.gotoPosition(queue.front().s_position, queue.front().s_speed, queue.front().s_time))
        {
            queue.pop_front();
        }
        else
        {
            ROS_WARN("QoS-Warning: not able to move to position.");
            queue.pop_front();
        }
        #ifdef TIMING
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "robotArm.gotoPosition took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
              << " milliseconds\n";
        #endif
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