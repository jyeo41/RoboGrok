#include "test.h"

// Test function to manually test each possible coordinate in quadrant 1 for the manipulator
//  to see if the coordinate is a valid coordinate in the manipulator's workspace
void test_manipulator_workspace()
{
    int x, y;
    
    servos_position_reset();
    
    for (x = 14; x < 15; x++)   // x and y coordinates are the size of the board in centimeters
    {
        for (y = 0; y < 15; y++)
        {
            servos_position_set_xy(x, y, 1000, 1000);
            rack_pinion_lower(1000);
            rack_pinion_raise(1000);
            
            lcd_display_ClearDisplay(); // print out the coordinate to the LCD display
            lcd_display_Position(0, 0);
            lcd_display_PrintNumber(x);
            lcd_display_Position(0, 3);
            lcd_display_PrintNumber(y);
            CyDelay(1500);  // delay to give time to note down the coordinate
        }
    }
}