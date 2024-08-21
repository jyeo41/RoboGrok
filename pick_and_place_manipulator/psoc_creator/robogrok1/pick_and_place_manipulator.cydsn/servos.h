#ifndef SERVOS_H
#define SERVOS_H
    
#include "project.h"
    
float theta_1(float angle);
float theta_2(float angle);
void servo_1_position_degrees(float angle, int delay);
void servo_2_position_degrees(float angle, int delay);
void servo_1_position_xy(float theta, int delay);
void servo_2_position_xy(float theta, int delay);
    
#endif  // SERVOS_H