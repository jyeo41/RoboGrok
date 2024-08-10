
#include "project.h"

int main(void)
{
    int counter = 0;
    int time;
    int target_count1 = 1000;   // target positions for rack and pinion
    int target_count2 = 2000;
        
    quaddec_1_Start();
    lcd_char_1_Start();
    pwm_1_Start();

    for(;;)
    {
        time = 0;
        
        // continue doing this control algorithm as long as it hasn't reached 5 seconds
        while(time < 5000)
        {
            counter = quaddec_1_GetCounter();  // Second count after the motor has been turned on
            
            // if we are less than the target position, turn the motor forwards
            if (counter < target_count1)
            {
                pwm_1_WriteCompare1(83);    // higher compare value means faster rack and pinion speed but more instability
                pwm_1_WriteCompare2(0);
            }
            else if (counter > target_count1) // if we are more than the target position, turn the motor backwards
            {
                pwm_1_WriteCompare1(0);    // calculated compare value
                pwm_1_WriteCompare2(83);                
            }
            else    // if we are at the desired position, then turn the motor off
            {
                pwm_1_WriteCompare1(0);
                pwm_1_WriteCompare2(0);                
            }
            CyDelay(1); // wait a millisecond and increment time variable
            lcd_char_1_ClearDisplay();
            lcd_char_1_Position(0, 0);
            lcd_char_1_PrintNumber(counter);
            time += 1;
        }
        
        time = 0;
        
        // continue doing this control algorithm as long as it hasn't reached 5 seconds
        while(time < 5000)
        {
            counter = quaddec_1_GetCounter();  // Second count after the motor has been turned on
            
            // if we are less than the target position, turn the motor forwards
            if (counter < target_count2)
            {
                pwm_1_WriteCompare1(83);
                pwm_1_WriteCompare2(0);
            }
            else if (counter > target_count2) // if we are more than the target position, turn the motor backwards
            {
                pwm_1_WriteCompare1(0); 
                pwm_1_WriteCompare2(83);                
            }
            else    // if we are at the desired position, then turn the motor off
            {
                pwm_1_WriteCompare1(0);
                pwm_1_WriteCompare2(0);                
            }
            CyDelay(1); // wait a millisecond and increment time variable
            lcd_char_1_ClearDisplay();
            lcd_char_1_Position(0, 0);
            lcd_char_1_PrintNumber(counter);
            time += 1;
        }
    }
}
