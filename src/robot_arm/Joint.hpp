/**
 * @brief All the joints of the used robot arm. The values are the signal pins the servo joint is connected to on the servocontroller board. 
 * 
 */
#ifndef JOINT_HPP
#define JOINT_HPP

enum e_joint {BASE = 0, SHOULDER = 1, ELBOW = 2, WRIST = 3, GRIPPER = 4, WRIST_ROTATE = 5};

#endif