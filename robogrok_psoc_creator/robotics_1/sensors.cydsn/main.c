
#include "project.h"

int main(void)
{
    int counter1 = 0;
    int counter2 = 0;
    int counter_difference = 0;
    float counts_per_rev = 815.5;
    float speed = 0;
    
    int compare = 0;
    
//    int pot = 0;
    quaddec_1_Start();
    lcd_char_1_Start();
    ADC_SAR_Seq_1_Start();  // start the ADC block
    ADC_SAR_Seq_1_StartConvert();   // start the conversion process
    PWM_1_Start();

    for(;;)
    {
        // the motor will turn in one direction because im setting one lead high, and the other lead low.
        // only providing power to one lead and pulling the other to ground.
        PWM_1_WriteCompare1(100);
        PWM_1_WriteCompare2(0);
        
        CyDelay(2000);
        
        PWM_1_WriteCompare1(0);
        PWM_1_WriteCompare2(100);
        
        CyDelay(2000);
        
        
        
        
        
//        compare = 0 ;   // this is what will control the speed of the motor
//        
//        while (compare <= 100)
//        {
//            // because the motor is going to run in the same direction for a good amount of time in this test, we will reach the maximum value of our ability
//            // to count the number of pulses from the encoder. At the beginning of the loop, we need to reset the encoder counter to 0.
//            quaddec_1_SetCounter(0);
//            
//            PWM_1_WriteCompare(compare);    // set motor speed
//            CyDelay(1000);  // let the motor reach its max speed
//            
//            counter1 = quaddec_1_GetCounter();   // counter from encoder
//            CyDelay(1000);  // wait 1 second
//            counter2 = quaddec_1_GetCounter();   // counter from encoder
//            PWM_1_WriteCompare(100); // turn motor off before calculating the counter difference
//            counter_difference = counter2 - counter1;   // units of counts per sec
//            
//            speed = (counter_difference * 60.0) / counts_per_rev;   // calculation to get rpm revolutions per minute, the 60.0 is 60 sec per minute
//            lcd_char_1_ClearDisplay();
//            lcd_char_1_Position(0, 0);
//            lcd_char_1_PrintNumber(compare);    // print the value of the potentiometer onto the LCd screen
//            lcd_char_1_Position(0, 5);
//            lcd_char_1_PrintNumber(speed);    // print the value of the potentiometer onto the LCd screen
//            CyDelay(2000);
//            compare = compare + 10;
//        }
            // In top design, we set input range to Vssa to Vdda (single ended) so we can convert analog to digital values using a graph-like relationship
            // We know our voltage is going to range from 0 volts to Vdd from the PSOC so we select this option. From GND to VDD voltage.
            // Resolution is set to 12 bits
//        ADC_SAR_Seq_1_IsEndConversion(ADC_SAR_Seq_1_WAIT_FOR_RESULT);   // Tell the ADC not to give us a result until the conversion is complete
//        pot = ADC_SAR_Seq_1_GetResult16(0); // save the digital value into "potential" variable        


        
//        // In top design, we set the drive mode for switch_1 to be pull down resistor because we want the default state to be low
//        // when the switch is not pressed. Otherwise, when button is released the circuit breaks without the pull down resistor.
//        // Switch is connected to VDD so it will read 1 when pressed. 
//        if(switch_1_Read() == 1)
//        {
//            lcd_char_1_ClearDisplay();
//            lcd_char_1_Position(0, 0);
//            lcd_char_1_PrintString("On");
//            CyDelay(50);
//        }
//        else
//        {
//            lcd_char_1_ClearDisplay();
//            lcd_char_1_Position(0, 0);
//            lcd_char_1_PrintString("Off");
//            CyDelay(50);
//        }
    }
}
