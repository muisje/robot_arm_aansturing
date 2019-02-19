#include <actionlib/server/simple_action_server.h>
#include <robot_arm_aansturing/setPoseAction.h>

class Controller
{
  protected:
  
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<robot_arm_aansturing::setPoseAction> as_;

    std::string action_name_;


    //Action
    robot_arm_aansturing::setPoseFeedback feedback_;
    robot_arm_aansturing::setPoseResult result_;


  public:
    Controller(std::string name) : 
    as_(nh_, name, boost::bind(&Controller::executeCB, this, _1), false),
    action_name_(name)
    {
        as_.start();
    }

    ~Controller(void)
    {
    }

    void executeCB(const robot_arm_aansturing::setPoseGoalConstPtr &goal)
    {
        std::cout << "Executing someting" <<std::endl;
        result_.finalPose = "yeay";
        as_.setSucceeded(result_);

    }
};