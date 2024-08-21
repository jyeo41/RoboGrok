#include "servos.h"
#include "electromagnet.h"
#include "motor.h"
#include "math.h"

int main(void)
{   
    float x = 4.0;    // desired x position as input
    float y = 7.0;    // desired y position as input
    
    const float a2 = 5.2;   // link length constants, incresing this contsant decreases the x positioning of the end effector
    const float a4 = 6.7;   // link length constant, increasing this constant decreases the y positioning of the end effector
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
    theta_2 = 3.14159 - phi_3;    // equation 6
    
    // Used to get the counter position of the dc motor.
    // c2 and c1 are digital INPUT signals.
    // Set to 32 bits and 4x resolution for maximum accuracy since the motor won't be running at max speed.
    quaddec_motor_Start();  
    
    // Initialization for all the relevant peripherals blocks
    pwm_servos_Start();  
    pwm_motor_Start();
    lcd_display_Start();
    
    for(;;)
    {
        CyDelay(5000);  // give time to plug in the external PSU
        // The initial position should be the rack at the top most position
        servo_1_position_xy(theta_1, 1000);
        servo_2_position_xy(theta_2, 3000);
        rack_pinion_lower(5000);
        rack_pinion_raise(3000);
        
//        servo_1_position_xy(theta_1, 1000);
//        servo_2_position_xy(theta_2, 2000);
//        rack_pinion_lower(3000);
//        rack_pinion_raise(3000);

//        electromagnet_on();
//        CyDelay(2000);
//        electromagnet_off();
//        CyDelay(10000);
    }
}
