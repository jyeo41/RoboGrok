#include "servos.h"
#include "electromagnet.h"
#include "motor.h"
#include "test.h"

int main(void)
{       
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
        CyDelay(3000);  // give time to plug in the external PSU
//        test_manipulator_workspace();
        
        servos_position_reset();
        servos_position_set_xy(7.0, 9.0, 1000, 2000);
        rack_pinion_lower(2000);
        rack_pinion_raise(10);
        servos_position_reset();
        rack_pinion_lower(2000);
        rack_pinion_raise(10);
        
//        electromagnet_on();
//        CyDelay(2000);
//        electromagnet_off();
//        CyDelay(10000);
    }
}
