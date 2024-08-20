#ifndef SCARA_MANIPULATOR_H
#define SCARA_MANIPULATOR_H
    
#include "project.h"
    
float theta_1(float angle);
float theta_2(float angle);
void manipulator_joint_1_angles(float angle_1, float angle_2);
void manipulator_joint_2_angles(float angle_1, float angle_2);
    
#endif  // SCARA_MANIPULATOR_H