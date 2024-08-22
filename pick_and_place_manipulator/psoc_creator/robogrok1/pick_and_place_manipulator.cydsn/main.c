#include "servos.h"
#include "electromagnet.h"
#include "motor.h"
#include "test.h"
#include "uart.h"

// All of these define macros are used for the rack and pinion's positioning.
// RESET is for moving the rack and pinion to the top most position as the base "starting" position with the encoder at 0 count.
// BELOW CAMERA is to get the rack low enough so it doesn't hit the camera.
// PICKUP OBJECT is used when the servos have reached the object destination and its time to pick up the object with the magnet.
// DROPOFF BIN is used to get the rack high enough to avoid hitting the dropoff bin.
#define TARGET_RESET 0
#define TARGET_BELOW_CAMERA 1000
#define TARGET_PICKUP_OBJECT 1800
#define TARGET_DROPOFF_BIN 600

int main(void)
{   
    float received_x = 0;  // variable used to get the value from python
    float received_y = 0;
    
    // Used to get the counter position of the dc motor.
    // c2 and c1 are digital INPUT signals.
    // Set to 32 bits and 4x resolution for maximum accuracy since the motor won't be running at max speed.
    quaddec_motor_Start();  
    
    // Initialization for all the relevant peripherals blocks
    pwm_servos_Start();  
    pwm_motor_Start();
    lcd_display_Start();
    uart_1_Start();
    
    for(;;)
    {
//        test_uart_polling_both_coordinates(&received_x, &received_y)
//        test_uart_polling_receive(&receive);
//        CyDelay(3000);  // give time to plug in the external PSU
//        test_manipulator_workspace();
//        test_motor_counter();
        uart_polling_receive_both_coordinates(&received_x, &received_y);
        uart_print_coordinates(&received_x, &received_y);

        servos_position_reset(150);
        rack_pinion_lower(1000, TARGET_DROPOFF_BIN);
        servos_position_set_xy(received_x, received_y, 300, 300);
        rack_pinion_lower(1000, TARGET_BELOW_CAMERA);
        rack_pinion_lower(1500, TARGET_PICKUP_OBJECT);
        rack_pinion_raise(1000, TARGET_BELOW_CAMERA);
        servos_position_before_dropoff(500);
        rack_pinion_raise(500, TARGET_DROPOFF_BIN);
        servos_position_reset(1000);
        rack_pinion_raise(10, TARGET_RESET);
        
//        electromagnet_on();
//        CyDelay(2000);
//        electromagnet_off();
//        CyDelay(10000);
    }
}


/***** PROJECT NOTES *****/
// Problem: Couldn't figure why I couldn't print out the floating point coordinates on my LCD screen.
// Solution: Turns out I made a simple mistake by having the x and y coordinates being received as uint8 in the PSoC code.
//           Naturally this truncates the floating point into an integer so I couldn't extract out the digits to print
//           them to the LCD screen during testing.
//
// Problem: Tuning of the servos was off after they started moving from the coordinates received from the UART.
// Solution: Weirdly enough the accuracy of the servo movement changed when none of the files or link length constants were changed.
//           The only changes were receiving the coordinates through UART instead of hard coding the values for testing.
//           Originally the tunings were off from the actual physical measurements by about 0.5cm for each link length a2 and a4 during the module testing.
//           I changed the values of the link lengths back closer to their physical measurements and the accuracy increased again.
//
// Problem: Top of the rack and pinion hitting the bottom of the camera when putting everything together.
//
// Problem: Servos having to clear from the bin and lowering the rack and pinion before it possibly hits the camera.