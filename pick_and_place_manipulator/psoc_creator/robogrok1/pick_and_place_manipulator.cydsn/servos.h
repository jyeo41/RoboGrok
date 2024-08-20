#ifndef SERVOS_H
#define SERVOS_H
    
#include "project.h"
    
float theta_1(float angle);
float theta_2(float angle);
void servo_1_position(float angle, int delay);
void servo_2_position(float angle, int delay);
    
#endif  // SERVOS_H