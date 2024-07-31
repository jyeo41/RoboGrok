#include "project.h"

float theta_1(float angle)
{
    int compare;
    int min_angle = 0;
    int max_angle = 180;
    int min_comp = 1250;
    int max_comp = 7000;
    
    return compare = (((max_comp - min_comp) / (max_angle - min_angle)) * (angle - min_angle)) + min_comp;
}

float theta_2(float angle)
{
    int compare;
    int min_angle = -90;
    int max_angle = 90;
    int min_comp = 1100;
    int max_comp = 6800;
    
    return compare = (((max_comp - min_comp) / (max_angle - min_angle)) * (angle - min_angle)) + min_comp;
}

int main(void)
{
    PWM_1_Start();
    
    for(;;)
    {
        PWM_1_WriteCompare1(theta_1(30.0));  // Send servo 1 to clockwise position
        PWM_1_WriteCompare2(theta_2(90.0));
        CyDelay(2000);
        
        
//        PWM_1_WriteCompare1(theta_1(180.0));  // Send servo 1 to CCW position
//        CyDelay(2000);
//        
//        PWM_1_WriteCompare2(theta_2(-90.0));
//        CyDelay(2000);
//        PWM_1_WriteCompare2(theta_2(90.0));
//        CyDelay(2000);
    }
}

