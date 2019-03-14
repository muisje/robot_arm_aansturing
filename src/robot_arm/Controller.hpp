#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP


#include "SSC32U.hpp"
#include "AL5D.hpp"

#include <chrono>
#include <thread>
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 

#include <actionlib/server/simple_action_server.h>
#include <robot_arm_aansturing/setPoseAction.h>
#include <robot_arm_aansturing/setCostumPoseAction.h>




class Controller
{

  public:
    /**
     * @brief Construct a new Controller object
     * 
     * @param a_setPose_name - The node u would like the controller set pose to subscribe to
     * @param a_setCostumPose_name - The node u would like the controller set costum pose to subscribe to
     * @param board - The controller driver for the robotic arm
     * @param ranges - The physical ranges of the arm
     */
    Controller(std::string a_setPose_name, std::string a_setCostumPose_name, SSC32U& board, std::map<e_joint, Range> ranges, const std::map<e_joint, int16_t> & jointOffsets);
    ~Controller(void);
    
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

    

  private:
    AL5D robotArm;


};

#endif