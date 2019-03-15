#ifndef MESSAGEAHNDLER_HPP
#define MESSAGEAHNDLER_HPP


#include "SSC32U.hpp"
#include "AL5D.hpp"

#include <chrono>
#include <thread>
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 
#include "Queue.hpp"

#include <actionlib/server/simple_action_server.h>
#include <robot_arm_aansturing/setPoseAction.h>
#include <robot_arm_aansturing/setCostumPoseAction.h>
#include <robot_arm_aansturing/emergencyAction.h>


class MessageHandler
{

  public:
    /**
     * @brief Construct a new MessageHandler object
     * 
     * @param a_setPose_name - The node u would like the MessageHandler set pose to subscribe to
     * @param a_setCostumPose_name - The node u would like the MessageHandler set costum pose to subscribe to
     * @param ranges - The physical ranges of the arm
     */
    MessageHandler(std::string _setPose_name, std::string a_setCostumPose_name, std::string a_emergency_name, std::shared_ptr<Queue> a_queue);
    ~MessageHandler(void);
    /**
     * @brief This function will be executed when a pose message is recieved
     * 
     * @param goal - The action goal variable from the sender
     */
    void executePose(const robot_arm_aansturing::setPoseGoalConstPtr &goal);

    /**
     * @brief This function will be executed when a costum pose message is recieved
     * 
     * @param goal 
     */
    void executeCostumPose(const robot_arm_aansturing::setCostumPoseGoalConstPtr &goal);

    /**
     * @brief This function will be executed when a costum pose message is recieved
     * 
     * @param goal 
     */
    void executeEmergency(const robot_arm_aansturing::emergencyGoalConstPtr &goal);

  protected:

    /**
     * @brief Pose action varible
     * 
     */
    robot_arm_aansturing::setPoseFeedback setPose_feedback;
    robot_arm_aansturing::setPoseResult setPose_result;

    ros::NodeHandle setPose_nh;
    actionlib::SimpleActionServer<robot_arm_aansturing::setPoseAction> setPose_as;

    std::string setPose_name;
    
    /**
     * @brief Constom pose action varible
     * 
     */
    robot_arm_aansturing::setCostumPoseFeedback setCostumPose_feedback;
    robot_arm_aansturing::setCostumPoseResult setCostumPose_result;

    ros::NodeHandle setCostumPose_nh;
    actionlib::SimpleActionServer<robot_arm_aansturing::setCostumPoseAction> setCostumPose_as;

    std::string setCostumPose_name;

    /**
     * @brief Emergency action varible
     * 
     */
    robot_arm_aansturing::emergencyFeedback emergency_feedback;
    robot_arm_aansturing::emergencyResult emergency_result;

    ros::NodeHandle emergency_nh;
    actionlib::SimpleActionServer<robot_arm_aansturing::emergencyAction> emergency_as;

    std::string emergency_name;

    

  private:
  std::shared_ptr<Queue> queue;
  
};

#endif