#include "scara_manipulator.h"
#include "electromagnet.h"
#include "motor.h"

int main(void)
{    
    // Used to get the counter position of the dc motor.
    // c2 and c1 are digital INPUT signals.
    // Set to 32 bits and 4x resolution for maximum accuracy since the motor won't be running at max speed.
    quaddec_motor_Start();  
    pwm_1_Start();  // first start the pwm block for the two revolute joint servos
    pwm_motor_Start();
    lcd_display_Start();
    
    for(;;)
    {
        // The initial position should be the rack at the top most position
        rack_pinion_lower(5000);    // lower the rack and pinion
        rack_pinion_raise(5000);    // raise the rack and pinion
        
        
//        manipulator_joint_1_angles(135.0, 180.0); 
//        manipulator_joint_2_angles(-45.0, 0.0);     // range from -90.0 to 90.0 degrees

//        electromagnet_on();
//        CyDelay(2000);
//        electromagnet_off();
//        CyDelay(10000);
    }
}
