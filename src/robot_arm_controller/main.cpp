#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <robot_arm_aansturing/setPoseAction.h>
#include <robot_arm_aansturing/setCostumPoseAction.h>

// Called once when the goal completes
// void doneCb(const actionlib::SimpleClientGoalState& state,
//             const FibonacciResultConstPtr& result)
// {
//   ROS_INFO("Finished in state [%s]", state.toString().c_str());
//   ROS_INFO("Answer: %i", result->finalLocation);
//   ros::shutdown();
// }

// // Called once when the goal becomes active
// void activeCb()
// {
//   ROS_INFO("Goal just went active");
// }

// void feedbackCb(const FibonacciFeedbackConstPtr& feedback)
// {
//   ROS_INFO("Got Feedback of length %lu", feedback->currentLocation);
// }


int main(int argc,char**argv)
{   

    if(argc == 1)
    {
    // Announce this program to the ROS master as a "node" called "hello_world_node"
    ros::init(argc,argv,"robot_arm");
    // Start the node resource managers (communication, time, etc)

    actionlib::SimpleActionClient<robot_arm_aansturing::setPoseAction> ac("robot_arm", true);
    

    ros::start();
    // Broadcast a simple log message
    ROS_INFO_STREAM("Hello, world!");
    // Process ROS callbacks until receiving a SIGINT (ctrl-c)

    ac.waitForServer();

    robot_arm_aansturing::setPoseGoal goal;
    goal.pos = 1;

    ac.sendGoal(goal);

    ac.waitForResult(ros::Duration(30.0));
    }else
    {
    ros::init(argc,argv,"test");
    // Start the node resource managers (communication, time, etc)

    actionlib::SimpleActionClient<robot_arm_aansturing::setCostumPoseAction> ac("test", true);
    

    ros::start();
    // Broadcast a simple log message
    ROS_INFO_STREAM("Hello, world!");
    // Process ROS callbacks until receiving a SIGINT (ctrl-c)

    ac.waitForServer();

    ROS_INFO_STREAM("Hello!");

    robot_arm_aansturing::setCostumPoseGoal goal;
    goal.a_Base = 1;

    ac.sendGoal(goal);

    ac.waitForResult(ros::Duration(30.0));
    }
    
    return 0;
}
