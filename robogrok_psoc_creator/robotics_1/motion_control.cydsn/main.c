
#include "project.h"

int main(void)
{
    int counter = 0;
    int time;
    int target_count1 = 1000;   // target positions for rack and pinion
    int target_count2 = 2000;
    int error = 0;  // used to calculate the error difference from current count to target count
    int speed = 0;  // the proportional speed used for linear control
    float kp = 3.0; // the control gain constant, higher values means more instability, speed, and accuracy
    uint8 receive;  // 8 bit byte to receive over uart transmission
    
        
    quaddec_1_Start();
    lcd_char_1_Start();
    pwm_1_Start();
    
    // we set UART pins Rx_1 to 12[6] and Tx_1 to 12[7] because those 2 pins are internally connected to the USB connection of our PSoC.
    // this allows serial communication to the PC over the USB
    UART_1_Start();

    for(;;)
    {
        while(1)
        {
            // wait for a value to come over UART
            // print the value to the LCD screen
            receive = UART_1_GetChar();
            
            // anytime we ask the PSoC to receive a value over UART and no value has been received, the PSoC treats it as "0"
            // keep polling until we receive a value
            while (receive == 0)
            {
                receive = UART_1_GetChar();
            }
            lcd_char_1_ClearDisplay();
            lcd_char_1_Position(0, 5);
            lcd_char_1_PrintNumber(receive);
            time += 10;
        }
        time = 0;
        
        // continue doing this control algorithm as long as it hasn't reached 5 seconds
        while(time < 5000)
        {
            counter = quaddec_1_GetCounter();  // Second count after the motor has been turned on
            error = target_count1 - counter;    // the error is the difference of where we want to be, and where we actually are

            
            // if we are less than the target position, turn the motor forwards
            if (error > 0)
            {
                speed = kp * error;
                if (speed > 100)
                {
                    speed = 100;
                }
                pwm_1_WriteCompare1(speed);    // higher compare value means faster rack and pinion speed but more instability
                pwm_1_WriteCompare2(0);
            }
            else    // case if error is <= 0, case where error == 0 we need to turn off the motor anyways
            {
                speed = -kp * error;    // speed value is what we're writing to compare
                if (speed > 100)
                {
                    speed = 100;
                }
                pwm_1_WriteCompare1(0);
                pwm_1_WriteCompare2(speed);
            }
            CyDelay(10); // wait a millisecond and increment the time value
            lcd_char_1_ClearDisplay();
            lcd_char_1_Position(0, 0);
            lcd_char_1_PrintNumber(counter);
            time += 10;
        }
        
        time = 0;
        
        // continue doing this control algorithm as long as it hasn't reached 5 seconds
        while(time < 5000)
        {
            counter = quaddec_1_GetCounter();  // Second count after the motor has been turned on
            error = target_count2 - counter;    // the error is the difference of where we want to be, and where we actually are

            
            // if we are less than the target position, turn the motor forwards
            if (error > 0)
            {
                speed = kp * error;
                if (speed > 100)
                {
                    speed = 100;
                }
                pwm_1_WriteCompare1(speed);    // higher compare value means faster rack and pinion speed but more instability
                pwm_1_WriteCompare2(0);
            }
            else    // case if error is <= 0, case where error == 0 we need to turn off the motor anyways
            {
                speed = -kp * error;    // speed value is what we're writing to compare
                if (speed > 100)
                {
                    speed = 100;
                }
                pwm_1_WriteCompare1(0);
                pwm_1_WriteCompare2(speed);
            }
            CyDelay(10); // wait 10 milliseconds and increment time variable accordingly, this is to make the jittering more apparent
            lcd_char_1_ClearDisplay();
            lcd_char_1_Position(0, 0);
            lcd_char_1_PrintNumber(counter);
            time += 10;
        }
    }
}
