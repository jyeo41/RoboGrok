
#include "project.h"

int main(void)
{
    int counter = 0;
    int time;
    int target_count1 = 1000;   // target positions for rack and pinion
    int target_count2 = 2000;
    int error = 0;  // used to calculate the error difference from current count to target count
    int speed = 0;  // the proportional speed used for linear control
    float kp = 0.14; // the control gain constant, higher values means more instability, speed, and accuracy
    uint8 receive;  // 8 bit byte to receive over uart transmission
//    uint8 transmit;
//    uint8 j;
    uint8 byte1;
    uint8 byte2;
    
    quaddec_1_Start();
    lcd_char_1_Start();
    pwm_1_Start();
    
    // we set UART pins Rx_1 to 12[6] and Tx_1 to 12[7] because those 2 pins are internally connected to the USB connection of our PSoC.
    // this allows serial communication to the PC over the USB
    UART_1_Start();

    for(;;)
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
        
//        while(1)
//        {
//
//            lcd_char_1_ClearDisplay();
//            lcd_char_1_Position(0, 5);
//            lcd_char_1_PrintNumber(receive);
//            
//            transmit = 1;
//            j = 1;
//            while (transmit <= 10)
//            {
//                UART_1_PutChar(j);    // command to send value over UART
//                CyDelay(200);
//                transmit += 1;
//                j += 10;
//            }
//        }
        time = 0;
        
        // continue doing this control algorithm as long as it hasn't reached 2 seconds
        while(time < 2000)
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
            lcd_char_1_ClearDisplay();
            lcd_char_1_Position(0, 0);
            lcd_char_1_PrintNumber(counter);
            
            // algorithm to split the 16 bit assumed integer of counter to 2, 8 bit bytes so we can transfer it correctly over UART
            // the algorithm keeps both byte1 and byte2 <= 255 which is what we want since that is the limit for 1 byte
            byte1 = counter / 256;
            byte2 = counter -(byte1 * 256);
            UART_1_PutChar(byte1);    // we want to send the encoder count position of the rack and pinion over the UART
            CyDelay(10);    // wait 10 milliseconds
            UART_1_PutChar(byte2);
            
            time += 10;
        }
        
        time = 0;
        
        // continue doing this control algorithm as long as it hasn't reached 2 seconds
        while(time < 2000)
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
            lcd_char_1_ClearDisplay();
            lcd_char_1_Position(0, 0);
            lcd_char_1_PrintNumber(counter);
            
            byte1 = counter / 256;
            byte2 = counter -(byte1 * 256);
            UART_1_PutChar(byte1);    // we want to send the encoder count position of the rack and pinion over the UART
            CyDelay(10);
            UART_1_PutChar(byte2);
            
            time += 10;
        }
    }
}
