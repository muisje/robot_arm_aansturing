#include <actionlib/server/simple_action_server.h>
#include <robot_arm_aansturing/setPoseAction.h>
#include <robot_arm_aansturing/setCostumPoseAction.h>

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Controller
{
  protected:
  

    //Action setPose
    robot_arm_aansturing::setPoseFeedback setPose_feedback;
    robot_arm_aansturing::setPoseResult setPose_result;

    ros::NodeHandle setPose_nh;
    actionlib::SimpleActionServer<robot_arm_aansturing::setPoseAction> setPose_as;

    std::string setPose_name;

    //Action setCostumPose
    robot_arm_aansturing::setCostumPoseFeedback setCostumPose_feedback;
    robot_arm_aansturing::setCostumPoseResult setCostumPose_result;

    ros::NodeHandle setCostumPose_nh;
    actionlib::SimpleActionServer<robot_arm_aansturing::setCostumPoseAction> setCostumPose_as;

    std::string setCostumPose_name;

  public:
    Controller(std::string name, std::string aname);
    ~Controller(void);

    void executePose(const robot_arm_aansturing::setPoseGoalConstPtr &goal);
    void executeCostumPose(const robot_arm_aansturing::setCostumPoseGoalConstPtr &goal);

};

#endif