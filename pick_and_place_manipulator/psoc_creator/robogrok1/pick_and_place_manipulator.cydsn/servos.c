#include "servos.h"

// Subroutine to take in desired user angle for joint 1 and then convert it to the proper compare value
//  to drive the servo to its correct position
int theta_1(float angle)
{
    int compare;  // Returns this value to write to the PWM to turn the servos
    int min_angle = 0;    // Servo 1 moves in an arc from 0 to 180 degrees on the board
    int max_angle = 180;
    int min_compare = 1330;   // Decreasing this value makes the servo turn more opposite of the RH rule
    int max_compare = 7100;   // Increasing this value makes the servo turn more with the RH rule
    
    // The equation to calculate the corresponding compare value when the user provides a desired angle
    compare = (((max_compare - min_compare) / (max_angle - min_angle)) * (angle - min_angle)) + min_compare;
    return compare;
}

int theta_2(float angle)
{
    int compare;
    int min_angle = -90;    // For servo two, the axis of rotation is from -90 to positive 90 due to the positioning of the joint
    int max_angle = 90;
    int min_compare = 1200; // Decreasing this value makes the servo turn more opposite of the RH rule
    int max_compare = 7050; // Increasing this value makes the servo turn more with the RH rule
    
    // The equation to calculate the corresponding compare value when the user provides a desired angle
    compare = (((max_compare - min_compare) / (max_angle - min_angle)) * (angle - min_angle)) + min_compare;
    return compare;
}

// Subroutine to actually move the joints to their desired position by writing the calculated compare values to the PWM block
// Angle parameter is between 0.0 and 180.0 degrees for servo 1
// Delay parameter is an integer in milliseconds
void servo_1_position_degrees(float angle, int delay)
{
    pwm_servos_WriteCompare1(theta_1(angle));
    CyDelay(delay);
}

// Angle parameter is from -90.0 to 90.0 degrees for servo 2
// Delay parameter is an integer in milliseconds
void servo_2_position_degrees(float angle, int delay)
{
    pwm_servos_WriteCompare2(theta_2(angle));
    CyDelay(delay);
}

// Function call to reset the servos position to neutral
void servos_position_reset(int delay)
{
    servo_1_position_degrees(0.0, delay);
    servo_2_position_degrees(0.0, delay);
}

// Function call to reset the servos position to neutral
void servos_position_before_dropoff(int delay)
{
    servo_1_position_degrees(0.0, delay);
    servo_2_position_degrees(25.0, delay);
}

// Modified subroutines to move servo joints using X and Y coordinates relative to the board grid rather than degree parameters
// Delay parameter is an integer in milliseconds
void servo_1_position_xy(float theta, int delay)
{
    pwm_servos_WriteCompare1(theta_1((theta / M_PI) * 180.0));
    CyDelay(delay);
}

// Angle parameter is from -90.0 to 90.0 degrees for servo 2
// Delay parameter is an integer in milliseconds
void servo_2_position_xy(float theta, int delay)
{
    pwm_servos_WriteCompare2(theta_2((theta / M_PI) * 180.0));
    CyDelay(delay);
}

// Subroutine to move the servos and end effector into the desired X and Y coordinates in Quadrant 1 of the board grid.
// Takes in the desired X and Y positions as well as a delay to set after moving each revolute joint servo.
// Note: The servo has a workspace it can target and if the desired coordinates cannot be reached it will result in
//       undefined behavior where the servo moves erratically to a random position, or it just does not move at all
//
// The following graph is a rough estimation of the manipulator workspace having tested each possible coordinate from test.c file
// The o's represent valid coordinates and the x's represent invalid coordinates
//
// 15 x x x x x x x x x x x x x x x x
//    x x x x x x x x x x x x x x x x
//    o o o o o x x x x x x x x x x x
//    o o o o o o o x x x x x x x x x
//    o o o o o o o o o x x x x x x x
// 10 o o o o o o o o o o x x x x x x
//    o o o o o o o o o o o x x x x x
//    o o o o o o o o o o o o x x x x
//    x x x o o o o o o o o o x x x x
//    x x x x x x x x x x o o o x x x
// 5  x x x x x x x x x x x o o x x x
//    x x x x x x x x x x x x o o x x
//    x x x x x x x x x x x x x o x x
//    x x x x x x x x x x x x x x x x
//    x x x x x x x x x x x x x x x x 
// 0  x x x x x x x x x x x x x x x x
//
//    0         5         10        15
//
void servos_position_set_xy(float x, float y, int delay_servo_1, int delay_servo_2)
{
    static const float a2 = 5.8;    // link lengths in centimeters, tuned to be within a fraction of a cm for targeted coordinates
    static const float a4 = 7.6;    // original tuning, 6.5 and 7.3
    
    float r1 = 0.0;
    float phi_1 = 0.0;
    float phi_2 = 0.0;
    float phi_3 = 0.0;
    float theta_1 = 0.0;
    float theta_2 = 0.0;
    
    // inverse kinematics equations to calculate the values for the joint variables theta_1 and theta_2
    r1 = sqrt((x * x) + (y * y));   // equation 1
    phi_1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));   // equation 2
    phi_2 = atan(y / x);    // equation 3
    theta_1 = phi_2 - phi_1;    // equation 4
    phi_3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));   // equation 5
    theta_2 = M_PI - phi_3;    // equation 6
    
    servo_1_position_xy(theta_1, delay_servo_1);    // use the calculated theta variables to move the servos to the desired position
    servo_2_position_xy(theta_2, delay_servo_2);
}
