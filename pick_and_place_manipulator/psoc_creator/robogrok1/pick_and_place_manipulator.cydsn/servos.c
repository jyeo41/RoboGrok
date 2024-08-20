#include "servos.h"

// Subroutine to take in desired user angle for joint 1 and then convert it to the proper compare value
//  to drive the servo to its correct position
float theta_1(float angle)
{
    float compare;  // Returns this value to write to the PWM to turn the servos
    float min_angle = 0;    // Servo 1 moves in an arc from 0 to 180 degrees on the board
    float max_angle = 180;
    float min_compare = 1350;   // Manually tuned the min and max compare values for best accuracy
    float max_compare = 7040;
    
    // The equation to calculate the corresponding compare value when the user provides a desired angle
    compare = (((max_compare - min_compare) / (max_angle - min_angle)) * (angle - min_angle)) + min_compare;
    return compare;
}

float theta_2(float angle)
{
    float compare;
    float min_angle = -90;    // For servo two, the axis of rotation is from -90 to positive 90 due to the positioning of the joint
    float max_angle = 90;
    float min_compare = 1130;
    float max_compare = 7030;
    
    // The equation to calculate the corresponding compare value when the user provides a desired angle
    compare = (((max_compare - min_compare) / (max_angle - min_angle)) * (angle - min_angle)) + min_compare;
    return compare;
}

// Subroutine to actually move the joints to their desired position by writing the calculated compare values to the PWM block
// Angle parameter is between 0.0 and 180.0 degrees for servo 1
// Delay parameter is an integer in milliseconds
void servo_1_position(float angle, int delay)
{
    pwm_servos_WriteCompare1(theta_1(angle));
    CyDelay(delay);
}

// Angle parameter is from -90.0 to 90.0 degrees for servo 2
// Delay parameter is an integer in milliseconds
void servo_2_position(float angle, int delay)
{
    pwm_servos_WriteCompare2(theta_2(angle));
    CyDelay(delay);
}

