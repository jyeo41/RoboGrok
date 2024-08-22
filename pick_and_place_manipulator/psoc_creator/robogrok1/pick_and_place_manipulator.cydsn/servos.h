#ifndef SERVOS_H
#define SERVOS_H

// Make sure to include 'm' in the project > build settings > ARM GCC > assembler/compiler > general > additional include directories
// Do the same for linker but you need to include 'm' for BOTH 'additional libraries' and 'additional library directories'
#include <math.h>
    
#include "project.h"
    
int theta_1(float angle);
int theta_2(float angle);
void servo_1_position_degrees(float angle, int delay);
void servo_2_position_degrees(float angle, int delay);
void servos_position_reset(int delay);
void servos_position_before_dropoff(int delay);
void servo_1_position_xy(float theta, int delay);
void servo_2_position_xy(float theta, int delay);
void servos_position_set_xy(float x, float y, int delay_servo_1, int delay_servo_2);
    
#endif  // SERVOS_H