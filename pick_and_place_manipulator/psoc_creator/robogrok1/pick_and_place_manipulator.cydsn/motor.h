#ifndef MOTOR_H
#define MOTOR_H
    
#include "project.h"
    
// All of these define macros are used for the rack and pinion's positioning.
// RESET is for moving the rack and pinion to the top most position as the base "starting" position with the encoder at 0 count.
// BELOW CAMERA is to get the rack low enough so it doesn't hit the camera.
// PICKUP OBJECT is used when the servos have reached the object destination and its time to pick up the object with the magnet.
// DROPOFF BIN is used to get the rack high enough to avoid hitting the dropoff bin.
#define TARGET_RESET 0
#define TARGET_BELOW_CAMERA 1000
#define TARGET_PICKUP_OBJECT 2000
#define TARGET_DROPOFF_BIN 400
    
void rack_pinion_lower(int time_delay, int target);
void rack_pinion_raise(int time_delay, int target);



#endif // MOTOR_H