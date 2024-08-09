
#include "project.h"

int main(void)
{
    int counter1 = 0;
    int counter2 = 0;
    int counter_difference = 0;
    int time;
    float counts_per_rev = 815.5;
//    float speed = 0;
    
//    int compare = 0;
    
    quaddec_1_Start();
    lcd_char_1_Start();
    pwm_1_Start();

    for(;;)
    {
        quaddec_1_SetCounter(0);
        counter1 = quaddec_1_GetCounter();  // first count before the motor is on
        
        // the motor will turn in one direction because im setting one lead high, and the other lead low.
        // only providing power to one lead and pulling the other to ground.
        pwm_1_WriteCompare1(83);    // calculated compare value
        pwm_1_WriteCompare2(0);
        
        counter2 = quaddec_1_GetCounter();  // Second count after the motor has been turned on
        counter_difference = counter2 - counter1;
        time = 0;
        
        // continue doing this control algorithm as long as our count difference is less than a quarter of a turn.
        // this value is 204 counts. When we tested our motor we got 815.5 counts per revolution, divide that by 4.
        // Give 5 seconds for the motor to reach the desired position
        while(time < 5000)
        {
            counter2 = quaddec_1_GetCounter();  // Second count after the motor has been turned on
            counter_difference = counter2 - counter1;
            
            // if we are less than the target position, turn the motor forwards
            if (counter_difference < (counts_per_rev / 4))
            {
                pwm_1_WriteCompare1(83);    // calculated compare value
                pwm_1_WriteCompare2(0);
            }
            else if (counter_difference > (counts_per_rev / 4)) // if we are more than the target position, turn the motor backwards
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
            time += 1;
        }
        
        CyDelay(43);    // wait delay should be the calculated 43ms
        
        pwm_1_WriteCompare1(0);
        pwm_1_WriteCompare2(0);
        
        CyDelay(5000);

    }
}
