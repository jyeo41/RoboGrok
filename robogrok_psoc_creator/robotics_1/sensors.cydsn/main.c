
#include "project.h"

int main(void)
{
    int counter1 = 0;
    int counter2 = 0;
    int counter_difference = 0;
    float counts_per_rev = 815.5;
    float speed = 0;
    
//    int pot = 0;
    quaddec_1_Start();
    lcd_char_1_Start();
    ADC_SAR_Seq_1_Start();  // start the ADC block
    ADC_SAR_Seq_1_StartConvert();   // start the conversion process

    for(;;)
    {
        motor_Write(0); // since the plugged in M1 wire is connected to VDD, writing a 0 turns on the motor since we need both VDD and GND
        CyDelay(1000);    // 1 second wait for motor to get up to speed
        
        
        // In top design, we set input range to Vssa to Vdda (single ended) so we can convert analog to digital values using a graph-like relationship
        // We know our voltage is going to range from 0 volts to Vdd from the PSOC so we select this option. From GND to VDD voltage.
        // Resolution is set to 12 bits
//        ADC_SAR_Seq_1_IsEndConversion(ADC_SAR_Seq_1_WAIT_FOR_RESULT);   // Tell the ADC not to give us a result until the conversion is complete
//        pot = ADC_SAR_Seq_1_GetResult16(0); // save the digital value into "potential" variable
        counter1 = quaddec_1_GetCounter();   // counter from encoder
        CyDelay(1000);  // wait 1 second
        
        counter2 = quaddec_1_GetCounter();   // counter from encoder
        
        motor_Write(1); // turn motor off before calculating the counter difference
        counter_difference = counter2 - counter1;   // units of counts per sec
        
        speed = (counter_difference * 60.0) / counts_per_rev;   // calculation to get rpm revolutions per minute, the 60.0 is 60 sec per minute
        
        lcd_char_1_ClearDisplay();
        lcd_char_1_Position(0, 0);
        lcd_char_1_PrintNumber(speed);    // print the value of the potentiometer onto the LCd screen
        CyDelay(1000);
        
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
