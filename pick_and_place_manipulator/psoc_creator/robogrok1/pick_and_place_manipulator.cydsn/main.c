#include "servos.h"
#include "electromagnet.h"
#include "motor.h"

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
        // The initial position should be the rack at the top most position
        servo_1_position(135.0, 1000);
        servo_2_position(45.0, 3000);
        rack_pinion_lower(3000);
        rack_pinion_raise(3000);
        
        servo_1_position(0.0, 1000);
        servo_2_position(0.0, 2000);
        rack_pinion_lower(3000);
        rack_pinion_raise(3000);

//        electromagnet_on();
//        CyDelay(2000);
//        electromagnet_off();
//        CyDelay(10000);
    }
}
