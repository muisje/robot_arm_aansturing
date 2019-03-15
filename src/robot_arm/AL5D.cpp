#include "AL5D.hpp"

#include <iostream>

AL5D::AL5D(SSC32U & servoController, const std::map<e_joint, Range> & jointRanges, const std::map<e_joint, int16_t> & jointOffsets) 
    : servoController(servoController), jointRanges(jointRanges), jointOffsets(jointOffsets)
{
}

AL5D::~AL5D()
{
}

bool AL5D::validateJointRanges( const std::map<e_joint, int16_t> position)
{
    for (auto const & value : position)
    {
        std::map<e_joint, Range>::iterator jointRange = jointRanges.find(value.first);
        if (jointRange != jointRanges.end())
        {
            if ( value.second < jointRange->second.min || value.second > jointRange->second.max )
            {
                return false;
            }
        }
    }
    return true;
}

int16_t AL5D::getCorrectedJointPosition(e_joint joint, int16_t orginalJointPosition)
{
    std::map<e_joint, int16_t>::iterator jointOffset = this->jointOffsets.find(joint);
    if (jointOffset == jointOffsets.end())
    {
        return orginalJointPosition;
    }
    return orginalJointPosition + jointOffset->second;
}
    

void AL5D::stopAllMotorFunctions()
{
    this->gotoPosition(this->getCurrentPosition());
}

std::map<e_joint, int16_t> AL5D::getCurrentPosition()
{
    if (currentInstruction.duration == boost::posix_time::time_duration(0,0,0,0))
    {
        return currentInstruction.positionGoal;
    }

    boost::posix_time::time_duration diff =  boost::posix_time::microsec_clock::local_time() - currentInstruction.startTime;

    #ifdef DEBUG
    std::cout << to_simple_string(diff) << std::endl; 
    #endif

    if (diff >= currentInstruction.duration)
    {
        //TODO maybe debug already at goal
        return currentInstruction.positionGoal;
    }
    else
    {
        double progress = double(diff.total_milliseconds()) / double(currentInstruction.duration.total_milliseconds() ) ;
        
        #ifdef DEBUG
        std::cout << "currentInstruction.duration " << to_simple_string(currentInstruction.duration) << std::endl;
        std::cout << "progress = " << std::to_string(currentInstruction.duration.total_milliseconds()) << " / " << std::to_string(diff.total_milliseconds()) << " = " << std::to_string(progress) << std::endl;
        #endif

        std::map<e_joint, int16_t> currentPosition;
        for (auto const & jointStart : currentInstruction.positionStart)
        {
            int16_t currentJointPosition = round((currentInstruction.positionGoal[jointStart.first] - jointStart.second ) * progress + jointStart.second);
            currentPosition.insert(std::pair<e_joint, int16_t>(jointStart.first, currentJointPosition));
            #ifdef DEBUG
            std::cout << std::to_string(currentInstruction.positionGoal[jointStart.first]) << " - " << std::to_string(jointStart.second) << "*" << std::to_string(progress) << " + " << std::to_string(jointStart.second) << " = " << std::to_string(currentJointPosition) << std::endl;
            #endif
        }
        return currentPosition;
    }
}

bool AL5D::gotoPosition(std::map<e_joint, int16_t> position, uint16_t speed, uint16_t time)
{
    if(!this->validateJointRanges(position))
    {
        return false;
    }
    if (this->currentInstruction.positionStart.empty())
    {
        this->currentInstruction.positionStart = POSITION_PRESET::PARK;
    }
    else
    {
        this->currentInstruction.positionStart = this->currentInstruction.positionGoal;
    }
    
    this->currentInstruction.positionGoal = position;
    this->currentInstruction.startTime = boost::posix_time::microsec_clock::local_time();
    this->currentInstruction.duration = boost::posix_time::milliseconds(time);
    
    #ifdef DEBUG
    std::cout << "given time " << std::to_string(time) << std::endl;
    std::cout << "set current duration: " << to_simple_string(this->currentInstruction.duration) << std::endl;
    #endif

    servoController.move(e_joint::BASE,         getCorrectedJointPosition(e_joint::BASE,            position[e_joint::BASE]),           speed, time);
    servoController.move(e_joint::SHOULDER,     getCorrectedJointPosition(e_joint::SHOULDER,        position[e_joint::SHOULDER]),       speed, time);
    servoController.move(e_joint::ELBOW,        getCorrectedJointPosition(e_joint::ELBOW,           position[e_joint::ELBOW]),          speed, time);
    servoController.move(e_joint::WRIST,        getCorrectedJointPosition(e_joint::WRIST,           position[e_joint::WRIST]),          speed, time);
    servoController.move(e_joint::GRIPPER,      getCorrectedJointPosition(e_joint::GRIPPER,         position[e_joint::GRIPPER]),        speed, time);
    servoController.move(e_joint::WRIST_ROTATE, getCorrectedJointPosition(e_joint::WRIST_ROTATE,    position[e_joint::WRIST_ROTATE]),   speed, time);
    return true;
}

bool AL5D::isAtDestination()
{
    auto currentPosition = this->getCurrentPosition();
    auto goalPosition = this->currentInstruction.positionGoal;

    return currentPosition.size() == goalPosition.size()
        && std::equal(goalPosition.begin(), goalPosition.end(),
                      currentPosition.begin());    
}