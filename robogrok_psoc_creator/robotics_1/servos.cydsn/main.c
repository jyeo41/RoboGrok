#include "project.h"
#include "math.h"

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
    float x = 3.0;  // Desired X position for end effector
    float y = 5.0;  // Desired Y position for end effector
    
    float a2 = 6.0; // measurements of our links on our board example
    float a4 = 5.5;
    float r1 = 0.0;
    float phi1 = 0.0;
    float phi2 = 0.0;
    float phi3 = 0.0;
    float T1 = 0.0; // T1 is theta 1 in radians
    float T2 = 0.0; // T2 is theta 2 in radians
    
    
    r1 = sqrt((x*x) + (y*y));   // Eq. 1 from derivation
    phi1 = acos(((a4*a4) - (a2*a2) - (r1*r1)) / (-2.0 * a2 * r1)); // Eq. 2 for phi 1
    phi2 = atan(y / x); // Eq. 3
    T1 = phi2 - phi1;   // Eq. 4, this is in radians so we need to convert to degrees later for our theta_1 and theta_2 functions
    phi3 = acos(((r1*r1) - (a2*a2) - (a4*a4)) / (-2.0 * a2 * a4)); // Eq. 5 for phi 1
    T2 = 3.14159 - phi3;    // Eq. 6, not 180 because thats degrees, we use pi instead because we are in radians
    
    PWM_1_Start();
    
    for(;;)
    {
        PWM_1_WriteCompare1(theta_1((T1 / 3.14159) * 180));  // Send servo 1 to clockwise position
        PWM_1_WriteCompare2(theta_2((T2 / 3.14159) * 180));
        CyDelay(2000);
        
        
//        PWM_1_WriteCompare1(theta_1(30.0));  // Send servo 1 to clockwise position
//        PWM_1_WriteCompare2(theta_2(90.0));
//        CyDelay(2000);
        
        
//        PWM_1_WriteCompare1(theta_1(180.0));  // Send servo 1 to CCW position
//        CyDelay(2000);
//        
//        PWM_1_WriteCompare2(theta_2(-90.0));
//        CyDelay(2000);
//        PWM_1_WriteCompare2(theta_2(90.0));
//        CyDelay(2000);
    }
}

