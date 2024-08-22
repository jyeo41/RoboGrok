#include "test.h"

// Test function to check accuracy of servos angles at 45 degree increments
void test_servo_angles()
{
    float i;
    while(1)
    {
        servos_position_reset(4000);
        rack_pinion_lower(1000, TARGET_BELOW_CAMERA);
        for (i = 0.0; i <= 180; i += 45.0)
        {
            servo_1_position_degrees(i, 3000);
        }
        
        for (i = -90.0; i <= 90; i += 45.0)
        {
            servo_2_position_degrees(i, 3000);
        }
        servos_position_reset(1000);
        rack_pinion_raise(3000, TARGET_RESET);
    }
}

// Test function to manually test each possible coordinate in quadrant 1 for the manipulator
//  to see if the coordinate is a valid coordinate in the manipulator's workspace
void test_manipulator_workspace()
{
    while(1)
    {
        int x, y;
        
        servos_position_reset(4000);
        for (x = 14; x < 15; x++)   // x and y coordinates are the size of the board in centimeters
        {
            for (y = 0; y < 15; y++)
            {
                servos_position_set_xy(x, y, 1000, 1000);
                rack_pinion_lower(1000, 1600);
                rack_pinion_raise(1000, 1000);
                
                lcd_display_ClearDisplay(); // print out the coordinate to the LCD display
                lcd_display_Position(0, 0);
                lcd_display_PrintNumber(x);
                lcd_display_Position(0, 3);
                lcd_display_PrintNumber(y);
                CyDelay(1500);  // delay to give time to note down the coordinate
            }
        }
        servos_position_reset(1000);
        rack_pinion_raise(3000, TARGET_RESET);
    }
}

// The coordinate range is constrained to the relevant FOV of the camera
void test_xy_coordinates_accuracy()
{
    while (1)
    {
        int x, y;
        servos_position_reset(4000);
        rack_pinion_lower(1000, TARGET_BELOW_CAMERA);
        for (x = 0; x <= 8; x++)
        {
            for (y = 7; y <= 13; y++)
            {
                if ((x == 0 && y == 7) || 
                    (x == 1 && y == 7) || 
                    (x == 2 && y == 7) || 
                    (x == 5 && y == 13) || 
                    (x == 6 && y == 13) || 
                    (x == 7 && y == 13) ||
                    (x == 8 && y == 13)) {
                    continue;
                }
                servos_position_set_xy(x, y, 500, 2500);
            }
        }
        servos_position_reset(1000);
        rack_pinion_raise(500, TARGET_RESET);
    }
}

// Test function to see the counter of encoder at different positions of the rack and pinion
void test_motor_counter()
{
    while(1)
    {
        int counter = 0;
        counter = quaddec_motor_GetCounter();
        lcd_display_ClearDisplay();
        lcd_display_Position(0, 0);
        lcd_display_PrintNumber(counter);
    }
}

// Test function to make sure the PSoC is correctly receiving the value from Pyserial and show it on the lcd display.
// Using super loop to isolate the testing to purely the UART function
void test_uart_polling_receive(float* receive)
{
    while(1)
    {
        uart_polling_receive(receive);
        lcd_display_ClearDisplay();
        lcd_display_Position(0, 0);
        lcd_display_PrintNumber(*receive);
    }
}

// Test function to see if the PSoC is able to receive both X and Y coordinates over UART
// Super loop so other parts of main.c code doesn't run to test in isolation
void test_uart_polling_both_coordinates(float* x, float* y)
{
    while(1)
    {
        uart_polling_receive_both_coordinates(x, y);
        lcd_display_ClearDisplay();
        lcd_display_Position(0, 0);
        lcd_display_PrintNumber(*x);
        lcd_display_Position(0, 3);
        lcd_display_PrintNumber(*y);
    }
}