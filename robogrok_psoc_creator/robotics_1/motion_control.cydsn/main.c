
#include "project.h"

int main(void)
{
//    int counter1 = 0;
//    int counter2 = 0;
//    int counter_difference = 0;
//    float counts_per_rev = 815.5;
//    float speed = 0;
    
//    int compare = 0;
    
    quaddec_1_Start();
    lcd_char_1_Start();
    pwm_1_Start();

    for(;;)
    {
        // the motor will turn in one direction because im setting one lead high, and the other lead low.
        // only providing power to one lead and pulling the other to ground.
        pwm_1_WriteCompare1(83);    // calculated compare value
        pwm_1_WriteCompare2(0);
        
        CyDelay(43);    // wait delay should be the calculated 43ms
        
        pwm_1_WriteCompare1(0);
        pwm_1_WriteCompare2(0);
        
        CyDelay(5000);

    }
}
