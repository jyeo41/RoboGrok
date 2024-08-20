#include "scara_manipulator.h"

// Subroutine to take in desired user angle for joint 1 and then convert it to the proper compare value
//  to drive the servo to its correct position
float theta_1(float angle)
{
    float compare;
    float min_angle = 0;
    float max_angle = 180;
    float min_compare = 1350;
    float max_compare = 7040;
    
    // the equation to calculate the corresponding compare value when the user provides a desired angle
    compare = (((max_compare - min_compare) / (max_angle - min_angle)) * (angle - min_angle)) + min_compare;
    return compare;
}

float theta_2(float angle)
{
    float compare;
    float min_angle = -90;    // for servo two, the axis of rotation is from -90 to positive 90 due to the positioning of the joint
    float max_angle = 90;
    float min_compare = 1130;
    float max_compare = 7030;
    
    // the equation to calculate the corresponding compare value when the user provides a desired angle
    compare = (((max_compare - min_compare) / (max_angle - min_angle)) * (angle - min_angle)) + min_compare;
    return compare;
}

// Subroutine to actually move the joints to their desired position by writing the calculated compare values to the PWM block
void manipulator_joint_1_angles(float angle_1, float angle_2)
{
    pwm_1_WriteCompare1(theta_1(angle_1));  // send servo 1 to clockwise position
    CyDelay(3000);
    pwm_1_WriteCompare1(theta_1(angle_2));  // send servo 1 to counter clockwise position
    CyDelay(3000);
}

void manipulator_joint_2_angles(float angle_1, float angle_2)
{
    pwm_1_WriteCompare2(theta_2(angle_1));  // send servo 1 to clockwise position
    CyDelay(3000);
    pwm_1_WriteCompare2(theta_2(angle_2));  // send servo 1 to counter clockwise position
    CyDelay(3000);
}

